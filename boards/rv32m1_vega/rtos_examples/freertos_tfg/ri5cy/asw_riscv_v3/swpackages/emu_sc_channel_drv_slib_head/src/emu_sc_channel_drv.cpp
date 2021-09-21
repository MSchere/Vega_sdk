/*
 * sc_channel_drv.c
 *
 *  Created on: Dec 20, 2016
 *      Author: user
 */

#include <public/sc_channel_drv_iface_v1.h>
#include <public/emu_sc_channel_drv_slib_v1.h>
#include <stdio.h>

#include "fsl_lpuart_freertos.h"
#include "fsl_debug_console.h"
#include "fsl_lpuart.h"

#include "board.h"
#include "fsl_lpuart.h"

#include "pin_mux.h"
#include "clock_config.h"

#define LPUART_CLK_FREQ CLOCK_GetFreq(kCLOCK_ScgFircAsyncDiv2Clk)
#define LPUART_CLKSRC kCLOCK_ScgFircAsyncDiv2Clk

CDTCDescriptor currentTC;

lpuart_transfer_t recvXfer;

lpuart_handle_t handle0;
lpuart_handle_t handle1;

char RxTC[256];
uint16_t idx = 0;
bool rx_ok = false;
uint8_t CurrentRxByte = 0;

char *currentTCBrief = NULL;

union TM_UINT16Serial_t{
    uint16_t data;
    uint8_t  bytes[2];
};

TM_UINT16Serial_t TCLength;

void GetNextTC(CDTCDescriptor *tc) {

	*tc = currentTC;

}

void SetNextTC(CDTCDescriptor *tc) {

	currentTC = *tc;

}

void Serializer_SetUInt16(uint16_t data , byte_t * aux){
	TM_UINT16Serial_t serializer;
    serializer.data=data;
    if(aux){
        *aux=serializer.bytes[1];
        *(aux+1)=serializer.bytes[0];
    }
  }

uint8_t SyncPattern[4] = {0xBE, 0xBA, 0xBE, 0xEF};

void EDROOMHandler(void) {
	if (idx < 4) {
		if (SyncPattern[idx] != CurrentRxByte) {
			idx = 0;
		} else{
			idx++;
		}
	} else if (4 == idx) {
		TCLength.bytes[1] = CurrentRxByte;
		idx = 5;

	} else if (5 == idx) {
		TCLength.bytes[0] = CurrentRxByte;
		idx = 6;
	} else {
		uint16_t tc_index = idx - 6;
		RxTC[tc_index] = CurrentRxByte;
		idx++;
		if (TCLength.data == (tc_index + 1)) { // TC complete
			idx = 0;
			rx_ok = true;
		}
	}
}

extern "C" void LPUART0_MyDriverIRQHandler(void)
{
	 if (LPUART_STAT_OR_MASK & LPUART0->STAT) {
			/* Clear overrun flag, otherwise the RX does not work. */
		 LPUART0->STAT = ((LPUART0->STAT & 0x3FE00000U) | LPUART_STAT_OR_MASK);
	 }

	 CurrentRxByte = LPUART_ReadByte(LPUART0);
	 //LPUART_WriteByte(LPUART1, CurrentRxByte); //ECHO
	 EDROOMHandler();

}

void Init_sc_channel() {
		lpuart_config_t config;

		//NVIC_SetPriority(LPUART0_IRQn, 5);
		CLOCK_SetIpSrc(kCLOCK_Lpuart1, kCLOCK_IpSrcFircAsync);

		LPUART_GetDefaultConfig(&config);
		config.enableTx = true;
		config.enableRx = true;

		LPUART_Init(LPUART0, &config, LPUART_CLK_FREQ);
	    LPUART_Init(LPUART1, &config, LPUART_CLK_FREQ);

	    //Disable TX in UART0
	    LPUART_DisableInterrupts(LPUART0,kLPUART_TxDataRegEmptyInterruptEnable);
		LPUART_EnableInterrupts(LPUART0,kLPUART_RxDataRegFullInterruptEnable);
	    //Disable TX in UART1
	    LPUART_DisableInterrupts(LPUART1,kLPUART_TxDataRegEmptyInterruptEnable | kLPUART_RxDataRegFullInterruptEnable);
	    EnableIRQ(LPUART0_IRQn);
}

void SendTM(CDTM *tm) {

	int i = 0;
	int j = 0;

	byte_t header[4] = { 0xBE, 0xBA, 0xBE, 0xEF };

	uint16_t length = tm->packHeader.length + 1 + 6;
	byte_t pSyncLength[2];
	Serializer_SetUInt16(length,pSyncLength);

	uint16_t packId = tm->packHeader.packID;
	byte_t pIdLength[2];
	Serializer_SetUInt16(packId,pIdLength);

	uint16_t seqCtrl = tm->packHeader.seqCtrl;
	byte_t pSeqCtrlLength[2];
	Serializer_SetUInt16(seqCtrl,pSeqCtrlLength);

	uint16_t packLength = tm->packHeader.length;
	byte_t pLength[2];
	Serializer_SetUInt16(packLength,pLength);


	uint8_t data[255] = {header[0], header[1], header[2], header[3],
			pSyncLength[0], pSyncLength[1],
			pIdLength[0], pIdLength[1],
			pSeqCtrlLength[0], pSeqCtrlLength[1],
			pLength[0], pLength[1],
			tm->dataFieldHeader.flat_pusVersion_Ack,
			tm->dataFieldHeader.service,
			tm->dataFieldHeader.subservice,
			tm->dataFieldHeader.dummy};


	for (i = 4; i < (packLength + 1); i++) {
				data[16+j] = tm->appData[i - 4];
				j++;
		}

	LPUART_WriteBlocking(LPUART0, data, 15+packLength-2);
	if(rx_ok){
	 LPUART_WriteBlocking(LPUART1, (uint8_t *) RxTC, TCLength.data);
	 rx_ok=false;
	}

}

void SendTMList(CDTMList *tm) {
	for (uint8_t i = 0; i < tm->GetTMNumber(); i++) {
		SendTM(tm->GetTM(i));

	}

}

void EmuPassSecond() {

	//Emulate Hw TimeCode reception
	PUSService9::CurrentUniTimeY2KSecns = PUSService9::NextUniTimeY2KSecns;
	PUSService9::NextUniTimeY2KSecns++;
	SendProgrammedTCs();

}

void SendProgrammedTCs(){
  while(ProgramTC::GetTCProgramed(PUSService9::CurrentUniTimeY2KSecns ,currentTC,currentTCBrief)){

        //Signal BottomHalf for TimeCode Interrupt

        CCEPDManager::EDROOMEventIRQ45.SignalFromTask();
        Pr_DelayIn(Pr_Time(0,20000));

    }
}

ProgramTC *ProgramTC::firstProgram = NULL;

ProgramTC::ProgramTC(uint32_t uniTime2YK, uint8_t service, uint8_t subservice,
		char *brief) {

	UniTime2YK = uniTime2YK;
	TC.dataFieldHeader.service = service;
	TC.dataFieldHeader.subservice = subservice;
	mBrief = brief;
	pAppData = TC.appData;
}

bool ProgramTC::GetTCProgramed(uint32_t uniTime2YK, CDTCDescriptor &TC,
		char *&brief) {
	bool encontrado = false;
	if (firstProgram) {
		if (firstProgram->UniTime2YK <= uniTime2YK) {
			TC = firstProgram->TC;
			brief = firstProgram->mBrief;
			firstProgram = firstProgram->next;
			encontrado = true;
		}
	}
	return encontrado;
}

void ProgramTC::NewProgram(ProgramTC *pTC) {
	if (pTC) {

		if (NULL == ProgramTC::firstProgram) {
			ProgramTC::firstProgram = pTC;
			pTC->next = NULL;
		} else {
			bool encontrado = false;
			ProgramTC *current;
			ProgramTC *prev = NULL;
			current = ProgramTC::firstProgram;
			while (!encontrado) {
				if (current->UniTime2YK > pTC->UniTime2YK) {
					if (prev) {
						prev->next = pTC;
					} else {
						ProgramTC::firstProgram = pTC;
					}
					pTC->next = current;
					encontrado = true;
				} else {
					prev = current;
					current = current->next;
					if (NULL == current) {
						prev->next = pTC;
						pTC->next = NULL;
						encontrado = true;
					}
				}
			}
		}
	}
}


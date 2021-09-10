/*
 * sc_channel_drv.c
 *
 *  Created on: Dec 20, 2016
 *      Author: user
 */

#define BEBASYNC 6
#include <public/sc_channel_drv_iface_v1.h>
#include <public/emu_sc_channel_drv_slib_v1.h>
#include <stdio.h>

#include "fsl_lpuart_freertos.h"
#include "fsl_debug_console.h"
#include "fsl_lpuart.h"

CDTCDescriptor currentTC;

char *currentTCBrief = NULL;

void GetNextTC(CDTCDescriptor *tc) {

	*tc = currentTC;

}

void SetNextTC(CDTCDescriptor *tc) {

	currentTC = *tc;

}

#define LPUART LPUART0
#define LPUART_CLKSRC kCLOCK_ScgFircAsyncDiv2Clk
#define LPUART_CLK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpuart0)

uint8_t background_buffer[32];

lpuart_rtos_handle_t handle;
struct _lpuart_handle t_handle;

lpuart_rtos_config_t lpuart_config = { base : LPUART, srcclk
		: LPUART_CLK_FREQ, baudrate : 115200, parity
		: kLPUART_ParityDisabled, stopbits : kLPUART_OneStopBit, buffer
		: background_buffer, buffer_size : sizeof(background_buffer), };

void Init_sc_channel() {
	NVIC_SetPriority(LPUART0_IRQn, 5);
	lpuart_config.srcclk = LPUART_CLK_FREQ;
	lpuart_config.base = LPUART;

	if (0 > LPUART_RTOS_Init(&handle, &t_handle, &lpuart_config)) {
		PRINTF("\r\nCONFIGURATION ERROR\r\n");
		vTaskSuspend(NULL);
	}
}

void SendTM(CDTM *tm) {

	int i = 0;

	byte_t *pHeader = (byte_t*) &tm->packHeader;
	byte_t *pDataFieldHeader = (byte_t*) &tm->dataFieldHeader;

	byte_t Header[4] = { 0xBE, 0xBA, 0xBE, 0xEF };

	uint16_t length = tm->packHeader.length + 1 + 6;
	byte_t *pSyncLength = (byte_t*) &length;

//for(i=0; i < 6 ; i++){

#ifdef BEBASYNC
	for (i = 0; i < 4; i++) {
		LPUART_WriteByte(LPUART0, Header[i]);
	}

	for (i = 0; i < 2; i++) {
		LPUART_WriteByte(LPUART0, *(pSyncLength + i));
	}
#endif

	for (i = 0; i < 6; i++) {
		LPUART_WriteByte(LPUART0, *(pHeader + i));

	}

	for (i = 0; i < 4; i++) {
		LPUART_WriteByte(LPUART0, *pDataFieldHeader);
		pDataFieldHeader++;
	}

	for (i = 4; i < (tm->packHeader.length + 1); i++) {

		LPUART_WriteByte(LPUART0, tm->appData[i - 4]);

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

        CCEPDManager::EDROOMEventIRQ17.SignalFromTask();
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


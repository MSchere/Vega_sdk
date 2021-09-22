#ifndef FCDTCDescriptorH
#define FCDTCDescriptorH



#include <platform/basic_types.h>
#include <fsl_lpuart.h>

extern byte_t sc_channel_drv_get_char();
extern uint8_t SyncPattern[4];

union TM_UINT16Serial_t{
    uint16_t data;
    uint8_t  bytes[2];
};

enum TTCExecCtrl{ExecAsPrioTC, ExecAsChangeModeTC, ExecAsHK_FDIRTC
	, ExecAsSensorMngTC
	,ExecAsBKGTC, ExecAsResetTC};

struct __attribute__((__packed__)) TCPackHeader_t{

 word16_t packID;
 word16_t seqCtrl;
 uint16_t length;

};

struct __attribute__((__packed__)) TCDataFieldHeader_t{
	byte_t flat_pusVersion_Ack;
	uint8_t service;
	uint8_t subservice;
	uint8_t dummy;
};

class CDTCDescriptor{

	friend class PUSService1;
	friend class PUSService19;

	protected:
	
	TTCExecCtrl tcexecCtrl;

	public:
	
	uint8_t rxBytesCounter;

	bool rx_ok;

	TCPackHeader_t packHeader;

	TCDataFieldHeader_t dataFieldHeader;

	TM_UINT16Serial_t TCLength;

	uint8_t appData[256];



	bool_t IsPrioTC(){return ExecAsPrioTC==tcexecCtrl;}
	bool_t IsChangeModeTC(){return ExecAsChangeModeTC==tcexecCtrl;}
	bool_t IsHK_FDIRTC(){return ExecAsHK_FDIRTC==tcexecCtrl;}
	bool_t IsSensorMngTC(){return ExecAsSensorMngTC==tcexecCtrl;}
	bool_t IsBKGTC(){return ExecAsBKGTC==tcexecCtrl;}
	bool_t IsResetTC(){return ExecAsResetTC==tcexecCtrl;}
	bool_t IsRebootTC(){return ExecAsResetTC==tcexecCtrl;}

	CDTCDescriptor(){
		rxBytesCounter=0;
		rx_ok = false;
	}
	
	//returns true if the TC is commpleted after IRQ 
	bool HandleIRQ(){
		return (RxByte(sc_channel_drv_get_char()));
	}

	bool RxByte(byte_t CurrentRxByte){

		bool rx_ok=false;

		if (rxBytesCounter < 4) { //Header
			if (SyncPattern[rxBytesCounter] != CurrentRxByte) {
				rxBytesCounter = 0;
			} else{
				rxBytesCounter++;
			}
		} else if (rxBytesCounter < 12){
			LPUART_WriteByte(LPUART1, CurrentRxByte); //ECHO
			TM_UINT16Serial_t * aux;
			switch (rxBytesCounter){
				case(4): //TM length byte 0
					TCLength.bytes[1] = CurrentRxByte;
				break;
				case(5): //TM length byte 1
					TCLength.bytes[0] = CurrentRxByte;
				break;
				case(6): //Package ID byte 0
					aux=(TM_UINT16Serial_t*)&packHeader.packID;
					aux->bytes[1]=CurrentRxByte;
				break;
				case(7): //Package ID byte 1
					aux=(TM_UINT16Serial_t*)&packHeader.packID;
					aux->bytes[0]=CurrentRxByte;
				break;
				case(8): //Sequence control byte 0
					aux=(TM_UINT16Serial_t*)&packHeader.seqCtrl;
					aux->bytes[1]=CurrentRxByte;
				break;
				case(9): //Sequence control byte 1
					aux=(TM_UINT16Serial_t*)&packHeader.seqCtrl;
					aux->bytes[0]=CurrentRxByte;
				break;
				case(10): //Package length byte 0
					aux=(TM_UINT16Serial_t*)&packHeader.length;
					aux->bytes[1]=CurrentRxByte;
				break;
				case(11): //Package length byte 1
					aux=(TM_UINT16Serial_t*)&packHeader.length;
					aux->bytes[0]=CurrentRxByte;
				break;
				default:
				;
			}
			rxBytesCounter++;
		} else if (rxBytesCounter < 16){
			LPUART_WriteByte(LPUART1, CurrentRxByte); //ECHO
			byte_t * aux=(byte_t*)&dataFieldHeader;
			*(aux + rxBytesCounter-6-BEBASYNC)=CurrentRxByte;
			rxBytesCounter++;
		} else{
			LPUART_WriteByte(LPUART1, CurrentRxByte); //ECHO
			appData[rxBytesCounter-10-BEBASYNC]=CurrentRxByte;
			rxBytesCounter++;
			if ((rxBytesCounter - 10 - BEBASYNC)== (packHeader.length - 4 + 1 )){
				rx_ok=true;
				rxBytesCounter=0;
				LPUART_WriteByte(LPUART1, 0xBE); //ECHO
				LPUART_WriteByte(LPUART1, 0xBA); //ECHO
				LPUART_WriteByte(LPUART1, dataFieldHeader.service); //ECHO
				LPUART_WriteByte(LPUART1, dataFieldHeader.subservice); //ECHO
			}
		}

		return rx_ok;

	}	
	private:
	
};

#endif

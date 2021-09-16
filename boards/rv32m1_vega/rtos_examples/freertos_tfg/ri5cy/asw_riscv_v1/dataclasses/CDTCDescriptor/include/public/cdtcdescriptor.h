#ifndef FCDTCDescriptorH
#define FCDTCDescriptorH



#include <platform/basic_types.h>


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

	TCPackHeader_t packHeader;

	TCDataFieldHeader_t dataFieldHeader;

	uint8_t appData[256];

	bool_t IsRebootTC(){return ExecAsResetTC==tcexecCtrl;}
	bool_t IsPrioTC(){return ExecAsPrioTC==tcexecCtrl;}
	bool_t IsChangeModeTC(){return ExecAsChangeModeTC==tcexecCtrl;}
	bool_t IsHK_FDIRTC(){return ExecAsHK_FDIRTC==tcexecCtrl;}
	bool_t IsSensorMngTC(){return ExecAsSensorMngTC==tcexecCtrl;}
	bool_t IsBKGTC(){return ExecAsBKGTC==tcexecCtrl;}
	bool_t IsResetTC(){return ExecAsResetTC==tcexecCtrl;}

    CDTCDescriptor(){

		rxBytesCounter=0;

	}

	private:
	
};

#endif

#ifndef FCDTMListH
#define FCDTMListH

#include <platform/basic_types.h>

#define TM_DATA_LENGTH 256
#define TM_LIST_LENGTH 4

struct __attribute__((__packed__)) TMPackHeader_t {

	word16_t packID;
	word16_t seqCtrl;
	uint16_t length;

};

struct __attribute__((__packed__)) TMDataFieldHeader_t {
	byte_t flat_pusVersion_Ack;
	uint8_t service;
	uint8_t subservice;
	byte_t dummy;
};

class CDTM {

public:

	TMPackHeader_t packHeader;

	TMDataFieldHeader_t dataFieldHeader;

	uint8_t appData[TM_DATA_LENGTH];

	CDTM() {
		packHeader.packID = 0x0B21;
		packHeader.seqCtrl = 0xC000;
		dataFieldHeader.flat_pusVersion_Ack = 0x10;
	}
};

class CDTMList {

	friend class PUSService1;

protected:

	uint8_t tm_number;

	CDTM tm[TM_LIST_LENGTH];

public:
	void Add(uint8_t serv, uint8_t subserv) {
		if (tm_number < TM_LIST_LENGTH) {
			tm[tm_number].dataFieldHeader.service = serv;
			tm[tm_number].dataFieldHeader.subservice = subserv;
			tm[tm_number].packHeader.length = 4 - 1;
			tm_number++;
		}
	}

	void Add(uint8_t serv,uint8_t subserv, uint8_t *dat){
		    if(tm_number<TM_LIST_LENGTH){
			tm[tm_number].dataFieldHeader.service=serv;
			tm[tm_number].dataFieldHeader.subservice=subserv;
			if(dat){
			   for (int i=0; i<TM_DATA_LENGTH; i++){
				tm[tm_number].appData[i]=*dat;
				dat++;
			   }
			}
			tm_number++;
		    }
		}

	void Add(uint8_t serv, uint8_t subserv, uint8_t *dat, uint8_t dataBytes) {
		if (tm_number < TM_LIST_LENGTH) {
			tm[tm_number].dataFieldHeader.service = serv;
			tm[tm_number].dataFieldHeader.subservice = subserv;
			tm[tm_number].packHeader.length = dataBytes + 4 - 1;
			if (dat) {
				for (int i = 0; i < dataBytes; i++) {
					tm[tm_number].appData[i] = *dat;
					dat++;
				}
			}
			tm_number++;
		}
	}

	CDTMList() {
		tm_number = 0;
	}

	uint8_t GetTMNumber() {
		return tm_number;
	}
	CDTM* GetTM(uint8_t i) {
		return &tm[i];
	}

	void Clear() {
		tm_number = 0;
	}

protected:
private:
};
#endif

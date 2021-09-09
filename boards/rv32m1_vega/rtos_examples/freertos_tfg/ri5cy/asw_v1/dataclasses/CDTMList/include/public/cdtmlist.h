#ifndef FCDTMListH
#define FCDTMListH

#include <platform/basic_types.h>

#define TM_DATA_LENGTH 256
#define TM_LIST_LENGTH 16


struct TMPackHeader_t{

 word16_t packID;
 word16_t seqCtrl;
 uint16_t length;

};

struct TMDataFieldHeader_t{
	byte_t flat_pusVersion_Ack;
	uint8_t service;
	uint8_t subservice;
};


class CDTM{

	public:

	TMPackHeader_t packHeader;

	TMDataFieldHeader_t dataFieldHeader;

	uint8_t appData[TM_DATA_LENGTH];


};

class CDTMList{

	friend class PUSService1;

	protected:

	uint8_t tm_number;

	CDTM tm[TM_LIST_LENGTH];

	public:
	
	void Add(uint8_t serv,uint8_t subserv){
	   if(tm_number<TM_LIST_LENGTH){
		tm[tm_number].dataFieldHeader.service=serv;
		tm[tm_number].dataFieldHeader.subservice=subserv;
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

	CDTMList(){
		tm_number=0;
	}

	
	uint8_t GetTMNumber(){return tm_number;}
	
	CDTM *GetTM(uint8_t i){return &tm[i];}

	
	void Clear(){tm_number=0;}

	protected:
	
	private:
	
};
#endif

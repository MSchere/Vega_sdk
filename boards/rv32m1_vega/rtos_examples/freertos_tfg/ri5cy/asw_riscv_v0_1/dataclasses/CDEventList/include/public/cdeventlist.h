#ifndef FCDEventListH
#define FCDEventListH

#include <platform/basic_types.h>

#define EVENT_LIST_MAX_NUM_OF_ELEMENTS 16

class CDEventList{
	
	public:
	
	uint16_t mRID[EVENT_LIST_MAX_NUM_OF_ELEMENTS];
	uint8_t  evCounter;

	void AddEvent(uint16_t eventRID){
		if(evCounter<EVENT_LIST_MAX_NUM_OF_ELEMENTS){
		  mRID[evCounter]=eventRID;
		  evCounter++;
		}
	}

	uint16_t  ExtractFirstEvent(){
	  uint16_t  RID=mRID[0];
	  for(int i=0; i < evCounter; i++)
	      mRID[i]=mRID[i+1];
	  evCounter--;
	  return RID;
	}

	void ClearEventList(){
	  evCounter=0;
	  for(int i=0; i < EVENT_LIST_MAX_NUM_OF_ELEMENTS; i++)
	    mRID[i]=0;
	}

	uint8_t GetNumberOfEvents(){
	    return evCounter;
	}

	uint16_t  GetEventRID(uint8_t index){
	  uint16_t  RID=0;
	  if(index<EVENT_LIST_MAX_NUM_OF_ELEMENTS)
	      RID=mRID[index];
	  return RID;
	}
	

	CDEventList(){
	  ClearEventList();
	}

	protected:
	
	private:
	
};
#endif

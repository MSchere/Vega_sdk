/*
 * icuasw_pus_private_services.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#include <public/icuasw_pus_services_iface_v1.h>


void  PUSService20::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                case(1):
					Exec20_1TC(TC, List);
                	break;
                case(3):
                	Exec20_3TC(TC, List);
                    break;
                  break;
                default:
                  List.Add(1,8);
  }

}

void PUSService20::Exec20_3TC( CDTCDescriptor &TC, CDTMList &List){

  byte_t *pAuxIn=TC.appData;
  uint16_t paramIndex=GetUInt16(pAuxIn);

  uint64_t paramVAlue=GetUInt64(pAuxIn);

  if(paramIndex < DATAPOOL_PARAMNumber){
      PUSServices::DATAPOOL_PARAMCurrentValue[paramIndex]=paramVAlue;
      List.Add(1,7);
  }else
    List.Add(1,8);

}
void PUSService20::Exec20_1TC( CDTCDescriptor &TC, CDTMList &List){

  byte_t *pAuxIn=TC.appData;
  uint16_t paramIndex=GetUInt16(pAuxIn);

  byte_t auxOut[256];
  byte_t *pAuxOut=auxOut;

  if(paramIndex < DATAPOOL_PARAMNumber){
      SetUInt16(paramIndex,pAuxOut);
      SetUInt64(PUSServices::DATAPOOL_PARAMCurrentValue[paramIndex],pAuxOut);
      List.Add(20,2,auxOut);
      List.Add(1,7);

  }else
    List.Add(1,8);

}


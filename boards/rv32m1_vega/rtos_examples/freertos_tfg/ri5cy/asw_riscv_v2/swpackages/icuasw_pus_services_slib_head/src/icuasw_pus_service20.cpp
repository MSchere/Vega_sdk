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
                  List.Add(1,8,(unsigned char *)&TC.packHeader,4);
  }

}

void PUSService20::Exec20_3TC( CDTCDescriptor &TC, CDTMList &List){

  byte_t *pAuxIn=TC.appData;

  uint16_t N=GetUInt16(pAuxIn);
  uint8_t error=0;
  error=(N>8);
  while(N&&(!error)){
	  uint16_t paramIndex=GetUInt16(pAuxIn);

	  uint64_t paramVAlue=GetUInt64(pAuxIn);

	  if(paramIndex < DATAPOOL_PARAMNumber){
		  PUSServices::DATAPOOL_PARAMCurrentValue[paramIndex]=paramVAlue;
	  }else
		 error=1;
	N--;
  }
  if(!error){
      List.Add(1,7,(unsigned char *)&TC.packHeader,4);
  }else
    List.Add(1,8,(unsigned char *)&TC.packHeader,4);

}
void PUSService20::Exec20_1TC( CDTCDescriptor &TC, CDTMList &List){

  byte_t *pAuxIn=TC.appData;
  byte_t auxOut[256];
  uint16_t N=GetUInt16(pAuxIn);
  uint16_t Naux=N;
  uint8_t error=0;
  byte_t *pAuxOut=auxOut;
  SetUInt16(N,pAuxOut);
  error=(N>8);
  while(Naux&&(!error)){
	  uint16_t paramIndex=GetUInt16(pAuxIn);
	  if(paramIndex < DATAPOOL_PARAMNumber){
		  SetUInt16(paramIndex,pAuxOut);
		  SetUInt64(PUSServices::DATAPOOL_PARAMCurrentValue[paramIndex],pAuxOut);
	  }
	  else {
		  error=1;
	  }
	  Naux--;
 }
 if(!error){
      List.Add(20,2,auxOut,2+10*N);
      List.Add(1,7,(unsigned char *)&TC.packHeader,4);
 }else
    List.Add(1,8,(unsigned char *)&TC.packHeader,4);

}


/*
 * icuasw_pus_private_services.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */


#include <public/icuasw_pus_services_iface_v1.h>


void  PUSService128::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                case(5):
                 Exec128_5TC(TC, List);
                 break;
                case(1):
                case(2):
                case(3):
                  List.Add(1,7,(unsigned char *)&TC.packHeader,4);
                  break;
                case(4):
                  Exec128_4TC(TC, List);
                  break;
                default:
                  List.Add(1,8,(unsigned char *)&TC.packHeader,4);
  }

}

void PUSService128::Exec128_4TC( CDTCDescriptor &TC, CDTMList &List){

  byte_t *pAuxIn=TC.appData;

  uint16_t N=GetUInt16(pAuxIn);
  uint8_t error=0;
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
void PUSService128::Exec128_5TC( CDTCDescriptor &TC, CDTMList &List){

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
      List.Add(128,6,auxOut,2+10*N);
      List.Add(1,7,(unsigned char *)&TC.packHeader,4);
 }else
    List.Add(1,8,(unsigned char *)&TC.packHeader,4);

}


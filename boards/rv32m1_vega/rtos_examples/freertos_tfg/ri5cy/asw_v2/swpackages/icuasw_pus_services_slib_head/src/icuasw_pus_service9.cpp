/*
 * icuasw_pus_service9.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#include <public/icuasw_pus_services_iface_v1.h>
#include <stdio.h>

uint32_t PUSService9::NextUniTimeY2KSecns=1;
uint32_t PUSService9::CurrentUniTimeY2KSecns=0;

void  PUSService9::ExecTC( CDTCDescriptor &TC, CDTMList &List){
   byte_t * pAux=(byte_t*)TC.appData;
   switch(TC.dataFieldHeader.subservice){
     case(129):
        NextUniTimeY2KSecns=GetUInt32(pAux);
        List.Add(1,7);
     break;
     default:
       List.Add(1,8);
  }

}

uint32_t PUSService9::GetCurrentUniTimeY2K(){

  return PUSService9::CurrentUniTimeY2KSecns;

}

uint32_t PUSService9::GetCurrentUniTimeNanoSecns(){

  return 0;
}

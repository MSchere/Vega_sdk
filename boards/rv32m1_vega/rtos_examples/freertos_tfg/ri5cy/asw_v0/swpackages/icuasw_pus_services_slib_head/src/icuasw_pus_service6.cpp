/*
 * icuasw_pus_service6.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#include <public/icuasw_pus_services_iface_v1.h>

void  PUSService6::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                case(2):
                List.Add(1,7);
                break;
                case(5):
                List.Add(6,6);
                List.Add(1,7);
                break;
                case(9):
                List.Add(6,10);
                List.Add(1,7);
                break;
                default:
                  List.Add(1,8);
  }
}

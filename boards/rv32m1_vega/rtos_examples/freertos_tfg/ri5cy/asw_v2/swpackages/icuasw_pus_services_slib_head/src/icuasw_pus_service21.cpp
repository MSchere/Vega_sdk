/*
 * icuasw_pus_service21.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#include <public/icuasw_pus_services_iface_v1.h>
#include <stdio.h>

void  PUSService21::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                case(1):
                case(2):
                case(128):
                List.Add(1,7);
                break;
                default:
                  List.Add(1,8);
  }

}


void  PUSService21::ProcessSensorTM( CDSensorTMBufferStatus &bufferStatus,
                                     CDTMList &List, CDEventList & eventList)
{

    //List.Add(21,3);

}

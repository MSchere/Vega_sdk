/*
 * icuasw_pus_Service17.cpp
 *
 *  Created on: Dec 22, 2016
 *      Author: user
 */



#include <public/icuasw_pus_services_iface_v1.h>

void  PUSService17::ExecTC( CDTCDescriptor &TC, CDTMList &List){

  switch(TC.dataFieldHeader.subservice){
                  case(1):
					List.Add(17,2);
                	List.Add(1,7);
                  break;
                  default:
                    List.Add(1,8);
    }

}

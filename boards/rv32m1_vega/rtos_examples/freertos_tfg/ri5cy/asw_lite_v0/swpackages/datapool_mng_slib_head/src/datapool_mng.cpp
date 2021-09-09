/*
 * sc_channel_drv.c
 *
 *  Created on: Dec 20, 2016
 *      Author: user
 */


#include <public/datapool_mng_iface_v1.h>
#include <public/icuasw_pus_services_iface_v1.h>

void ForceDataPOOLValue(uint8_t index, uint64_t value){

  if(index<DATAPOOL_PARAMNumber)
    PUSServices::DATAPOOL_PARAMCurrentValue[index]=value;


}



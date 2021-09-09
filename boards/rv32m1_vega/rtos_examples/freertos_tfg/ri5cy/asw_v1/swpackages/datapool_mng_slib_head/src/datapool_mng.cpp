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

/*
void ForceDataPOOLMonitoring( uint8_t index,
                              bool  enabled,
                              uint8_t interval,
                              CheckStatus_t  status,
                              uint16_t highLimitRID,
                              uint64_t highLimit,
                              uint16_t lowLimitRID,
                              uint64_t lowLimit){


  PUSService12::PARAMMonitoringConfig[index].enabled=enabled;
  PUSService12::PARAMMonitoringConfig[index].interval=interval;
  PUSService12::PARAMMonitoringConfig[index].intervalControl=0;

  PUSService12::PARAMLimitDefinition[index].status=status;
  PUSService12::PARAMLimitDefinition[index]. highLimitRID=highLimitRID;
  PUSService12::PARAMLimitDefinition[index].highLimit=highLimit;
  PUSService12::PARAMLimitDefinition[index].lowLimitRID=lowLimitRID;
  PUSService12::PARAMLimitDefinition[index].lowLimit=lowLimit;

  byte_t data[256];
  byte_t *aux=data;
  Serializer::SetUInt16(interval,aux);
  aux+=2;
  Serializer::SetUInt16(index,aux);
  aux+=2;
  Serializer::SetUInt64(lowLimit,aux);
  aux+=8;
  Serializer::SetUInt16(lowLimitRID,aux);
  aux+=2;
  Serializer::SetUInt64(highLimit,aux);
  aux+=8;
  Serializer::SetUInt16(highLimitRID,aux);

}
*/

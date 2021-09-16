#ifndef PUBLIC__DATAPOOL_MNG_IFACE_V1_H
#define PUBLIC__DATAPOOL_MNG_IFACE_V1_H

#include <public/config.h>
#include <platform/basic_types.h>
#include <public/icuasw_pus_services_iface_v1.h>

void ForceDataPOOLValue(uint8_t index, uint64_t value);

void ForceDataPOOLMonitoring( uint8_t index, bool  enabled,
                             uint8_t interval,
                             CheckStatus_t  status,
                              uint16_t highLimitRID,
                              uint64_t highLimit,
                              uint16_t lowLimitRID,
                              uint64_t lowLimit);

/*PROTECTED REGION END*/


#endif // PUBLIC__CONSOLE_DRV_IFACE_V1_H

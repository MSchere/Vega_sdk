#ifndef PUBLIC__SC_CHANNEL_DRV_IFACE_V1_H
#define PUBLIC__SC_CHANNEL_DRV_IFACE_V1_H



#include <public/config.h>
#include <platform/basic_types.h>
#include <public/icuasw_pus_services_iface_v1.h>

/**
 * \brief	Get Next Telecommand.*/

void Init_sc_channel();


/**
 * \brief	Get Next Telecommand.
 * @param tc PUS TC Decriptor.
 */
void GetNextTC(CDTCDescriptor *tc);

/**
 * \brief	telemetry transmission
 * @param tm telemetry pointer
 */
void SendTM(CDTM * tm);

/**
 * \brief telemetry list transmission
 * @param tm list telemetry pointer
 */
void SendTMList(CDTMList * tm);
/*PROTECTED REGION END*/



#endif // PUBLIC__CONSOLE_DRV_IFACE_V1_H

/*
 * emu_sc_channel_drv_slib_v1.h
 *
 *  Created on: Dec 20, 2016
 *      Author: user
 */

#ifndef EMU_SC_CHANNEL_DRV_SLIB_V1_H_
#define EMU_SC_CHANNEL_DRV_SLIB_V1_H_

#ifdef __cplusplus
#include <public/ccepdmanager_iface_v1.h>
#include <public/ccsensormanager_iface_v1.h>

extern "C"
{
#endif


void SetNextTC(uint8_t service, uint8_t subservice, uint8_t *rawTC);


#ifdef __cplusplus
}
#endif

#endif /* EMU_SC_CHANNEL_DRV_SLIB_V1_H_ */

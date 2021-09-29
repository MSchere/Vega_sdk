#ifndef __PUBLIC__CONFIG_H__
#define __PUBLIC__CONFIG_H__

#define CONFIG_EDROOMBP_DEPLOYMENT_NEED_TASK
#define CONFIG_EDROOMDEPLOYMENT_NEED_TASK
#define CONFIG_SWI_XPRINTF_IFACE_V1_OUTPUT_CHANNEL_EDROOMBP_SLIB_HEAD_OUTPUT_CHANNEL_ID 1
#define CONFIG_SWP_XPRINTF_SLIB_HEAD_CHANNEL_OUTPUT_NULL  0
#define CONFIG_SWP_XPRINTF_SLIB_HEAD_CHANNEL_OUTPUT_STDOUT 1
#define CONFIG_SWP_XPRINTF_SLIB_HEAD_CHANNEL_1_OUTPUT     1
#define CONFIG_SWP_XPRINTF_SLIB_HEAD_CHANNEL_0_OUTPUT     0
#define CONFIG_SWI_XPRINTF_IFACE_V1_NB_MAX_CHANNELS     2

//RV32M1 port-specific config

#define CPU_RV32M1_ri5cy
#define BEBASYNC 6
#define USE_EDROOMBP_LPUART0_IRQ_HANDLER


#endif // __PUBLIC__CONFIG_H__
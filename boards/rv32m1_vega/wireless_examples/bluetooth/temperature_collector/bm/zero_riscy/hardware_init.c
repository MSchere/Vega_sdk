/*
 * Copyright 2018 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*${header:start}*/
#include "pin_mux.h"
#include "board.h"
#include "mcmgr.h"
#include "fsl_debug_console.h"
#include "clock_config.h"
#include "Flash_Adapter.h"
/*${header:end}*/

/* RV32M1_VEGA Rev A2 xtal trim */
static const uint8_t mXtalTrimDefault = 0x29;

#if (defined(gUseHciTransportUpward_d) && (gUseHciTransportUpward_d > 0U))
uint32_t startupData;
#endif

/*${function:start}*/
void BOARD_InitHardware(void)
{
#if (defined(gUseHciTransportUpward_d) && (gUseHciTransportUpward_d > 0U))
    mcmgr_status_t status;
#endif

#if (defined(gUseHciTransportUpward_d) && (gUseHciTransportUpward_d > 0U))
    /* Initialize MCMGR - low level multicore management library.
       Call this function as close to the reset entry as possible,
       (into the startup sequence) to allow CoreUp event triggering. */
    MCMGR_EarlyInit();

    /* Initialize MCMGR, install generic event handlers */
    MCMGR_Init();

    /* Get the startup data */
    do
    {
        status = MCMGR_GetStartupData(&startupData);
    } while (status != kStatus_MCMGR_Success);
#else
    CLOCK_EnableClock(kCLOCK_Rgpio1);

    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm0, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm1, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm2, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm3, kCLOCK_IpSrcFircAsync);

    BOARD_InitLPUART();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
#endif
    BOARD_InitPins_zero_riscy();

    /* Set correct XCVR Xtal trim value */
    NV_ReadHWParameters(&gHardwareParameters);
    if (0xFFFFFFFF == gHardwareParameters.xtalTrim)
    {
        gHardwareParameters.xtalTrim = mXtalTrimDefault;
    }
}

void hardware_init(void)
{
    //BOARD_InitHardware();
}

uint8_t BOARD_GetBatteryLevel(void)
{
    return 100;
}

uint32_t BOARD_GetTpmClock(uint32_t instance)
{
    uint32_t clock = 0;

    switch (instance)
    {
    case 0:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm0) / 4;
        break;
    case 1:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm1) / 4;
        break;
    case 2:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm2) / 4;
        break;
    case 3:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm3) / 4;
        break;
    default:
        break;
    }

    return clock;
}
/*${function:end}*/

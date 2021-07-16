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
/*${header:end}*/

/*${function:start}*/
void BOARD_InitHardware(void)
{
    /* Boot Secondary core application */
    //PRINTF("Starting Secondary core.\r\n");
    //Board_StartSecondaryCoreApp();
    //PRINTF("The secondary core application has been started.\r\n");
}

void hardware_init(void)
{
    CLOCK_EnableClock(kCLOCK_Rgpio1);

    CLOCK_SetIpSrc(kCLOCK_Lpuart1, kCLOCK_IpSrcFircAsync);

    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm0, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm1, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm2, kCLOCK_IpSrcFircAsync);
    /* Select the clock source for the TPM counter as MCGPLLCLK */
    CLOCK_SetIpSrc(kCLOCK_Tpm3, kCLOCK_IpSrcFircAsync);

    /* Initialize MCMGR - low level multicore management library.
       Call this function as close to the reset entry as possible,
       (into the startup sequence) to allow CoreUp event triggering. */
    MCMGR_EarlyInit();
    /* Stops the core 1 only if it was already started*/
    MCMGR_StopCore(kMCMGR_Core1);
    MCMGR_RegisterEvent(kMCMGR_RemoteCoreUpEvent, Board_RemoteCoreUpEventHandler, NULL);
    MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, Board_RemoteApplicationEventHandler, NULL);
    /* Initialize MCMGR, install generic event handlers */
    MCMGR_Init();

    BOARD_InitPins_ri5cy();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
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
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm0);
        break;
    case 1:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm1);
        break;
    case 2:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm2);
        break;
    case 3:
        clock = CLOCK_GetIpFreq(kCLOCK_Tpm3);
        break;
    default:
        break;
    }

    return clock;
}
/*${function:end}*/

/*! *********************************************************************************
* Copyright 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
*
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#include <stdint.h>
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "mcmgr.h"
#include "Flash_Adapter.h"
#include "fsl_os_abstraction.h"
#if (defined(CPU_RV32M1_cm0plus) || defined(CPU_RV32M1_cm0plus))
#include "fsl_intmux.h"
#endif

/******************************************************************************
*******************************************************************************
* Private type definitions
*******************************************************************************
******************************************************************************/
typedef enum mCore1Status_tag {
  mCore1Status_InReset_c,
  mCore1Status_Uninitialized_c,
  mCore1Status_Initialized_c
} mCore1Status_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* RV32M1_VEGA Rev A2 xtal trim */
static const uint8_t mXtalTrimDefault = 0x29;

#if (defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_ri5cy))
extern char rpmsg_lite_base[];
volatile mCore1Status_t mCore1Status = mCore1Status_InReset_c;
#if 0
#if LPADC_USE_MUTEX
/* Name: mADCMutexId
* Description: mutex to be used in application where more than 1 software module uses ADC (temperature sensor for instance)
*/
static osaMutexId_t mADCMutexId;
#endif //LPADC_USE_MUTEX
#if gDCDC_Enabled_d == 1

const dcdcConfig_t mDcdcDefaultConfig =
{
  .vbatMin = 2100,
  .vbatMax = 4250,
  .vBatMonitorIntervalMs = APP_DCDC_VBAT_MONITOR_INTERVAL,
  .pfDCDCAppCallback = NULL, /* .pfDCDCAppCallback = DCDCCallback, */
  .dcdc1P2OutputTargetVal = gDCDC_1P2_OutputTargetVal_1_225_c,
  .dcdc1P2_HS_OutputTargetVal = gDCDC_1P2_HS_OutputTargetVal_1_400_c,
  .dcdc1P8OutputTargetVal = gDCDC_1P8_OutputTargetVal_1_500_c
};

#endif //gDCDC_Enabled_d == 1
#elif (defined(CPU_RV32M1_cm0plus) || defined(CPU_RV32M1_cm0plus))
uint32_t startupData;
#endif
#endif
/************************************************************************************
*************************************************************************************
* Public functions prototypes
*************************************************************************************
************************************************************************************/
void BOARD_GetMCUUid(uint8_t* aOutUid16B, uint8_t* pOutLen);
void BOARD_GetMACAddr(uint8_t* aOutMacAddr5B);

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/
static void BOARD_Adc_EarlyInit(void);
/*******************************************************************************
 * Code
 ******************************************************************************/

/* Initialize debug console. */
void BOARD_InitDebugConsole(void)
{
    CLOCK_SetIpSrc(kCLOCK_Lpuart0, kCLOCK_IpSrcFircAsync);

    uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;

    DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, BOARD_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
}

/* get 4 words of information that uniquely identifies the MCU */
void BOARD_GetMCUUid(uint8_t* aOutUid16B, uint8_t* pOutLen)
{
    uint32_t uid[4] = {0};

    uid[0] = SIM->SDID;
    uid[1] = SIM->UIDH;
    uid[2] = SIM->UIDM;
    uid[3] = SIM->UIDL;

    FLib_MemCpy(aOutUid16B, (uint8_t*)uid, sizeof(uid));
    *pOutLen = sizeof(uid);

    return;
}

/* get the device MAC ADDRESS of 40 bits */
void BOARD_GetMACAddr(uint8_t* aOutMacAddr5B)
{
    aOutMacAddr5B[4] = (SIM->RFADDRH    )&0xFF;
    aOutMacAddr5B[3] = (SIM->RFADDRL>>24)&0xFF;
    aOutMacAddr5B[2] = (SIM->RFADDRL>>16)&0xFF;
    aOutMacAddr5B[1] = (SIM->RFADDRL>>8 )&0xFF;
    aOutMacAddr5B[0] = (SIM->RFADDRL    )&0xFF;
    return;
}

uint32_t BOARD_GetLpuartClock(uint32_t instance)
{
    uint32_t clock = 0;

    switch (instance)
    {
    case 0:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpuart0);
        break;
    case 1:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpuart1);
        break;
    case 2:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpuart2);
        break;
    default:
        break;
    }

    return clock;
}

uint32_t BOARD_GetSpiClock(uint32_t instance)
{
    uint32_t clock = 0;

    switch (instance)
    {
    case 0:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpspi0);
        break;
    case 1:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpspi1);
        break;
    case 2:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpspi2);
        break;
    case 3:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpspi3);
        break;
    default:
        break;
    }

    return clock;
}

uint32_t BOARD_GetI2cClock(uint32_t instance)
{
    uint32_t clock = 0;

    switch (instance)
    {
    case 0:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpi2c0);
        break;
    case 1:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpi2c1);
        break;
    case 2:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpi2c2);
        break;
    case 3:
        clock = CLOCK_GetIpFreq(kCLOCK_Lpi2c3);
        break;
    default:
        break;
    }

    return clock;
}

#if (defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_ri5cy))
void Board_RemoteCoreUpEventHandler(uint16_t remoteData, void *context)
{
    (void)context;
    if(mCore1Status != mCore1Status_InReset_c)
    {
        mCore1Status = mCore1Status_InReset_c;
        // This means that cm0+ has just reset
        // Place cm0+ initialization code here
    }
    mCore1Status = mCore1Status_Uninitialized_c;
}

void Board_RemoteApplicationEventHandler(uint16_t remoteData, void *context)
{
     mCore1Status = mCore1Status_Initialized_c;
}

void Board_StartSecondaryCoreApp()
{
    PRINTF("Starting Secondary core.\r\n");
    /* Boot Secondary core application */
#if 0
    MCMGR_StartCore(kMCMGR_Core1, (void *)0x01000000, 5, kMCMGR_Start_Synchronous);
#else
    MCMGR_StartCore(kMCMGR_Core1, (void *)CORE1_BOOT_ADDRESS, (uint32_t)rpmsg_lite_base, kMCMGR_Start_Synchronous);
#endif
    while(mCore1Status != mCore1Status_Initialized_c);
    PRINTF("The secondary core application has been started.\r\n");
}
#endif

#if (defined(CPU_RV32M1_zero_riscy) || defined(CPU_RV32M1_cm0plus))
void Board_NotifyRemotePrimaaryCore()
{
    /* Signal the other core we are ready */
    MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, 0);
}
#endif

void BOARD_InitAdc(void)
{
}

/* Initialize DCDC. */
void BOARD_DCDCInit(void)
{
}

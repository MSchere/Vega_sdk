/*! *********************************************************************************
* Copyright 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* 
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h"
#include "fsl_gpio.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief The board name */
#define MANUFACTURER_NAME         "NXP"
#define BOARD_NAME                "RV32M1-VEGA"

/* The UART to use for debug messages. */
#define BOARD_DEBUG_UART_TYPE DEBUG_CONSOLE_DEVICE_TYPE_LPUART
#define BOARD_DEBUG_UART_BAUDRATE 115200U
#define BOARD_DEBUG_UART_BASEADDR (uint32_t) LPUART0
#define BOARD_DEBUG_UART_INSTANCE    0U
#define BOARD_DEBUG_UART_CLK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpuart0)
#define BOARD_UART_IRQ LPUART0_IRQn
#define BOARD_UART_IRQ_HANDLER LPUART0_IRQHandler

#define BOARD_XTAL0_CLK_HZ        32000000U
#define BOARD_XTAL32_CLK_HZ       32768U

/* Connectivity */
#ifndef APP_SERIAL_INTERFACE_TYPE
#define APP_SERIAL_INTERFACE_TYPE (gSerialMgrLpuart_c)
#endif

#ifndef APP_SERIAL_INTERFACE_INSTANCE
#define APP_SERIAL_INTERFACE_INSTANCE (0)
#endif

#ifndef APP_SERIAL_INTERFACE_SPEED
#define APP_SERIAL_INTERFACE_SPEED (115200)
#endif

/* HCI */
#ifndef HCI_SERIAL_INTERFACE_TYPE
#define HCI_SERIAL_INTERFACE_TYPE (gSerialMgrLpuart_c)
#endif

#ifndef HCI_SERIAL_INTERFACE_INSTANCE
#define HCI_SERIAL_INTERFACE_INSTANCE (0)
#endif


/* 1<<x to enable PINx as wakup source in LLWU */
#define BOARD_LLWU_PIN_ENABLE_BITMAP ( 1<<23 | 1<<24  | 1<<26 )

/* The PWM channels used for RGB LED */
#ifndef BOARD_USE_PWM_FOR_RGB_LED
#define BOARD_USE_PWM_FOR_RGB_LED       1
#endif

#ifndef gStackTimerInstance_c
#define gStackTimerInstance_c           0
#endif
#ifndef gRedLedPwmTimerInstance_c
#define gRedLedPwmTimerInstance_c       2
#endif
#ifndef gGreenLedPwmTimerInstance_c
#define gGreenLedPwmTimerInstance_c     2
#endif
#ifndef gBlueLedPwmTimerInstance_c
#define gBlueLedPwmTimerInstance_c      2
#endif

#ifndef gRedLedPwmTimerChannel_c
#define gRedLedPwmTimerChannel_c        0
#endif
#ifndef gGreenLedPwmTimerChannel_c
#define gGreenLedPwmTimerChannel_c      1
#endif
#ifndef gBlueLedPwmTimerChannel_c
#define gBlueLedPwmTimerChannel_c       2
#endif
/* Index into the ledPins[] array */
#ifndef gRedLedIdx_c
#define gRedLedIdx_c                    1
#endif
#ifndef gGreenLedIdx_c
#define gGreenLedIdx_c                  2
#endif
#ifndef gBlueLedIdx_c
#define gBlueLedIdx_c                   3
#endif
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

void BOARD_InitDebugConsole(void);

/* Function called by the BLE connection manager to generate PER MCU keys */
extern void BOARD_GetMCUUid(uint8_t* aOutUid16B, uint8_t* pOutLen);

/* Function to get the MAC ADDRESS of the device */
extern void BOARD_GetMACAddr(uint8_t* aOutMacAddr5B);

extern uint16_t BOARD_GetPotentiometerLevel(void);

/* Functions used to determine the frequency of a module's input clock. */
uint32_t BOARD_GetLpuartClock(uint32_t instance);
uint32_t BOARD_GetTpmClock(uint32_t instance);
uint32_t BOARD_GetSpiClock(uint32_t instance);
uint32_t BOARD_GetI2cClock(uint32_t instance);

/* Function to initialize ADC for temp sensor measurement. */
void BOARD_InitAdc(void);

/* Function to read the temperature from the internal sensor. */
int32_t BOARD_GetTemperature(void);

/* Function to read battery level on board configuration. */
uint8_t BOARD_GetBatteryLevel(void);

/* Function to start secondary core application */
void Board_StartSecondaryCoreApp(void);

/* Function to initialize ADC for bandgap and vbatt measurement. */
void BOARD_DCDC_Adc_Init(void);

uint16_t BOARD_DCDC_AdcGetBatteryVoltageMv(void);

/* Function to initialize DCDC on board configuration. */
void BOARD_DCDCInit(void);

#if (defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_cm4) || defined(CPU_RV32M1_ri5cy))
void Board_RemoteCoreUpEventHandler(uint16_t remoteData, void *context);
void Board_RemoteApplicationEventHandler(uint16_t remoteData, void *context);
void Board_StartSecondaryCoreApp();
#endif

#if (defined(CPU_RV32M1_zero_riscy) || defined(CPU_RV32M1_cm0plus))
void Board_NotifyRemotePrimaaryCore();
#endif

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* _BOARD_H_ */

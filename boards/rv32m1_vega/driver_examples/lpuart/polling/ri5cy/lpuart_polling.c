/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_lpuart.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DEMO_LPUART_CLKSRC kCLOCK_ScgFircAsyncDiv2Clk
#define DEMO_LPUART_CLK_FREQ CLOCK_GetFreq(kCLOCK_ScgFircAsyncDiv2Clk)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t txbuff[] = "Lpuart polling example\r\nBoard will send back received characters\r\n";
uint8_t rxbuff[20] = {0};

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */


int main(void)
{
    uint8_t ch;

    lpuart_config_t config;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    CLOCK_SetIpSrc(kCLOCK_Lpuart1, kCLOCK_IpSrcFircAsync); //Necessary
    BOARD_InitDebugConsole();


    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kLPUART_ParityDisabled;
     * config.stopBitCount = kLPUART_OneStopBit;
     * config.txFifoWatermark = 0;
     * config.rxFifoWatermark = 0;
     * config.enableTx = false;
     * config.enableRx = false;
     */

    LPUART_GetDefaultConfig(&config);
    config.enableTx = true;
    config.enableRx = true;

    LPUART_Init(LPUART0, &config, DEMO_LPUART_CLK_FREQ);
    LPUART_WriteBlocking(LPUART0, txbuff, sizeof(txbuff) - 1);

    LPUART_Init(LPUART1, &config, DEMO_LPUART_CLK_FREQ);
    LPUART_WriteBlocking(LPUART1, txbuff, sizeof(txbuff) - 1);

    while (1)
    {
        LPUART_ReadBlocking(LPUART1, &ch, 1);

    	LPUART_WriteBlocking(LPUART0, &ch, 1);
    	LPUART_WriteBlocking(LPUART1, &ch, 1);
    }
}

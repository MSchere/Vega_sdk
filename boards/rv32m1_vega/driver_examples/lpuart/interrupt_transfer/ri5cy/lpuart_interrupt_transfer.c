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
#define ECHO_BUFFER_LENGTH 1

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* LPUART user callback */
void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/
lpuart_handle_t handle0;
lpuart_handle_t handle1;

uint8_t g_tipString[] =
    "Lpuart interrupt example\r\nBoard receives 8 characters then sends them out\r\nNow please input:\r\n";

uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};
uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};
char aux;
lpuart_transfer_t receiveXfer;


/*******************************************************************************
 * Code
 ******************************************************************************/
/* LPUART user callback */
void LPUART_UserCallback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
	aux=*receiveXfer.data;
	LPUART_WriteByte(base, aux); //Show input
}


/*!
 * @brief Main function
 */
int main(void)
{
    lpuart_config_t config;
    lpuart_transfer_t xfer;
    lpuart_transfer_t sendXfer;


    BOARD_InitPins();
    BOARD_BootClockRUN();
    CLOCK_SetIpSrc(kCLOCK_Lpuart1, kCLOCK_IpSrcFircAsync);
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
    LPUART_TransferCreateHandle(LPUART0, &handle0, LPUART_UserCallback, NULL);

    LPUART_Init(LPUART1, &config, DEMO_LPUART_CLK_FREQ);
    LPUART_TransferCreateHandle(LPUART1, &handle1, LPUART_UserCallback, NULL);

    EnableIRQ(LPUART1_IRQn);

    LPUART_EnableInterrupts(LPUART1,
    			kLPUART_TxDataRegEmptyInterruptEnable
    					| kLPUART_TransmissionCompleteInterruptEnable);
    LPUART_EnableInterrupts(LPUART1,
    						kLPUART_RxDataRegFullInterruptEnable
    							| kLPUART_RxOverrunInterruptEnable
    							| kLPUART_IdleLineInterruptEnable);


    /* Send g_tipString out. */
    xfer.data = g_tipString;
    xfer.dataSize = sizeof(g_tipString) - 1;
    //LPUART_TransferSendNonBlocking(LPUART0, &handle0, &xfer);
    LPUART_TransferSendNonBlocking(LPUART1, &handle1, &xfer);

    //LPUART_WriteByte(LPUART1, 'o');

    /* Start to echo. */
    sendXfer.data = g_txBuffer;
    sendXfer.dataSize = ECHO_BUFFER_LENGTH;
    receiveXfer.data = g_rxBuffer;
    receiveXfer.dataSize = ECHO_BUFFER_LENGTH;

    while (1)
    {
       //LPUART_TransferReceiveNonBlocking(LPUART0, &handle0, &receiveXfer, NULL);
       LPUART_TransferReceiveNonBlocking(LPUART1, &handle1, &receiveXfer, NULL);
    }
}

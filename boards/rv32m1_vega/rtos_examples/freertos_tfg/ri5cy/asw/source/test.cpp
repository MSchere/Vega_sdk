/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/* FreeRTOS kernel includes. */


#include <public/edroom_glue.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_LPUART LPUART0
#define DEMO_LPUART_CLKSRC kCLOCK_ScgFircAsyncDiv2Clk
#define DEMO_LPUART_CLK_FREQ CLOCK_GetIpFreq(kCLOCK_Lpuart0)
/* Task priorities. */
#define recv_task_PRIORITY (configMAX_PRIORITIES - 2)
#define send_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void recv_task(void *pvParameters);
static void send_task(void *pvParameters);
/*******************************************************************************
 * Code
 ******************************************************************************/
const char *recv_task_msg = "\r\nStream received, suspending...\r\n";
const char *send_task_msg = "\r\nIn sender task\r\n";
const char *send_ring_overrun = "\r\nRing buffer overrun!\r\n";
const char *send_hardware_overrun = "\r\nHardware buffer overrun!\r\n";

TaskHandle_t recv_task_handle = NULL;
TaskHandle_t send_task_handle = NULL;

uint8_t background_buffer[32];
uint8_t recv_buffer[1];

lpuart_rtos_handle_t handle;
struct _lpuart_handle t_handle;

lpuart_rtos_config_t lpuart_config = { base : DEMO_LPUART, srcclk
		: DEMO_LPUART_CLK_FREQ, baudrate : 115200, parity
		: kLPUART_ParityDisabled, stopbits : kLPUART_OneStopBit, buffer
		: background_buffer, buffer_size : sizeof(background_buffer), };

/*!
 * @brief Application entry point.
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	NVIC_SetPriority(LPUART0_IRQn, 5);
	if (xTaskCreate(recv_task, "Recv_task", configMINIMAL_STACK_SIZE + 10, NULL,
	recv_task_PRIORITY, &recv_task_handle) != pdPASS) {
		PRINTF("Recv_task creation failed!.\r\n");
		while (1)
			;
	}
	if (xTaskCreate(send_task, "Send_task", configMINIMAL_STACK_SIZE + 10, NULL,
	send_task_PRIORITY, &send_task_handle) != pdPASS) {
		PRINTF("Send_task creation failed!.\r\n");
		while (1)
			;
	}
	vTaskSuspend(send_task_handle);
	vTaskStartScheduler();
	for (;;)
		;
}

/*!
 * @brief Task responsible for loopback.
 */
static void recv_task(void *pvParameters) {
	int error;
	size_t n;

	lpuart_config.srcclk = DEMO_LPUART_CLK_FREQ;
	lpuart_config.base = DEMO_LPUART;

	if (0 > LPUART_RTOS_Init(&handle, &t_handle, &lpuart_config)) {
		PRINTF("\r\nCONFIGURATION ERROR\r\n");
		vTaskSuspend(NULL);
	}
	// Receive user input, interrupt happens on first char sent
	do {
		PRINTF("\r\nAwaiting new stream...\r\n");
		if (stream_ok()) {
			PRINTF("\r\nStream received, suspending receiver task...\r\n");
			vTaskResume(send_task_handle);
			vTaskSuspend(NULL);
		}
		error = LPUART_RTOS_Receive(&handle, recv_buffer, sizeof(recv_buffer),
				&n);

		if (error == kStatus_LPUART_RxHardwareOverrun) {
			/* Notify about hardware buffer overrun */
			if (kStatus_Success != LPUART_RTOS_Send(&handle,
							(uint8_t*) send_hardware_overrun,
							strlen(send_hardware_overrun))) {
				break;
			}
		}
		if (error == kStatus_LPUART_RxRingBufferOverrun) {
			/* Notify about ring buffer overrun */
			if (kStatus_Success != LPUART_RTOS_Send(&handle,
								(uint8_t*) send_ring_overrun,
								strlen(send_ring_overrun))) {
				break;
			}
		}

	} while (kStatus_Success == error);
	PRINTF("\r\nERROR\r\n");
	LPUART_RTOS_Deinit(&handle);
	vTaskSuspend(NULL);
}

static void send_task(void *pvParameters) {
	do {
		char *stream = "";
		PRINTF("\r\nSending stream...\r\n");
		stream = get_stream();
		// Send bit stream.
		if (0 > LPUART_RTOS_Send(&handle, (uint8_t*) stream, strlen(stream))) {
			break;
		}
		PRINTF("\r\nStream sent, resetting handler...\r\n");
		vTaskResume(recv_task_handle);
		reset_handler();
		vTaskSuspend(NULL);
	} while (true);
	PRINTF("\r\nERROR\r\n");
	LPUART_RTOS_Deinit(&handle);
	vTaskSuspend(NULL);
}

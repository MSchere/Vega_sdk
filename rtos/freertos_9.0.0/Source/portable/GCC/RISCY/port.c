/*
    FreeRTOS V8.2.2 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
//#include <pthread.h>


#define MSTATUS_MIE_MASK (0x01 << 3)
#define MSTATUS_MPIE_MASK (0x01 << 7)
#define MSTATUS_MPP_MASK (0x03 << 11)

volatile UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

volatile UBaseType_t uxInterruptNesting = 0;;

volatile UBaseType_t uxYieldRequired = pdFALSE;

static inline uint32_t portCPU_IRQ_DISABLE(void)
{
    uint32_t mstatus;

    __ASM volatile ("csrrci %0, mstatus, 8" : "=r"(mstatus));

    return mstatus;
}
static inline void portCPU_IRQ_ENABLE(uint32_t mstatus)
{
    __ASM volatile ("csrw mstatus, %0" : : "r"(mstatus));
}

/* Let the user override the pre-loading of the initial LR with the address of
prvTaskExitError() in case it messes up unwinding of the stack in the
debugger. */
#ifdef configTASK_RETURN_ADDRESS
    #define portTASK_RETURN_ADDRESS    configTASK_RETURN_ADDRESS
#else
    #define portTASK_RETURN_ADDRESS    prvTaskExitError
#endif

#define portBASE_INT_PRIO_REG (*(volatile uint32_t *)configBASE_INT_PRIO_REG)

extern void xPortStartFirstTask(void);

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RI5CY port.
 *----------------------------------------------------------*/

void portYIELD_FROM_ISR(BaseType_t x)
{
    if (pdFALSE != (x))
    {
        uxYieldRequired = pdTRUE;
    }
}

void portYIELD()
{
    if (uxCriticalNesting == 0)
    {
        __ASM volatile("ecall");
    }
    else
    {
        uxYieldRequired = pdTRUE;
    }
}

/*-----------------------------------------------------------*/

static void prvTaskExitError( void )
{
    /* A function that implements a task must not exit or attempt to return to
    its caller as there is nothing to return to.  If a task wants to exit it
    should instead call vTaskDelete( NULL ).

    Artificially force an assert() to be triggered if configASSERT() is
    defined, then stop here so application writers can catch the error. */
    configASSERT( uxCriticalNesting == ~0UL );
    portCPU_IRQ_DISABLE();
    for(;;);
}

/*
 * Setup mtimcmp and mtime regisiter to periodically generate tick interrupts.
 */

/*
 * See header file for description.
 */
extern uint32_t __global_pointer;
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
    /* End of stack marker. Useful for debugging - unncecessary for deployment */
    *pxTopOfStack = ( StackType_t ) 0xdeadbeef;
    pxTopOfStack--;

    /* mstatus. */
    *pxTopOfStack = ( StackType_t ) (MSTATUS_MPIE_MASK | MSTATUS_MPP_MASK);
    pxTopOfStack--;

    /* mepc */
    *pxTopOfStack = ( StackType_t ) pxCode;
    pxTopOfStack--;

    /* reg x17 -> x11, lpstart, lpend, lpcount */
    pxTopOfStack -= 13;

    /* Parameter: x10 (a0) */
    *pxTopOfStack = ( StackType_t ) pvParameters;
    pxTopOfStack--;

    /* reg x4 - x7 */
    pxTopOfStack -= 4;

    /* reg x3: gp */
    *pxTopOfStack = ( StackType_t ) (&__global_pointer);
    pxTopOfStack--;

    /* return address: x1*/
    *pxTopOfStack = ( StackType_t ) portTASK_RETURN_ADDRESS;
    pxTopOfStack--;

    /* reg x8 - x9, x18 - x31 */
    pxTopOfStack -= 15;

    return pxTopOfStack;
}
/*-----------------------------------------------------------*/

BaseType_t xPortStartScheduler( void )
{
    configSETUP_TICK_INTERRUPT();

    uxCriticalNesting = 0;

    xPortStartFirstTask();

    prvTaskExitError();

    return pdTRUE;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler( void )
{
    portCPU_IRQ_DISABLE();
    for (;;);
}
/*-----------------------------------------------------------*/

void vPortEnterCritical( void )
{
    /* Mask interrupts up to the max syscall interrupt priority. */
    portDISABLE_INTERRUPTS();

    /* Now interrupts are disabled ulCriticalNesting can be accessed
    directly.  Increment ulCriticalNesting to keep a count of how many times
    portENTER_CRITICAL() has been called. */
    uxCriticalNesting++;

    /* This is not the interrupt safe version of the enter critical function so
    assert() if it is being called from an interrupt context.  Only API
    functions that end in "FromISR" can be used in an interrupt.  Only assert if
    the critical nesting count is 1 to protect against recursive calls if the
    assert function also uses a critical section. */
    if( uxCriticalNesting == 1 )
    {
        configASSERT( uxInterruptNesting == 0 );
    }
}
/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
    configASSERT( uxCriticalNesting );
    uxCriticalNesting--;
    if( uxCriticalNesting == 0 )
    {
        portENABLE_INTERRUPTS();
        if (uxYieldRequired)
        {
            __ASM volatile("ecall");
        }
    }
}

uint32_t vPortSetInterruptMask(void)
{
    uint32_t ret;
    uint32_t mstatus;

    mstatus = portCPU_IRQ_DISABLE();

    ret = portBASE_INT_PRIO_REG;

    portBASE_INT_PRIO_REG = configMAX_SYSCALL_INTERRUPT_PRIORITY;

    portCPU_IRQ_ENABLE(mstatus);

    return ret;
}

void vPortClearInterruptMask(uint32_t newMask)
{
    uint32_t mstatus;

    mstatus = portCPU_IRQ_DISABLE();

    portBASE_INT_PRIO_REG = newMask;

    portCPU_IRQ_ENABLE(mstatus);
}

void FreeRTOS_Tick_Handler( void )
{
	/* The SysTick runs at the lowest interrupt priority, so when this interrupt
	executes all interrupts must be unmasked.  There is therefore no need to
	save and then restore the interrupt mask value as its value is already
	known. */
	portDISABLE_INTERRUPTS();

    configCLEAR_TICK_INTERRUPT();

    /* Increment the RTOS tick. */
    if( xTaskIncrementTick() != pdFALSE )
    {
        uxYieldRequired = pdTRUE;
    }

	portENABLE_INTERRUPTS();
}
/*-----------------------------------------------------------*/

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


#include "FreeRTOSConfig.h"

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the RI5CY port.
 *----------------------------------------------------------*/

    .data
tsp: .word 0 /* Task stack pointer. */

    .text
    .global Ecall_Handler
    .global FreeRTOS_IRQ_Handler
    .global xPortStartFirstTask

	.extern vTaskSwitchContext
	.extern vApplicationIRQHandler
	.extern uxInterruptNesting

/*
 * Save these registers.
 *
 *  CSR 0x300 // mstatus
 *  CSR 0x341 // mepc
 *  CSR 0x7B6 // lpcount[1]
 *  CSR 0x7B5 // lpend[1]
 *  CSR 0x7B4 // lpstart[1]
 *  CSR 0x7B2 // lpcount[0]
 *  CSR 0x7B1 // lpend[0]
 *  CSR 0x7B0 // lpstart[0]
 *  x10 - x17 // a0 - a7
 *   x5 - x7  // t0 - t2
 *   x4       // tp
 *   x3       // gp
 *   x1       // ra
 *
 *  x18 - x31
 *  x8 - x9
 *
 * RISCY does not have dedicate stack for exception, it reuse the task's stack.
 * This makes it difficult to ditermine the minimal task stack. In this FreeRTOS
 * porting, system stack is used for exception. When enters ISR, the stack pointer
 * changes to use the system stack.
 */

.macro portSAVE_MINIMAL_CONTEXT
    addi sp, sp, -0x58
    sw  x1, 0x00(x2)  // ra
    sw  x3, 0x04(x2)  // gp
    sw  x4, 0x08(x2)  // tp
    sw  x5, 0x0c(x2)  // t0
    sw  x6, 0x10(x2)  // t1
    sw  x7, 0x14(x2)  // t2
    sw x10, 0x18(x2)  // a0
    sw x11, 0x1c(x2)  // a1
    sw x12, 0x20(x2)  // a2
    sw x13, 0x24(x2)  // a3
    sw x14, 0x28(x2)  // a4
    sw x15, 0x2c(x2)  // a5
    sw x16, 0x30(x2)  // a6
    sw x17, 0x34(x2)  // a7

    csrr a0, 0x7B0
    csrr a1, 0x7B1
    csrr a2, 0x7B2
    sw a0, 0x38(x2)  // lpstart[0]
    sw a1, 0x3c(x2)  // lpend[0]
    sw a2, 0x40(x2)  // lpcount[0]
    csrr a0, 0x7B4
    csrr a1, 0x7B5
    csrr a2, 0x7B6
    sw a0, 0x44(x2)  // lpstart[1]
    sw a1, 0x48(x2)  // lpend[1]
    sw a2, 0x4c(x2)  // lpcount[1]

    csrr a0, 0x341
    sw a0, 0x50(x2)  // mepc
    csrr a0, 0x300
    sw a0, 0x54(x2)  // mstatus
    .endm

.macro portRESTORE_MINIMAL_CONTEXT
    lw a0, 0x54(x2)  // mstatus
    csrrw x0, 0x300, a0
    lw a0, 0x50(x2)  // mepc
    csrrw x0, 0x341, a0

    lw a0, 0x44(x2)  // lpstart[1]
    lw a1, 0x48(x2)  // lpend[1]
    lw a2, 0x4c(x2)  // lpcount[1]
    csrrw x0, 0x7B4, a0
    csrrw x0, 0x7B5, a1
    csrrw x0, 0x7B6, a2
    lw a0, 0x38(x2)  // lpstart[0]
    lw a1, 0x3c(x2)  // lpend[0]
    lw a2, 0x40(x2)  // lpcount[0]
    csrrw x0, 0x7B0, a0
    csrrw x0, 0x7B1, a1
    csrrw x0, 0x7B2, a2

    lw  x1, 0x00(x2)  // ra
    lw  x3, 0x04(x2)  // gp
    lw  x4, 0x08(x2)  // tp
    lw  x5, 0x0c(x2)  // t0
    lw  x6, 0x10(x2)  // t1
    lw  x7, 0x14(x2)  // t2
    lw x10, 0x18(x2)  // a0
    lw x11, 0x1c(x2)  // a1
    lw x12, 0x20(x2)  // a2
    lw x13, 0x24(x2)  // a3
    lw x14, 0x28(x2)  // a4
    lw x15, 0x2c(x2)  // a5
    lw x16, 0x30(x2)  // a6
    lw x17, 0x34(x2)  // a7
    addi sp, sp, 0x58
    .endm

.macro portSAVE_MINIMAL_CONTEXT_ECALL
    addi sp, sp, -0x58
    sw  x1, 0x00(x2)  // ra
    sw  x3, 0x04(x2)  // gp
    sw  x4, 0x08(x2)  // tp
    sw  x5, 0x0c(x2)  // t0
    sw  x6, 0x10(x2)  // t1
    sw  x7, 0x14(x2)  // t2
    sw x10, 0x18(x2)  // a0
    sw x11, 0x1c(x2)  // a1
    sw x12, 0x20(x2)  // a2
    sw x13, 0x24(x2)  // a3
    sw x14, 0x28(x2)  // a4
    sw x15, 0x2c(x2)  // a5
    sw x16, 0x30(x2)  // a6
    sw x17, 0x34(x2)  // a7

    csrr a0, 0x7B0
    csrr a1, 0x7B1
    csrr a2, 0x7B2
    sw a0, 0x38(x2)  // lpstart[0]
    sw a1, 0x3c(x2)  // lpend[0]
    sw a2, 0x40(x2)  // lpcount[0]
    csrr a0, 0x7B4
    csrr a1, 0x7B5
    csrr a2, 0x7B6
    sw a0, 0x44(x2)  // lpstart[1]
    sw a1, 0x48(x2)  // lpend[1]
    sw a2, 0x4c(x2)  // lpcount[1]

    csrr a0, 0x341
    /* Note, here mepc is set to pc + 4 */
    addi a0, a0, 4
    sw a0, 0x50(x2)  // mepc
    csrr a0, 0x300
    sw a0, 0x54(x2)  // mstatus
    .endm

    .macro portSAVE_EXTRA_CONTEXT
    lw t0, tsp
    addi t0,   t0, -0x40
    sw   x8,   0x00(t0)
    sw   x9,   0x04(t0)
    sw   x18,  0x08(t0)
    sw   x19,  0x0c(t0)
    sw   x20,  0x10(t0)
    sw   x21,  0x14(t0)
    sw   x22,  0x18(t0)
    sw   x23,  0x1c(t0)
    sw   x24,  0x20(t0)
    sw   x25,  0x24(t0)
    sw   x26,  0x28(t0)
    sw   x27,  0x2c(t0)
    sw   x28,  0x30(t0)
    sw   x29,  0x34(t0)
    sw   x30,  0x38(t0)
    sw   x31,  0x3c(t0)
    lw   t1,   pxCurrentTCB
    sw   t0,   (t1)
    .endm

    .macro portSAVE_CONTEXT
    portSAVE_MINIMAL_CONTEXT
    portSAVE_EXTRA_CONTEXT
    .endm

    .macro portRESTORE_EXTRA_CONTEXT
    lw   sp,   pxCurrentTCB
    lw   sp,   (sp)
    lw   x8,   0x00(sp)
    lw   x9,   0x04(sp)
    lw   x18,  0x08(sp)
    lw   x19,  0x0c(sp)
    lw   x20,  0x10(sp)
    lw   x21,  0x14(sp)
    lw   x22,  0x18(sp)
    lw   x23,  0x1c(sp)
    lw   x24,  0x20(sp)
    lw   x25,  0x24(sp)
    lw   x26,  0x28(sp)
    lw   x27,  0x2c(sp)
    lw   x28,  0x30(sp)
    lw   x29,  0x34(sp)
    lw   x30,  0x38(sp)
    lw   x31,  0x3c(sp)
    addi sp,   sp, 0x40
    .endm

/*
 * Opposite to portSAVE_CONTEXT().  Interrupts will have been disabled during
 * the context save so we can write to the stack pointer.
 */
    .macro portRESTORE_CONTEXT
    csrci mstatus, 8
    portRESTORE_EXTRA_CONTEXT
    portRESTORE_MINIMAL_CONTEXT
    .endm

    .type xPortStartFirstTask, %function
xPortStartFirstTask:
    portRESTORE_CONTEXT
    csrsi mstatus, 8
    mret

/*-----------------------------------------------------------*/

    .type Ecall_Handler, %function
Ecall_Handler:
    portSAVE_MINIMAL_CONTEXT_ECALL

    sw sp, tsp, a5
    la sp, __StackTop

    portSAVE_EXTRA_CONTEXT

    jal vTaskSwitchContext

    sw zero, uxYieldRequired, a5
    portRESTORE_CONTEXT
    mret

.type FreeRTOS_IRQ_Handler, %function
FreeRTOS_IRQ_Handler:
    portSAVE_MINIMAL_CONTEXT

    lw a4, uxInterruptNesting

    /* If enter ISR from task, then switch to use exception stack. */
    bnez a4, 1f
    sw sp, tsp, a5
    la sp, __StackTop

1:
    /* Increase nesting count. */
    addi a4, a4, 1
    sw a4, uxInterruptNesting, a5

    /* Call the interrupt handler. */
    csrr a0, mcause
    jal vApplicationIRQHandler

    /* Decrease nesting count. */
    lw a4, uxInterruptNesting
    addi a4, a4, -1
    sw a4, uxInterruptNesting, a5

    /* A context switch is never performed if the nesting count is not 0. */
    bnez a4, restore_minimal_context

    /* Did the interrupt request a context switch? */
    lw a4, uxYieldRequired
    beqz a4, exit_without_switch

switch_before_exit:
    /* A context swtich is to be performed.  Clear the context switch pending
    flag. */
    sw zero, uxYieldRequired, a5

    portSAVE_EXTRA_CONTEXT
    jal vTaskSwitchContext
    portRESTORE_EXTRA_CONTEXT /* sp is set to task stask pointer in this step. */
    j restore_minimal_context

exit_without_switch:
    lw sp, tsp

restore_minimal_context:
    /* Restore the context of, and branch to, the task selected to execute
    next. */
    portRESTORE_MINIMAL_CONTEXT
    mret

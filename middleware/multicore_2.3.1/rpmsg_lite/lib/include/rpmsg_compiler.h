/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * Copyright (c) 2016 Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**************************************************************************
 * FILE NAME
 *
 *       rpmsg_compiler.h
 *
 * DESCRIPTION
 *
 *       This file defines compiler-specific macros.
 *
 ***************************************************************************/
#ifndef _RPMSG_COMPILER_H_
#define _RPMSG_COMPILER_H_

/* IAR ARM build tools */
#if defined(__ICCARM__)

#include <intrinsics.h>

#define MEM_BARRIER() __DSB()

#ifndef RL_PACKED_BEGIN
#define RL_PACKED_BEGIN __packed
#endif

#ifndef RL_PACKED_END
#define RL_PACKED_END
#endif

/* GNUC */
#elif defined(__GNUC__)

#if defined(__riscv) && __riscv
#define MEM_BARRIER() asm volatile("nop" : : : "memory")
#else
#define MEM_BARRIER() asm volatile("dsb" : : : "memory")
#endif

#ifndef RL_PACKED_BEGIN
#define RL_PACKED_BEGIN
#endif

#ifndef RL_PACKED_END
#define RL_PACKED_END __attribute__((__packed__))
#endif

/* ARM GCC */
#elif defined(__CC_ARM)

#define MEM_BARRIER() __schedule_barrier()

#ifndef RL_PACKED_BEGIN
#define RL_PACKED_BEGIN _Pragma("pack(1U)")
#endif

#ifndef RL_PACKED_END
#define RL_PACKED_END _Pragma("pack()")
#endif

#else
/* There is no default definition here to avoid wrong structures packing in case of not supported compiler */
#error Please implement the structure packing macros for your compiler here!
#endif

#endif /* _RPMSG_COMPILER_H_ */

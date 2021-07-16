/*
 * Copyright (c) 2014, Mentor Graphics Corporation
 * Copyright (c) 2015 Xilinx, Inc.
 * Copyright (c) 2016 Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _RPMSG_DEFAULT_CONFIG_H
#define _RPMSG_DEFAULT_CONFIG_H

#define RL_USE_CUSTOM_CONFIG (1)

#if RL_USE_CUSTOM_CONFIG
#include "rpmsg_config.h"
#endif

/* default values */
/* START { */
#ifndef RL_MS_PER_INTERVAL
#define RL_MS_PER_INTERVAL (1)
#endif

#ifndef RL_BUFFER_PAYLOAD_SIZE
#define RL_BUFFER_PAYLOAD_SIZE (496)
#endif

#ifndef RL_BUFFER_COUNT
#define RL_BUFFER_COUNT (2)
#endif

#ifndef RL_API_HAS_ZEROCOPY
#define RL_API_HAS_ZEROCOPY (1)
#endif

#ifndef RL_USE_STATIC_API
#define RL_USE_STATIC_API (0)
#endif

#ifndef RL_CLEAR_USED_BUFFERS
#define RL_CLEAR_USED_BUFFERS (0)
#endif

#ifndef RL_USE_MCMGR_IPC_ISR_HANDLER
#define RL_USE_MCMGR_IPC_ISR_HANDLER (1)
#endif

#ifndef RL_ASSERT
#define RL_ASSERT(x)  \
    do                \
    {                 \
        if (!x)       \
            while (1) \
                ;     \
    } while (0);
#endif
/* } END */

#endif /* _RPMSG_DEFAULT_CONFIG_H */

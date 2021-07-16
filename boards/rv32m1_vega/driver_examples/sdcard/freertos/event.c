/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "event_groups.h"
#include "event.h"

/*******************************************************************************
 * Definitons
 ******************************************************************************/
/*! @brief Convert the milliseconds to ticks in FreeRTOS. */
#define MSEC_TO_TICK(msec) \
    (((uint32_t)(msec) + 500uL / (uint32_t)configTICK_RATE_HZ) * (uint32_t)configTICK_RATE_HZ / 1000uL)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Get event instance.
 * @param eventType The event type
 * @return The event instance's pointer.
 */
static volatile SemaphoreHandle_t *EVENT_GetInstance(event_t eventType);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Transfer complete event. */
static volatile SemaphoreHandle_t g_eventTransferComplete;
/*! @brief Card detect event. */
static volatile SemaphoreHandle_t g_eventCardDetect;

/*******************************************************************************
 * Code
 ******************************************************************************/
static volatile SemaphoreHandle_t *EVENT_GetInstance(event_t eventType)
{
    volatile SemaphoreHandle_t *event;

    switch (eventType)
    {
        case kEVENT_TransferComplete:
            event = &g_eventTransferComplete;
            break;
        case kEVENT_CardDetect:
            event = &g_eventCardDetect;
            break;
        default:
            event = NULL;
            break;
    }

    return event;
}

bool EVENT_Create(event_t eventType)
{
    volatile SemaphoreHandle_t *event = EVENT_GetInstance(eventType);

    if (event)
    {
        *event = xSemaphoreCreateBinary();
        if (*event == NULL)
        {
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool EVENT_Wait(event_t eventType, uint32_t timeoutMilliseconds)
{
    uint32_t timeoutTicks;
    volatile SemaphoreHandle_t *event = EVENT_GetInstance(eventType);

    if (timeoutMilliseconds && event)
    {
        if (timeoutMilliseconds == ~0U)
        {
            timeoutTicks = portMAX_DELAY;
        }
        else
        {
            timeoutTicks = MSEC_TO_TICK(timeoutMilliseconds);
        }
        if (xSemaphoreTake(*event, timeoutTicks) == pdFALSE)
        {
            return false; /* timeout */
        }
        else
        {
            return true; /* event taken */
        }
    }
    else
    {
        return false;
    }
}

bool EVENT_Notify(event_t eventType)
{
    volatile SemaphoreHandle_t *event = EVENT_GetInstance(eventType);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    BaseType_t xResult = pdFAIL;

    if (event)
    {
        xResult = xSemaphoreGiveFromISR(*event, &xHigherPriorityTaskWoken);
        if (xResult != pdFAIL)
        {
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

void EVENT_Delete(event_t eventType)
{
    volatile SemaphoreHandle_t *event = EVENT_GetInstance(eventType);

    if (event)
    {
        vSemaphoreDelete(*event);
    }
}

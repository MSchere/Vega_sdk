/*! *********************************************************************************
* \addtogroup BLE PROFILES
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright 2016-2017 NXP
* All rights reserved.
* 
* 
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/***********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */
#include "ble_general.h"
#include "gatt_db_app_interface.h"
#include "gatt_server_interface.h"
#include "gap_interface.h"
#include "current_time_interface.h"

/***********************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
********************************************************************************** */
/*! Current Time Service - Subscribed Client*/
deviceId_t mCts_SubscribedClientId;

/***********************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
********************************************************************************** */
static uint8_t getMonthDays (uint8_t month, uint8_t isLeapYear);

/***********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
bleResult_t Cts_Start (ctsConfig_t *pServiceConfig)
{
    /* Record initial time and info */
    Cts_RecordCurrentTime(pServiceConfig);
    Cts_RecordLocalTimeInfo(pServiceConfig);
    Cts_RecordReferenceTimeInfo(pServiceConfig);

    return gBleSuccess_c;
}

bleResult_t Cts_Stop (ctsConfig_t *pServiceConfig)
{
    mCts_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Cts_Subscribe(deviceId_t clientDeviceId)
{
    mCts_SubscribedClientId = clientDeviceId;
    return gBleSuccess_c;
}

bleResult_t Cts_Unsubscribe(void)
{
    mCts_SubscribedClientId = gInvalidDeviceId_c;
    return gBleSuccess_c;
}

bleResult_t Cts_RecordCurrentTime (ctsConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_CurrentTime_d);
    ctsMeasurement_t ctsMeasurement;

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
        gBleUuidType16_c, &uuid, &handle);

    if (result != gBleSuccess_c)
        return result;

    ctsMeasurement.exactTime.ctsDayDateTime = Cts_EpochToDayDateTime(pServiceConfig->localTime);
    ctsMeasurement.exactTime.fractions = 0U;
    ctsMeasurement.adjustReason = pServiceConfig->adjustReason;
    
    /* Update characteristic value and send notification */
    result = GattDb_WriteAttribute(handle, sizeof(ctsMeasurement_t), (uint8_t*)&ctsMeasurement);

    if (result != gBleSuccess_c)
        return result;

    if (ctsMeasurement.adjustReason != gCts_UnknownReason)
    {
        if(ctsMeasurement.adjustReason != gCts_ExternalRefUpdate)
        {
            Cts_SendNotifications(handle);
            pServiceConfig->referenceChanged = FALSE;
        } 
        else
        {
            if (((pServiceConfig->lastTime > pServiceConfig->localTime) && (pServiceConfig->lastTime - pServiceConfig->localTime > 60)) ||
                ((pServiceConfig->localTime > pServiceConfig->lastTime) && (pServiceConfig->localTime - pServiceConfig->lastTime > 60)))
            {
                Cts_SendNotifications(handle);
                pServiceConfig->referenceChanged = FALSE;
            }
            else
            {
                pServiceConfig->referenceChanged = TRUE;
            }
        }
    }
    
    pServiceConfig->lastTime = pServiceConfig->localTime;
    
    return gBleSuccess_c;
}

bleResult_t Cts_RecordLocalTimeInfo (ctsConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_LocalTimeInformation_d);

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
        gBleUuidType16_c, &uuid, &handle);

    if (result != gBleSuccess_c)
        return result;
    
    /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, sizeof(ctsLocalTimeInfo_t), (uint8_t*)&pServiceConfig->localTimeInfo);

    if (result != gBleSuccess_c)
        return result;

    return gBleSuccess_c;
}

bleResult_t Cts_RecordReferenceTimeInfo (ctsConfig_t *pServiceConfig)
{
    uint16_t  handle;
    bleResult_t result;
    bleUuid_t uuid = Uuid16(gBleSig_ReferenceTimeInformation_d);

    /* Get handle of  characteristic */
    result = GattDb_FindCharValueHandleInService(pServiceConfig->serviceHandle,
        gBleUuidType16_c, &uuid, &handle);

    if (result != gBleSuccess_c)
        return result;
    
    /* Update characteristic value */
    result = GattDb_WriteAttribute(handle, sizeof(ctsReferenceTimeInfo_t), (uint8_t*)&pServiceConfig->referenceTimeInfo);

    if (result != gBleSuccess_c)
        return result;

    return gBleSuccess_c;
}

void Cts_SendNotifications (uint16_t handle)
{
    uint16_t  handleCccd;
    bool_t isNotifActive;
   
    /* Get handle of CCCD */
    if (GattDb_FindCccdHandleForCharValueHandle(handle, &handleCccd) != gBleSuccess_c)
        return;

    if (gBleSuccess_c == Gap_CheckNotificationStatus
        (mCts_SubscribedClientId, handleCccd, &isNotifActive) &&
        TRUE == isNotifActive)
    {
        GattServer_SendNotification(mCts_SubscribedClientId, handle);
    }
}

void Cts_CurrentTimeWrittenHandler (ctsConfig_t *pServiceConfig, gattServerAttributeWrittenEvent_t *pEvent)
{
    uint8_t retStatus =  gAttErrCodeNoError_c;
    uint8_t reason;
    ctsExactTime256_t exactTime;

    exactTime = *(ctsExactTime256_t*)pEvent->aValue;
    reason = pEvent->aValue[sizeof(ctsExactTime256_t)];
    
    /* Test if reserved bits are trying to be written */
    if(reason & 0x80)
        /* return error status - couldn't find the codes table for this profile */
        retStatus = 0x80;
    else
        pServiceConfig->localTime = Cts_DayDateTimeToEpochTime(exactTime.ctsDayDateTime);
    
    GattServer_SendAttributeWrittenStatus(mCts_SubscribedClientId, pEvent->handle, retStatus);
}

ctsDayDateTime_t Cts_EpochToDayDateTime (uint32_t epochTime)
{
    ctsDayDateTime_t tempTime;
    uint16_t dayOfYear;
    uint16_t dayOfMonth;
    uint8_t month;
    uint32_t year;

    tempTime.dateTime.seconds = epochTime % 60U;
    epochTime /= 60;
    tempTime.dateTime.minutes = epochTime % 60U;
    epochTime /= 60;
    tempTime.dateTime.hours = epochTime % 24U;
    epochTime /= 24;
    year = (((epochTime * 4U) + 2U) / 1461U);
    tempTime.dateTime.year = (year + 1970U);
    dayOfYear = (epochTime - (((year * 1461U) + 1U) / 4U));
                       
    dayOfMonth = dayOfYear + 1;
    for(month = 1U; month<=12U; month++)
    {
        uint8_t monthDays = getMonthDays(month, !((year+2) % 4U));
        if(dayOfMonth > monthDays)
        {
            dayOfMonth -= monthDays;
        }
        else
            break;
    }
    
    tempTime.dateTime.month = month;
    tempTime.dateTime.day = dayOfMonth;
    tempTime.dayOfWeek = ((dayOfYear + 4U) % 7U);
    
    return tempTime;
}

uint32_t Cts_DayDateTimeToEpochTime (ctsDayDateTime_t dayDateTime)
{
    uint32_t epochTime;
    uint32_t year;

    year = (dayDateTime.dateTime.year  - 1970U);
    epochTime = ((year * 1461U) / 4U);
    
    for(uint8_t month = 1U; month<dayDateTime.dateTime.month; month++)
    {
        epochTime += getMonthDays(month, (!((year+2)%4)));
    }
    
    if(year % 4 > 2)
    {
        epochTime++;
    }
    
    epochTime += dayDateTime.dateTime.day - 1;
    
    epochTime *= 24;
    epochTime += dayDateTime.dateTime.hours;
    epochTime *= 60;
    epochTime += dayDateTime.dateTime.minutes;
    epochTime *= 60;
    epochTime += dayDateTime.dateTime.seconds;

    return epochTime;
}

/***********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************** */
static uint8_t getMonthDays (unitMonth_t month, uint8_t isLeapYear)
{
    uint8_t result = 0;
    switch(month)
    {
        case gUnit_January_c: result = 31; break;
        case gUnit_February_c:
        {
            if(isLeapYear)
                result = 29;
            else
                result = 28;
        }
        break;
        case gUnit_March_c: result = 31; break;
        case gUnit_April_c: result = 30; break;
        case gUnit_May_c: result = 31; break;
        case gUnit_June_c: result = 30; break;
        case gUnit_July_c: result = 31; break;
        case gUnit_August_c: result = 31; break;
        case gUnit_September_c: result = 30; break;
        case gUnit_October_c: result = 31; break;
        case gUnit_November_c: result = 30; break;
        case gUnit_December_c: result = 31; break;
        default: result = 0; break;
    }
		return result;
}

/*! *********************************************************************************
* @}
********************************************************************************** */

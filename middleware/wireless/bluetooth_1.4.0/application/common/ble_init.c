/*! *********************************************************************************
 * \addtogroup BLE
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* 
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "ble_init.h"
#include "ble_general.h"
#include "ble_host_task_config.h"
#include "ble_controller_task_config.h"
#include "hci_transport.h"
#include "board.h"

#if !gUseHciTransportDownward_d
#include "controller_interface.h"
#ifndef CPU_QN908X
#include "fsl_xcvr.h"
#endif /* CPU_QN908X */
#include "Flash_Adapter.h"
#endif /* gUseHciTransportDownward_d */

/************************************************************************************
*************************************************************************************
* Public constants & macros
*************************************************************************************
************************************************************************************/
#ifndef cMCU_SleepDuringBleEvents
    #define cMCU_SleepDuringBleEvents    0
#endif

#define BLE_INIT_DEBUG 0

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/


/************************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
************************************************************************************/
extern bool_t Ble_CheckMemoryStorage(void);

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/
#ifndef CPU_QN908X
extern bool_t gEnableSingleAdvertisement;
extern bool_t gMCUSleepDuringBleEvents;
#endif /* CPU_QN908X */

#if (gUseHciTransportDownward_d == 1)
#elif (gUseHciTransportUpward_d == 1)
#else

#if BLE_INIT_DEBUG
bleResult_t Ble_HciRecvLog
    (
        hciPacketType_t packetType,
        void* pHciPacket,
        uint16_t hciPacketLength
    )
{
#if BLE_INIT_DEBUG
    Serial_Print(0, "READ <- ", gAllowToBlock_d);
    Serial_PrintHex(0, (uint8_t*)&packetType, 1, gPrtHexSpaces_c | gPrtHexBigEndian_c);
    Serial_PrintHex(0, pHciPacket, hciPacketLength, gPrtHexSpaces_c | gPrtHexBigEndian_c);
    Serial_Print(0, "\r\n", gAllowToBlock_d);
#endif
    return Ble_HciRecv(packetType, pHciPacket, hciPacketLength);
}

bleResult_t Ble_HciSendLog
    (
        hciPacketType_t packetType,
        void* pHciPacket,
        uint16_t hciPacketLength
    )
{
#if BLE_INIT_DEBUG
    Serial_Print(0, "WRITE -> ", gAllowToBlock_d);
    Serial_PrintHex(0, (uint8_t*)&packetType, 1, gPrtHexSpaces_c | gPrtHexBigEndian_c);
    Serial_PrintHex(0, pHciPacket, hciPacketLength, gPrtHexSpaces_c | gPrtHexBigEndian_c);
    Serial_Print(0, "\r\n", gAllowToBlock_d);
#endif
    return Hci_SendPacketToController(packetType, pHciPacket, hciPacketLength);
}

#else
#define Ble_HciRecvLog Ble_HciRecv
#define Ble_HciSendLog Hci_SendPacketToController
#endif

#endif

bleResult_t Ble_Initialize
(
    gapGenericCallback_t gapGenericCallback
)
{

#if (gUseHciTransportDownward_d == 1)
    
    /* Configure HCI Transport */
    hcitConfigStruct_t hcitConfigStruct = 
    {
        .interfaceType = gHcitInterfaceType_d,
        .interfaceChannel = gHcitInterfaceNumber_d,
        .interfaceBaudrate = gHcitInterfaceSpeed_d,
        .transportInterface =  Ble_HciRecv
    };
      
    /* HCI Transport Init */
    if (gHciSuccess_c != Hcit_Init(&hcitConfigStruct))
    {
        return gHciTransportError_c;
    }
    
    /* Check for available memory storage */
    if (!Ble_CheckMemoryStorage())
    {
        return gBleOutOfMemory_c;
    }

    /* BLE Host Tasks Init */
    if (osaStatus_Success != Ble_HostTaskInit())
    {
        return gBleOsError_c;
    }
    
    /* BLE Host Stack Init */
    return Ble_HostInitialize(gapGenericCallback, Hcit_SendPacket);
    
#elif (gUseHciTransportUpward_d == 1)
    
#ifndef CPU_QN908X
    /* BLE Radio Init */
    XCVR_Init(BLE_MODE, DR_1MBPS);    
    XCVR_SetXtalTrim( (uint8_t)gHardwareParameters.xtalTrim );
#endif /* CPU_QN908X */

    if (osaStatus_Success != Controller_TaskInit())
    {
        return gBleOsError_c;
    }

#ifndef CPU_QN908X    
    gMCUSleepDuringBleEvents = cMCU_SleepDuringBleEvents;
#endif /* CPU_QN908X */
    
    /* BLE Controller Init */
    if (osaStatus_Success != Controller_Init(Hcit_SendPacket))
    {
        return gBleOsError_c;
    }
    
    /* Configure HCI Transport */
    hcitConfigStruct_t hcitConfigStruct = 
    {
        .interfaceType = gHcitInterfaceType_d,
        .interfaceChannel = gHcitInterfaceNumber_d,
        .interfaceBaudrate = gHcitInterfaceSpeed_d,
        .transportInterface =  (hciTransportInterface_t)Hci_SendPacketToController
    };
    
    return Hcit_Init(&hcitConfigStruct);
    
#else    

#ifndef CPU_QN908X
    /* BLE Radio Init */    
    XCVR_Init(BLE_MODE, DR_1MBPS);    
    XCVR_SetXtalTrim( (uint8_t)gHardwareParameters.xtalTrim );
#endif /* CPU_QN908X */
    
    /* BLE Controller Task Init */
    if (osaStatus_Success != Controller_TaskInit())
    {
        return gBleOsError_c;
    }
     
#ifndef CPU_QN908X 
    gEnableSingleAdvertisement = FALSE;
    gMCUSleepDuringBleEvents = cMCU_SleepDuringBleEvents;
#endif /* CPU_QN908X */
        
    /* BLE Controller Init */
    if (osaStatus_Success != Controller_Init(Ble_HciRecvLog))
    {
        return gBleOsError_c;
    }

    /* Check for available memory storage */
    if (!Ble_CheckMemoryStorage())
    {
        return gBleOutOfMemory_c;
    }

    /* BLE Host Tasks Init */
    if (osaStatus_Success != Ble_HostTaskInit())
    {
        return gBleOsError_c;
    }
    
    /* BLE Host Stack Init */
    return Ble_HostInitialize(gapGenericCallback, 
                (hciHostToControllerInterface_t) Ble_HciSendLog);
    
#endif
}


/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/


/*! *********************************************************************************
* @}
********************************************************************************** */

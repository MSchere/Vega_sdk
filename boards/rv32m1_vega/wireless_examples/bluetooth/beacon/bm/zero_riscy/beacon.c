/*! *********************************************************************************
* \addtogroup Beacon
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* 
*
* This file is the source file for the Beacon application
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
/* Framework / Drivers */
#include "RNG_Interface.h"
#include "Keyboard.h"
#include "LED.h"
#include "TimersManager.h"
#include "FunctionLib.h"
#include "fsl_os_abstraction.h"
#include "Panic.h"
#include "SecLib.h"
#include "fsl_device_registers.h"

/* BLE Host Stack */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"

#if MULTICORE_HOST
#include "dynamic_gatt_database.h"
#else
#include "gatt_db_handles.h"
#endif

/* Application */
#include "ApplMain.h"
#include "beacon.h"

#if MULTICORE_HOST
#include "erpc_host.h"
#include "dynamic_gatt_database.h"
#else
#include "hci_transport.h"
#endif

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
static bleDeviceAddress_t maBleDeviceAddress;

/* Adv Parmeters */
bool_t      mAdvertisingOn = FALSE;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_Config(void);
static void BleApp_Advertise(void);

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
* \brief    Initializes application specific functionality before the BLE stack init.
*
********************************************************************************** */
void BleApp_Init(void)
{
    uint8_t buffer[16] = {0};
    uint8_t hash[SHA256_HASH_SIZE];
#if MULTICORE_HOST
    /* Init eRPC host */
    init_erpc_host();
#endif /* MULTICORE_HOST */
#ifdef FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR
    FLib_MemCpy(&buffer[0], (uint8_t*)FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR, 6);
    FLib_MemCopy32Unaligned(&buffer[7], 0);
    FLib_MemCopy16Unaligned(&buffer[11], 0);
#else /* FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR */
    /* Initialize sha buffer with values from SIM_UID */
    uint8_t len;
    BOARD_GetMCUUid(buffer, &len);
#endif /* FSL_FEATURE_FLASH_ADDR_OF_VENDOR_BD_ADDR */
    
    SHA256_Hash(buffer, 16, hash);
    
    /* Updated UUID value from advertising data with the hashed value */
    FLib_MemCpy(&gAppAdvertisingData.aAdStructures[1].aData[3], hash, 16);
}

/*! *********************************************************************************
* \brief    Starts the BLE application.
*
********************************************************************************** */
void BleApp_Start(void)
{
    if (!mAdvertisingOn)
    {
        BleApp_Advertise();
    }
}

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
{
    switch (events)
    {
        case gKBD_EventPB1_c:
        {
            BleApp_Start();
            break;
        }
        case gKBD_EventLongPB1_c:
        {
            if (mAdvertisingOn)
            {
                Gap_StopAdvertising();
            }
            break;
        }
    default:
         break;
    }
}

void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    switch (pGenericEvent->eventType)
    {
        case gInitializationComplete_c:    
        {
            BleApp_Config();
        }
        break;    
            
        case gPublicAddressRead_c:
        {
            /* Use address read from the controller */
            FLib_MemCpyReverseOrder(maBleDeviceAddress, pGenericEvent->eventData.aAddress, sizeof(bleDeviceAddress_t));
        }
        break;            
            
        case gAdvertisingDataSetupComplete_c:
        {            
            BleApp_Start();
        }
        break;  
        
        case gAdvertisingParametersSetupComplete_c:
        {
            App_StartAdvertising(BleApp_AdvertisingCallback, NULL);
        }
        break;         

        case gInternalError_c:
        {
            panic(0,0,0,0);
        }
        break;

        default: 
            break;
    }
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/
/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{
#if MULTICORE_HOST
    if (GattDbDynamic_CreateDatabase() != gBleSuccess_c)
    {
        panic(0,0,0,0);
        return;
    }
#endif /* MULTICORE_HOST */

    /* Read public address from controller */
    Gap_ReadPublicDeviceAddress();
    /* Setup Advertising and scanning data */
    Gap_SetAdvertisingData(&gAppAdvertisingData, NULL);

    mAdvertisingOn = FALSE;
}

/*! *********************************************************************************
* \brief        Configures GAP Advertise parameters. Advertise will satrt after
*               the parameters are set.
*
********************************************************************************** */
static void BleApp_Advertise(void)
{
    /* Set advertising parameters*/
    Gap_SetAdvertisingParameters((gapAdvertisingParameters_t*)&gAppAdvParams);
}

/*! *********************************************************************************
* \brief        Handles BLE Advertising callback from host stack.
*
* \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
********************************************************************************** */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent)
{
    switch (pAdvertisingEvent->eventType)
    {
        case gAdvertisingStateChanged_c:
        {
            mAdvertisingOn = !mAdvertisingOn;
            LED_StopFlashingAllLeds();
            Led1Flashing();

            if(!mAdvertisingOn)
            {
                Led2Flashing();
                Led3Flashing();
                Led4Flashing();
            }
        }
        break;

        case gAdvertisingCommandFailed_c:
        {
            panic(0,0,0,0);
        }
        break;

        default:
            break;
    }
}
/*! *********************************************************************************
* @}
********************************************************************************** */

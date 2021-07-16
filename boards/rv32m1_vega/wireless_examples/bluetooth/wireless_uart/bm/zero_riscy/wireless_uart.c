/*! *********************************************************************************
 * \addtogroup Wireless UART Application
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* 
*
* This file is the source file for the Wireless UART Application
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
#include "Panic.h"
#include "SerialManager.h"
#include "MemManager.h"
#include "board.h"

/* BLE Host Stack */
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_database.h"
#include "gap_interface.h"
#include "gatt_db_app_interface.h"

#if !MULTICORE_HOST
#include "gatt_db_handles.h"
#else
#define UUID128(name, ...)\
    extern uint8_t name[16];
#include "gatt_uuid128.h"
#undef UUID128
#endif

/* Profile / Services */
#include "wireless_uart_interface.h"
#include "battery_interface.h"
/* Wrappers */
#include "ble_conn_manager.h"
#include "ble_service_discovery.h"

#include "board.h"
#include "ApplMain.h"
#include "wireless_uart.h"

#if MULTICORE_HOST
#include "erpc_host.h"
#include "dynamic_gatt_database.h"
#endif

/************************************************************************************
 *************************************************************************************
 * Private macros
 *************************************************************************************
 ************************************************************************************/

#define mAppUartBufferSize_c   			gAttMaxWriteDataSize_d(gAttMaxMtu_c) /* Local Buffer Size */

#define mAppUartFlushIntervalInMs_c   	(7) 	/* Flush Timeout in Ms */

#define mBatteryLevelReportInterval_c   (10)	/* battery level report interval in seconds  */
/************************************************************************************
 *************************************************************************************
 * Private type definitions
 *************************************************************************************
 ************************************************************************************/
typedef enum appEvent_tag{
    mAppEvt_PeerConnected_c,
    mAppEvt_PairingComplete_c,
    mAppEvt_ServiceDiscoveryComplete_c,
    mAppEvt_ServiceDiscoveryNotFound_c,
    mAppEvt_ServiceDiscoveryFailed_c,
    mAppEvt_GattProcComplete_c,
    mAppEvt_GattProcError_c
}appEvent_t;

typedef enum appState_tag
{
    mAppIdle_c, 
    mAppExchangeMtu_c,	
    mAppServiceDisc_c,
    mAppServiceDiscRetry_c,
    mAppRunning_c
} appState_t;

typedef struct appPeerInfo_tag
{
    deviceId_t  deviceId;
    bool_t      isBonded;
    wucConfig_t clientInfo;
    appState_t  appState;
    gapRole_t   gapRole;
} appPeerInfo_t;

typedef struct advState_tag
{
    bool_t advOn;
} advState_t;
/************************************************************************************
 *************************************************************************************
 * Private memory declarations
 *************************************************************************************
 ************************************************************************************/

static appPeerInfo_t maPeerInformation[gAppMaxConnections_c];
static gapRole_t     mGapRole;

/* Adv Parmeters */
static advState_t mAdvState;
static bool_t   mScanningOn = FALSE;

static uint16_t mCharMonitoredHandles[1] = { value_uart_stream };

/* Service Data*/
static wusConfig_t mWuServiceConfig;
static bool_t      mBasValidClientList[gAppMaxConnections_c] = {FALSE};
static basConfig_t mBasServiceConfig = {service_battery, 0, mBasValidClientList, gAppMaxConnections_c};

static tmrTimerID_t mAppTimerId = gTmrInvalidTimerID_c;
static tmrTimerID_t mUartStreamFlushTimerId = gTmrInvalidTimerID_c;
static tmrTimerID_t mBatteryMeasurementTimerId = gTmrInvalidTimerID_c;

static uint8_t gAppSerMgrIf;
static uint16_t mAppUartBufferSize = mAppUartBufferSize_c;
static volatile bool_t mAppUartNewLine = FALSE;
/************************************************************************************
 *************************************************************************************
 * Private functions prototypes
 *************************************************************************************
 ************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback(gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ScanningCallback (gapScanningEvent_t* pScanningEvent);
static void BleApp_ConnectionCallback
(
    deviceId_t peerDeviceId,
    gapConnectionEvent_t* pConnectionEvent
);
static void BleApp_GattServerCallback 
(
   deviceId_t deviceId,
   gattServerEvent_t* pServerEvent
);

static void BleApp_GattClientCallback 
(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
);

static void BleApp_ServiceDiscoveryCallback
(
    deviceId_t deviceId,
    servDiscEvent_t* pEvent
);

static void BleApp_Config (void);
static void BleApp_Advertise (void);

void BleApp_StateMachineHandler
(
    deviceId_t peerDeviceId,
    uint8_t event
);

static void BleApp_StoreServiceHandles
(
    deviceId_t 	     peerDeviceId,
    gattService_t   *pService
);
static bool_t BleApp_CheckScanEvent (gapScannedDevice_t* pData);

/* Timer Callbacks */
static void ScaningTimerCallback (void *);
static void UartStreamFlushTimerCallback(void *);
static void BatteryMeasurementTimerCallback (void *);

/* Uart Tx/Rx Callbacks*/
static void Uart_RxCallBack(void *pData);
static void Uart_TxCallBack(void *pBuffer);

static void BleApp_FlushUartStream(void *pParam);
static void BleApp_ReceivedUartStream(deviceId_t peerDeviceId, uint8_t *pStream, uint16_t streamLength);
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
    /* Initialize application support for drivers */
    BOARD_InitAdc();

    /* UI */
    SerialManager_Init();

    /* Register Serial Manager interface */
    Serial_InitInterface(&gAppSerMgrIf, APP_SERIAL_INTERFACE_TYPE, APP_SERIAL_INTERFACE_INSTANCE);

    Serial_SetBaudRate(gAppSerMgrIf, gUARTBaudRate115200_c);

    /* Install Controller Events Callback handler */
    Serial_SetRxCallBack(gAppSerMgrIf, Uart_RxCallBack, NULL);
    
#if MULTICORE_HOST
    /* Init eRPC host */
    init_erpc_host();
#endif    
}

/*! *********************************************************************************
 * \brief    Starts the BLE application.
 *
 * \param[in]    mGapRole    GAP Start Role (Central or Peripheral).
 ********************************************************************************** */
void BleApp_Start (gapRole_t mGapRole)
{
    switch (mGapRole)
    {
        case gGapCentral_c:
        {
            Serial_Print(gAppSerMgrIf, "\n\rScanning...\n\r", gAllowToBlock_d);
            mAppUartNewLine = TRUE;
            gPairingParameters.localIoCapabilities = gIoKeyboardDisplay_c;
            App_StartScanning(&gScanParams, BleApp_ScanningCallback, TRUE);
            break;
        }
        case gGapPeripheral_c:
        {
            Serial_Print(gAppSerMgrIf, "\n\rAdvertising...\n\r", gAllowToBlock_d);
            mAppUartNewLine = TRUE;
            gPairingParameters.localIoCapabilities = gIoDisplayOnly_c;
            BleApp_Advertise();
            break;
        }
        default:
            break;
    }
}

/*! *********************************************************************************
* \brief        Handles keyboard events.
*
* \param[in]    events    Key event structure.
********************************************************************************** */
void BleApp_HandleKeys(key_event_t events)
{
    uint8_t mPeerId = 0;
    switch (events)
    {
        case gKBD_EventPressPB1_c:
        {
            LED_StopFlashingAllLeds();
            Led1Flashing();

            BleApp_Start(mGapRole);
            break;
        }
        case gKBD_EventLongPB1_c:
        {
            for(mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
            {
                if (maPeerInformation[mPeerId].deviceId != gInvalidDeviceId_c)
                    Gap_Disconnect(maPeerInformation[mPeerId].deviceId);
            }
            break;
        }
        case gKBD_EventPressPB2_c:
        {
            /* Switch current role */
            if( mGapRole == gGapCentral_c )
            {
                Serial_Print(gAppSerMgrIf, "\n\rSwitched role to GAP Peripheral.\n\r", gAllowToBlock_d);
                mAppUartNewLine = TRUE;
                mGapRole = gGapPeripheral_c;
            }
            else
            {
                Serial_Print(gAppSerMgrIf, "\n\rSwitched role to GAP Central.\n\r", gAllowToBlock_d);
                mAppUartNewLine = TRUE;
                mGapRole = gGapCentral_c;
            }
            break;
        }
        case gKBD_EventLongPB2_c:
            break;
    default:
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles BLE generic callback.
*
* \param[in]    pGenericEvent    Pointer to gapGenericEvent_t.
********************************************************************************** */
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent)
{
    /* Call BLE Conn Manager */
    BleConnManager_GenericEvent(pGenericEvent);
    
    switch (pGenericEvent->eventType)
    {
        case gInitializationComplete_c:    
        {
            BleApp_Config();
            BleApp_Start(mGapRole);
        }
        break;    
        
        case gAdvertisingParametersSetupComplete_c:
        {
            App_StartAdvertising(BleApp_AdvertisingCallback, BleApp_ConnectionCallback);
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
    uint8_t mPeerId = 0;
    
#if MULTICORE_HOST
    if (GattDbDynamic_CreateDatabase() != gBleSuccess_c)
    {
        panic(0,0,0,0);
        return;
    }
#endif /* MULTICORE_HOST */

    /* Configure as GAP Dual Role */
    BleConnManager_GapDualRoleConfig();
        
    /* Register for callbacks */
    App_RegisterGattServerCallback(BleApp_GattServerCallback);
    App_RegisterGattClientProcedureCallback(BleApp_GattClientCallback);
    GattServer_RegisterHandlesForWriteNotifications(NumberOfElements(mCharMonitoredHandles), mCharMonitoredHandles);
    BleServDisc_RegisterCallback(BleApp_ServiceDiscoveryCallback);
	
    for(mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
    {
        maPeerInformation[mPeerId].appState = mAppIdle_c;
        maPeerInformation[mPeerId].deviceId = gInvalidDeviceId_c;
        maPeerInformation[mPeerId].clientInfo.hService = gGattDbInvalidHandleIndex_d;
        maPeerInformation[mPeerId].clientInfo.hUartStream = gGattDbInvalidHandleIndex_d;
    }
    
    /* By default, always start node as GAP central */
    mGapRole = gGapPeripheral_c;
    
    Serial_Print(gAppSerMgrIf, "\n\rWireless UART starting as GAP Central, press the role switch to change it.\n\r", gAllowToBlock_d);
    
    mAdvState.advOn = FALSE;
    mScanningOn = FALSE;
    
    /* Start services */
    Wus_Start(&mWuServiceConfig);

    mBasServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_Start(&mBasServiceConfig);

    /* Allocate application timer */
    mAppTimerId = TMR_AllocateTimer();
    mUartStreamFlushTimerId = TMR_AllocateTimer();
    mBatteryMeasurementTimerId = TMR_AllocateTimer();
}

/*! *********************************************************************************
* \brief        Configures GAP Advertise parameters. Advertise will satrt after
*               the parameters are set.
*
********************************************************************************** */
static void BleApp_Advertise(void)
{
    /* Set advertising parameters*/
    Gap_SetAdvertisingParameters(&gAdvParams);
}

/*! *********************************************************************************
 * \brief        Handles BLE Scanning callback from host stack.
 *
 * \param[in]    pScanningEvent    Pointer to gapScanningEvent_t.
 ********************************************************************************** */
static void BleApp_ScanningCallback (gapScanningEvent_t* pScanningEvent)
{
    switch (pScanningEvent->eventType)
    {
        case gDeviceScanned_c:
        {
            if (BleApp_CheckScanEvent(&pScanningEvent->eventData.scannedDevice))
            {        
                gConnReqParams.peerAddressType = pScanningEvent->eventData.scannedDevice.addressType;
                FLib_MemCpy(gConnReqParams.peerAddress, 
                            pScanningEvent->eventData.scannedDevice.aAddress,
                            sizeof(bleDeviceAddress_t));
                
                Gap_StopScanning();
#if gAppUsePrivacy_d
                gConnReqParams.usePeerIdentityAddress = pScanningEvent->eventData.scannedDevice.advertisingAddressResolved;
#endif
                App_Connect(&gConnReqParams, BleApp_ConnectionCallback);
            }
        }        
        break;
        
        case gScanStateChanged_c:
        {
            mScanningOn = !mScanningOn;
            
            /* Node starts scanning */
            if (mScanningOn)
            { 
                /* Start advertising timer */
                TMR_StartLowPowerTimer(mAppTimerId, 
                           gTmrLowPowerSecondTimer_c,
                           TmrSeconds(gScanningTime_c),
                           ScaningTimerCallback, NULL);  

                Led1Flashing();
            }
            /* Node is not scanning */
            else
            {                
                TMR_StopTimer(mAppTimerId);
                
                Led1Flashing();
                Led2Flashing();
                Led3Flashing();
                Led4Flashing();
            }
        }
        break;
    case gScanCommandFailed_c:
    {
        panic(0, 0, 0, 0);
        break;
    }
    default:
        break;
    }
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
            mAdvState.advOn = !mAdvState.advOn;
            LED_StopFlashingAllLeds();
            Led1Flashing();

            if(!mAdvState.advOn)
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
* \brief        Handles BLE Connection callback from host stack.
*
* \param[in]    peerDeviceId        Peer device ID.
* \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
********************************************************************************** */
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent)
{
    switch (pConnectionEvent->eventType)
    {
        case gConnEvtConnected_c:
        {
            if(peerDeviceId < gAppMaxConnections_c)
            {
                maPeerInformation[peerDeviceId].deviceId = peerDeviceId;
            }
            else
            {
                Gap_Disconnect(peerDeviceId);
                break;
            }

            /* Advertising stops when connected */
            mAdvState.advOn = FALSE;

            /* Subscribe client*/
            Wus_Subscribe(peerDeviceId);
            Bas_Subscribe(&mBasServiceConfig, peerDeviceId);

            /* UI */
            LED_StopFlashingAllLeds();
            Led1On();

            /* Stop Advertising Timer*/
            mAdvState.advOn = FALSE;
            TMR_StopTimer(mAppTimerId);
            
            if(!TMR_IsTimerActive(mBatteryMeasurementTimerId))
            {
                /* Start battery measurements */
                TMR_StartLowPowerTimer(mBatteryMeasurementTimerId, gTmrLowPowerIntervalMillisTimer_c,
                                       TmrSeconds(mBatteryLevelReportInterval_c), BatteryMeasurementTimerCallback, NULL);
            }

#if gAppUsePairing_d
#if gAppUseBonding_d            
            Gap_CheckIfBonded(peerDeviceId, &maPeerInformation[peerDeviceId].isBonded);
            
            if ((maPeerInformation[peerDeviceId].isBonded) &&
                (gBleSuccess_c == Gap_LoadCustomPeerInformation(peerDeviceId,
                    (void*) &maPeerInformation[peerDeviceId].clientInfo, 0, sizeof (wucConfig_t))))
            {
                /* Restored custom connection information. Encrypt link */
                Gap_EncryptLink(peerDeviceId);
            }
#endif /* gAppUseBonding_d*/ 
#endif /* gAppUsePairing_d */

            Serial_Print(gAppSerMgrIf, "Connected to device ", gAllowToBlock_d);
            Serial_PrintDec(gAppSerMgrIf, peerDeviceId);
            if( mGapRole == gGapCentral_c )
            {
                Serial_Print(gAppSerMgrIf, " as master.\n\r", gAllowToBlock_d);
            }
            else
            {
                Serial_Print(gAppSerMgrIf, " as slave.\n\r", gAllowToBlock_d);
            }
            mAppUartNewLine = TRUE;
            
            maPeerInformation[peerDeviceId].gapRole = mGapRole;

            /* run the state machine */
            BleApp_StateMachineHandler(peerDeviceId, mAppEvt_PeerConnected_c);
        }
        break;

        case gConnEvtDisconnected_c:
        {
            Serial_Print(gAppSerMgrIf, "Disconnected from device ", gAllowToBlock_d);
            Serial_PrintDec(gAppSerMgrIf, peerDeviceId);
            Serial_Print(gAppSerMgrIf, ".\n\r", gAllowToBlock_d);
            
            maPeerInformation[peerDeviceId].appState = mAppIdle_c;
            maPeerInformation[peerDeviceId].clientInfo.hService = gGattDbInvalidHandleIndex_d;
            maPeerInformation[peerDeviceId].clientInfo.hUartStream = gGattDbInvalidHandleIndex_d;
            
            /* Unsubscribe client */
            Wus_Unsubscribe();
            Bas_Unsubscribe(&mBasServiceConfig, peerDeviceId); 
            
            TMR_StopTimer(mBatteryMeasurementTimerId);

            /* Reset Service Discovery to be sure*/
            BleServDisc_Stop(peerDeviceId);

            /* UI */
            LED_TurnOffAllLeds();
            LED_StartFlash(LED_ALL);
 
            /* mark device id as invalid */
            maPeerInformation[peerDeviceId].deviceId = gInvalidDeviceId_c;
            
            /* recalculate minimum of maximum MTU's of all connected devices */
            mAppUartBufferSize                       = mAppUartBufferSize_c;
            
            for(uint8_t mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
            {
                if(gInvalidDeviceId_c != maPeerInformation[mPeerId].deviceId)
                {
                    uint16_t tempMtu;
                    
                    Gatt_GetMtu(mPeerId, &tempMtu);
                    tempMtu = gAttMaxWriteDataSize_d(tempMtu);
                    
                    if(tempMtu < mAppUartBufferSize)
                    {
                        mAppUartBufferSize = tempMtu;
                    }
                }
            }
            BleApp_Start(mGapRole);
        }
        break;

#if gAppUsePairing_d		
        case gConnEvtPairingComplete_c:
        {
            if (pConnectionEvent->eventData.pairingCompleteEvent.pairingSuccessful)
            {
                BleApp_StateMachineHandler(peerDeviceId, 
                                           mAppEvt_PairingComplete_c);
            }
        }
        break;
#endif /* gAppUsePairing_d */

    default:
        break;
    }
    
    /* Connection Manager to handle Host Stack interactions */
    if (maPeerInformation[peerDeviceId].gapRole == gGapCentral_c)
    {
        BleConnManager_GapCentralEvent(peerDeviceId, pConnectionEvent);
    }
    else if (maPeerInformation[peerDeviceId].gapRole == gGapPeripheral_c)
    {
        BleConnManager_GapPeripheralEvent(peerDeviceId, pConnectionEvent);
    }
}

static void BleApp_ServiceDiscoveryCallback(deviceId_t peerDeviceId, servDiscEvent_t* pEvent)
{
    switch(pEvent->eventType)
    {
        case gServiceDiscovered_c:
        {
            if (pEvent->eventData.pService->uuidType == gBleUuidType128_c)
            {
                if(FLib_MemCmp((void*)&uuid_service_wireless_uart, (void*)&pEvent->eventData.pService->uuid, sizeof(bleUuid_t)))
                { 
                    BleApp_StoreServiceHandles(peerDeviceId, pEvent->eventData.pService); 
                }
            }
        }
        break;

        case gDiscoveryFinished_c:
        {
            if (pEvent->eventData.success)
            {
                if (gGattDbInvalidHandleIndex_d != maPeerInformation[peerDeviceId].clientInfo.hService)
                {
                    BleApp_StateMachineHandler(peerDeviceId, 
                                               mAppEvt_ServiceDiscoveryComplete_c);
                }
                else
                {
                    BleApp_StateMachineHandler(peerDeviceId, 
                                               mAppEvt_ServiceDiscoveryNotFound_c);                
                }
            }
            else
            {
                BleApp_StateMachineHandler(peerDeviceId, 
                                           mAppEvt_ServiceDiscoveryFailed_c);
            }
        }
        break;

        default:
        break;
    }
}

/*! *********************************************************************************
* \brief        Handles GATT client callback from host stack.
*
* \param[in]    serverDeviceId      GATT Server device ID.
* \param[in]    procedureType    	Procedure type.
* \param[in]    procedureResult    	Procedure result.
* \param[in]    error    			Callback result.
********************************************************************************** */
static void BleApp_GattClientCallback(
    deviceId_t              serverDeviceId,
    gattProcedureType_t     procedureType,
    gattProcedureResult_t   procedureResult,
    bleResult_t             error
)
{  
    if (procedureResult == gGattProcError_c)
    {    
        BleApp_StateMachineHandler(serverDeviceId, 
                                   mAppEvt_GattProcError_c);
    }
    else if (procedureResult == gGattProcSuccess_c)
    {        
    	BleApp_StateMachineHandler(serverDeviceId, 
                                   mAppEvt_GattProcComplete_c);
    }

    /* Signal Service Discovery Module */
    BleServDisc_SignalGattClientEvent(serverDeviceId, 
                                      procedureType,procedureResult, error);
}

/*! *********************************************************************************
 * \brief        Handles GATT server callback from host stack.
 *
 * \param[in]    deviceId        Client peer device ID.
 * \param[in]    pServerEvent    Pointer to gattServerEvent_t.
 ********************************************************************************** */
static void BleApp_GattServerCallback (
                                       deviceId_t deviceId,
                                       gattServerEvent_t* pServerEvent)
{
    uint16_t tempMtu = 0;
    
    switch (pServerEvent->eventType)
    {
        case gEvtAttributeWrittenWithoutResponse_c:
        {
            if (pServerEvent->eventData.attributeWrittenEvent.handle == value_uart_stream)
            {
            	BleApp_ReceivedUartStream(deviceId, pServerEvent->eventData.attributeWrittenEvent.aValue,
                            pServerEvent->eventData.attributeWrittenEvent.cValueLength);
            }
            break;
        }
        case gEvtMtuChanged_c:
        {
            /* update stream length with minimum of  new MTU */
            Gatt_GetMtu(deviceId, &tempMtu);
            tempMtu = gAttMaxWriteDataSize_d(tempMtu);
            
            mAppUartBufferSize = mAppUartBufferSize <= tempMtu? mAppUartBufferSize : tempMtu;
        }
        break;
    default:
        break;
    }
}


static bool_t MatchDataInAdvElementList (
                                         gapAdStructure_t *pElement,
                                         void *pData,
                                         uint8_t iDataLen)
{
    uint8_t i;

    for (i = 0; i < pElement->length; i += iDataLen)
    {
        if (FLib_MemCmp(pData, &pElement->aData[i], iDataLen))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*! *********************************************************************************
 * \brief        Checks Scan data for a device to connect.
 *
 * \param[in]    pData    Pointer to gapScannedDevice_t.
 ********************************************************************************** */
static bool_t BleApp_CheckScanEvent (gapScannedDevice_t* pData)
{
    uint8_t index = 0;
    bool_t foundMatch = FALSE;

    while (index < pData->dataLength)
    {
        gapAdStructure_t adElement;

        adElement.length = pData->data[index];
        adElement.adType = (gapAdType_t) pData->data[index + 1];
        adElement.aData = &pData->data[index + 2];

        /* Search for Wireless UART Service */
        if ((adElement.adType == gAdIncomplete128bitServiceList_c)
            || (adElement.adType == gAdComplete128bitServiceList_c))
        {
            foundMatch = MatchDataInAdvElementList(&adElement,
                &uuid_service_wireless_uart, 16);
        }

        /* Move on to the next AD element type */
        index += adElement.length + sizeof(uint8_t);
    }

    return foundMatch;
}

/*! *********************************************************************************
 * \brief        Stores handles used by the application.
 *
 * \param[in]    pService    Pointer to gattService_t.
 ********************************************************************************** */
static void BleApp_StoreServiceHandles (deviceId_t peerDeviceId, gattService_t *pService)
{
    /* Found Wireless UART Service */
    maPeerInformation[peerDeviceId].clientInfo.hService = pService->startHandle;

    if (pService->cNumCharacteristics > 0 &&
        pService->aCharacteristics != NULL)
    {
        /* Found Uart Characteristic */
        maPeerInformation[peerDeviceId].clientInfo.hUartStream =
            pService->aCharacteristics[0].value.handle;
    }
}

static void BleApp_SendUartStream(uint8_t *pRecvStream, uint8_t streamSize)
{
    gattCharacteristic_t characteristic = {gGattCharPropNone_c, {0}, 0, 0};
    uint8_t              mPeerId = 0;

    /* send UART stream to all peers */
    for(mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
    {
        if(gInvalidDeviceId_c != maPeerInformation[mPeerId].deviceId && 
           mAppRunning_c == maPeerInformation[mPeerId].appState)
        {
            characteristic.value.handle = maPeerInformation[mPeerId].clientInfo.hUartStream;
            GattClient_WriteCharacteristicValue(mPeerId, &characteristic,
                                                streamSize, pRecvStream, TRUE,
                                                FALSE, FALSE, NULL);
        }
    }
}

void BleApp_StateMachineHandler(deviceId_t peerDeviceId, uint8_t event)
{
    uint16_t tempMtu = 0;
    
    /* invalid client information */
    if(gInvalidDeviceId_c == maPeerInformation[peerDeviceId].deviceId)
    {
        return;
    }
    
    switch (maPeerInformation[peerDeviceId].appState)
    {
        case mAppIdle_c:
        {
            if (event == mAppEvt_PeerConnected_c)
            {
                /* Let the central device initiate the Exchange MTU procedure*/
                if (mGapRole == gGapCentral_c)
                {
                    /* Moving to Exchange MTU State */
                    maPeerInformation[peerDeviceId].appState = mAppExchangeMtu_c;
                    GattClient_ExchangeMtu(peerDeviceId);
                }
                else
                {
                    /* Moving to Service Discovery State*/
                    maPeerInformation[peerDeviceId].appState = mAppServiceDisc_c;

                    /* Start Service Discovery*/
                    BleServDisc_FindService(peerDeviceId, 
                                            gBleUuidType128_c,
                                            (bleUuid_t*) &uuid_service_wireless_uart);                  
                }
            }
        }
        break;

        case mAppExchangeMtu_c:
        {
            if (event == mAppEvt_GattProcComplete_c)
            {
                /* update stream length with minimum of maximum MTU's of connected devices */
                Gatt_GetMtu(peerDeviceId, &tempMtu);
                tempMtu = gAttMaxWriteDataSize_d(tempMtu);
                
                mAppUartBufferSize = mAppUartBufferSize <= tempMtu? mAppUartBufferSize : tempMtu;
                
                /* Moving to Service Discovery State*/
                maPeerInformation[peerDeviceId].appState = mAppServiceDisc_c;

                /* Start Service Discovery*/
                BleServDisc_FindService(peerDeviceId, 
                                        gBleUuidType128_c,
                                        (bleUuid_t*) &uuid_service_wireless_uart);
            }
            else if (event == mAppEvt_GattProcError_c) 
            {
                Gap_Disconnect(peerDeviceId);
            }
        }
        break;

        case mAppServiceDisc_c:
        {
            if (event == mAppEvt_ServiceDiscoveryComplete_c)
            {            	
                /* Moving to Running State*/
                maPeerInformation[peerDeviceId].appState = mAppRunning_c;
#if gAppUseBonding_d
                /* Write data in NVM */
                Gap_SaveCustomPeerInformation(maPeerInformation[peerDeviceId].deviceId,
                                              (void*) &maPeerInformation[peerDeviceId].clientInfo, 0,
                                              sizeof (wucConfig_t));
#endif
            }
            else if (event == mAppEvt_ServiceDiscoveryNotFound_c)
            {
                /* Moving to Service discovery Retry State*/
                maPeerInformation[peerDeviceId].appState = mAppServiceDiscRetry_c;              
                /* Retart Service Discovery for all services */
                BleServDisc_Start(peerDeviceId);              
            }
            else if (event == mAppEvt_ServiceDiscoveryFailed_c)
            {
                Gap_Disconnect(peerDeviceId);
            }
        }
        break;
        
        case mAppServiceDiscRetry_c:
        {
            if (event == mAppEvt_ServiceDiscoveryComplete_c)
            {            	
                /* Moving to Running State*/
                maPeerInformation[peerDeviceId].appState = mAppRunning_c;
            }
            else if( (event == mAppEvt_ServiceDiscoveryNotFound_c) ||
                     (event == mAppEvt_ServiceDiscoveryFailed_c) )
            {
                Gap_Disconnect(peerDeviceId);
            }
        }
        break;        

        case mAppRunning_c:
                break;
        default:
                break;
    }
}

/*! *********************************************************************************
 * \brief        Handles scanning timer callback.
 *
 * \param[in]    pParam        Calback parameters.
 ********************************************************************************** */
static void ScaningTimerCallback (void * pParam)
{
    /* Stop scanning */
    Gap_StopScanning();
}

static void BleApp_FlushUartStream(void *pParam)
{
    uint8_t *pMsg = NULL;
    uint16_t bytesRead = 0;
    uint8_t  mPeerId = 0;
    bool_t   mValidDevices = FALSE;
    
    /* Valid devices are in Running state */
    for(mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
    {
        if( gInvalidDeviceId_c != maPeerInformation[mPeerId].deviceId && 
           mAppRunning_c == maPeerInformation[mPeerId].appState)
        {
            mValidDevices = TRUE;
            break;
        }
    }
    
    if(!mValidDevices)
    {
        return;
    }

    /* Allocate buffer for GATT Write */
    pMsg = MEM_BufferAlloc(mAppUartBufferSize);
    
    if (pMsg == NULL)
    {
    	return;
    }

    /* Collect the data from the serial manager buffer */
    if ( Serial_Read( gAppSerMgrIf, pMsg, mAppUartBufferSize, &bytesRead) == gSerial_Success_c )
    {
        if (bytesRead != 0)
        {
            /* Send data over the air */
            BleApp_SendUartStream(pMsg, bytesRead);
        }
    }    
    /* Free Buffer */
    MEM_BufferFree(pMsg);
}

static void BleApp_ReceivedUartStream(deviceId_t peerDeviceId, uint8_t *pStream, uint16_t streamLength)
{
    static deviceId_t previousDeviceId = gInvalidDeviceId_c;
    
    uint8_t  additionalInfoBuff[10] = { '\r','\n','[', '0', '0', '-', 'M', ']', ':', ' '};
    uint8_t *pBuffer = NULL;
    uint8_t  messageHeaderSize = 0;

    if(gInvalidDeviceId_c == peerDeviceId)
    {
        return;
    }
    
    if( (previousDeviceId != peerDeviceId) || mAppUartNewLine )
    {
        streamLength += sizeof(additionalInfoBuff);
    }
    
    /* Allocate buffer for asynchronous write */
    pBuffer = MEM_BufferAlloc(streamLength);

    if (pBuffer != NULL)
    {
        /* if this is a message from a previous device, print device ID */
        if( (previousDeviceId != peerDeviceId) || mAppUartNewLine )
        {
            messageHeaderSize = sizeof(additionalInfoBuff);
            
            if( mAppUartNewLine )
            {
                mAppUartNewLine = FALSE;
            }
            
            if(peerDeviceId > 9)
            {
                additionalInfoBuff[3] = '0' + (peerDeviceId / 10);
            }
            additionalInfoBuff[4] = '0' + (peerDeviceId % 10);
            
            if( gGapCentral_c != maPeerInformation[peerDeviceId].gapRole )
            {
                additionalInfoBuff[6] = 'S';
            }
            
            FLib_MemCpy(pBuffer, additionalInfoBuff, sizeof(additionalInfoBuff));
        }
        
        FLib_MemCpy(pBuffer + messageHeaderSize, pStream, streamLength - messageHeaderSize);
        Serial_AsyncWrite(gAppSerMgrIf, pBuffer, streamLength, Uart_TxCallBack, pBuffer);
    }
    /* update the previous device ID */
    previousDeviceId = peerDeviceId;
}

static void UartStreamFlushTimerCallback(void *pData)
{
    App_PostCallbackMessage(BleApp_FlushUartStream, NULL);
}

/*! *********************************************************************************
* \brief        Handles UART Receive callback.
*
* \param[in]    pData        Parameters.
********************************************************************************** */
static void Uart_RxCallBack(void *pData)
{
    static uint8_t bAppMsgPosted = 0;
    static uint16_t msgByteCount = 0;
    uint16_t byteCount;

    Serial_RxBufferByteCount(gAppSerMgrIf, &byteCount);
    
    if (byteCount < mAppUartBufferSize)
    {
        /* Clear App Msg if posted earlier */
        if( 1 == bAppMsgPosted )
        {
            bAppMsgPosted = 0;
        }
        
        /* Restart flush timer */
        TMR_StartLowPowerTimer(mUartStreamFlushTimerId,
                gTmrLowPowerSingleShotMillisTimer_c,
                mAppUartFlushIntervalInMs_c,
                UartStreamFlushTimerCallback, NULL);
    }
    else
    {
        /* Post App Msg only one at a time */
        if( 0 == bAppMsgPosted )
        {
            bAppMsgPosted = 1;
            msgByteCount = byteCount;
            App_PostCallbackMessage(BleApp_FlushUartStream, NULL);
        }
        else
        {
            /* Check if application has read bytes */
            if( byteCount < msgByteCount )
            {
                bAppMsgPosted = 0;
            }
        }
    }
}

/*! *********************************************************************************
* \brief        Handles UART Transmit callback.
*
* \param[in]    pData        Parameters.
********************************************************************************** */
static void Uart_TxCallBack(void *pBuffer)
{
    MEM_BufferFree(pBuffer);
}


/*! *********************************************************************************
* \brief        Handles battery measurement timer callback.
*
* \param[in]    pParam        Calback parameters.
********************************************************************************** */
static void BatteryMeasurementTimerCallback(void * pParam)
{
    mBasServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_RecordBatteryMeasurement(&mBasServiceConfig);
}

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

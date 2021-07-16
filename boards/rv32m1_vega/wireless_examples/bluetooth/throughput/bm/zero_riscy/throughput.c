/*! *********************************************************************************
* \addtogroup Temperature Sensor
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
*
*
* This file is the source file for the Throughput Peripheral application
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "fsl_debug_console.h"

/* Framework / Drivers */
#include "RNG_Interface.h"
#include "Keyboard.h"
#include "LED.h"
#include "TimersManager.h"
#include "FunctionLib.h"
#include "MemManager.h"
#include "Panic.h"


#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#include "PWR_Configuration.h"
#endif

/* BLE Host Stack */
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gap_interface.h"
#include "gatt_db_handles.h"

/* Profile / Services */
#include "wireless_uart_interface.h"
#include "battery_interface.h"
#include "device_info_interface.h"

/* Connection Manager */
#include "ble_conn_manager.h"
#include "ble_service_discovery.h"

#include "board.h"
#include "ApplMain.h"
#include "throughput.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define mBatteryLevelReportInterval_c   (10)        /* battery level report interval in seconds  */

#define gBleApp_TxInterval_c (4) /* ms */
#define gBleApp_TxPacketCount_c (2)

#define gThroghputL2capLePsm_c          (0x004FU)
#define gThroghputMaxLength_c           (240U)
#define gThroghputInitialCredits_c      (32768)
#define gThroghputReceiveCount_c        (100U)
#define gThroghputReceiveCycle_c        (10U)
#define gThroghputTimerInterval_c       (1U)

/* Defines throughput test task priority */
#define gThroghputThreadPriority_c      (8U)
/* Defines throughput test task stack size */
#define gThroghputThreadStackSize_c     (2048U)
/* Defines throughput test task stack size */
#define gThroghputEventL2capConnected_c      (0x00000001U)
#define gThroghputEventGattConnected_c       (0x00000002U)
#define gThroghputEventCccdNotification_c    (0x00000004U)
/* Defines throughput test pack count */
#define gThroghputPackCount_c           (0xFFFFFFFFU)

#define gCentralThroghputWaitingConnection_c    (0U)
#define gCentralThroghput_c             (1U)
#define gPeripheralThroghputWaitingConnection_c (2U)
#define gPeripheralThroghput_c          (3U)

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
    mAppRunning_c,
} appState_t;

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef struct advState_tag{
    bool_t      advOn;
}advState_t;

/*! Structure containing the OTAP Client functional data. */
typedef struct _throughput_test
{
    osaEventId_t                event;
    volatile uint32_t           tick;
    volatile uint32_t           startTick;
    volatile uint32_t           ReceivedLength;
    volatile uint32_t           ReceivedCount;
    volatile uint32_t           ReceivedCycle;
    volatile uint32_t           sendCount;
    uint16_t                    negotiatedMaxAttChunkSize;                      /*!< The negotiated maximum ATT chunk size based on the negotiated ATT MTU between the OTAP Server and the OTAP Client. */
    uint16_t                    negotiatedMaxL2CapChunkSize;                    /*!< The negotiated maximum L2CAP chunk size based on the negotiated L2CAP MTU between the OTAP Server and the OTAP Client. */
    uint16_t                    l2capPsmConnected;                              /*!< Flag which is set to true if an L2CAP PSM connection is currently established with a peer device. */
    uint16_t                    l2capPsmChannelId;                              /*!< Channel Id for an L2CAP PSM connection currently established with a peer device. */
    uint8_t                     buffer[gThroghputMaxLength_c];
    tmrTimerID_t                timerId;
    volatile uint8_t            testStep;
} throughput_test_t;

/*! Wireless UART Client - Configuration */
typedef struct throughputConfig_tag
{
    uint16_t    hService;
    uint16_t    hUartStream;
    uint16_t    hStatus;
    uint16_t    hStatusCccd;
} throughputConfig_t;

/*! Wireless UART Client - Configuration */
typedef struct throughputCccd_tag
{
    volatile uint16_t    cccdNotification;
    volatile uint16_t    cccdNotificationNewData;
} throughputCccd_t;

typedef struct appPeerInfo_tag
{
    deviceId_t  deviceId;
    bool_t      isBonded;
    throughputConfig_t clientInfo;
    throughputCccd_t   cccd;
    appState_t  appState;
    gapRole_t   gapRole;
    uint16_t    bufferSize;
    uint16_t    peerNotificationValue;
    uint16_t    throughputTestFinished;
} appPeerInfo_t;
/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

static appPeerInfo_t maPeerInformation[gAppMaxConnections_c];
static gapRole_t     mGapRole;

/* Adv State */
static advState_t  mAdvState;
static bool_t   mScanningOn = FALSE;

/* Service Data*/
static bool_t           mBasValidClientList[gAppMaxConnections_c] = {FALSE};
static basConfig_t      basServiceConfig = {service_battery, 0, mBasValidClientList, gAppMaxConnections_c};
static disConfig_t      disServiceConfig = {service_device_info};

/* Application specific data*/
static tmrTimerID_t mAppTimerId;

static uint32_t packetSent = 0;
static uint8_t testBytes[gThroghputMaxLength_c];

static throughput_test_t throughputTest;

static uint16_t mCharMonitoredHandles[1] = { value_throughput_stream };

/* Buffer used for Characteristic related procedures */
static gattAttribute_t      *mpCharProcBuffer = NULL;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/* Gatt and Att callbacks */
static void BleApp_AdvertisingCallback (gapAdvertisingEvent_t* pAdvertisingEvent);
static void BleApp_ConnectionCallback (deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent);
static void BleApp_Config();
static void BleApp_UpdateNotification(uint16_t deviceId, uint16_t value);

/* Timer Callbacks */
#if cPWR_UsePowerDownMode
static void AdvertisingTimerCallback (void *);
static void DisconnectTimerCallback(void* );
#endif

static void BleApp_Advertise(void);
static void BleApp_SendTemperature(void);

static void TestSendPackets(deviceId_t deviceId);
static void BleApp_SendData(void *p);

/* client */
void BleApp_StateMachineHandler(deviceId_t peerDeviceId, uint8_t event);

void throughput_test_task(void* param);

OSA_TASK_DEFINE(throughput_test_task, gThroghputThreadPriority_c, 1, gThroghputThreadStackSize_c, 0);
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
    OSA_TaskCreate(OSA_TASK(throughput_test_task),NULL);
    /* Initialize application support for drivers */
    BOARD_InitAdc();
    TMR_TimeStampInit();
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
                &uuid_service_throughput, 16);
        }

        /* Move on to the next AD element type */
        index += adElement.length + sizeof(uint8_t);
    }

    return foundMatch;
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
* \brief    Starts the BLE application.
*
********************************************************************************** */
void BleApp_Start(gapRole_t mGapRole)
{
    switch (mGapRole)
    {
        case gGapCentral_c:
        {
            TMR_StopTimer(mAppTimerId);
            PRINTF("\n\rScanning...\n\r");
            gPairingParameters.localIoCapabilities = gIoKeyboardDisplay_c;
            App_StartScanning(&gScanParams, BleApp_ScanningCallback, TRUE);
            break;
        }
        case gGapPeripheral_c:
        {
            TMR_StopTimer(mAppTimerId);
            PRINTF("\n\rAdvertising...\n\r");
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
                PRINTF("\n\rSwitched role to GAP Peripheral.\n\r");
                mGapRole = gGapPeripheral_c;
            }
            else
            {
                PRINTF("\n\rSwitched role to GAP Central.\n\r");
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

static void BleApp_L2capPsmDataCallback (deviceId_t     deviceId,
                                         uint16_t       lePsm,
                                         uint8_t*       pPacket,
                                         uint16_t       packetLength)
{
    if (0 == throughputTest.startTick)
    {
        throughputTest.startTick = throughputTest.tick;
        throughputTest.ReceivedCount = 0;
        throughputTest.ReceivedLength = 0;
    }
    else
    {
        if (gThroghputReceiveCount_c > throughputTest.ReceivedCount)
        {
            throughputTest.ReceivedLength += packetLength;
            throughputTest.ReceivedCount++;
        }

        if (gThroghputReceiveCount_c <= throughputTest.ReceivedCount)
        {
            uint32_t tick = throughputTest.tick-throughputTest.startTick;
            extern uint32_t SystemCoreClock;
            PRINTF("received length = %d, speed = %d\r\n", throughputTest.ReceivedLength, (uint32_t)((uint64_t)throughputTest.ReceivedLength * (uint64_t)1000 / (uint64_t)tick));
            throughputTest.startTick = 0;
        }
    }
}

static void BleApp_HandlePsmConnectionComplete (l2caLeCbConnectionComplete_t *pConnComplete)
{
    if (pConnComplete->result == gSuccessful_c)
    {
        /* Starting throughput testing */
        throughputTest.l2capPsmConnected = 1;
        throughputTest.l2capPsmChannelId = pConnComplete->cId;

        if (pConnComplete->peerMtu < gThroghputMaxLength_c)
        {
            throughputTest.negotiatedMaxL2CapChunkSize = pConnComplete->peerMtu;
        }
        else
        {
            throughputTest.negotiatedMaxL2CapChunkSize = gThroghputMaxLength_c;
        }
        throughputTest.startTick = 0;
        throughputTest.testStep++;
        if (gPeripheralThroghput_c == throughputTest.testStep)
        {
            OSA_EventSet(throughputTest.event, gThroghputEventL2capConnected_c);
        }
        /* Start the throughput test */
    }
    else
    {
        throughputTest.l2capPsmConnected = 0;
        /* If the connection failed try to reconnect. */
        L2ca_ConnectLePsm (gThroghputL2capLePsm_c,
                           pConnComplete->deviceId,
                           gThroghputInitialCredits_c);
    }
}

static void BleApp_HandlePsmDisconnection (l2caLeCbDisconnection_t *pCbDisconnect)
{
    throughputTest.l2capPsmConnected = 0;

    {
        throughputTest.testStep ++;

        if (throughputTest.testStep < gPeripheralThroghput_c)
        {
            /* If the connection failed try to reconnect. */
            L2ca_ConnectLePsm (gThroghputL2capLePsm_c,
                               pCbDisconnect->deviceId,
                               gThroghputInitialCredits_c);
        }
    }
}

static void BleApp_L2capPsmControlCallback(l2capControlMessageType_t    messageType,
                                           void*                        pMessage)
{
    switch (messageType)
    {
        case gL2ca_LePsmConnectRequest_c:
        {
            l2caLeCbConnectionRequest_t *pConnReq = (l2caLeCbConnectionRequest_t *)pMessage;

            /* This message is unexpected on the OTAP Client, the OTAP Client sends L2CAP PSM connection
             * requests and expects L2CAP PSM connection responses.
             * Disconnect the peer. */
            Gap_Disconnect (pConnReq->deviceId);

            break;
        }
        case gL2ca_LePsmConnectionComplete_c:
        {
            l2caLeCbConnectionComplete_t *pConnComplete = (l2caLeCbConnectionComplete_t *)pMessage;

            /* Call the application PSM connection complete handler. */
            BleApp_HandlePsmConnectionComplete (pConnComplete);

            break;
        }
        case gL2ca_LePsmDisconnectNotification_c:
        {
            l2caLeCbDisconnection_t *pCbDisconnect = (l2caLeCbDisconnection_t *)pMessage;

            /* Call the application PSM disconnection handler. */
            BleApp_HandlePsmDisconnection (pCbDisconnect);

            break;
        }
        case gL2ca_NoPeerCredits_c:
        {
            l2caLeCbNoPeerCredits_t *pCbNoPeerCredits = (l2caLeCbNoPeerCredits_t *)pMessage;
            L2ca_SendLeCredit (pCbNoPeerCredits->deviceId,
                               pCbNoPeerCredits->cId,
                               gThroghputInitialCredits_c);
            break;
        }
        case gL2ca_LocalCreditsNotification_c:
        {
            l2caLeCbLocalCreditsNotification_t *pMsg = (l2caLeCbLocalCreditsNotification_t *)pMessage;

            if (0 == pMsg->localCredits)
            {
#if 0
                L2ca_HandleLeFlowControlCredit (pMsg->deviceId,
                                                pMsg->cId,
                                                gThroghputInitialCredits_c);
#endif

                throughputTest.sendCount = gThroghputPackCount_c;
                throughputTest.startTick = throughputTest.tick;
            }
            break;
        }
        default:
            break;
    }
}

static bleResult_t BleApp_ConfigureNotifications(uint8_t deviceId, uint16_t cccdHandle)
{
    bleResult_t result = gBleSuccess_c;
    uint16_t value = gCccdNotification_c;

    if( mpCharProcBuffer == NULL )
    {
        mpCharProcBuffer = MEM_BufferAlloc(sizeof(gattAttribute_t) + 23);
    }

    if( mpCharProcBuffer != NULL )
    {
        mpCharProcBuffer->handle = cccdHandle;
        mpCharProcBuffer->uuid.uuid16 = gBleSig_CCCD_d;
        mpCharProcBuffer->valueLength = 0;
        GattClient_WriteCharacteristicDescriptor(deviceId,
                                                 mpCharProcBuffer,
                                                 sizeof(value), (void*)&value);
    }
    else
    {
        result = gBleOutOfMemory_c;
    }

    return result;
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
                maPeerInformation[peerDeviceId].bufferSize = gAttMaxWriteDataSize_d(gAttMaxMtu_c);
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
                                            (bleUuid_t*) &uuid_service_throughput);
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

                maPeerInformation[peerDeviceId].bufferSize = maPeerInformation[peerDeviceId].bufferSize <= tempMtu? maPeerInformation[peerDeviceId].bufferSize : tempMtu;

                /* Moving to Service Discovery State*/
                maPeerInformation[peerDeviceId].appState = mAppServiceDisc_c;

                /* Start Service Discovery*/
                BleServDisc_FindService(peerDeviceId,
                                        gBleUuidType128_c,
                                        (bleUuid_t*) &uuid_service_throughput);
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
                if (maPeerInformation[peerDeviceId].clientInfo.hStatusCccd)
                {
                    if( gBleSuccess_c != BleApp_ConfigureNotifications(peerDeviceId, maPeerInformation[peerDeviceId].clientInfo.hStatusCccd) )
                    {
                        Gap_Disconnect(peerDeviceId);
                    }
                    else
                    {
                        /* Moving to Running State*/
                        maPeerInformation[peerDeviceId].appState = mAppRunning_c;
                        if (gGapPeripheral_c == mGapRole)
                        {
                            maPeerInformation[peerDeviceId].cccd.cccdNotificationNewData = 0;
                        }
                        else
                        {
                            maPeerInformation[peerDeviceId].cccd.cccdNotificationNewData = 1;
                        }
                        OSA_EventSet(throughputTest.event, gThroghputEventCccdNotification_c);
                    }
                }
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
                //OSA_EventSet(throughputTest.event, gThroghputEventGattConnected_c);
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
        for (int i = 0;i < pService->cNumCharacteristics; i++)
        {
            if ((pService->aCharacteristics[i].value.uuidType == gBleUuidType128_c) &&
                FLib_MemCmp(pService->aCharacteristics[i].value.uuid.uuid128, uuid_throughput_stream, 16))
            {
                /* Found Uart Characteristic */
                maPeerInformation[peerDeviceId].clientInfo.hUartStream = pService->aCharacteristics[i].value.handle;
            }
            else if ((pService->aCharacteristics[i].value.uuidType == gBleUuidType128_c) &&
                FLib_MemCmp(pService->aCharacteristics[i].value.uuid.uuid128, uuid_throughput_status, 16))
            {
                /* Found Uart Characteristic */
                maPeerInformation[peerDeviceId].clientInfo.hStatus = pService->aCharacteristics[i].value.handle;

                for (int j = 0; j < pService->aCharacteristics[i].cNumDescriptors; j++)
                {
                    if (pService->aCharacteristics[i].aDescriptors[j].uuidType == gBleUuidType16_c)
                    {
                        switch (pService->aCharacteristics[i].aDescriptors[j].uuid.uuid16)
                        {
//                            case gBleSig_CharPresFormatDescriptor_d:
//                            {
//                                mPeerInformation.customInfo.tempClientConfig.hTempDesc = pService->aCharacteristics[i].aDescriptors[j].handle;
//                                break;
//                            }
                            case gBleSig_CCCD_d:
                            {
                                maPeerInformation[peerDeviceId].clientInfo.hStatusCccd = pService->aCharacteristics[i].aDescriptors[j].handle;
                                break;
                            }
                            default:
                                break;
                        }
                    }
                }
            }
            else
            {
            }
        }
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
                if(FLib_MemCmp((void*)&uuid_service_throughput, (void*)&pEvent->eventData.pService->uuid, sizeof(bleUuid_t)))
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
* \brief        Handles GATT client notification callback from host stack.
*
* \param[in]    serverDeviceId      		GATT Server device ID.
* \param[in]    characteristicValueHandle   Handle.
* \param[in]    aValue    					Pointer to value.
* \param[in]    valueLength    				Value length.
********************************************************************************** */
static void BleApp_GattNotificationCallback
(
    deviceId_t  serverDeviceId,
    uint16_t    characteristicValueHandle,
    uint8_t*    aValue,
    uint16_t    valueLength
)
{
    if (characteristicValueHandle == maPeerInformation[serverDeviceId].clientInfo.hStatus)
    {
        maPeerInformation[serverDeviceId].peerNotificationValue = *(uint16_t*)aValue;
        if (0 == maPeerInformation[serverDeviceId].peerNotificationValue)
        {
            OSA_EventSet(throughputTest.event, gThroghputEventGattConnected_c);
        }
    }
}

/*! *********************************************************************************
* \brief        Configures BLE Stack after initialization. Usually used for
*               configuring advertising, scanning, white list, services, et al.
*
********************************************************************************** */
static void BleApp_Config()
{
    /* Configure as GAP peripheral */
    BleConnManager_GapDualRoleConfig();

    /* Register for callbacks*/
    App_RegisterGattServerCallback(BleApp_GattServerCallback);
    App_RegisterGattClientProcedureCallback(BleApp_GattClientCallback);
    App_RegisterGattClientNotificationCallback(BleApp_GattNotificationCallback);
    BleServDisc_RegisterCallback(BleApp_ServiceDiscoveryCallback);

    GattServer_RegisterHandlesForWriteNotifications(NumberOfElements(mCharMonitoredHandles), mCharMonitoredHandles);

    /* Register throughput L2CAP PSM */
    L2ca_RegisterLePsm (gThroghputL2capLePsm_c,
                        gThroghputMaxLength_c);  /*!< The negotiated MTU must be higher than the biggest data chunk that will be sent fragmented */

    /* Register stack callbacks */
    App_RegisterLeCbCallbacks(BleApp_L2capPsmDataCallback, BleApp_L2capPsmControlCallback);

    mAdvState.advOn = FALSE;

    basServiceConfig.batteryLevel = BOARD_GetBatteryLevel();
    Bas_Start(&basServiceConfig);
    Dis_Start(&disServiceConfig);

    for(int mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
    {
        maPeerInformation[mPeerId].appState = mAppIdle_c;
        maPeerInformation[mPeerId].deviceId = gInvalidDeviceId_c;
        maPeerInformation[mPeerId].clientInfo.hService = gGattDbInvalidHandleIndex_d;
        maPeerInformation[mPeerId].clientInfo.hUartStream = gGattDbInvalidHandleIndex_d;
        maPeerInformation[mPeerId].peerNotificationValue = 0xFFFF;
        maPeerInformation[mPeerId].throughputTestFinished = 0;
    }

    for (int i = 0;i < sizeof(throughputTest.buffer); i++)
    {
        throughputTest.buffer[i] = i;
    }

    mGapRole = gGapPeripheral_c;

    /* Allocate aplication timer */
    mAppTimerId = TMR_AllocateTimer();

#if (cPWR_UsePowerDownMode)
    PWR_ChangeDeepSleepMode(3);
    PWR_AllowDeviceToSleep();
#endif
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

#if (cPWR_UsePowerDownMode)
            if(!mAdvState.advOn)
            {
                Led1Off();
                PWR_ChangeDeepSleepMode(3);
                PWR_SetDeepSleepTimeInMs(cPWR_DeepSleepDurationMs);
                PWR_AllowDeviceToSleep();
            }
            else
            {
                /* Start advertising timer */
                TMR_StartLowPowerTimer(mAppTimerId,
                           gTmrLowPowerSecondTimer_c,
                           TmrSeconds(gAdvTime_c),
                           AdvertisingTimerCallback, NULL);

                //Led1On();
            }
#else
            LED_StopFlashingAllLeds();
            Led1Flashing();

            if(!mAdvState.advOn)
            {
                Led2Flashing();
                Led3Flashing();
                Led4Flashing();
            }
#endif
        }
        break;

        case gAdvertisingCommandFailed_c:
        {
            //Led2On();
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

            LED_StopFlashingAllLeds();
            Led1On();
            maPeerInformation[peerDeviceId].gapRole = mGapRole;
            PRINTF("Connected to device %d ", peerDeviceId);
            if( mGapRole == gGapCentral_c )
            {
               PRINTF(" as master.\n\r");
            }
            else
            {
               PRINTF(" as slave.\n\r");
            }
            TMR_StopTimer(mAppTimerId);
            throughputTest.ReceivedCycle = 0;

            /* run the state machine */
            BleApp_StateMachineHandler(peerDeviceId, mAppEvt_PeerConnected_c);
        }
        break;

    case gConnEvtDisconnected_c:
        {
            PRINTF( "Disconnected from device %d \r\n", peerDeviceId);
            /* Unsubscribe client */
            maPeerInformation[peerDeviceId].appState = mAppIdle_c;
            maPeerInformation[peerDeviceId].clientInfo.hService = gGattDbInvalidHandleIndex_d;
            maPeerInformation[peerDeviceId].clientInfo.hUartStream = gGattDbInvalidHandleIndex_d;
            maPeerInformation[peerDeviceId].peerNotificationValue = 0xFFFF;
            maPeerInformation[peerDeviceId].throughputTestFinished = 0;

            Bas_Unsubscribe(&basServiceConfig, peerDeviceId);

            /* Reset Service Discovery to be sure*/
            BleServDisc_Stop(peerDeviceId);

            /* UI */
            LED_TurnOffAllLeds();
            LED_StartFlash(LED_ALL);

            /* mark device id as invalid */
            maPeerInformation[peerDeviceId].deviceId = gInvalidDeviceId_c;

            for(uint8_t mPeerId = 0; mPeerId < gAppMaxConnections_c; mPeerId++)
            {
                if(gInvalidDeviceId_c != maPeerInformation[mPeerId].deviceId)
                {
                    uint16_t tempMtu;

                    Gatt_GetMtu(mPeerId, &tempMtu);
                    tempMtu = gAttMaxWriteDataSize_d(tempMtu);

                    if(tempMtu < maPeerInformation[peerDeviceId].bufferSize)
                    {
                         maPeerInformation[peerDeviceId].bufferSize = tempMtu;
                    }
                }
            }
            /* restart advertising*/
            BleApp_Start(mGapRole);
        }
        break;
    case gConnEvtPairingComplete_c:

    case gConnEvtEncryptionChanged_c:
        {
//            TestSendPackets(peerDeviceId);
        }
        break;
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
    else
    {
    }
}

static void BleApp_UpdateNotification(uint16_t deviceId, uint16_t value)
{
    bleResult_t result;
    bool_t isNotificationActive;

    /* Update characteristic value */
    result = (bleResult_t)GattDb_WriteAttribute(value_throughput_status, sizeof(uint16_t), (uint8_t*)&value);

    if (result != gBleSuccess_c)
    {
        return;
    }

    GattServer_SendNotification(deviceId, value_throughput_status);
}

/*! *********************************************************************************
* \brief        Handles GATT server callback from host stack.
*
* \param[in]    deviceId        Peer device ID.
* \param[in]    pServerEvent    Pointer to gattServerEvent_t.
********************************************************************************** */
static void BleApp_GattServerCallback (deviceId_t deviceId, gattServerEvent_t* pServerEvent)
{
    switch (pServerEvent->eventType)
    {
        case gEvtAttributeWrittenWithoutResponse_c:
        {
            if (pServerEvent->eventData.attributeWrittenEvent.handle == value_throughput_stream)
            {
//            	BleApp_ReceivedUartStream(deviceId, pServerEvent->eventData.attributeWrittenEvent.aValue,
//                            pServerEvent->eventData.attributeWrittenEvent.cValueLength);
                if (0 == throughputTest.startTick)
                {
                    throughputTest.startTick = throughputTest.tick;
                    throughputTest.ReceivedCount = 0;
                    throughputTest.ReceivedLength = 0;
                }
                else
                {
                    if (gThroghputReceiveCount_c > throughputTest.ReceivedCount)
                    {
                        throughputTest.ReceivedLength += pServerEvent->eventData.attributeWrittenEvent.cValueLength;
                        throughputTest.ReceivedCount++;
                    }

                    if (gThroghputReceiveCount_c <= throughputTest.ReceivedCount)
                    {
                        uint32_t tick = throughputTest.tick-throughputTest.startTick;
                        extern uint32_t SystemCoreClock;
                        PRINTF("received length = %d, speed = %d\r\n", throughputTest.ReceivedLength, (uint32_t)((uint64_t)throughputTest.ReceivedLength * (uint64_t)1000 / (uint64_t)tick));
                        throughputTest.startTick = 0;
                        throughputTest.ReceivedCycle++;
                    }
                }
                if (gThroghputReceiveCycle_c <= throughputTest.ReceivedCycle)
                {
                    if (maPeerInformation[deviceId].cccd.cccdNotification)
                    {
                        maPeerInformation[deviceId].cccd.cccdNotificationNewData = 1;
                        OSA_EventSet(throughputTest.event, gThroghputEventCccdNotification_c);
                    }
                }
            }
            break;
        }
        case gEvtCharacteristicCccdWritten_c:
        {
            if (cccd_throughput_status == pServerEvent->eventData.charCccdWrittenEvent.handle)
            {
                maPeerInformation[deviceId].cccd.cccdNotification = (gCccdNotification_c == pServerEvent->eventData.charCccdWrittenEvent.newCccd) ? 1 : 0;
            }
        }
        break;
    default:
        break;
    }
}

static void throughput_test_timer(void* params)
{
    throughputTest.tick += 4;
}

void throughput_test_task(void* param)
{
    static uint32_t initialization = 0;
    osaEventFlags_t event = 0;
    int sendEvent = 0;

    if (!initialization)
    {
        /* Create application event */
        throughputTest.event = OSA_EventCreate(TRUE);
        if( NULL == throughputTest.event )
        {
            panic(0,0,0,0);
            return;
        }
        throughputTest.timerId = TMR_AllocateTimer();
        TMR_StartLowPowerTimer(throughputTest.timerId, gTmrIntervalTimer_c, gThroghputTimerInterval_c, throughput_test_timer, NULL);
#if 0
#if (defined(__CORTEX_M) && (__CORTEX_M == 4U))
        CoreDebug->DEMCR |= (1 << CoreDebug_DEMCR_TRCENA_Pos);
#elif defined(RISCV32)
#else
#endif
#endif
        throughputTest.sendCount = 0;
        initialization = 1;
    }

    do
    {
        OSA_EventWait(throughputTest.event, osaEventFlagsAll_c, FALSE, osaWaitForever_c , &event);

        if (event & gThroghputEventL2capConnected_c)
        {
            if (gPeripheralThroghput_c == throughputTest.testStep)
            {
                if (throughputTest.l2capPsmConnected)
                {
                    if (throughputTest.sendCount < gThroghputPackCount_c)
                    {
                        bleResult_t     bleResult = gBleSuccess_c;
                        bleResult =  L2ca_SendLeCbData (maPeerInformation[0].deviceId,
                                        throughputTest.l2capPsmChannelId,
                                        throughputTest.buffer,
                                        sizeof(throughputTest.buffer));
                        if (gBleSuccess_c == bleResult)
                        {
                            throughputTest.sendCount++;
                        }
                        sendEvent = 1;
                    }
                    else
                    {
                        if ((throughputTest.tick - throughputTest.startTick) > 500U )
                        {
                            bleResult_t result = (bleResult_t)L2caRm_DisconnectLePsm (maPeerInformation[0].deviceId,
                                                                             throughputTest.l2capPsmChannelId);
                            if (gBleSuccess_c == result)
                            {
                                throughputTest.testStep = gPeripheralThroghputWaitingConnection_c;
                            }
                            else
                            {
                                sendEvent = 1;
                            }
                        }
                        else
                        {
                            sendEvent = 1;
                        }
                    }
                }
            }
            else
            {
            }

            if (sendEvent)
            {
                /* Start the throughput test */
                OSA_EventSet(throughputTest.event, gThroghputEventL2capConnected_c);
            }
        }
        if (event & gThroghputEventGattConnected_c)
        {
            if ((mAppRunning_c == maPeerInformation[0].appState)
                && (gInvalidDeviceId_c != maPeerInformation[0].deviceId))
            {
                if (0 == maPeerInformation[0].peerNotificationValue)
                {
                    bleResult_t     bleResult = gBleSuccess_c;
                    gattCharacteristic_t characteristic = {gGattCharPropNone_c, {0}, 0, 0};
                    characteristic.value.handle = maPeerInformation[0].clientInfo.hUartStream;
                    bleResult = GattClient_WriteCharacteristicValue(0, &characteristic,
                                                        sizeof(throughputTest.buffer),
                                                        throughputTest.buffer, TRUE,
                                                        FALSE, FALSE, NULL);
                    if (gBleSuccess_c == bleResult)
                    {
                        throughputTest.sendCount++;
                    }
                    sendEvent = 1;
                }
                else
                {
                    if (0 == maPeerInformation[0].throughputTestFinished)
                    {
                        if (1 == maPeerInformation[0].peerNotificationValue)
                        {
                            maPeerInformation[0].peerNotificationValue = 2;
                            throughputTest.startTick = throughputTest.tick;
                        }
                        if ((throughputTest.tick - throughputTest.startTick) > 500U )
                        {
                            maPeerInformation[0].cccd.cccdNotificationNewData = 0;
                            OSA_EventSet(throughputTest.event, gThroghputEventCccdNotification_c);
                        }
                        else
                        {
                            sendEvent = 1;
                        }
                    }
                    else
                    {
                        PRINTF("Throughput test finished!\r\n");
                    }
                }
            }

            if (sendEvent)
            {
                /* Start the throughput test */
                OSA_EventSet(throughputTest.event, gThroghputEventGattConnected_c);
            }
        }
        if (event & gThroghputEventCccdNotification_c)
        {
            sendEvent = 1;
            if ((mAppRunning_c == maPeerInformation[0].appState)
                && (0 != maPeerInformation[0].cccd.cccdNotification))
            {
                BleApp_UpdateNotification(0, maPeerInformation[0].cccd.cccdNotificationNewData);
                if (0 == maPeerInformation[0].cccd.cccdNotificationNewData)
                {
                    maPeerInformation[0].throughputTestFinished = 1;
                }
                sendEvent = 0;
            }

            if (sendEvent)
            {
                /* Start the throughput test */
                OSA_EventSet(throughputTest.event, gThroghputEventCccdNotification_c);
            }
        }
    }
    while(gUseRtos_c);
}

/*! *********************************************************************************
* @}
********************************************************************************** */

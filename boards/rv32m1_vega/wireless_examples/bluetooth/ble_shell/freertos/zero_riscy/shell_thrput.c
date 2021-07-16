/*! *********************************************************************************
 * \addtogroup SHELL THRPUT
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* 
*
* This file is the source file for the THRPUT Shell module
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

/************************************************************************************
 *************************************************************************************
 * Include
 *************************************************************************************
 ************************************************************************************/
/* Framework / Drivers */
#include "TimersManager.h"
#include "FunctionLib.h"
#include "fsl_os_abstraction.h"
#include "shell.h"
#include "Panic.h"
#include "MemManager.h"
#include "board.h"

/* BLE Host Stack */
#include "ble_shell.h"
#include "gatt_interface.h"
#include "gatt_server_interface.h"
#include "gatt_client_interface.h"
#include "gatt_db_app_interface.h"
#include "gatt_db_dynamic.h"
#include "gap_interface.h"
#include "l2ca_interface.h"

#include "shell_gattdb.h"
#include "ApplMain.h"
#include "shell_thrput.h"
#include "dynamic_gatt_database.h"

#include <string.h>
#include <stdlib.h>

#if MULTICORE_HOST
    #define UUID128(name, ...) extern uint8_t name[16];
    #include "gatt_uuid128.h"
    #undef UUID128
    #include "erpc_host.h"
#else
    #define UUID128(name, ...) uint8_t name[16] = { __VA_ARGS__ };
    #include "gatt_uuid128.h"
    #undef UUID128
#endif

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#define mShellThrBufferCountDefault_c       1000
#define mShellThrBufferSizeDefault_c        20
#define mShellThrBufferSizeMax_c            244
#define mShellThrTxInterval_c              (4) /* ms */

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
/* Command structure type definition */
typedef struct thrCmds_tag
{
    char*       name;
    int8_t      (*cmd)(uint8_t argc, char * argv[]); 
}thrCmds_t;

/* GAP roles type definition */
typedef enum thrGapRoles_tag
{
    thrNone = 0,
    thrCentral,
    thrPeripheral,
} thrGapRoles_t;

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/
static void ShellThr_StartThroughputTest(thrGapRoles_t role);
static void ShellThr_PrintReport(appCallbackParam_t p);
static void ShellThr_CheckResults(void* p);
static bool_t ShellThr_CheckScanEvent(gapScannedDevice_t* pData);
static bool_t ShellThr_MatchDataInAdvElementList(gapAdStructure_t *pElement, void *pData, uint8_t iDataLen);

/* LE Callbacks */
static void ShellThr_AdvertisingCallback(gapAdvertisingEvent_t* pAdvertisingEvent);
static void ShellThr_ConnectionCallback(deviceId_t peerDeviceId, gapConnectionEvent_t* pConnectionEvent);
static void ShellThr_ScanningCallback (gapScanningEvent_t* pScanningEvent);

/* Shell API Functions */
static int8_t ShellThr_SetParams(uint8_t argc, char * argv[]);
static int8_t ShellThr_Start(uint8_t argc, char * argv[]);
static int8_t ShellThr_Stop(uint8_t argc, char * argv[]);

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/* Throughput test shell commands */
const thrCmds_t mThrShellCmds[] = 
{
    {"setparam",      ShellThr_SetParams},
    {"start",         ShellThr_Start},
    {"stop",          ShellThr_Stop},
};

/* GAP role */
static thrGapRoles_t mThrShellRole = thrNone;

/* Adverising status */
static bool_t mAdvOn = FALSE;

/* Scanning status */
static bool_t mScanningOn = FALSE;

/* GAP connection params */
static gapConnectionParameters_t mConnectionParams;

/* pair device to connect to was found */
static bool_t   mFoundDeviceToConnect = FALSE;

/* stores the last received notifications count */
static uint16_t mLastNotifRecv = 0;

/* Throughput test configuration structure */
thrConfig_t gTroughputConfig = 
{
    .buffCnt = mShellThrBufferCountDefault_c,
    .buffSz =  mShellThrBufferSizeDefault_c,
    .pBuff = NULL
};

/* Scanning and Advertising Data */
static const uint8_t adData0[1] =  { (gapAdTypeFlags_t)(gLeGeneralDiscoverableMode_c | gBrEdrNotSupported_c) };
static const gapAdStructure_t advScanStruct[3] = 
{
    {
        .length = NumberOfElements(adData0) + 1,
        .adType = gAdFlags_c,
        .aData = (uint8_t *)adData0
    },  
    {
        .length = NumberOfElements(uuid_service_throughput) + 1,
        .adType = gAdComplete128bitServiceList_c,
        .aData = (uint8_t *)uuid_service_throughput
    },  
    {
        .adType = gAdShortenedLocalName_c,
        .length = 8,
        .aData = (uint8_t*)"THR_PER"
    }  
};

static gapAdvertisingData_t gThrAdvertisingData = 
{
    NumberOfElements(advScanStruct),
    (void *)advScanStruct
};

static gapScanResponseData_t gThrScanRspData = 
{
    0,
    NULL
};

/* Default Advertising Parameters */
static gapAdvertisingParameters_t mAdvParams =
{
    /* minInterval */         1600 /* 1 s */,
    /* maxInterval */         1600 /* 1 s */,
    /* advertisingType */     gAdvConnectableUndirected_c,
    /* addressType */         gBleAddrTypePublic_c,
    /* directedAddressType */ gBleAddrTypePublic_c,
    /* directedAddress */     {0, 0, 0, 0, 0, 0},
    /* channelMap */          (gapAdvertisingChannelMapFlags_t) (gAdvChanMapFlag37_c | gAdvChanMapFlag38_c | gAdvChanMapFlag39_c),
    /* filterPolicy */        gProcessAll_c
};

/* Default Connection Request Parameters */
static gapConnectionRequestParameters_t mConnReqParams =
{
    .scanInterval = gGapScanIntervalDefault_d,
    .scanWindow = gGapScanWindowDefault_d,
    .filterPolicy = gUseDeviceAddress_c,
    .ownAddressType = gBleAddrTypePublic_c,
    .connIntervalMin = gGapDefaultMaxConnectionInterval_d,
    .connIntervalMax = gGapDefaultMaxConnectionInterval_d,
    .connLatency = gGapConnLatencyMin_d,
    .supervisionTimeout = gGapConnSuperTimeoutMax_d,
    .connEventLengthMin = gGapConnEventLengthMin_d,
    .connEventLengthMax = gGapConnEventLengthMax_d,
};

static gapScanningParameters_t mAppScanParams =
{
    /* type */              gScanTypePassive_c,
    /* interval */          gGapScanIntervalDefault_d,
    /* window */            gGapScanWindowDefault_d,
    /* ownAddressType */    gBleAddrTypePublic_c,
    /* filterPolicy */      gScanAll_c
};

static uint32_t loopCnt;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
/* Peer Device ID */
extern deviceId_t   gPeerDeviceId;
/* Variable used to indicate if the throughput test is in progress */
bool_t gTroughputInProgress = FALSE;
/* Timer used by the throughput test */
tmrTimerID_t gThroughputTestTimerId = gTmrInvalidTimerID_c;
/* Throughput test statistics */
thrStatistics_t gThrStatistics;

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
 * \brief        Throughput test command
 *
 * \param[in]    argc    shell argument count
 *
 * \param[in]    argv    shell argument value
 *
 * \return       -
 ********************************************************************************** */
int8_t ShellThrput_Command(uint8_t argc, char * argv[])
{
    uint8_t i;
    int8_t status = CMD_RET_USAGE;
    
    if (argc > 1)
    {
        for (i=0; i<NumberOfElements(mThrShellCmds); i++)
        {
            if(!strcmp((char*)argv[1], mThrShellCmds[i].name) )
            {
                status = mThrShellCmds[i].cmd(argc-2, (char **)(&argv[2]));
                break;
            }
        }
    }
    
    return status;
}

/************************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
 * \brief        Configure the throughput test variables
 *
 * \param[in]    argc    shell argument count
 *
 * \param[in]    argv    shell argument value
 *
 * \return       -
 ********************************************************************************** */
static int8_t ShellThr_SetParams(uint8_t argc, char * argv[])
{  
    int8_t result = CMD_RET_USAGE;
    bool_t bConfigChanged = FALSE;
    uint32_t i = 0;
    
    switch (argc)
    {
    case 0:
        {
            shell_write("No parameters set, using defaults: ");
            shell_writeDec(gTroughputConfig.buffCnt);
            shell_write(" buffers of ");
            shell_writeDec(gTroughputConfig.buffSz);
            shell_write(" bytes");
            shell_write("\n\r");
            result = CMD_RET_SUCCESS;
        }
        break;
        
    case 1:
        {
            shell_write("ERROR: Missing parameter value\n\r");
        }
        break;

    default:
        {
            /* Two or more params */
            while (argc > i)
            {
                if(!strcmp((char*)argv[i], "-c"))
                {
                    i++;
                    gTroughputConfig.buffCnt = (uint16_t)atoi(argv[i]);
                    i++;
                    result = CMD_RET_SUCCESS;
                    bConfigChanged = TRUE;
                }
                else if(!strcmp((char*)argv[i], "-s"))
                {
                    i++;
                    gTroughputConfig.buffSz = (uint8_t)atoi(argv[i]);
                    i++;
                    if(gTroughputConfig.buffSz > mShellThrBufferSizeMax_c)
                    {
                        gTroughputConfig.buffSz = mShellThrBufferSizeMax_c;
                    }
                    result = CMD_RET_SUCCESS;
                    bConfigChanged = TRUE;
                }
                else if(!strcmp((char*)argv[i], "-connint"))
                {
                    i++;
                    mConnReqParams.connIntervalMin = (uint16_t)atoi(argv[i]);
                    if (mConnReqParams.connIntervalMin < gGapConnIntervalMin_d)
                    {
                        mConnReqParams.connIntervalMin = gGapConnIntervalMin_d;
                    }
                    
                    i++;
                    mConnReqParams.connIntervalMax = (uint16_t)atoi(argv[i]);
                    if (mConnReqParams.connIntervalMax > gGapConnIntervalMax_d)
                    {
                        mConnReqParams.connIntervalMax = gGapConnIntervalMax_d;
                    }
                    i++;
                    result = CMD_RET_SUCCESS;
                    bConfigChanged = TRUE;
                }
                else
                {
                    /* Wrong input */
                    break;
                }
            } 
        }
    }
    
    if (bConfigChanged)
    {
        shell_write("Parameter set.\n\r"
                    "Current config: ");
        shell_writeDec(gTroughputConfig.buffCnt);
        shell_write(" buffers of ");
        shell_writeDec(gTroughputConfig.buffSz);
        shell_write(" bytes\n\r"
                    "Connection interval [min-max]: ");
        shell_writeDec(mConnReqParams.connIntervalMin);
        shell_write("-");
        shell_writeDec(mConnReqParams.connIntervalMax);
        shell_write("\n\r");
        result = CMD_RET_SUCCESS;
    }
    
    return result; 
}

/*! *********************************************************************************
 * \brief        Starts the throughput test
 *
 * \param[in]    argc    shell argument count
 *
 * \param[in]    argv    shell argument value
 *
 * \return       -
 ********************************************************************************** */
static int8_t ShellThr_Start(uint8_t argc, char * argv[])
{
    bleResult_t result;
    uint16_t    handle;
    int8_t      status = CMD_RET_SUCCESS;
    uint8_t     aInitialValue[] = {0x00};

    if (argc != 1) 
    {
        status = CMD_RET_USAGE;
    }
    else if (!strcmp((char*)argv[0], "rx"))
    {
        mThrShellRole = thrCentral;
        if (gPeerDeviceId == gInvalidDeviceId_c)
        {
            /* Start scanning if not in a connection */
            App_StartScanning(&mAppScanParams, ShellThr_ScanningCallback, TRUE);        
        }
        else
        {
            /* Allready in a connection */
            ShellThr_StartThroughputTest(mThrShellRole);
        }
    }
    else if (!strcmp((char*)argv[0], "tx")) /* GAP Peripheral */
    {
        mThrShellRole = thrPeripheral;
        
        if (gPeerDeviceId == gInvalidDeviceId_c)
        {
            /* Add service */
            result = GattDbDynamic_AddPrimaryServiceDeclaration(0, gBleUuidType128_c, 
                                                                (bleUuid_t*)uuid_service_throughput,
                                                                &handle);
            if (result == gBleSuccess_c)
            {
                /* Add characteristic */
                result = GattDbDynamic_AddCharacteristicDescriptor(gBleUuidType128_c,
                                                                   (bleUuid_t*)uuid_throughput_stream,
                                                                   sizeof(aInitialValue),
                                                                   aInitialValue,
                                                                   gPermissionFlagReadable_c,
                                                                   &handle);
            }
            
            if (result == gBleSuccess_c)
            {            
                /* Setup advertising data */
                result = Gap_SetAdvertisingData(&gThrAdvertisingData, &gThrScanRspData);    
            }
            
            if (result == gBleSuccess_c)
            {  
                /* Set advertising parameters*/
                result = Gap_SetAdvertisingParameters(&mAdvParams);
            }

            if (result == gBleSuccess_c)
            {  
                /* Start advertising */
                result = App_StartAdvertising(ShellThr_AdvertisingCallback, ShellThr_ConnectionCallback);
            }
            
            if (result != gBleSuccess_c)
            {
                status = CMD_RET_FAILURE;
            }
        }
        else
        {
            /* Allready in a connection */
            ShellThr_StartThroughputTest(mThrShellRole);
        }
    }
    else
    {
        status = CMD_RET_USAGE;
    }
    
    return status;
}

/*! *********************************************************************************
 * \brief        Stops the throughput test
 *
 * \param[in]    argc    shell argument count
 *
 * \param[in]    argv    shell argument value
 *
 * \return       -
 ********************************************************************************** */
static int8_t ShellThr_Stop(uint8_t argc, char * argv[])
{
    if (gTroughputInProgress)
    {
        /* Stop Advertising if needed */
        if (mAdvOn)
        {
            Gap_StopAdvertising();
        }
        
        /* Stop Scanning if needed */
        if (mScanningOn)
        {
            Gap_StopScanning();
        }
        
        /* Disconnect if needed */
        if (gPeerDeviceId != gInvalidDeviceId_c)
        {    
            Gap_Disconnect(gPeerDeviceId);
        }
        
        /* Stop timer */
        TMR_StopTimer(gThroughputTestTimerId);
        
        if(mThrShellRole == thrPeripheral) /* GAP Peripheral */
        {
            MEM_BufferFree(gTroughputConfig.pBuff);
        }
        
        shell_write("Throuhgput test stopped.\n\r");
        gTroughputInProgress = FALSE;
    }
    
    return CMD_RET_SUCCESS;
}

/*! *********************************************************************************
 * \brief        GAP peripheral send data function. Called from timer callback.
 *
 * \param[in]    p  ignored
 *
 * \return       -
 ********************************************************************************** */
static void ShellThr_SendData(void *p)
{   
    (void)p;   
    
    if(gTroughputConfig.pBuff)
    {    
        if(loopCnt >= gTroughputConfig.buffCnt)
        {
            /* stop timer */
            TMR_StopTimer(gThroughputTestTimerId);
            MEM_BufferFree(gTroughputConfig.pBuff);
            gTroughputConfig.pBuff = NULL;
            //shell_write("Throuhgput test stopped.\n\r");
        }
        else
        {
            FLib_MemCpy(gTroughputConfig.pBuff, &loopCnt, sizeof(loopCnt));
            
            if(gBleSuccess_c == GattServer_SendInstantValueNotification(gPeerDeviceId, value_throughput_stream, gTroughputConfig.buffSz, gTroughputConfig.pBuff))
            {
                loopCnt++;
            }
            else
            {
                gThrStatistics.droppedPackets++;
            }
            
        }    
    }
}

/*! *********************************************************************************
 * \brief        Handles BLE Advertising callback from host stack.
 *
 * \param[in]    pAdvertisingEvent    Pointer to gapAdvertisingEvent_t.
 ********************************************************************************** */
static void ShellThr_AdvertisingCallback
(
gapAdvertisingEvent_t* pAdvertisingEvent
)
{
    shell_write("\n\r-->  GAP Event: Advertising ");
    
    switch (pAdvertisingEvent->eventType)
    {
    case gAdvertisingStateChanged_c:
        {
            mAdvOn = !mAdvOn;
            
            if (mAdvOn)
            {
                shell_write("started.\n\r");
            }
            else
            {
                shell_write("stopped.\n\r");
            }
            break;
        }
        
    case gAdvertisingCommandFailed_c:
        {
            shell_write("state could not be changed.\n\r");
            break;
        }
        
    default:
        break;
    }
    
    //shell_cmd_finished();
}

/*! *********************************************************************************
 * \brief        Handles BLE Connection callback from host stack.
 *
 * \param[in]    peerDeviceId        Peer device ID.
 * \param[in]    pConnectionEvent    Pointer to gapConnectionEvent_t.
 ********************************************************************************** */
static void ShellThr_ConnectionCallback
(
deviceId_t peerDeviceId,
gapConnectionEvent_t* pConnectionEvent
)
{
    switch (pConnectionEvent->eventType)
    {
    case gConnEvtConnected_c:
        {
            gPeerDeviceId = peerDeviceId;
            shell_write("\n\r-->  GAP Event: Connected\n\r");
            //shell_cmd_finished();
            
            /* Save connection parameters */
            FLib_MemCpy(&mConnectionParams,
                        &pConnectionEvent->eventData.connectedEvent.connParameters,
                        sizeof(gapConnectionParameters_t));
            
            if (mThrShellRole == thrPeripheral)
            {
                gTroughputInProgress = TRUE;
                GattClient_ExchangeMtu(gPeerDeviceId);
            }
            else
            {
                ShellThr_StartThroughputTest(mThrShellRole);
            }
        }
        break;
        
    case gConnEvtDisconnected_c:
        {
            gPeerDeviceId = gInvalidDeviceId_c;
            shell_write("\n\r-->  GAP Event: Disconnected\n\r");
            //shell_cmd_finished();
        }
        break;    
        
    default:
        break;
    }
}

/*! *********************************************************************************
 * \brief        Handles BLE Scanning callback from host stack.
 *
 * \param[in]    pScanningEvent    Pointer to gapScanningEvent_t.
 ********************************************************************************** */
static void ShellThr_ScanningCallback (gapScanningEvent_t* pScanningEvent)
{
    switch (pScanningEvent->eventType)
    {
    case gDeviceScanned_c:
        {           
            mFoundDeviceToConnect = ShellThr_CheckScanEvent(&pScanningEvent->eventData.scannedDevice);
            if (mFoundDeviceToConnect)
            {        
                mConnReqParams.peerAddressType = pScanningEvent->eventData.scannedDevice.addressType;
                
                FLib_MemCpy(mConnReqParams.peerAddress, 
                            pScanningEvent->eventData.scannedDevice.aAddress,
                            sizeof(bleDeviceAddress_t));
                
                Gap_StopScanning();
            }
        }
        break;        
        
    case gScanStateChanged_c:
        {
            mScanningOn = !mScanningOn;
            
            shell_write("\n\r->  GAP Event: Scan ");
            if (mScanningOn)
            {                
                mFoundDeviceToConnect = FALSE;
                shell_write("started.\n\r");
            }
            else
            {
                shell_write("stopped.\n\r");
                
                if (mFoundDeviceToConnect)
                {
                    App_Connect(&mConnReqParams, ShellThr_ConnectionCallback);
                }
            }
            //shell_cmd_finished();
            break;
        }
        
    case gScanCommandFailed_c:
        {
            shell_write("\n\r-->  GAP Event: Scan state could not be changed.");
            //shell_cmd_finished();
            break;
        }
    default:
        break;
    }
}

/*! *********************************************************************************
 * \brief        Checks scan event. Search for Temperature Custom Service.
 *
 * \param[in]    pData       Pointer to scanned device information structure
 *
 * \return       TRUE if temperature custom service is found, FALSE otherwise
 ********************************************************************************** */
static bool_t ShellThr_CheckScanEvent(gapScannedDevice_t* pData)
{
    uint8_t index = 0;
    uint8_t name[10];
    uint8_t nameLength = 0;
    bool_t foundMatch = FALSE;
    
    while (index < pData->dataLength)
    {
        gapAdStructure_t adElement;
        
        adElement.length = pData->data[index];
        adElement.adType = (gapAdType_t)pData->data[index + 1];
        adElement.aData = &pData->data[index + 2];
        
        /* Search for Temperature Custom Service */
        if ((adElement.adType == gAdIncomplete128bitServiceList_c) ||
            (adElement.adType == gAdComplete128bitServiceList_c))
        {
            foundMatch = ShellThr_MatchDataInAdvElementList(&adElement, &uuid_service_throughput, 16);
        }
        
        if ((adElement.adType == gAdShortenedLocalName_c) ||
            (adElement.adType == gAdCompleteLocalName_c))
        {
            nameLength = MIN(adElement.length, 10);
            FLib_MemCpy(name, adElement.aData, nameLength);
        }
        
        /* Move on to the next AD element type */
        index += adElement.length + sizeof(uint8_t);
    }
    
    if (foundMatch)
    {
        /* UI */
        shell_write("\r\nFound device: \r\n");
        shell_writeN((char*)name, nameLength-1);
        SHELL_NEWLINE();
        shell_writeHex(pData->aAddress, 6);
    }
    return foundMatch;
}

/*! *********************************************************************************
 * \brief        Search if a particular data is present in a specified AD 
 *               structure list
 *
 * \param[in]    pElement    Pointer to AD structure list
 *
 * \param[in]    pData       Pointer to data to be searched.
 *
 * \param[in]    iDataLen    AD data lenght
 *
 * \return       TRUE if data is found, FALSE otherwise
 ********************************************************************************** */
static bool_t ShellThr_MatchDataInAdvElementList(gapAdStructure_t *pElement, 
                                                 void *pData, 
                                                 uint8_t iDataLen)
{ 
    uint8_t i;
    bool_t status = FALSE;
    
    for (i=0; i < pElement->length; i+=iDataLen)
    {
        if (FLib_MemCmp(pData, &pElement->aData[i], iDataLen))
        {
            status = TRUE;
            break;
        } 
    }    
    return status;
}

/*! *********************************************************************************
 * \brief        Starts throughput test
 *
 * \param[in]    role    GAP role of the device
 ********************************************************************************** */
static void ShellThr_StartThroughputTest(thrGapRoles_t role)
{
    /* Allocate throughput test timer */
    if(gTmrInvalidTimerID_c == gThroughputTestTimerId)
    {
        gThroughputTestTimerId = TMR_AllocateTimer();
    }
    
    if (role == thrCentral) // GAP Central
    {
        gThrStatistics.notifRcv = 0;
        gThrStatistics.firstPacketTs = 0;
        gThrStatistics.lastPacketTs = 0;
        
        if(gTmrInvalidTimerID_c != gThroughputTestTimerId)
        {
            TMR_StartIntervalTimer(gThroughputTestTimerId, gShell_ThoroughputReportTimeout_c, ShellThr_CheckResults, NULL);
            shell_write("Throughput test started.\n\rReceiving packets...\n\r");
            gTroughputInProgress = TRUE;
        }
        else
        {
            shell_write("ERROR: Invalid timer ID\n\r");
        }
    }
    else // GAP Peripheral
    {
        loopCnt = 0;
        
        if(NULL == gTroughputConfig.pBuff)
        {
            /* Allocate throughput test buffer */
            if((gTroughputConfig.pBuff = MEM_BufferAlloc(gTroughputConfig.buffSz)) == NULL)
            {
                shell_write("ERROR: Cannot allocate buffer.\n\r");
            }       
        }
        
        if (gTmrInvalidTimerID_c != gThroughputTestTimerId)
        {      
            TMR_StartIntervalTimer(gThroughputTestTimerId, mShellThrTxInterval_c, ShellThr_SendData, NULL); 
            shell_write("Throughput test started.\n\rSending packets...\n\r");
        }
        else
        {
            shell_write("ERROR: Invalid timer ID\n\r");
        }
    }
}

/*! *********************************************************************************
* \brief  Checks if the throughput test has ended. 
*
* \param[in] p           Ignored. Can be NULL.
*
* \return  -
*
* \remarks Called from TMR (callback) context
*
********************************************************************************** */
static void ShellThr_CheckResults(void* p)
{
    (void)p;
    
    if(mLastNotifRecv == gThrStatistics.notifRcv)
    {      
        /* stop timer */
        TMR_StopTimer(gThroughputTestTimerId);
        /* post message to application task */
        App_PostCallbackMessage(ShellThr_PrintReport, NULL);
    }
    else
    {
        mLastNotifRecv = gThrStatistics.notifRcv;
    }
}

/*! *********************************************************************************
* \brief  Prints the throughput test report
*
* \param[in] pParam           Ignored. Can be NULL.
*
* \return  -
*
* \remarks This function is executed in the context of the Application Task.
*
********************************************************************************** */
static void ShellThr_PrintReport(appCallbackParam_t pParam)
{ 
    (void)pParam;
    
    if (gThrStatistics.notifRcv == 0)
    {
        shell_write("No data received.\n\r");
    }
    else
    {
        shell_write("\r\n************************************\r\n"
                        "*********** TEST REPORT ************\r\n"
                        "************************************\r\n"
                    "\r\nPackets received: ");
        shell_writeDec(gThrStatistics.notifRcv);
        shell_write("\r\nTotal bytes: ");
        shell_writeDec(gThrStatistics.bytesRcv);
        shell_write("\r\nReceive duration: ");
        shell_writeDec((gThrStatistics.lastPacketTs - gThrStatistics.firstPacketTs)/1000);
        shell_write(" ms\r\n"
                    "Average bitrate: ");
        shell_writeDec(gThrStatistics.bytesRcv*8/((gThrStatistics.lastPacketTs - gThrStatistics.firstPacketTs)/1000));
        shell_write(" kbps \r\n"
                    "\r\n************************************\r\n"
                        "********** END OF REPORT ***********\r\n"
                        "************************************\r\n");
        
        gThrStatistics.notifRcv = 0;
        mLastNotifRecv = gThrStatistics.notifRcv;
    }
}

/*! *********************************************************************************
 * \brief  Updates statistics. Restart the report timer
 *
 * \remarks This function is executed in the context of the Application Task.
 *
 ********************************************************************************** */
void ShellThr_ProcessNotification(uint32_t len)
{
    if ( 0 == gThrStatistics.notifRcv )
    {
        gThrStatistics.firstPacketTs = TMR_GetTimestamp();
        gThrStatistics.bytesRcv = 0;
        /* Restart the timer */
        TMR_StartIntervalTimer(gThroughputTestTimerId, gShell_ThoroughputReportTimeout_c, ShellThr_CheckResults, NULL);
    }

    gThrStatistics.lastPacketTs = TMR_GetTimestamp();
    gThrStatistics.notifRcv++;
    gThrStatistics.bytesRcv += len;
}

/*! *********************************************************************************
 * \brief  Signals that the MTU Exchange procedure has been completed.
 *
 * \remarks This function is executed in the context of the Application Task.
 *
 ********************************************************************************** */
void ShellThr_MtuExchangeCallback(void)
{
    ShellThr_StartThroughputTest(mThrShellRole);
}
/* EOF */
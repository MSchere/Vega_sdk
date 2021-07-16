/*! *********************************************************************************
* \addtogroup HCI
* @{
********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "MemManager.h"

#include "ble_general.h"
#include "hci_transport.h"

#include "rpmsg_lite.h"
#include "mcmgr.h"

#include "fsl_debug_console.h"

/************************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
************************************************************************************/
#if (defined(gUseHciTransportDownward_d) && (gUseHciTransportDownward_d > 0U))
#define HCI_DEBUG 0
#else
#define HCI_DEBUG 0
#endif
#define APP_RPMSG_READY_EVENT_DATA     (1)
#define APP_RPMSG_EP_READY_EVENT_DATA  (2)

/************************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
************************************************************************************/
typedef PACKED_STRUCT hciCommandPacketHeader_tag
{
    uint16_t    opCode;
    uint8_t     parameterTotalLength;
}hciCommandPacketHeader_t;

typedef PACKED_STRUCT hciAclDataPacketHeader_tag
{
    uint16_t    handle      :12;
    uint16_t    pbFlag      :2;
    uint16_t    bcFlag      :2;
    uint16_t    dataTotalLength;
}hciAclDataPacketHeader_t;

typedef PACKED_STRUCT hciEventPacketHeader_tag
{
    hciEventCode_t  eventCode;
    uint8_t     dataTotalLength;
}hciEventPacketHeader_t;

typedef PACKED_STRUCT hcitPacketHdr_tag
{
    hciPacketType_t packetTypeMarker;
    PACKED_UNION
    {
        hciAclDataPacketHeader_t    aclDataPacket;
        hciEventPacketHeader_t      eventPacket;
        hciCommandPacketHeader_t    commandPacket;
    };
}hcitPacketHdr_t;

typedef PACKED_STRUCT hcitPacketStructured_tag
{
    hcitPacketHdr_t header;
    uint8_t         payload[gHcitMaxPayloadLen_c];
} hcitPacketStructured_t;

typedef PACKED_UNION hcitPacket_tag
{
    /* The entire packet as unformatted data. */
    uint8_t raw[sizeof(hcitPacketStructured_t)];
}hcitPacket_t;

typedef struct hcitComm_tag
{
    hcitPacket_t        *pPacket;
    hcitPacketHdr_t     pktHeader;
    uint16_t            bytesReceived;
    uint16_t            expectedLength;
}hcitComm_t;

typedef uint8_t detectState_t;
typedef enum{
    mDetectMarker_c       = 0,
    mDetectHeader_c,
    mPacketInProgress_c
}detectState_tag;

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/
static bool_t   mHcitInit = FALSE;

static hcitComm_t mHcitData;
static hciTransportInterface_t  mTransportInterface;

static detectState_t  mPacketDetectStep;

static hcitPacket_t mHcitPacketRaw;

struct rpmsg_lite_ept_static_context my_ept_context;
struct rpmsg_lite_endpoint *my_ept;
struct rpmsg_lite_instance rpmsg_ctxt;
struct rpmsg_lite_instance *my_rpmsg;

volatile int has_received;

#if (defined(gUseHciTransportUpward_d) && (gUseHciTransportUpward_d > 0U))

extern uint32_t startupData;

#elif (defined(gUseHciTransportDownward_d) && (gUseHciTransportDownward_d > 0U))

#if defined(__ICCARM__) /* IAR Workbench */
#pragma location = "rpmsg_sh_mem_section"
char rpmsg_lite_base[SH_MEM_TOTAL_SIZE];
#elif defined(__GNUC__) /* LPCXpresso */
char rpmsg_lite_base[SH_MEM_TOTAL_SIZE] __attribute__((section(".noinit.$rpmsg_sh_mem")));
#elif defined(__CC_ARM) /* Keil MDK */
char rpmsg_lite_base[SH_MEM_TOTAL_SIZE] __attribute__((section("rpmsg_sh_mem_section")));
#else
#error "RPMsg: Please provide your definition of rpmsg_lite_base[]!"
#endif
volatile uint16_t RPMsgRemoteReadyEventData = 0;
#else
#endif

/************************************************************************************
*************************************************************************************
* Private functions prototypes
*************************************************************************************
************************************************************************************/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
#if gUseHciTransportDownward_d
    osaSemaphoreId_t gHciDataBufferingSem;
#endif /* gUseHciTransportDownward_d */

/************************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
************************************************************************************/

static inline void Hcit_SendMessage(void)
{
    /* Send the message to HCI */
    mTransportInterface( mHcitData.pktHeader.packetTypeMarker,
                                mHcitData.pPacket,
                                mHcitData.bytesReceived);

    mHcitData.pPacket = NULL;
    mPacketDetectStep = mDetectMarker_c;
}

extern WEAK bleResult_t Ble_HciRecv
    (
        hciPacketType_t packetType,
        void* pHciPacket,
        uint16_t hciPacketLength
    );

/* This is the read callback, note we are in a task context when this callback
is invoked, so kernel primitives can be used freely */
static int my_ept_read_cb(void *payload, int payload_len, unsigned long src, void *priv)
{
    int *has_received = priv;
    uint8_t*        buffer = (uint8_t*)payload;
    uint16_t        count = payload_len;
    uint8_t         recvChar = buffer[0];

#if HCI_DEBUG
    PRINTF("READ <- ");
    for (int i = 0;i < payload_len; i++)
    {
        PRINTF("%02X ", buffer[i]);
    }
    PRINTF("\r\n");
#endif
    while( count )
    {
        switch( mPacketDetectStep )
        {
            case mDetectMarker_c:
                if( (recvChar == gHciDataPacket_c) || (recvChar == gHciEventPacket_c) ||
                    (recvChar == gHciCommandPacket_c) )
                {
                    mHcitData.pPacket = (hcitPacket_t*)&mHcitData.pktHeader;

                    mHcitData.pktHeader.packetTypeMarker = (hciPacketType_t)recvChar;
                    mHcitData.bytesReceived = 1;

                    mPacketDetectStep = mDetectHeader_c;
                }
                break;

            case mDetectHeader_c:
                mHcitData.pPacket->raw[mHcitData.bytesReceived++] = recvChar;
                switch( mHcitData.pktHeader.packetTypeMarker )
                {
                    case gHciDataPacket_c:
                        /* ACL Data Packet */
                        if( mHcitData.bytesReceived == (gHciAclDataPacketHeaderLength_c + 1) )
                        {
                            /* Validate ACL Data packet length */
                            if( mHcitData.pktHeader.aclDataPacket.dataTotalLength > gHcLeAclDataPacketLengthDefault_c )
                            {
                                mHcitData.pPacket = NULL;
                                mPacketDetectStep = mDetectMarker_c;
                                break;
                            }
                            mHcitData.expectedLength = gHciAclDataPacketHeaderLength_c +
                                                       mHcitData.pktHeader.aclDataPacket.dataTotalLength;

                            mPacketDetectStep = mPacketInProgress_c;
                        }
                        break;

                    case gHciEventPacket_c:
                        /* HCI Event Packet */
                        if( mHcitData.bytesReceived == (gHciEventPacketHeaderLength_c + 1) )
                        {
                            /* Validate HCI Event packet length
                            if( mHcitData.pktHeader.eventPacket.dataTotalLength > gHcEventPacketLengthDefault_c )
                            {
                                mHcitData.pPacket = NULL;
                                mPacketDetectStep = mDetectMarker_c;
                                break;
                            } */
                            mHcitData.expectedLength = gHciEventPacketHeaderLength_c +
                                                       mHcitData.pktHeader.eventPacket.dataTotalLength;
                            mPacketDetectStep = mPacketInProgress_c;
                        }
                        break;

                    case gHciCommandPacket_c:
                        /* HCI Command Packet */
                        if( mHcitData.bytesReceived == (gHciCommandPacketHeaderLength_c + 1) )
                        {

                            mHcitData.expectedLength = gHciCommandPacketHeaderLength_c +
                                                       mHcitData.pktHeader.commandPacket.parameterTotalLength;
                            mPacketDetectStep = mPacketInProgress_c;
                        }
                        break;
                    case gHciSynchronousDataPacket_c:
                    default:
                        /* Not Supported */
                        break;
                }

                if( mPacketDetectStep == mPacketInProgress_c )
                {
                    mHcitData.pPacket = &mHcitPacketRaw;
                    FLib_MemCpy(mHcitData.pPacket, (uint8_t*)&mHcitData.pktHeader + 1, sizeof(hcitPacketHdr_t) - 1);
                    mHcitData.bytesReceived -= 1;

                    if( mHcitData.bytesReceived == mHcitData.expectedLength )
                    {
                        Hcit_SendMessage();
                    }
                }
                break;

            case mPacketInProgress_c:
                mHcitData.pPacket->raw[mHcitData.bytesReceived++] = recvChar;

                if( mHcitData.bytesReceived == mHcitData.expectedLength )
                {
                    Hcit_SendMessage();
                }
                break;

            default:
                break;
        }
        count --;
        buffer++;
        recvChar = buffer[0];
    }
    if (has_received)
    {
        *has_received = 1;
    }
    return RL_RELEASE;
}

static void RPMsgRemoteReadyEventHandler(uint16_t eventData, void *context)
{
    uint16_t *data = (uint16_t*)context;

    *data = eventData;
}

/*! *********************************************************************************
* \brief
*
* \param[in]
*
* \param[out]
*
* \return
*
* \pre
*
* \remarks
*
********************************************************************************** */
bleResult_t Hcit_Init( hcitConfigStruct_t* hcitConfigStruct )
{
    bleResult_t result = gHciSuccess_c;

    if( mHcitInit == FALSE )
    {
#if gUseHciTransportDownward_d
        gHciDataBufferingSem = OSA_SemaphoreCreate(0);

        if (gHciDataBufferingSem == NULL)
        {
            return gHciTransportError_c;
        }
#endif /* gUseHciTransportDownward_d */

        /* Initialize HCI Transport interface */
        mTransportInterface = hcitConfigStruct->transportInterface;

#if (defined(gUseHciTransportDownward_d) && (gUseHciTransportDownward_d > 0U))

        /* Register the application event before starting the secondary core */
        MCMGR_RegisterEvent(kMCMGR_RemoteApplicationEvent, RPMsgRemoteReadyEventHandler, (void *)&RPMsgRemoteReadyEventData);
#if 0
        /* Wait until the secondary core application signals the rpmsg remote has been initialized and is ready to communicate. */
        while(APP_RPMSG_READY_EVENT_DATA != RPMsgRemoteReadyEventData) {};
#endif
        my_rpmsg = rpmsg_lite_master_init(rpmsg_lite_base, SH_MEM_TOTAL_SIZE, RPMSG_LITE_LINK_ID, RL_NO_FLAGS, &rpmsg_ctxt);

        my_ept = rpmsg_lite_create_ept(my_rpmsg, LOCAL_EPT_ADDR, my_ept_read_cb, (void *)&has_received, &my_ept_context);

        /* Wait until the secondary core application signals the rpmsg remote endpoint has been created. */
        while(APP_RPMSG_EP_READY_EVENT_DATA != RPMsgRemoteReadyEventData) {};

#elif (defined(gUseHciTransportUpward_d) && (gUseHciTransportUpward_d > 0U))

        my_rpmsg = rpmsg_lite_remote_init((void *)startupData, RPMSG_LITE_LINK_ID, RL_NO_FLAGS, &rpmsg_ctxt);

        /* Signal the other core we are ready by triggering the event and passing the APP_RPMSG_READY_EVENT_DATA */
        MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, APP_RPMSG_READY_EVENT_DATA);
#if ((defined(CPU_RV32M1_zero_riscy) || defined(CPU_RV32M1_cm0plus)) && (!MULTICORE_BLACKBOX))
        Board_NotifyRemotePrimaaryCore();
#endif
        while (!rpmsg_lite_is_link_up(my_rpmsg)) {};

        my_ept = rpmsg_lite_create_ept(my_rpmsg, LOCAL_EPT_ADDR, my_ept_read_cb, (void *)&has_received, &my_ept_context);

        /* Signal the other core the endpoint has been created by triggering the event and passing the APP_RPMSG_READY_EP_EVENT_DATA */
        MCMGR_TriggerEvent(kMCMGR_RemoteApplicationEvent, APP_RPMSG_EP_READY_EVENT_DATA);

#else

#endif
        /* Flag initialization on module */
        mHcitInit = TRUE;
    }
    else
    {
        /* Module has already been initialized */
        result = gHciAlreadyInit_c;
    }

    return result;
}

/*! *********************************************************************************
* \brief
*
* \param[in]
*
* \param[out]
*
* \return
*
* \pre
*
* \remarks
*
********************************************************************************** */
bleResult_t Hcit_SendPacket
    (
        hciPacketType_t packetType,
        void*           pPacket,
        uint16_t        packetSize
    )
{
    uint8_t*        pSerialPacket = NULL;
    bleResult_t     result = gBleSuccess_c;
    bleResult_t     status = gBleSuccess_c;

    pSerialPacket = MEM_BufferAlloc(1+packetSize);
    if( NULL != pSerialPacket )
    {
        pSerialPacket[0] = packetType;
        FLib_MemCpy(pSerialPacket+1, (uint8_t*)pPacket, packetSize);

#if HCI_DEBUG
        PRINTF("WRITE -> ");
        for (int i = 0;i < (1 + packetSize); i++)
        {
            PRINTF("%02X ", pSerialPacket[i]);
        }
        PRINTF("\r\n");
#endif
        status = (bleResult_t)rpmsg_lite_send(my_rpmsg, my_ept, REMOTE_EPT_ADDR, (char *)pSerialPacket, 1+packetSize, RL_BLOCK);

        if( gBleSuccess_c != status )
        {
            result = gHciTransportError_c;
        }
        MEM_BufferFree(pSerialPacket);
    }
    else
    {
        result = gBleOutOfMemory_c;
    }

    return result;
}

/*! *********************************************************************************
* \brief
*
* \param[in]
*
* \param[out]
*
* \return
*
* \pre
*
* \remarks
*
********************************************************************************** */
bleResult_t Hcit_RecvPacket
    (
        void*           pPacket,
        uint16_t        packetSize
    )
{
    bleResult_t result = gHciSuccess_c;

    uint8_t* aData = (uint8_t*) pPacket;
    uint8_t type = aData[0];

    if (type != 0x01 && type != 0x02 && type != 0x04)
    {
        result = /* Something more meaningful? */ gHciTransportError_c;
    }
    else
    {
        hciPacketType_t packetType = (hciPacketType_t) type;
        result = Ble_HciRecv
        (
            packetType,
            aData + 1,
            packetSize - 1
        );

        MEM_BufferFree( pPacket );  ///TODO: Verify here in FSCI
    }

    return result;
}

/*! *********************************************************************************
* @}
********************************************************************************** */

/*! *********************************************************************************
 * \defgroup CONTROLLER - Controller Interface
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

#ifndef _CONTROLLER_INTERFACE_H_
#define _CONTROLLER_INTERFACE_H_

#ifndef CPU_QN908X

/************************************************************************************
*************************************************************************************
* Include
*************************************************************************************
************************************************************************************/
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"
#include "ble_general.h"


/************************************************************************************
*************************************************************************************
* Public macros
*************************************************************************************
************************************************************************************/

#define Controller_SetAdvertisingTxPowerLevel(level) \
    Controller_SetTxPowerLevel(level,gAdvTxChannel_c)

#define Controller_SetConnectionTxPowerLevel(level) \
    Controller_SetTxPowerLevel(level,gConnTxChannel_c)

/************************************************************************************
*************************************************************************************
* Structures/Data Types
*************************************************************************************
************************************************************************************/

typedef enum txChannelType_tag {
    gAdvTxChannel_c,
    gConnTxChannel_c
} txChannelType_t;

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
************************************************************************************/
extern osaEventId_t mControllerTaskEvent;
extern bool_t gActivateHybridMode;
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*! *********************************************************************************
 * \brief  Sets the BD_ADDR.
 * \param[in]  packetType HCI packet Type
 *
 * \return gBleSuccess_c, gBleInvalidState_c or gBleInvalidParameter_c
 ********************************************************************************** */
bleResult_t Controller_SetDeviceAddress(uint8_t* bdAddr);

/*! *********************************************************************************
 * \brief  Controller Get Next instance
 * \param[in]  pNextInstant Pointer to the calculated_instant CE instant
 *   for applying new channel map or for updating connection parameters.
 * \return uint16_t
 ********************************************************************************** */
uint16_t Controller_GetNextInstance(uint16_t* pNextInstant);

/*! *********************************************************************************
 * \brief  Controller Get Inactivity Duration
 *
 * \return uint32_t
 ********************************************************************************** */
uint32_t Controller_GetInactivityDuration(void);

/*! *********************************************************************************
 * \brief  Sets the TX Power on the advertising or connection channel.
 * \param[in]  level    Power level (range 0-15) as defined in the table bellow.
 * \param[in]  channel  Advertising or connection channel.      
 *
 * \return gBleSuccess_c or error.
 *
 * \remarks This function executes synchronously.
 *
 * \remarks For MKW40Z BLE controller there are 16 possible power levels 0 <= N <= 15 
 * for which the output power is distributed evenly between minimum and maximum power levels.
 * For further details see the silicon datasheet.
 *
 * \remarks For MKW41Z BLE controller there are 32 possible power levels 0 <= N <= 31 
 * for which the output power is distributed evenly between minimum and maximum power levels.
 * For further details see the silicon datasheet.
 ********************************************************************************** */
bleResult_t Controller_SetTxPowerLevel(uint8_t level, txChannelType_t channel);

#ifdef __cplusplus
}
#endif 



/* ******************************************************************************** */
/* ******************************************************************************** */
/* ******************************************************************************** */
#else /* CPU_QN908X */

#include "hci_transport.h"
#include "fsl_power.h"

void        Controller_TaskHandler(void* handler);

void        BLE_Init(uint8_t max_ble_devices);

/*
 * @brief Send deep sleep command to controller
 * @retunr: the sleep mode the controller will enter
 */
power_mode_t BLE_sleep(void);

/*
 * @brief Get the sleep mode allowed by BLE Controller
 *        No sleep command is executed.
 * @return: the sleep mode the controller will enter
 */
power_mode_t BLE_get_sleep_mode(void);

/*
 * @brief Informs the controller deep sleep is not yet permited as wake-up is not finished.
 * The BLE controller will allow deep sleep once wake-up is finished.
 */
void BLE_prevent_sleep_on_wakeup(void);

/*
 * @brief Informs the controller deep sleep is permited.
 */
void BLE_enable_sleep(void);

/*
 * @brief Informs the controller deep sleep is NOT permited.
 */
void BLE_disable_sleep(void);

/*
 * @brief Enable the hardware WiFi coexistence mechanism in BLE controller.
 */
void BLE_EnableWlanCoex(void);

#endif /* CPU_QN908X */


#define BD_ADDR_SIZE 6

/************************************************************************************
 ************************************************************************************
 *                  Common header section, for all platforms                        *
 ************************************************************************************
 ***********************************************************************************/

typedef bleResult_t (*gHostHciRecvCallback_t)
(
    hciPacketType_t packetType,
    void* pHciPacket,
    uint16_t hciPacketLength
);

/*! *********************************************************************************
 * \brief  Performs initialization of the Controller.
 * \param[in]  callback HCI Host Receive Callback
 *
 * \return osaStatus_Success or osaStatus_Error
 ********************************************************************************** */
osaStatus_t Controller_Init(gHostHciRecvCallback_t callback);

/*! *********************************************************************************
 * \brief  Controller Receive Interface
 * \param[in]  packetType HCI packet Type
 * \param[in]  pPacket    data buffer      
 * \param[in]  packetSize data buffer length 
 *
 * \return gBleSuccess_c, gBleOutOfMemory_c or gBleInvalidParameter_c
 ********************************************************************************** */
bleResult_t Hci_SendPacketToController( hciPacketType_t packetType, void* pPacket, 
                                uint16_t packetSize);

#endif /* _CONTROLLER_INTERFACE_H_ */

/*! *********************************************************************************
* @}
********************************************************************************** */


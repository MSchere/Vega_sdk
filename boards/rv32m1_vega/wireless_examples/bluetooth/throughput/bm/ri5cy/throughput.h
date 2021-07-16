/*! *********************************************************************************
 * \defgroup Temperature Sensor
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
*
*
* This file is the interface file for the Throughput Peripheral application
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef _THROUGHPUT_PERIPHERAL_H_
#define _THROUGHPUT_PERIPHERAL_H_

/*************************************************************************************
**************************************************************************************
* Public macros
**************************************************************************************
*************************************************************************************/

/* Profile Parameters */

#define gReducedPowerMinAdvInterval_c   1600 /* 1 s */
#define gReducedPowerMaxAdvInterval_c   4000 /* 2.5 s */

#define gAdvTime_c                      10 /* 10 s*/
#define gScanningTime_c                 10   /* 10 s*/
#define gGoToSleepAfterDataTime_c       5 /* 5 s*/

/************************************************************************************
*************************************************************************************
* Public memory declarations
*************************************************************************************
********************************************************************************** */
extern gapAdvertisingData_t         gAppAdvertisingData;
extern gapScanResponseData_t        gAppScanRspData;
extern gapAdvertisingParameters_t   gAdvParams;
extern gapSmpKeys_t                 gSmpKeys;
extern gapPairingParameters_t       gPairingParameters;
extern gapDeviceSecurityRequirements_t deviceSecurityRequirements;
/************************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void BleApp_Init(void);
void BleApp_Start(gapRole_t mGapRole);
void BleApp_GenericCallback (gapGenericEvent_t* pGenericEvent);

#ifdef __cplusplus
}
#endif


#endif /* _THROUGHPUT_PERIPHERAL_L2CAP_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

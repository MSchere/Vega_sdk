/*! *********************************************************************************
 * \defgroup app
 * @{
 ********************************************************************************** */
/*! *********************************************************************************
* Copyright 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2017 NXP
* All rights reserved.
*
* 
*
* This file is the app configuration file which is pre included.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#ifndef _APP_PREINCLUDE_H_
#define _APP_PREINCLUDE_H_

/*! *********************************************************************************
 *  SDK Configuration
 ********************************************************************************** */

#define MBEDTLS_CONFIG_FILE "connectivity_mbedtls_config.h"

#define NVIC_EnableIRQ EnableIRQ
#define NVIC_DisableIRQ DisableIRQ
#define NVIC_ClearPendingIRQ(x)
#define __get_IPSR SystemInISR

#define FSL_CAU3_USE_HW_SEMA            0

#define ERPC_DEFAULT_BUFFER_SIZE 1024

#define SH_MEM_TOTAL_SIZE (6144)

#define RPMSG_LITE_LINK_ID (0)

#define REMOTE_EPT_ADDR (30)
#define LOCAL_EPT_ADDR  (40)

/* Address of memory, from which the secondary core will boot */
#define CORE1_BOOT_ADDRESS (void *)0x01000000

/*! *********************************************************************************
 *  Board Configuration
 ********************************************************************************** */
/* Defines the number of available keys for the keyboard module */
#define gKeyBoardSupported_d            1
#define gKBD_KeysCount_c                4

/* Specifies the number of physical LEDs on the target board */
#define gLEDSupported_d                 1
#define gLEDsOnTargetBoardCnt_c         4
#define gLED_InvertedMode_d             1

/*! *********************************************************************************
 *  Framework Configuration
 ********************************************************************************** */
#define gMWS_UseCoexistence_d           0

/* Defines Num of Serial Manager interfaces */
#define gSerialManagerMaxInterfaces_c   1

/* Defines Rx Buffer Size for Serial Manager */
#define gSerialMgrRxBufSize_c           1000

/* Defines Tx Queue Size for Serial Manager */
#define gSerialMgrTxQueueSize_c         30

/* Defines Size for Serial Manager Task*/
#define gSerialTaskStackSize_c          2048

/* Defines Size for Timer Task*/
#define gTmrTaskStackSize_c             2048

/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.*/
#define AppPoolsDetails_c \
         _block_size_  16  _number_of_blocks_     4 _eol_  \
         _block_size_  32  _number_of_blocks_    50 _eol_  \
         _block_size_  80  _number_of_blocks_    28 _eol_  \
         _block_size_ 128  _number_of_blocks_    28 _eol_  \
         _block_size_ 512  _number_of_blocks_    18 _eol_

/* Defines number of timers needed by the application */
#define gTmrApplicationTimers_c         6

/* Defines number of timers needed by the protocol stack */
#define gTmrStackTimers_c               3

/* Set this define TRUE if the PIT frequency is an integer number of MHZ */
#define gTMR_PIT_FreqMultipleOfMHZ_d    0

#define gTMR_PIT_Timestamp_Enabled_d    0

/* Enables / Disables the precision timers platform component */
#define gTimestamp_Enabled_d            0

/* Enable/Disable Low Power Timer */
#define gTMR_EnableLowPowerTimers       0

/* Enables / Disables the DCDC platform component */
#define gDCDC_Enabled_d                 1

/* Default DCDC Battery Level Monitor interval */
#define APP_DCDC_VBAT_MONITOR_INTERVAL  600000
#define gAppUseNvm_d                    0

/* NVM Module Configuration - gAppUseNvm_d shall be defined above as 1 or 0 */    
#if gAppUseNvm_d
    #define gNvmMemPoolId_c 1
    /* Defines NVM pools by block size and number of blocks. Must be aligned to 4 bytes.*/
    #define NvmPoolsDetails_c \
         _block_size_ 32   _number_of_blocks_    20 _pool_id_(1) _eol_ \
         _block_size_ 60   _number_of_blocks_    10 _pool_id_(1) _eol_ \
         _block_size_ 80   _number_of_blocks_    10 _pool_id_(1) _eol_ \
         _block_size_ 100  _number_of_blocks_    2 _pool_id_(1) _eol_
             
    /* configure NVM module */
    #define  gNvStorageIncluded_d                (1)
    #define  gNvFragmentation_Enabled_d          (1)
    #define  gUnmirroredFeatureSet_d             (1)
    #define  gNvRecordsCopiedBufferSize_c        (128)
#endif

/* Defines pools by block size and number of blocks. Must be aligned to 4 bytes.
 * DO NOT MODIFY THIS DIRECTLY. CONFIGURE AppPoolsDetails_c
 * If gMaxBondedDevices_c increases, adjust NvmPoolsDetails_c
*/
#if gAppUseNvm_d
    #define PoolsDetails_c \
         AppPoolsDetails_c \
         NvmPoolsDetails_c
#else
    #define PoolsDetails_c \
         AppPoolsDetails_c
#endif

/*! *********************************************************************************
 *  RTOS Configuration
 ********************************************************************************** */

 /* Defines the RTOS used */
#ifndef FSL_RTOS_FREE_RTOS
#define FSL_RTOS_FREE_RTOS
#endif

/* Defines the usage of the FreeRTOS IDLE task hook to enter low power */           
#define configUSE_IDLE_HOOK             0

/* Defines number of OS events used */
#define osNumberOfEvents                6

/* Defines main task stack size */
#define gMainThreadStackSize_c          3000

/* Defines total heap size used by the OS */
#define gTotalHeapSize_c                40000

/*! *********************************************************************************
 *  BLE Stack Configuration
 ********************************************************************************** */

/* Enable/Disable Dynamic GattDb functionality */
#define gGattDbDynamic_d                0

#define gUseHciTransportDownward_d      1

/* Defines Size for BLE Host Task */
#define gHost_TaskStackSize_c           2048

/*! *********************************************************************************
 *  Application Configuration
 ********************************************************************************** */

/*! Enable/disable use of bonding capability */
#define gAppUseBonding_d                0

/*! Enable/disable use of pairing procedure */
#define gAppUsePairing_d                0

/*! Enable/disable use of privacy */
#define gAppUsePrivacy_d                0

#define gPasskeyValue_c                 999999

#if (gAppUseBonding_d) && (!gAppUsePairing_d)
  #error "Enable pairing to make use of bonding"
#endif

#define gMaxServicesCount_d             10

#define MULTICORE_HOST                  0

/*! Maximum number of connections supported for this application */
#define gAppMaxConnections_c            8

#endif /* _APP_PREINCLUDE_H_ */

/*! *********************************************************************************
 * @}
 ********************************************************************************** */

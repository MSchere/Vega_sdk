/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* Copyright 2016-2018 NXP
* All rights reserved.
*
* 
*
* This is the source file for the security module that implements AES.
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */


/*! *********************************************************************************
*************************************************************************************
* Include
*************************************************************************************
********************************************************************************** */

#include "MemManager.h"
#include "FunctionLib.h"
#include "SecLib.h"
#include "fsl_device_registers.h"
#include "fsl_os_abstraction.h"
#include "Panic.h"
#include "RNG_Interface.h"

#if defined(FSL_FEATURE_SOC_LTC_COUNT) && (FSL_FEATURE_SOC_LTC_COUNT > 0)
#include "fsl_ltc.h"
#endif
#if defined(FSL_FEATURE_SOC_CAAM_COUNT) && (FSL_FEATURE_SOC_CAAM_COUNT > 0)
#include "fsl_caam.h"
#endif
#if defined(FSL_FEATURE_SOC_CAU3_COUNT) && (FSL_FEATURE_SOC_CAU3_COUNT > 0)
#include "fsl_cau3.h"
#endif
#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
#include "fsl_trng.h"
#elif defined(FSL_FEATURE_SOC_RNG_COUNT) && (FSL_FEATURE_SOC_RNG_COUNT > 0)
#include "fsl_rnga.h"
#endif

#ifndef cPWR_UsePowerDownMode
#define cPWR_UsePowerDownMode 0
#endif

#if (cPWR_UsePowerDownMode)
#include "PWR_Interface.h"
#endif

/* mbedTLS headers */
#include "ksdk_mbedtls.h"
#include "mbedtls/aes.h"
#include "mbedtls/cipher.h"
#include "mbedtls/cmac.h"
#include "mbedtls/ccm.h"
#include "mbedtls/sha1.h"
#include "mbedtls/sha256.h"
#include "mbedtls/md.h"
#include "mbedtls/ecdh.h"


/*! *********************************************************************************
*************************************************************************************
* Private macros
*************************************************************************************
********************************************************************************** */
#if (cPWR_UsePowerDownMode)
    #define SecLib_DisallowToSleep() PWR_DisallowDeviceToSleep()
    #define SecLib_AllowToSleep()    PWR_AllowDeviceToSleep()
#else
    #define SecLib_DisallowToSleep()
    #define SecLib_AllowToSleep()
#endif

#if USE_RTOS && \
    (FSL_FEATURE_SOC_LTC_COUNT || FSL_FEATURE_SOC_MMCAU_COUNT || FSL_FEATURE_SOC_CAU3_COUNT) && \
    gSecLibUseMutex_c
    #define SECLIB_MUTEX_LOCK()   OSA_MutexLock(mSecLibMutexId, osaWaitForever_c)
    #define SECLIB_MUTEX_UNLOCK() OSA_MutexUnlock(mSecLibMutexId)
#else
    #define SECLIB_MUTEX_LOCK()
    #define SECLIB_MUTEX_UNLOCK()
#endif /* USE_RTOS */

/*! *********************************************************************************
*************************************************************************************
* Private type definitions
*************************************************************************************
********************************************************************************** */
#if USE_RTOS && (FSL_FEATURE_SOC_LTC_COUNT || FSL_FEATURE_SOC_MMCAU_COUNT || FSL_FEATURE_SOC_CAU3_COUNT)
/*! Mutex used to protect the AES Context when an RTOS is used. */
osaMutexId_t mSecLibMutexId;
#endif /* USE_RTOS */

/************************************************************************************
*************************************************************************************
* Private memory declarations
*************************************************************************************
************************************************************************************/

/*! *********************************************************************************
*************************************************************************************
* Public prototypes
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Private prototypes
*************************************************************************************
********************************************************************************** */

/*! *********************************************************************************
*************************************************************************************
* Public functions
*************************************************************************************
********************************************************************************** */
/*!
 * @brief Application init for various Crypto blocks.
 *
 * This function is provided to be called by MCUXpresso SDK applications.
 * It calls basic init for Crypto Hw acceleration and Hw entropy modules.
 *
 * This function is modeled after CRYPTO_InitHardware in kskd_mbedtls.c
 * It includes additional configuration of the TRNG for faster entropy generation.
 */
void SecLib_InitHardwareConnectivity(void)
{
#if defined(FSL_FEATURE_SOC_LTC_COUNT) && (FSL_FEATURE_SOC_LTC_COUNT > 0)
    /* Initialize LTC driver.
     * This enables clocking and resets the module to a known state. */
    LTC_Init(LTC0);
#endif
#if defined(FSL_FEATURE_SOC_CAAM_COUNT) && (FSL_FEATURE_SOC_CAAM_COUNT > 0) && defined(CRYPTO_USE_DRIVER_CAAM)
    /* Initialize CAAM driver. */
    caam_config_t caamConfig;

    CAAM_GetDefaultConfig(&caamConfig);
    caamConfig.jobRingInterface[0] = &s_jrif0;
    caamConfig.jobRingInterface[1] = &s_jrif1;
    CAAM_Init(CAAM, &caamConfig);
#endif
#if defined(FSL_FEATURE_SOC_CAU3_COUNT) && (FSL_FEATURE_SOC_CAU3_COUNT > 0)
    /* Initialize CAU3 */
    CAU3_Init(CAU3);
#endif
    { /* Init RNG module.*/
#if defined(FSL_FEATURE_SOC_TRNG_COUNT) && (FSL_FEATURE_SOC_TRNG_COUNT > 0)
        trng_config_t trngConfig;

        /* 512 samples * 3200 clocks_per_sample ~ 1600000 clocks ~ 8ms @200Mhz */
        /* uint32_t clocks_per_sample = 3200u; */ /* default clocks to generate each bit of entropy */
        uint32_t clocks_per_sample =
            800u;                /* default clocks 3200 @200 MHz scaled down to 48 MHz to generate each bit of entropy */
        uint32_t samples = 512u; /* number of bits to generate and test */
        int32_t freq_min = 0;
        int32_t freq_max = 0;
        int32_t mono_min = 195;
        int32_t mono_max = 317;
        int32_t poker_min = 1031;
        int32_t poker_max = 1600;
        int32_t retries = 1;  /* if self-test fails, allow 1 retry */
        int32_t lrun_max = 32;
        int32_t run_1_min = 27;
        int32_t run_1_max = 107;
        int32_t run_2_min = 7;
        int32_t run_2_max = 62;
        int32_t run_3_min = 0;
        int32_t run_3_max = 39;
        int32_t run_4_min = 0;
        int32_t run_4_max = 26;
        int32_t run_5_min = 0;
        int32_t run_5_max = 18;
        int32_t run_6_min = 0;
        int32_t run_6_max = 17;

        /* Set freq_min and freq_max based on clocks_per_sample */
        freq_min = clocks_per_sample / 4u;
        freq_max = clocks_per_sample * 16u;

        TRNG_GetDefaultConfig(&trngConfig);

        trngConfig.frequencyCountLimit.minimum = freq_min;
        trngConfig.frequencyCountLimit.maximum = freq_max;
        trngConfig.entropyDelay = clocks_per_sample;
        trngConfig.sampleSize = samples;

        /* Load new statistical test values */
        /*RNG TRNG Poker Maximum Limit Register (RTPKRMAX) defines Maximum
          Limit allowable during the TRNG Statistical Check Poker Test. Note
          that this address (0xBASE_060C) is used as RTPKRMAX only if
          RTMCTL[PRGM] is 1. If RTMCTL[PRGM] is 0, this address is used as
          RTPKRSQ readback register, as described in the next
          section. a.k.a. poker sum square register*/

        trngConfig.retryCount = retries;
        trngConfig.longRunMaxLimit = lrun_max;
        trngConfig.pokerLimit.maximum = poker_max;
        trngConfig.pokerLimit.minimum = poker_min - 1;
        trngConfig.monobitLimit.maximum = mono_max;
        trngConfig.monobitLimit.minimum = mono_min;
        trngConfig.runBit1Limit.maximum = run_1_max;
        trngConfig.runBit1Limit.minimum = run_1_min;
        trngConfig.runBit2Limit.maximum = run_2_max;
        trngConfig.runBit2Limit.minimum = run_2_min;
        trngConfig.runBit3Limit.maximum = run_3_max;
        trngConfig.runBit3Limit.minimum = run_3_min;
        trngConfig.runBit4Limit.maximum = run_4_max;
        trngConfig.runBit4Limit.minimum = run_4_min;
        trngConfig.runBit5Limit.maximum = run_5_max;
        trngConfig.runBit5Limit.minimum = run_5_min;
        trngConfig.runBit6PlusLimit.maximum = run_6_max;
        trngConfig.runBit6PlusLimit.minimum = run_6_min;

        /* Set sample mode of the TRNG ring oscillator to Von Neumann, for better random data.*/
        trngConfig.sampleMode = kTRNG_SampleModeVonNeumann;
        /* Initialize TRNG */
        TRNG_Init(TRNG0, &trngConfig);
#elif defined(FSL_FEATURE_SOC_RNG_COUNT) && (FSL_FEATURE_SOC_RNG_COUNT > 0)
        RNGA_Init(RNG);
        RNGA_Seed(RNG, SIM->UIDL);
#endif
    }
}

/*! *********************************************************************************
* \brief  This function performs initialization of the cryptografic HW acceleration.
*
********************************************************************************** */
void SecLib_Init(void)
{
    /* Initialize cryptographic hardware.
     * This function should also initialize TRNG hardware.*/
    SecLib_InitHardwareConnectivity();

#if USE_RTOS && (FSL_FEATURE_SOC_LTC_COUNT || FSL_FEATURE_SOC_MMCAU_COUNT)
    /*! Initialize the SecLib Mutex here. */
    mSecLibMutexId = OSA_MutexCreate();
    if (mSecLibMutexId == NULL)
    {
        panic( ID_PANIC(0,0), (uint32_t)SecLib_Init, 0, 0 );
        return;
    }
#endif
}


/*! *********************************************************************************
* \brief  This function performs AES-128 encryption on a 16-byte block.
*
* \param[in]  pInput Pointer to the location of the 16-byte plain text block.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_Encrypt (const uint8_t*    pInput,
                      const uint8_t*    pKey,
                      uint8_t*          pOutput)
{
    mbedtls_aes_context aesCtx;

    mbedtls_aes_init (&aesCtx);
    mbedtls_aes_setkey_enc (&aesCtx,
                            pKey,
                            AES_128_KEY_BITS);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_crypt_ecb (&aesCtx,
                           MBEDTLS_AES_ENCRYPT,
                           pInput,
                           pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_aes_free (&aesCtx);
}


/*! *********************************************************************************
* \brief  This function performs AES-128 decryption on a 16-byte block.
*
* \param[in]  pInput Pointer to the location of the 16-byte plain text block.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_Decrypt (const uint8_t*    pInput,
                      const uint8_t*    pKey,
                      uint8_t*          pOutput)
{
    mbedtls_aes_context aesCtx;

    mbedtls_aes_init (&aesCtx);
    mbedtls_aes_setkey_dec (&aesCtx,
                            pKey,
                            AES_128_KEY_BITS);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_crypt_ecb (&aesCtx,
                           MBEDTLS_AES_DECRYPT,
                           pInput,
                           pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_aes_free (&aesCtx);
}


/*! *********************************************************************************
* \brief  This function performs AES-128-ECB encryption on a message block.
*         This function only acepts input lengths which are multiple
*         of 16 bytes (AES 128 block size).
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* \pre All Input/Output pointers must refer to a memory address alligned to 4 bytes!
*
********************************************************************************** */
void AES_128_ECB_Encrypt (uint8_t*  pInput,
                          uint32_t  inputLen,
                          uint8_t*  pKey,
                          uint8_t*  pOutput)
{
    /* If the input length is not a multiple of AES 128 block size return */
    if ((inputLen == 0) || (inputLen % AES_128_BLOCK_SIZE))
    {
        return;
    }

    /* Process all data blocks*/
    while (inputLen)
    {
        AES_128_Encrypt (pInput, pKey, pOutput);
        pInput += AES_128_BLOCK_SIZE;
        pOutput += AES_128_BLOCK_SIZE;
        inputLen -= AES_128_BLOCK_SIZE;
    }
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CBC encryption on a message block.
*         This function only acepts input lengths which are multiple
*         of 16 bytes (AES 128 block size).
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
********************************************************************************** */
void AES_128_CBC_Encrypt (uint8_t*  pInput,
                          uint32_t  inputLen,
                          uint8_t*  pInitVector,
                          uint8_t*  pKey,
                          uint8_t*  pOutput)
{
    mbedtls_aes_context aesCtx;

    /* If the input length is not a multiple of AES 128 block size return */
    if ((inputLen == 0) || (inputLen % AES_128_BLOCK_SIZE))
    {
        return;
    }

    mbedtls_aes_init (&aesCtx);
    mbedtls_aes_setkey_enc (&aesCtx,
                            pKey,
                            AES_128_KEY_BITS);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_crypt_cbc (&aesCtx,
                           MBEDTLS_AES_ENCRYPT,
                           inputLen,
                           pInitVector,
                           pInput,
                           pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_aes_free (&aesCtx);
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CBC encryption on a message block after
*         padding it with 1 bit of 1 and 0 bits trail.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
*             IMPORTANT: User must make sure that input and output
*             buffers have at least inputLen + 16 bytes size
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* Return value: size of output buffer (after padding)
*
********************************************************************************** */
uint32_t AES_128_CBC_Encrypt_And_Pad (uint8_t*  pInput,
                                      uint32_t  inputLen,
                                      uint8_t*  pInitVector,
                                      uint8_t*  pKey,
                                      uint8_t*  pOutput)
{
    uint32_t newLen = 0;
    uint32_t idx;
    mbedtls_aes_context aesCtx;

    /* compute new length */
    newLen = inputLen + (AES_128_BLOCK_SIZE - (inputLen & (AES_128_BLOCK_SIZE - 1)));
    /* pad the input buffer with 1 bit of 1 and trail of 0's from inputLen to newLen */
    for (idx = 0; idx < ((newLen - inputLen) - 1); idx++)
    {
        pInput[newLen - 1 - idx] = 0x00;
    }
    pInput[inputLen] = 0x80;

    mbedtls_aes_init (&aesCtx);
    mbedtls_aes_setkey_enc (&aesCtx,
                            pKey,
                            AES_128_KEY_BITS);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_crypt_cbc (&aesCtx,
                           MBEDTLS_AES_ENCRYPT,
                           inputLen,
                           pInitVector,
                           pInput,
                           pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_aes_free (&aesCtx);

    return newLen;
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CBC decryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
* Return value: size of output buffer (after depadding)
*
********************************************************************************** */
uint32_t AES_128_CBC_Decrypt_And_Depad (uint8_t*    pInput,
                                        uint32_t    inputLen,
                                        uint8_t*    pInitVector,
                                        uint8_t*    pKey,
                                        uint8_t*    pOutput)
{
    uint32_t newLen = inputLen;
    mbedtls_aes_context aesCtx;

    mbedtls_aes_init (&aesCtx);
    mbedtls_aes_setkey_dec (&aesCtx,
                            pKey,
                            AES_128_KEY_BITS);


    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_crypt_cbc (&aesCtx,
                           MBEDTLS_AES_DECRYPT,
                           inputLen,
                           pInitVector,
                           pInput,
                           pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_aes_free (&aesCtx);

    while ((pOutput[--newLen] != 0x80) && (newLen !=0)) {}
    return newLen;
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CTR encryption on a message block.
*         This function only acepts input lengths which are multiple
*         of 16 bytes (AES 128 block size).
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pCounter Pointer to the location of the 128-bit counter.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
********************************************************************************** */
void AES_128_CTR (uint8_t*  pInput,
                  uint32_t  inputLen,
                  uint8_t*  pCounter,
                  uint8_t*  pKey,
                  uint8_t*  pOutput)
{
    mbedtls_aes_context aesCtx;
    uint32_t            ctrOffset = 0;
    uint8_t             streamBlk[AES_128_BLOCK_SIZE] = {0};

    /* If the input length is not a multiple of AES 128 block size return */
    if ((inputLen == 0) || (inputLen % AES_128_BLOCK_SIZE))
    {
        return;
    }

    mbedtls_aes_init (&aesCtx);
    mbedtls_aes_setkey_enc (&aesCtx,
                            pKey,
                            AES_128_KEY_BITS);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_crypt_ctr (&aesCtx,
                           inputLen,
                           (size_t*)&ctrOffset,
                           pCounter,
                           (unsigned char *)&streamBlk,
                           pInput,
                           pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_aes_free (&aesCtx);
}


/*! *********************************************************************************
* \brief  This function performs AES-128-OFB encryption on a message block.
*         This function only acepts input lengths which are multiple
*         of 16 bytes (AES 128 block size).
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Input message length in bytes.
*
* \param[in]  pInitVector Pointer to the location of the 128-bit initialization vector.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the ciphered output.
*
********************************************************************************** */
void AES_128_OFB (uint8_t*  pInput,
                  uint32_t  inputLen,
                  uint8_t*  pInitVector,
                  uint8_t*  pKey,
                  uint8_t*  pOutput)
{
    uint8_t tempBuffIn[AES_128_BLOCK_SIZE] = {0};
    uint8_t tempBuffOut[AES_128_BLOCK_SIZE] = {0};

    if (pInitVector != NULL)
    {
        FLib_MemCpy (tempBuffIn, pInitVector, AES_128_BLOCK_SIZE);
    }

    /* If the input length is not a multiple of AES 128 block size return */
    if ((inputLen == 0) || (inputLen % AES_128_BLOCK_SIZE))
    {
        return;
    }

    /* Process all data blocks*/
    while (inputLen)
    {
        AES_128_Encrypt (tempBuffIn, pKey, tempBuffOut);
        FLib_MemCpy (tempBuffIn, tempBuffOut, AES_128_BLOCK_SIZE);
        SecLib_XorN (tempBuffOut, pInput, AES_128_BLOCK_SIZE);
        FLib_MemCpy (pOutput, tempBuffOut, AES_128_BLOCK_SIZE);
        pInput += AES_128_BLOCK_SIZE;
        pOutput += AES_128_BLOCK_SIZE;
        inputLen -= AES_128_BLOCK_SIZE;
    }
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CMAC on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes. The input data must be provided MSB first.
*
* \param[in]  pKey Pointer to the location of the 128-bit key. The key must be provided MSB first.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code. The code will be generated MSB first.
*
* \remarks This is public open source code! Terms of use must be checked before use!
*
********************************************************************************** */
void AES_128_CMAC (uint8_t* pInput,
                   uint32_t inputLen,
                   uint8_t* pKey,
                   uint8_t* pOutput)
{
    const mbedtls_cipher_info_t*    pCmacCipherInfo;

    pCmacCipherInfo = mbedtls_cipher_info_from_type (MBEDTLS_CIPHER_AES_128_ECB);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_cipher_cmac (pCmacCipherInfo,
                         pKey,
                         AES_128_KEY_BITS,
                         pInput,
                         inputLen,
                         pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CMAC on a message block accepting input data
*         which is in LSB first format and computing the authentication code starting fromt he end of the data.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes. The input data must be provided LSB first.
*
* \param[in]  pKey Pointer to the location of the 128-bit key. The key must be provided MSB first.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code. The code will be generated MSB first.
*
********************************************************************************** */
void AES_128_CMAC_LsbFirstInput (uint8_t*   pInput,
                                 uint32_t   inputLen,
                                 uint8_t*   pKey,
                                 uint8_t*   pOutput)
{
    const mbedtls_cipher_info_t*    pCmacCipherInfo;
    mbedtls_cipher_context_t        cmacCipherCtx;
    uint8_t                         reversedBlock[AES_128_BLOCK_SIZE] = {0};

    /* This function does not perform dynamic allocation, it just returns
     * the address of a static global structure. */
    pCmacCipherInfo = mbedtls_cipher_info_from_type (MBEDTLS_CIPHER_AES_128_ECB);

    mbedtls_cipher_init (&cmacCipherCtx);
    mbedtls_cipher_setup (&cmacCipherCtx, pCmacCipherInfo);
    mbedtls_cipher_cmac_starts (&cmacCipherCtx,
                                pKey,
                                AES_128_KEY_BITS);

    /* Walk the input buffer from the end to the start and reverse the blocks
     * before calling the CMAC update function. */
    pInput += inputLen;
    do
    {
        uint32_t    currentCmacInputBlkLen = 0;
        if (inputLen < AES_128_BLOCK_SIZE)
        {
            /* If this is the first and single block it is legal for it to have an input length of 0
             * in which case nothing will be copied in the reversed CMAC input buffer. */
            currentCmacInputBlkLen = inputLen;
        }
        else
        {
            currentCmacInputBlkLen = AES_128_BLOCK_SIZE;
        }
        pInput -= currentCmacInputBlkLen;
        inputLen -= currentCmacInputBlkLen;
        /* Copy the input block to the reversed CAMC input buffer */
        FLib_MemCpyReverseOrder (reversedBlock, pInput, currentCmacInputBlkLen);

        SecLib_DisallowToSleep ();
        SECLIB_MUTEX_LOCK();

        mbedtls_cipher_cmac_update (&cmacCipherCtx,
                                    (const unsigned char *)&reversedBlock,
                                    currentCmacInputBlkLen);

        SECLIB_MUTEX_UNLOCK();
        SecLib_AllowToSleep ();
    }
    while (inputLen);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_cipher_cmac_finish (&cmacCipherCtx, pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    /*CALL THIS AT THE END*/
    mbedtls_cipher_free (&cmacCipherCtx);
}


/*! *********************************************************************************
* \brief  This function performs AES 128 CMAC Pseudo-Random Function (AES-CMAC-PRF-128),
*         according to rfc4615, on a message block.
*
* \details The AES-CMAC-PRF-128 algorithm behaves similar to teh AES CMAC 128 algorithm
*          but removes 128 bit key size restriction.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes.
*
* \param[in]  pVarKey Pointer to the location of the variable length key.
*
* \param[in]  varKeyLen Length of the input key in bytes
*
* \param[out]  pOutput Pointer to the location to store the 16-byte pseudo random variable.
*
********************************************************************************** */
void AES_CMAC_PRF_128 (uint8_t* pInput,
                       uint32_t inputLen,
                       uint8_t* pVarKey,
                       uint32_t varKeyLen,
                       uint8_t* pOutput)
{
    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_aes_cmac_prf_128 (pVarKey,
                              varKeyLen,
                              pInput,
                              inputLen,
                              pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}


/*! *********************************************************************************
* \brief  This function performs AES-128-EAX encryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes.
*
* \param[in]  pNonce Pointer to the location of the nonce.
*
* \param[in]  nonceLen Nonce length in bytes.
*
* \param[in]  pHeader Pointer to the location of header.
*
* \param[in]  headerLen Header length in bytes.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code.
*
* \param[out]  pTag Pointer to the location to store the 128-bit tag.
*
********************************************************************************** */
secResultType_t AES_128_EAX_Encrypt (uint8_t*   pInput,
                                     uint32_t   inputLen,
                                     uint8_t*   pNonce,
                                     uint32_t   nonceLen,
                                     uint8_t*   pHeader,
                                     uint8_t    headerLen,
                                     uint8_t*   pKey,
                                     uint8_t*   pOutput,
                                     uint8_t*   pTag)
{
    uint8_t*        buf;
    uint32_t        buf_len;
    uint8_t         nonce_mac[AES_128_BLOCK_SIZE] = {0};
    uint8_t         hdr_mac[AES_128_BLOCK_SIZE] = {0};
    uint8_t         data_mac[AES_128_BLOCK_SIZE] = {0};
    uint8_t         tempBuff[AES_128_BLOCK_SIZE] = {0};
    secResultType_t status = gSecSuccess_c;
    uint32_t        i;

    if (nonceLen > inputLen)
    {
        buf_len = nonceLen;
    }
    else
    {
        buf_len = inputLen;
    }

    if (headerLen > buf_len)
    {
        buf_len = headerLen;
    }

    buf_len += 16U;

    buf = MEM_BufferAlloc (buf_len);

    if (buf == NULL)
    {
        status = gSecAllocError_c;
    }
    else
    {
        FLib_MemSet (buf, 0, 15);

        buf[15] = 0;
        FLib_MemCpy ((buf + 16), pNonce, nonceLen);
        AES_128_CMAC (buf, 16 + nonceLen, pKey, nonce_mac);

        buf[15] = 1;
        FLib_MemCpy ((buf + 16), pHeader, headerLen);
        AES_128_CMAC (buf, 16 + headerLen, pKey, hdr_mac);

        /* keep the original value of nonce_mac, because AES_128_CTR will increment it */
        FLib_MemCpy (tempBuff, nonce_mac, nonceLen);

        AES_128_CTR (pInput, inputLen, tempBuff, pKey, pOutput);

        buf[15] = 2;
        FLib_MemCpy ((buf + 16), pOutput, inputLen);
        AES_128_CMAC (buf, 16 + inputLen, pKey, data_mac);

        for (i = 0; i < AES_128_BLOCK_SIZE; i++)
        {
            pTag[i] = nonce_mac[i] ^ data_mac[i] ^ hdr_mac[i];
        }

        MEM_BufferFree (buf);
    }

    return status;
}


/*! *********************************************************************************
* \brief  This function performs AES-128-EAX decryption on a message block.
*
* \param[in]  pInput Pointer to the location of the input message.
*
* \param[in]  inputLen Length of the input message in bytes.
*
* \param[in]  pNonce Pointer to the location of the nonce.
*
* \param[in]  nonceLen Nonce length in bytes.
*
* \param[in]  pHeader Pointer to the location of header.
*
* \param[in]  headerLen Header length in bytes.
*
* \param[in]  pKey Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput Pointer to the location to store the 16-byte authentication code.
*
* \param[out]  pTag Pointer to the location to store the 128-bit tag.
*
********************************************************************************** */
secResultType_t AES_128_EAX_Decrypt (uint8_t*   pInput,
                                     uint32_t   inputLen,
                                     uint8_t*   pNonce,
                                     uint32_t   nonceLen,
                                     uint8_t*   pHeader,
                                     uint8_t    headerLen,
                                     uint8_t*   pKey,
                                     uint8_t*   pOutput,
                                     uint8_t*   pTag)
{
    uint8_t*        buf;
    uint32_t        buf_len;
    uint8_t         nonce_mac[AES_128_BLOCK_SIZE] = {0};
    uint8_t         hdr_mac[AES_128_BLOCK_SIZE] = {0};
    uint8_t         data_mac[AES_128_BLOCK_SIZE] = {0};
    secResultType_t status = gSecSuccess_c;
    uint32_t        i;

    if (nonceLen > inputLen)
    {
        buf_len = nonceLen;
    }
    else
    {
        buf_len = inputLen;
    }

    if (headerLen > buf_len)
    {
        buf_len = headerLen;
    }

    buf_len += 16U;

    buf = MEM_BufferAlloc (buf_len);

    if (buf == NULL)
    {
        status = gSecAllocError_c;
    }
    else
    {
        FLib_MemSet (buf, 0, 15);

        buf[15] = 0;
        FLib_MemCpy ((buf + 16), pNonce, nonceLen);
        AES_128_CMAC (buf, 16 + nonceLen, pKey, nonce_mac);

        buf[15] = 1;
        FLib_MemCpy ((buf + 16), pHeader, headerLen);
        AES_128_CMAC (buf, 16 + headerLen, pKey, hdr_mac);

        buf[15] = 2;
        FLib_MemCpy ((buf + 16), pInput, inputLen);
        AES_128_CMAC (buf, 16 + inputLen, pKey, data_mac);

        MEM_BufferFree (buf);

        for (i = 0; i < AES_128_BLOCK_SIZE; i++)
        {
            if (pTag[i] != (nonce_mac[i] ^ data_mac[i] ^ hdr_mac[i]))
            {
                status = gSecError_c;
                break;
            }
        }

        if( gSecSuccess_c == status )
        {
            AES_128_CTR (pInput, inputLen, nonce_mac, pKey, pOutput);
        }
    }

    return status;
}


/*! *********************************************************************************
* \brief  This function performs AES-128-CCM on a message block.
*
* \param[in]  pInput       Pointer to the location of the input message (plaintext or cyphertext).
*
* \param[in]  inputLen     Length of the input plaintext in bytes when encrypting.
*                          Length of the input cypertext without the MAC length when decrypting.
*
* \param[in]  pAuthData    Pointer to the additional authentication data.
*
* \param[in]  authDataLen  Length of additional authentication data.
*
* \param[in]  pNonce       Pointer to the Nonce.
*
* \param[in]  nonceSize    The size of the nonce (7-13).
*
* \param[in]  pKey         Pointer to the location of the 128-bit key.
*
* \param[out]  pOutput     Pointer to the location to store the plaintext data when decrypting.
*                          Pointer to the location to store the cyphertext data when encrypting.
*
* \param[out]  pCbcMac     Pointer to the location to store the Message Authentication Code (MAC) when encrypting.
*                          Pointer to the location where the received MAC can be found when decrypting.
*
* \param[out]  macSize     The size of the MAC.
*
* \param[out]  flags       Select encrypt/decrypt operations (gSecLib_CCM_Encrypt_c, gSecLib_CCM_Decrypt_c)
*
* \return 0 if encryption/decryption was successfull; otherwise, error code for failed encryption/decryption
*
* \remarks At decryption, MIC fail is also signaled by returning a non-zero value.
*
********************************************************************************** */
uint8_t AES_128_CCM (uint8_t*   pInput,
                     uint16_t   inputLen,
                     uint8_t*   pAuthData,
                     uint16_t   authDataLen,
                     uint8_t*   pNonce,
                     uint8_t    nonceSize,
                     uint8_t*   pKey,
                     uint8_t*   pOutput,
                     uint8_t*   pCbcMac,
                     uint8_t    macSize,
                     uint32_t   flags)
{
    int32_t             status;
    mbedtls_ccm_context ccmCtx;

    mbedtls_ccm_init (&ccmCtx);
    mbedtls_ccm_setkey (&ccmCtx,
                        MBEDTLS_CIPHER_ID_AES,
                        pKey,
                        AES_128_KEY_BITS);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    if (flags & gSecLib_CCM_Decrypt_c)
    {
        status = mbedtls_ccm_auth_decrypt (&ccmCtx,
                                           inputLen,
                                           pNonce,
                                           nonceSize,
                                           pAuthData,
                                           authDataLen,
                                           pInput,
                                           pOutput,
                                           pCbcMac,
                                           macSize);
    }
    else
    {
        status = mbedtls_ccm_encrypt_and_tag (&ccmCtx,
                                              inputLen,
                                              pNonce,
                                              nonceSize,
                                              pAuthData,
                                              authDataLen,
                                              pInput,
                                              pOutput,
                                              pCbcMac,
                                              macSize);
    }

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_ccm_free (&ccmCtx);

    if (status == 0)
    {
        return gSecSuccess_c;
    }
    else
    {
        return gSecError_c;
    }
}


/*! *********************************************************************************
* \brief  This function calculates XOR of individual byte pairs in two uint8_t arrays.
*         pDst[i] := pDst[i] ^ pSrc[i] for i=0 to n-1
*
* \param[in, out]  pDst First byte array operand for XOR and destination byte array
*
* \param[in]  pSrc Second byte array operand for XOR
*
* \param[in]  n  Length of the byte arrays which will be XORed
*
********************************************************************************** */
void SecLib_XorN (uint8_t*  pDst,
                  uint8_t*  pSrc,
                  uint8_t   n)
{
    while (n)
    {
        *pDst = *pDst ^ *pSrc;
        pDst = pDst + 1;
        pSrc = pSrc + 1;
        n--;
    }
}


/*! *********************************************************************************
*************************************************************************************
* Private functions
*************************************************************************************
********************************************************************************** */
#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function allocates a memory buffer for a SHA1 context structure
*
* \return    Address of the SHA1 context buffer
*            Deallocate using SHA1_FreeCtx()
*
********************************************************************************** */
void* SHA1_AllocCtx (void)
{
    void* sha1Ctx = MEM_BufferAlloc(sizeof(mbedtls_sha1_context));

    return sha1Ctx;
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function deallocates the memory buffer for the SHA1 context structure
*
* \param [in]    pContext    Address of the SHA1 context buffer
*
********************************************************************************** */
void SHA1_FreeCtx (void* pContext)
{
    MEM_BufferFree (pContext);
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function clones a SHA1 context.
*         Make sure the size of the allocated destination context buffer is appropriate.
*
* \param [in]    pDestCtx    Address of the destination SHA1 context
* \param [in]    pSourceCtx  Address of the source SHA1 context
*
********************************************************************************** */
void SHA1_CloneCtx (void* pDestCtx, void* pSourceCtx)
{
    mbedtls_sha1_clone (pDestCtx, pSourceCtx);
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function initializes the SHA1 context data
*
* \param [in]    pContext    Pointer to the SHA1 context data
*                            Allocated using SHA1_AllocCtx()
*
********************************************************************************** */
void SHA1_Init (void* pContext)
{
    mbedtls_sha1_context* pSha1Ctx = (mbedtls_sha1_context*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha1_init (pSha1Ctx);
    mbedtls_sha1_starts (pSha1Ctx);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function performs SHA1 on multiple bytes and updates the context data
*
* \param [in]    pContext    Pointer to the SHA1 context data
*                            Allocated using SHA1_AllocCtx()
* \param [in]    pData       Pointer to the input data
* \param [in]    numBytes    Number of bytes to hash
*
********************************************************************************** */
void SHA1_HashUpdate (void*     pContext,
                      uint8_t*  pData,
                      uint32_t  numBytes)
{
    mbedtls_sha1_context* pSha1Ctx = (mbedtls_sha1_context*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha1_update (pSha1Ctx,
                         pData,
                         numBytes);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function performs SHA1 on the last bytes of data and updates the context data.
*         The final hash value is stored at the provided output location.
*
* \param [in]       pContext    Pointer to the SHA1 context data
*                               Allocated using SHA1_AllocCtx()
* \param [in,out]   pOutput     Pointer to the output location
*
********************************************************************************** */
void SHA1_HashFinish (void*     pContext,
                      uint8_t*  pOutput)
{
    mbedtls_sha1_context* pSha1Ctx = (mbedtls_sha1_context*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha1_finish (pSha1Ctx, pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_sha1_free (pSha1Ctx);
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha1Enable_d == 1)
/*! *********************************************************************************
* \brief  This function performs all SHA1 steps on multiple bytes: initialize,
*         update, finish, and update context data.
*         The final hash value is stored at the provided output location.
*
* \param [in]       pData       Pointer to the input data
* \param [in]       numBytes    Number of bytes to hash
* \param [in,out]   pOutput     Pointer to the output location
*
********************************************************************************** */
void SHA1_Hash (uint8_t*    pData,
                uint32_t    numBytes,
                uint8_t*    pOutput)
{
    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha1 (pData,
                  numBytes,
                  pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}
#endif /* (gSecLibSha1Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function allocates a memory buffer for a SHA256 context structure
*
* \return    Address of the SHA256 context buffer
*            Deallocate using SHA256_FreeCtx()
*
********************************************************************************** */
void* SHA256_AllocCtx (void)
{
    void* sha256Ctx = MEM_BufferAlloc(sizeof(mbedtls_sha256_context));

    return sha256Ctx;
}
#endif /* (gSecLibSha256Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function deallocates the memory buffer for the SHA256 context structure
*
* \param [in]    pContext    Address of the SHA256 context buffer
*
********************************************************************************** */
void SHA256_FreeCtx (void* pContext)
{
    MEM_BufferFree (pContext);
}
#endif /* (gSecLibSha256Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function clones SHA256 context.
*         Make sure the size of the allocated destination context buffer is appropriate.
*
* \param [in]    pDestCtx    Address of the destination SHA256 context
* \param [in]    pSourceCtx  Address of the source SHA256 context
*
********************************************************************************** */
void SHA256_CloneCtx (void* pDestCtx, void* pSourceCtx)
{
    mbedtls_sha256_clone (pDestCtx, pSourceCtx);
}
#endif /* (gSecLibSha256Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function initializes the SHA256 context data
*
* \param [in]    pContext    Pointer to the SHA256 context data
*                            Allocated using SHA256_AllocCtx()
*
********************************************************************************** */
void SHA256_Init (void* pContext)
{
    mbedtls_sha256_context*     pSha256Ctx = (mbedtls_sha256_context*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha256_init (pSha256Ctx);
    mbedtls_sha256_starts (pSha256Ctx, 0);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}
#endif /* (gSecLibSha256Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function performs SHA256 on multiple bytes and updates the context data
*
* \param [in]    pContext    Pointer to the SHA256 context data
*                            Allocated using SHA256_AllocCtx()
* \param [in]    pData       Pointer to the input data
* \param [in]    numBytes    Number of bytes to hash
*
********************************************************************************** */
void SHA256_HashUpdate (void*       pContext,
                        uint8_t*    pData,
                        uint32_t    numBytes)
{
    mbedtls_sha256_context* pSha256Ctx = (mbedtls_sha256_context*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha256_update (pSha256Ctx,
                           pData,
                           numBytes);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}
#endif /* (gSecLibSha256Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function performs SHA256 on the last bytes of data and updates the context data.
*         The final hash value is stored at the provided output location.
*
* \param [in]       pContext    Pointer to the SHA256 context data
*                               Allocated using SHA256_AllocCtx()
* \param [in,out]   pOutput     Pointer to the output location
*
********************************************************************************** */
void SHA256_HashFinish (void*       pContext,
                        uint8_t*    pOutput)
{
    mbedtls_sha256_context* pSha256Ctx = (mbedtls_sha256_context*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha256_finish (pSha256Ctx, pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_sha256_free (pSha256Ctx);
}
#endif /* (gSecLibSha256Enable_d == 1) */


#if (gSecLibSha256Enable_d == 1)
/*! *********************************************************************************
* \brief  This function performs all SHA256 steps on multiple bytes: initialize,
*         update, finish, and update context data.
*         The final hash value is stored at the provided output location.
*
* \param [in]       pData       Pointer to the input data
* \param [in]       numBytes    Number of bytes to hash
* \param [in,out]   pOutput     Pointer to the output location
*
********************************************************************************** */
void SHA256_Hash (uint8_t*  pData,
                  uint32_t  numBytes,
                  uint8_t*  pOutput)
{
    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_sha256 (pData,
                    numBytes,
                    pOutput,
                    0);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}
#endif /* (gSecLibSha256Enable_d == 1) */


/*! *********************************************************************************
* \brief  This function allocates a memory buffer for a HMAC SHA256 context structure
*
* \return    Address of the HMAC SHA256 context buffer
*            Deallocate using HMAC_SHA256_FreeCtx()
*
********************************************************************************** */
void* HMAC_SHA256_AllocCtx (void)
{
    void* mdHmacSha256Ctx = MEM_BufferAlloc(sizeof(mbedtls_md_context_t));

    return mdHmacSha256Ctx;
}


/*! *********************************************************************************
* \brief  This function deallocates the memory buffer for the HMAC SHA256 context structure
*
* \param [in]    pContext    Address of the HMAC SHA256 context buffer
*
********************************************************************************** */
void HMAC_SHA256_FreeCtx (void* pContext)
{
    MEM_BufferFree (pContext);
}


/*! *********************************************************************************
* \brief  This function performs the initialization of the HMAC SHA256 context data
*
* \param [in]    pContext    Pointer to the HMAC SHA256 context data
*                            Allocated using HMAC_SHA256_AllocCtx()
* \param [in]    pKey        Pointer to the HMAC key
* \param [in]    keyLen      Length of the HMAC key in bytes
*
********************************************************************************** */
void HMAC_SHA256_Init (void*    pContext,
                       uint8_t* pKey,
                       uint32_t keyLen)
{
    mbedtls_md_context_t*       pMdHmacSha256Ctx = (mbedtls_md_context_t*)pContext;
    const mbedtls_md_info_t*    pMdInfo;

    pMdInfo = mbedtls_md_info_from_type (MBEDTLS_MD_SHA256);

    mbedtls_md_init (pMdHmacSha256Ctx);
    mbedtls_md_setup (pMdHmacSha256Ctx,
                      pMdInfo,
                      1);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_md_hmac_starts (pMdHmacSha256Ctx,
                            pKey,
                            keyLen);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}


/*! *********************************************************************************
* \brief  This function performs HMAC update with the input data.
*
* \param [in]    pContext    Pointer to the HMAC SHA256 context data
*                            Allocated using HMAC_SHA256_AllocCtx()
* \param [in]    pData       Pointer to the input data
* \param [in]    numBytes    Number of bytes to hash
*
********************************************************************************** */
void HMAC_SHA256_Update (void*      pContext,
                         uint8_t*   pData,
                         uint32_t   numBytes)
{
    mbedtls_md_context_t* pMdHmacSha256Ctx = (mbedtls_md_context_t*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_md_hmac_update (pMdHmacSha256Ctx,
                            pData,
                            numBytes);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}


/*! *********************************************************************************
* \brief  This function finalizes the HMAC SHA256 computaion and clears the context data.
*         The final hash value is stored at the provided output location.
*
* \param [in]       pContext    Pointer to the HMAC SHA256 context data
*                               Allocated using HMAC_SHA256_AllocCtx()
* \param [in,out]   pOutput     Pointer to the output location
*
********************************************************************************** */
void HMAC_SHA256_Finish (void*      pContext,
                         uint8_t*   pOutput)
{
    mbedtls_md_context_t* pMdHmacSha256Ctx = (mbedtls_md_context_t*)pContext;

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_md_hmac_finish (pMdHmacSha256Ctx, pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    mbedtls_md_free (pMdHmacSha256Ctx);
}


/*! *********************************************************************************
* \brief  This function performs all HMAC SHA256 steps on multiple bytes: initialize,
*         update, finish, and update context data.
*         The final HMAC value is stored at the provided output location.
*
* \param [in]       pKey        Pointer to the HMAC key
* \param [in]       keyLen      Length of the HMAC key in bytes
* \param [in]       pData       Pointer to the input data
* \param [in]       numBytes    Number of bytes to perform HMAC on
* \param [in,out]   pOutput     Pointer to the output location
*
********************************************************************************** */
void HMAC_SHA256 (uint8_t*  pKey,
                  uint32_t  keyLen,
                  uint8_t*  pData,
                  uint32_t  numBytes,
                  uint8_t*  pOutput)
{
    const mbedtls_md_info_t* pMdInfo;

    pMdInfo = mbedtls_md_info_from_type (MBEDTLS_MD_SHA256);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    mbedtls_md_hmac (pMdInfo,
                     pKey,
                     keyLen,
                     pData,
                     numBytes,
                     pOutput);

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();
}

/************************************************************************************
* \brief Generates a new ECDH P256 Private/Public key pair
*
* \return gSecSuccess_c or error
*
************************************************************************************/
secResultType_t ECDH_P256_GenerateKeys
(
    ecdhPublicKey_t*    pOutPublicKey,
    ecdhPrivateKey_t*   pOutPrivateKey
)
{
#if mRevertEcdhKeys_d
    ecdhPublicKey_t                 reversedPublicKey;
    ecdhPrivateKey_t                reversedPrivateKey;
#endif /* mRevertEcdhKeys_d */
    fpRngPrng_t                     pfPrng;
    void*                           pPrngCtx;

    mbedtls_ecp_group               p256EcpGrp;
    mbedtls_mpi                     p256EcpPrivateKey;
    mbedtls_ecp_point               p256EcpPublicKey;

    const mbedtls_ecp_curve_info*   pP256CurveInfo;

    int ecdhRes = 0;

    pfPrng = RNG_GetPrngFunc();
    if (NULL == pfPrng)
    {
        return gSecError_c;
    }

    pPrngCtx = RNG_GetPrngContext();
    if (NULL == pPrngCtx)
    {
        return gSecError_c;
    }

    mbedtls_ecp_group_init (&p256EcpGrp);
    mbedtls_mpi_init (&p256EcpPrivateKey);
    mbedtls_ecp_point_init (&p256EcpPublicKey);

    pP256CurveInfo = mbedtls_ecp_curve_info_from_grp_id (MBEDTLS_ECP_DP_SECP256R1);
    mbedtls_ecp_group_load (&p256EcpGrp, pP256CurveInfo->grp_id);

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    ecdhRes = mbedtls_ecdh_gen_public (&p256EcpGrp,
                                       &p256EcpPrivateKey,
                                       &p256EcpPublicKey,
                                       pfPrng,
                                       pPrngCtx
                                      );

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    /* Write the generated Secret Key and Public Key to the designated output locations.
     * The sizes copied should correspond to the sizes of the keys for the P256 curve. */
    if (ecdhRes == 0)
    {
#if !mRevertEcdhKeys_d
        mbedtls_mpi_write_binary (&p256EcpPrivateKey,
                                  pOutPrivateKey->raw_8bit,
                                  sizeof(pOutPrivateKey->raw_8bit));
        mbedtls_mpi_write_binary (&p256EcpPublicKey.X,
                                  pOutPublicKey->components_8bit.x,
                                  sizeof(pOutPublicKey->components_8bit.x));
        mbedtls_mpi_write_binary (&p256EcpPublicKey.Y,
                                  pOutPublicKey->components_8bit.y,
                                  sizeof(pOutPublicKey->components_8bit.y));
#else /* mRevertEcdhKeys_d */
        mbedtls_mpi_write_binary (&p256EcpPrivateKey,
                                  reversedPrivateKey.raw_8bit,
                                  sizeof(reversedPrivateKey.raw_8bit));
        FLib_MemCpyReverseOrder (pOutPrivateKey->raw_8bit,
                                 reversedPrivateKey.raw_8bit,
                                 sizeof(pOutPrivateKey->raw_8bit));
        mbedtls_mpi_write_binary (&p256EcpPublicKey.X,
                                  reversedPublicKey.components_8bit.x,
                                  sizeof(reversedPublicKey.components_8bit.x));
        FLib_MemCpyReverseOrder (pOutPublicKey->components_8bit.x,
                                 reversedPublicKey.components_8bit.x,
                                 sizeof(pOutPublicKey->components_8bit.x));
        mbedtls_mpi_write_binary (&p256EcpPublicKey.Y,
                                  reversedPublicKey.components_8bit.y,
                                  sizeof(reversedPublicKey.components_8bit.y));
        FLib_MemCpyReverseOrder (pOutPublicKey->components_8bit.y,
                                 reversedPublicKey.components_8bit.y,
                                 sizeof(pOutPublicKey->components_8bit.y));
#endif /* mRevertEcdhKeys_d */
    }

    mbedtls_ecp_group_free (&p256EcpGrp);
    mbedtls_mpi_free (&p256EcpPrivateKey);
    mbedtls_ecp_point_free (&p256EcpPublicKey);

    if (ecdhRes != 0)
    {
        return gSecError_c;
    }
    else
    {
        return gSecSuccess_c;
    }
}


/************************************************************************************
* \brief Computes the Diffie-Hellman Key for an ECDH P256 key pair.
*
* \return gSecSuccess_c or error
*
************************************************************************************/
secResultType_t ECDH_P256_ComputeDhKey
(
    ecdhPrivateKey_t*   pInPrivateKey,
    ecdhPublicKey_t*    pInPeerPublicKey,
    ecdhDhKey_t*        pOutDhKey
)
{
#if mRevertEcdhKeys_d
    ecdhPublicKey_t                 reversedPeerPublicKey;
    ecdhPrivateKey_t                reversedPrivateKey;
#endif /* mRevertEcdhKeys_d */
    fpRngPrng_t                     pfPrng;
    void*                           pPrngCtx;

    mbedtls_ecp_group               p256EcpGrp;
    mbedtls_mpi                     p256EcpPrivateKey;
    mbedtls_ecp_point               p256EcpPublicKey;
    mbedtls_mpi                     sharedZ;
    /*! The Z coordinate of the P256 public key has the value positive 1.
     *  Only the X and Y coordinates should be stored and provided by the caller of this fucntion */
    const uint8_t                   publicZ = 1;

    const mbedtls_ecp_curve_info*   pP256CurveInfo;

    int ecdhRes = 0;

    pfPrng = RNG_GetPrngFunc();
    if (NULL == pfPrng)
    {
        return gSecError_c;
    }

    pPrngCtx = RNG_GetPrngContext();
    if (NULL == pPrngCtx)
    {
        return gSecError_c;
    }

    mbedtls_ecp_group_init (&p256EcpGrp);
    mbedtls_mpi_init (&p256EcpPrivateKey);
    mbedtls_ecp_point_init (&p256EcpPublicKey);
    mbedtls_mpi_init (&sharedZ);

    pP256CurveInfo = mbedtls_ecp_curve_info_from_grp_id (MBEDTLS_ECP_DP_SECP256R1);
    mbedtls_ecp_group_load (&p256EcpGrp, pP256CurveInfo->grp_id);

    /* Load the local Secret Key and remote Public Key to the appropriate local variables.
     * The sizes loaded should correspond to the sizes of the keys for the P256 curve. */
#if !mRevertEcdhKeys_d
    mbedtls_mpi_read_binary (&p256EcpPrivateKey,
                             pInPrivateKey->raw_8bit,
                             sizeof(pInPrivateKey->raw_8bit));
    mbedtls_mpi_read_binary (&p256EcpPublicKey.X,
                             pInPeerPublicKey->components_8bit.x,
                             sizeof(pInPeerPublicKey->components_8bit.x));
    mbedtls_mpi_read_binary (&p256EcpPublicKey.Y,
                             pInPeerPublicKey->components_8bit.y,
                             sizeof(pInPeerPublicKey->components_8bit.y));
#else /* mRevertEcdhKeys_d */
    FLib_MemCpyReverseOrder (reversedPrivateKey.raw_8bit,
                             pInPrivateKey->raw_8bit,
                             sizeof(reversedPrivateKey.raw_8bit));
    mbedtls_mpi_read_binary (&p256EcpPrivateKey,
                             reversedPrivateKey.raw_8bit,
                             sizeof(reversedPrivateKey.raw_8bit));
    FLib_MemCpyReverseOrder (reversedPeerPublicKey.components_8bit.x,
                             pInPeerPublicKey->components_8bit.x,
                             sizeof(reversedPeerPublicKey.components_8bit.x));
    mbedtls_mpi_read_binary (&p256EcpPublicKey.X,
                             reversedPeerPublicKey.components_8bit.x,
                             sizeof(reversedPeerPublicKey.components_8bit.x));
    FLib_MemCpyReverseOrder (reversedPeerPublicKey.components_8bit.y,
                             pInPeerPublicKey->components_8bit.y,
                             sizeof(reversedPeerPublicKey.components_8bit.y));
    mbedtls_mpi_read_binary (&p256EcpPublicKey.Y,
                             reversedPeerPublicKey.components_8bit.y,
                             sizeof(reversedPeerPublicKey.components_8bit.y));
#endif /* mRevertEcdhKeys_d */

    mbedtls_mpi_read_binary (&p256EcpPublicKey.Z,
                             &publicZ,
                             sizeof(publicZ));

    SecLib_DisallowToSleep ();
    SECLIB_MUTEX_LOCK();

    ecdhRes = mbedtls_ecdh_compute_shared (&p256EcpGrp,
                                           &sharedZ,
                                           &p256EcpPublicKey,
                                           &p256EcpPrivateKey,
                                           pfPrng,
                                           pPrngCtx
                                          );

    SECLIB_MUTEX_UNLOCK();
    SecLib_AllowToSleep ();

    /* Write the generated Shared Key to the designated output location.
     * The size copied should correspond to the size of the key for the P256 curve.
     * Only the X component is provided by the implementation thus it is the only one
     * written to the output location. */
    if (ecdhRes == 0)
    {
#if !mRevertEcdhKeys_d
        mbedtls_mpi_write_binary (&sharedZ,
                                  pOutDhKey->components_8bit.x,
                                  sizeof(pOutDhKey->components_8bit.x));
#else /* mRevertEcdhKeys_d */
        /* Use the reversed public key X component asa buffer for the reversed shared key. */
        mbedtls_mpi_write_binary (&sharedZ,
                                  reversedPeerPublicKey.components_8bit.x,
                                  sizeof(reversedPeerPublicKey.components_8bit.x));
        FLib_MemCpyReverseOrder (pOutDhKey->components_8bit.x,
                                 reversedPeerPublicKey.components_8bit.x,
                                 sizeof(pOutDhKey->components_8bit.x));
#endif /* mRevertEcdhKeys_d */
    }

    mbedtls_ecp_group_free (&p256EcpGrp);
    mbedtls_mpi_free (&p256EcpPrivateKey);
    mbedtls_ecp_point_free (&p256EcpPublicKey);
    mbedtls_mpi_free (&sharedZ);

    if (ecdhRes == MBEDTLS_ERR_ECP_INVALID_KEY)
    {
        return gSecInvalidPublicKey_c;
    }
    else if (ecdhRes != 0)
    {
        return gSecError_c;
    }
    else
    {
        return gSecSuccess_c;
    }
}

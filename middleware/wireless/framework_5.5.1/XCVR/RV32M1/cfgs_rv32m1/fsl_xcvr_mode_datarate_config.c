/*! *********************************************************************************
* Copyright (c) 2016, Freescale Semiconductor, Inc.
* Copyright 2018 NXP
* All rights reserved.
*
* 
*
* SPDX-License-Identifier: BSD-3-Clause
********************************************************************************** */

#include "fsl_xcvr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
/* ========================= DATA RATE ONLY settings ===============*/
/*!
 * @brief XCVR 2Mbps DATA RATE specific configure structure
 */
#if RADIO_IS_GEN_3P0
const xcvr_datarate_config_t xcvr_2mbps_config =
{
    .data_rate = DR_2MBPS,
    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(0) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),
    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(1) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),

    .dcoc_ctrl_0_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(8) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(7),
    .dcoc_ctrl_0_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(10) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(8),
    .dcoc_ctrl_2_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(8) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(7),
    .dcoc_ctrl_2_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(10) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(8),

    .dcoc_ctrl_1_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dcoc_ctrl_1_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dc_resid_ctrl_26mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(6),
    .dc_resid_ctrl_32mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(6),

};
#endif /* RADIO_IS_GEN_3P0 */

/*!
 * @brief XCVR 1Mbps DATA RATE specific configure structure
 */
const xcvr_datarate_config_t xcvr_1mbps_config =
{
    .data_rate = DR_1MBPS,
    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(1) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),
    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(2) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),

    .dcoc_ctrl_0_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(10) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(7),
    .dcoc_ctrl_0_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(12) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(8),
    .dcoc_ctrl_2_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(10) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(7),
    .dcoc_ctrl_2_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(12) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(8),

    .dcoc_ctrl_1_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dcoc_ctrl_1_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dc_resid_ctrl_26mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),

    .dc_resid_ctrl_32mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),

};

/*!
 * @brief XCVR 500K bps DATA RATE specific configure structure
 */
const xcvr_datarate_config_t xcvr_500kbps_config =
{
    .data_rate = DR_500KBPS,
    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(2) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),
    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(4) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),

    .dcoc_ctrl_0_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(13) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(11),
    .dcoc_ctrl_0_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(16) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(14),
    .dcoc_ctrl_2_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(13) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(11),
    .dcoc_ctrl_2_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(16) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(14),

    .dcoc_ctrl_1_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dcoc_ctrl_1_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dc_resid_ctrl_26mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),
    .dc_resid_ctrl_32mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),
};

/*!
 * @brief XCVR 250K bps DATA RATE specific configure structure
 */
const xcvr_datarate_config_t xcvr_250kbps_config =
{
    .data_rate = DR_250KBPS,

    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(4) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),
    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(8) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),

    .dcoc_ctrl_0_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(16) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(15),
    .dcoc_ctrl_0_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(20) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(18),
    .dcoc_ctrl_2_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(16) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(15),
    .dcoc_ctrl_2_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(20) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(18),

    .dcoc_ctrl_1_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dcoc_ctrl_1_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3),

    .dc_resid_ctrl_26mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),
    .dc_resid_ctrl_32mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),

};



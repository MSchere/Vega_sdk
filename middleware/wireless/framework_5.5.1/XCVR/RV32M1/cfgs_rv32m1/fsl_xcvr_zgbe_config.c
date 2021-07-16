/*! *********************************************************************************
* Copyright (c) 2015, Freescale Semiconductor, Inc.
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
 *******************************************************************************/
const xcvr_mode_config_t zgbe_mode_config =
{
    .radio_mode = ZIGBEE_MODE,
    .scgc5_clock_ena_bits = RSIM_CONTROL_RSIM_CGC_XCVR_EN_MASK | RSIM_CONTROL_RSIM_CGC_ZIG_EN_MASK,


    /* XCVR_MISC configs */
    .xcvr_ctrl.mask = XCVR_CTRL_XCVR_CTRL_PROTOCOL_MASK |
                      XCVR_CTRL_XCVR_CTRL_TGT_PWR_SRC_MASK |
                      XCVR_CTRL_XCVR_CTRL_DEMOD_SEL_MASK,
    .xcvr_ctrl.init = XCVR_CTRL_XCVR_CTRL_PROTOCOL(4) |
                      XCVR_CTRL_XCVR_CTRL_TGT_PWR_SRC(7) |
                      XCVR_CTRL_XCVR_CTRL_DEMOD_SEL(2),

    /* XCVR_PHY configs */
    .phy_fsk_pd_cfg0 = 0x0U,
    .phy_fsk_pd_cfg1 = 0x0U,
    .phy_fsk_cfg = 0x0U,
    .phy_fsk_misc = 0x0U,
    .phy_fad_ctrl = 0x0U,

    /* XCVR_PLL_DIG configs */

    /* XCVR_RX_DIG configs */
    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_FSK_ZB_SEL(1) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DC_RESID_EN(1) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_SRC_RATE(0),

    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_FSK_ZB_SEL(1) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DC_RESID_EN(1), /* Depends on protocol */

    .agc_ctrl_0_init = XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_BBA_STEP_SZ(2) |
                       XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_RSSI_THRESH(0xEC) |
                       XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_LNA_STEP_SZ(2),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ALPHA(1) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_EXT_DC_EN(1),

    /* XCVR_TX_DIG configs */
    .tx_gfsk_ctrl = XCVR_TX_DIG_GFSK_CTRL_GFSK_MULTIPLY_TABLE_MANUAL(0x4000) |
                    XCVR_TX_DIG_GFSK_CTRL_GFSK_MI(1) |
                    XCVR_TX_DIG_GFSK_CTRL_GFSK_MLD(0) |
                    XCVR_TX_DIG_GFSK_CTRL_GFSK_FLD(0) |
                    XCVR_TX_DIG_GFSK_CTRL_GFSK_MOD_INDEX_SCALING(0) |
                    XCVR_TX_DIG_GFSK_CTRL_TX_IMAGE_FILTER_OVRD_EN(0) |
                    XCVR_TX_DIG_GFSK_CTRL_TX_IMAGE_FILTER_0_OVRD(0) |
                    XCVR_TX_DIG_GFSK_CTRL_TX_IMAGE_FILTER_1_OVRD(0) |
                    XCVR_TX_DIG_GFSK_CTRL_TX_IMAGE_FILTER_2_OVRD(0),
    .tx_gfsk_coeff1_26mhz = 0,
    .tx_gfsk_coeff2_26mhz = 0,
    .tx_gfsk_coeff1_32mhz = 0,
    .tx_gfsk_coeff2_32mhz = 0,


};

const xcvr_mode_datarate_config_t xcvr_ZIGBEE_250kbps_config =
{
    .radio_mode = ZIGBEE_MODE,
    .data_rate = DR_250KBPS,

    .ana_sy_ctrl2.mask = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM_MASK,
    .ana_sy_ctrl2.init = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM(1), /* VCO KVM */

    .ana_rx_bba.mask = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL_MASK | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL_MASK,
    .ana_rx_bba.init = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL(1) | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL(1), /* BBA_BW_SEL and BBA2_BW_SEL */
    .ana_rx_tza.mask = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL_MASK,
    .ana_rx_tza.init = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL(1), /* TZA_BW_SEL */

    .phy_fsk_pd_cfg1_mode_datarate_26mhz = 0x0U,
    .phy_fsk_pd_cfg1_mode_datarate_32mhz = 0x0U,

    .phy_fsk_cfg_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),
    .phy_fsk_cfg_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),

    .phy_fsk_misc_mode_datarate_26mhz = 0x0U,
    .phy_fsk_misc_mode_datarate_32mhz = 0x0U,

    /* AGC configs */
    .agc_ctrl_0_init_26mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(2) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x05),
    .agc_ctrl_0_init_32mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(2) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x05),

    .agc_ctrl_1_init_26mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(13) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),
    .agc_ctrl_1_init_32mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(10) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),

    .agc_ctrl_2_init_26mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(8) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x09),
    .agc_ctrl_2_init_32mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(10) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x09),

    .agc_ctrl_3_init = XCVR_RX_DIG_AGC_CTRL_3_AGC_UNFREEZE_TIME(21),

    .dcoc_cal_gain_init = XCVR_RX_DIG_DCOC_CAL_GAIN_DCOC_LNA_CAL_GAIN2(3),
    .dcoc_cal_rcp_init = XCVR_RX_DIG_DCOC_CAL_RCP_ALPHA_CALC_RECIP(50),

    .dcoc_cal_iir_init_26mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(0),
    .dcoc_cal_iir_init_32mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(1) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(1),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ITER_FREEZE(3) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_MIN_AGC_IDX(4),

    /* All constant values are represented as 16 bits, register writes will remove unused bits */
    .rx_chf_coeffs_26mhz.rx_chf_coef_0 = 0xFFFF,
    .rx_chf_coeffs_26mhz.rx_chf_coef_1 = 0xFFFF,
    .rx_chf_coeffs_26mhz.rx_chf_coef_2 = 0x0002,
    .rx_chf_coeffs_26mhz.rx_chf_coef_3 = 0x0008,
    .rx_chf_coeffs_26mhz.rx_chf_coef_4 = 0x000A,
    .rx_chf_coeffs_26mhz.rx_chf_coef_5 = 0x0000,
    .rx_chf_coeffs_26mhz.rx_chf_coef_6 = 0xFFE8,
    .rx_chf_coeffs_26mhz.rx_chf_coef_7 = 0xFFD7,
    .rx_chf_coeffs_26mhz.rx_chf_coef_8 = 0xFFE6,
    .rx_chf_coeffs_26mhz.rx_chf_coef_9 = 0x0022,
    .rx_chf_coeffs_26mhz.rx_chf_coef_10 = 0x0075,
    .rx_chf_coeffs_26mhz.rx_chf_coef_11 = 0x00B2,

    /* IEEE 802.15.4 32MHz Channel Filter  -- 1.55/1.25/5/0.97/B5   */
    .rx_chf_coeffs_32mhz.rx_chf_coef_0 = 0xFFFF,
    .rx_chf_coeffs_32mhz.rx_chf_coef_1 = 0xFFFF,
    .rx_chf_coeffs_32mhz.rx_chf_coef_2 = 0x0005,
    .rx_chf_coeffs_32mhz.rx_chf_coef_3 = 0x0004,
    .rx_chf_coeffs_32mhz.rx_chf_coef_4 = 0xFFF2,
    .rx_chf_coeffs_32mhz.rx_chf_coef_5 = 0xFFF2,
    .rx_chf_coeffs_32mhz.rx_chf_coef_6 = 0x001D,
    .rx_chf_coeffs_32mhz.rx_chf_coef_7 = 0x0025,
    .rx_chf_coeffs_32mhz.rx_chf_coef_8 = 0xFFCE,
    .rx_chf_coeffs_32mhz.rx_chf_coef_9 = 0xFFA1,
    .rx_chf_coeffs_32mhz.rx_chf_coef_10 = 0x0040,
    .rx_chf_coeffs_32mhz.rx_chf_coef_11 = 0x0124,

    .rx_rccal_ctrl_0 = XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_MANUAL(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_DIS(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_RCCAL_SMP_DLY(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_RCCAL_COMP_INV(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_MANUAL(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_DIS(0),
    .rx_rccal_ctrl_1 = XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_MANUAL(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_DIS(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_MANUAL(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_DIS(0),

    .tx_fsk_scale_26mhz = XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_0(0x1627) | XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_1(0x09d9),
    .tx_fsk_scale_32mhz = XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_0(0x1800) | XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_1(0x0800),
};

/* CUSTOM datarate dependent config structure for ONLY 802.15.4 */
/*!
 * @brief XCVR 500K bps DATA RATE specific configure structure
 */
const xcvr_datarate_config_t xcvr_802_15_4_250kbps_config =
{
    .data_rate = DR_250KBPS,

    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(5) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),
    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_OSR(2) |
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DEC_FILT_GAIN(16),

    .dcoc_ctrl_0_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(13) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(29),
    .dcoc_ctrl_0_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_DLY(21) |
                              XCVR_RX_DIG_DCOC_CTRL_0_DCOC_CORR_HOLD_TIME(18),
    .dcoc_ctrl_2_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(13) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(29),
    .dcoc_ctrl_2_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_DLY_ALT(21) |
                              XCVR_RX_DIG_DCOC_CTRL_2_DCOC_CORR_HOLD_TIME_ALT(18),

    .dcoc_ctrl_1_init_26mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_GS_IDX(1),

    .dcoc_ctrl_1_init_32mhz = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_TRK_EST_GS_CNT(0) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_SIGN_SCALE_GS_IDX(1) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHAC_SCALE_GS_IDX(3) |
                              XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_GS_IDX(1),

    .dc_resid_ctrl_26mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_NWIN(96) |
                           XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(4),
    .dc_resid_ctrl_32mhz = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_NWIN(96) |
                           XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_DLY(6),
};



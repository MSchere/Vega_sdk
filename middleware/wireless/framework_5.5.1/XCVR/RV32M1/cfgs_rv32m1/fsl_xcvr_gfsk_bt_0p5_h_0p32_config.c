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
/* MODE only configuration */
const xcvr_mode_config_t gfsk_bt_0p5_h_0p32_mode_config =
{
    .radio_mode = GFSK_BT_0p5_h_0p32,

    .scgc5_clock_ena_bits = RSIM_CONTROL_RSIM_CGC_XCVR_EN_MASK | RSIM_CONTROL_RSIM_CGC_GEN_EN_MASK, /* Used to control RSIM clock enables. */

    /* XCVR_MISC configs */
    .xcvr_ctrl.mask = XCVR_CTRL_XCVR_CTRL_PROTOCOL_MASK |
                      XCVR_CTRL_XCVR_CTRL_TGT_PWR_SRC_MASK |
                      XCVR_CTRL_XCVR_CTRL_DEMOD_SEL_MASK,
    .xcvr_ctrl.init = XCVR_CTRL_XCVR_CTRL_PROTOCOL(8) |
                      XCVR_CTRL_XCVR_CTRL_TGT_PWR_SRC(7) |
                      XCVR_CTRL_XCVR_CTRL_DEMOD_SEL(1),

    /* XCVR_PHY configs */
    .phy_fsk_pd_cfg0 = XCVR_PHY_PHY_FSK_PD_CFG0_PRE_REF0(0x1F) |
                       XCVR_PHY_PHY_FSK_PD_CFG0_PRE_REF1(0x00) |
                       XCVR_PHY_PHY_FSK_PD_CFG0_PRE_REF2(0x01) |
                       XCVR_PHY_PHY_FSK_PD_CFG0_PRE_REF3(0x02) |
                       XCVR_PHY_PHY_FSK_PD_CFG0_PRE_REF4(0x01) |
                       XCVR_PHY_PHY_FSK_PD_CFG0_PRE_REF5(0x00) |
                       XCVR_PHY_PHY_FSK_PD_CFG0_PHY_CLK_ON(0x00),
    .phy_fsk_pd_cfg1 = XCVR_PHY_PHY_FSK_PD_CFG1_PRE_REF6(0x1F) |
                       XCVR_PHY_PHY_FSK_PD_CFG1_PRE_REF7(0x1E) |
                       XCVR_PHY_PHY_FSK_PD_CFG1_PD_TIMEOUT(0x07),
    .phy_fsk_cfg = XCVR_PHY_PHY_FSK_CFG_AA_PLAYBACK(1) |
                   XCVR_PHY_PHY_FSK_CFG_AA_OUT_SEL(0) |
                   XCVR_PHY_PHY_FSK_CFG_FSK_BIT_INVERT(0) |
                   XCVR_PHY_PHY_FSK_CFG_BSM_EN_BLE(0) |
                   XCVR_PHY_PHY_FSK_CFG_AA_CORR_GAIN(0x0C) |
                   XCVR_PHY_PHY_FSK_CFG_PDB_CONF_EN(0) |
                   XCVR_PHY_PHY_FSK_CFG_PDA_CONF_EN(0) |
                   XCVR_PHY_PHY_FSK_CFG_DEMOD_TIMEOUT(0x0B) |
                   XCVR_PHY_PHY_FSK_CFG_PDB_COMP_EN(0) |
                   XCVR_PHY_PHY_FSK_CFG_PDA_COMP_EN(0) |
                   XCVR_PHY_PHY_FSK_CFG_BLE_NTW_ADR_THR(0) |
                   XCVR_PHY_PHY_FSK_CFG_PD_LAT_BASE(0xF),
    .phy_fsk_misc = XCVR_PHY_PHY_FSK_MISC_FORCE_AA(0) |
                    XCVR_PHY_PHY_FSK_MISC_EL_EN(1) |
                    /* XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ and XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL  are mode/datarate dependent */
                    XCVR_PHY_PHY_FSK_MISC_MSK_EN(0) |
                    XCVR_PHY_PHY_FSK_MISC_FIFO_PRE_CHARGE(0x8) |
                    XCVR_PHY_PHY_FSK_MISC_CLK_CTRL(0xF),
    .phy_fad_ctrl = XCVR_PHY_FSK_FAD_CTRL_FAD_EN(0) |
                    XCVR_PHY_FSK_FAD_CTRL_FAD_PROC_DUR(0) |
                    XCVR_PHY_FSK_FAD_CTRL_FAD_PROC_DLY(0) |
                    XCVR_PHY_FSK_FAD_CTRL_FAD_THRESH(0) |
                    XCVR_PHY_FSK_FAD_CTRL_PHY_DBG_CFG(0x4),


    /* XCVR_RX_DIG configs */
    .rx_dig_ctrl_init_26mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_FSK_ZB_SEL(0) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DC_RESID_EN(1) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_SRC_RATE(0),

    .rx_dig_ctrl_init_32mhz = XCVR_RX_DIG_RX_DIG_CTRL_RX_FSK_ZB_SEL(0) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_DC_RESID_EN(1) | /* Depends on protocol */
                              XCVR_RX_DIG_RX_DIG_CTRL_RX_SRC_RATE(1),

    .agc_ctrl_0_init = XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_BBA_STEP_SZ(2) |
                       XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_RSSI_THRESH(0xEC) |
                       XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_LNA_STEP_SZ(2),

    .agc_man_agc_idx = XCVR_RX_DIG_AGC_MAN_AGC_IDX_AGC_IDX_CMP_PHY(PHY_AGC_PD_SWITCH_IDX),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ALPHA(1) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_EXT_DC_EN(1),

    /* XCVR_TX_DIG configs */
    .tx_gfsk_ctrl = XCVR_TX_DIG_GFSK_CTRL_GFSK_MULTIPLY_TABLE_MANUAL(0x4000) |
                    XCVR_TX_DIG_GFSK_CTRL_GFSK_MI(0) |
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


/* MODE& DATA RATE combined configuration */
const xcvr_mode_datarate_config_t xcvr_GFSK_BT_0p5_h_0p32_2mbps_config =
{
    .radio_mode = GFSK_BT_0p5_h_0p5,
    .data_rate = DR_2MBPS,

    .ana_sy_ctrl2.mask = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM_MASK,
    .ana_sy_ctrl2.init = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM(1), /* VCO KVM */
    .ana_rx_bba.mask = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL_MASK | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL_MASK,
    .ana_rx_bba.init = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL(0) | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL(0), /* BBA_BW_SEL and BBA2_BW_SEL */
    .ana_rx_tza.mask = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL_MASK,
    .ana_rx_tza.init = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL(0), /*TZA_BW_SEL */

    .phy_fsk_misc_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),
    .phy_fsk_misc_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),

    .phy_fsk_cfg_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),
    .phy_fsk_cfg_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),

    .phy_fsk_pd_cfg1_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0A) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),
    .phy_fsk_pd_cfg1_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0A) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),


    /* AGC configs */
    .agc_ctrl_0_init_26mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),
    .agc_ctrl_0_init_32mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),

    .agc_ctrl_1_init_26mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(7) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),
    .agc_ctrl_1_init_32mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(8) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),

    .agc_ctrl_2_init_26mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(7) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x09),
    .agc_ctrl_2_init_32mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(8) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x09),

    .agc_ctrl_3_init = XCVR_RX_DIG_AGC_CTRL_3_AGC_UNFREEZE_TIME(21),

    .dcoc_cal_gain_init = XCVR_RX_DIG_DCOC_CAL_GAIN_DCOC_LNA_CAL_GAIN2(7),
    .dcoc_cal_rcp_init = XCVR_RX_DIG_DCOC_CAL_RCP_ALPHA_CALC_RECIP(28),

    .dcoc_cal_iir_init_26mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(3) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(1),
    .dcoc_cal_iir_init_32mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(3) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(2),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ITER_FREEZE(3) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_NWIN(96) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_MIN_AGC_IDX(26),

    .dcoc_ctrl_1_init = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_IDX(3) |
                        XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_GS_IDX(3),

    /* BLE 26MHz Channel Filter  */
    /* All constant values are represented as 16 bits, register writes will remove unused bits */
    .rx_chf_coeffs_26mhz.rx_chf_coef_0  = 0x0003,
    .rx_chf_coeffs_26mhz.rx_chf_coef_1  = 0x0001,
    .rx_chf_coeffs_26mhz.rx_chf_coef_2  = 0xFFFC,
    .rx_chf_coeffs_26mhz.rx_chf_coef_3  = 0xFFF4,
    .rx_chf_coeffs_26mhz.rx_chf_coef_4  = 0xFFEB,
    .rx_chf_coeffs_26mhz.rx_chf_coef_5  = 0xFFE8,
    .rx_chf_coeffs_26mhz.rx_chf_coef_6  = 0xFFF0,
    .rx_chf_coeffs_26mhz.rx_chf_coef_7  = 0x0003,
    .rx_chf_coeffs_26mhz.rx_chf_coef_8  = 0x0022,
    .rx_chf_coeffs_26mhz.rx_chf_coef_9  = 0x0046,
    .rx_chf_coeffs_26mhz.rx_chf_coef_10 = 0x0065,
    .rx_chf_coeffs_26mhz.rx_chf_coef_11 = 0x0078,

    /* BLE 32MHz Channel Filter  */
    .rx_chf_coeffs_32mhz.rx_chf_coef_0  = 0xFFFE,
    .rx_chf_coeffs_32mhz.rx_chf_coef_1  = 0xFFFE,
    .rx_chf_coeffs_32mhz.rx_chf_coef_2  = 0x0002,
    .rx_chf_coeffs_32mhz.rx_chf_coef_3  = 0x000B,
    .rx_chf_coeffs_32mhz.rx_chf_coef_4  = 0x000D,
    .rx_chf_coeffs_32mhz.rx_chf_coef_5  = 0x0000,
    .rx_chf_coeffs_32mhz.rx_chf_coef_6  = 0xFFE6,
    .rx_chf_coeffs_32mhz.rx_chf_coef_7  = 0xFFD3,
    .rx_chf_coeffs_32mhz.rx_chf_coef_8  = 0xFFE4,
    .rx_chf_coeffs_32mhz.rx_chf_coef_9  = 0x0021,
    .rx_chf_coeffs_32mhz.rx_chf_coef_10 = 0x0077,
    .rx_chf_coeffs_32mhz.rx_chf_coef_11 = 0x00B4,

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

const xcvr_mode_datarate_config_t xcvr_GFSK_BT_0p5_h_0p32_1mbps_config =
{
    .radio_mode = GFSK_BT_0p5_h_0p32,
    .data_rate = DR_1MBPS,

    .ana_sy_ctrl2.mask = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM_MASK,
    .ana_sy_ctrl2.init = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM(0), /* VCO KVM */
    .ana_rx_bba.mask = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL_MASK | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL_MASK,
    .ana_rx_bba.init = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL(5) | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL(5), /* BBA_BW_SEL and BBA2_BW_SEL */
    .ana_rx_tza.mask = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL_MASK,
    .ana_rx_tza.init = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL(5), /*TZA_BW_SEL */

    .phy_fsk_misc_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),
    .phy_fsk_misc_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),

    .phy_fsk_cfg_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),
    .phy_fsk_cfg_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),

    .phy_fsk_pd_cfg1_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0A) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),
    .phy_fsk_pd_cfg1_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0A) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),


    /* AGC configs */
    .agc_ctrl_0_init_26mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),
    .agc_ctrl_0_init_32mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),

    .agc_ctrl_1_init_26mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(10) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),
    .agc_ctrl_1_init_32mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(12) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),

    .agc_ctrl_2_init_26mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(11) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x0A),
    .agc_ctrl_2_init_32mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(14) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x0A),

    .agc_ctrl_3_init = XCVR_RX_DIG_AGC_CTRL_3_AGC_UNFREEZE_TIME(21),

    .dcoc_cal_gain_init = XCVR_RX_DIG_DCOC_CAL_GAIN_DCOC_LNA_CAL_GAIN2(7),
    .dcoc_cal_rcp_init = XCVR_RX_DIG_DCOC_CAL_RCP_ALPHA_CALC_RECIP(28),

    .dcoc_cal_iir_init_26mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(2),
    .dcoc_cal_iir_init_32mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(1) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(1),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ITER_FREEZE(5) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_NWIN(28) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_MIN_AGC_IDX(26),

    .dcoc_ctrl_1_init = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_IDX(2) |
                        XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_GS_IDX(3),

    /* All constant values are represented as 16 bits, register writes will remove unused bits */
    .rx_chf_coeffs_26mhz.rx_chf_coef_0  = 0x0005,
    .rx_chf_coeffs_26mhz.rx_chf_coef_1  = 0x0004,
    .rx_chf_coeffs_26mhz.rx_chf_coef_2  = 0xFFFE,
    .rx_chf_coeffs_26mhz.rx_chf_coef_3  = 0xFFF5,
    .rx_chf_coeffs_26mhz.rx_chf_coef_4  = 0xFFEA,
    .rx_chf_coeffs_26mhz.rx_chf_coef_5  = 0xFFE5,
    .rx_chf_coeffs_26mhz.rx_chf_coef_6  = 0xFFEA,
    .rx_chf_coeffs_26mhz.rx_chf_coef_7  = 0xFFFD,
    .rx_chf_coeffs_26mhz.rx_chf_coef_8  = 0x001F,
    .rx_chf_coeffs_26mhz.rx_chf_coef_9  = 0x0046,
    .rx_chf_coeffs_26mhz.rx_chf_coef_10 = 0x006A,
    .rx_chf_coeffs_26mhz.rx_chf_coef_11 = 0x007F,

    /* 32MHz Channel Filter */
    .rx_chf_coeffs_32mhz.rx_chf_coef_0  = 0xFFFE,
    .rx_chf_coeffs_32mhz.rx_chf_coef_1  = 0xFFFC,
    .rx_chf_coeffs_32mhz.rx_chf_coef_2  = 0x0000,
    .rx_chf_coeffs_32mhz.rx_chf_coef_3  = 0x000A,
    .rx_chf_coeffs_32mhz.rx_chf_coef_4  = 0x0010,
    .rx_chf_coeffs_32mhz.rx_chf_coef_5  = 0x0005,
    .rx_chf_coeffs_32mhz.rx_chf_coef_6  = 0xFFE9,
    .rx_chf_coeffs_32mhz.rx_chf_coef_7  = 0xFFCF,
    .rx_chf_coeffs_32mhz.rx_chf_coef_8  = 0xFFDB,
    .rx_chf_coeffs_32mhz.rx_chf_coef_9  = 0x001C,
    .rx_chf_coeffs_32mhz.rx_chf_coef_10 = 0x0079,
    .rx_chf_coeffs_32mhz.rx_chf_coef_11 = 0x00BE,

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

const xcvr_mode_datarate_config_t xcvr_GFSK_BT_0p5_h_0p32_500kbps_config =
{
    .radio_mode = GFSK_BT_0p5_h_0p32,
    .data_rate = DR_500KBPS,

    .ana_sy_ctrl2.mask = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM_MASK,
    .ana_sy_ctrl2.init = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM(0), /* VCO KVM */
    .ana_rx_bba.mask = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL_MASK | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL_MASK,
    .ana_rx_bba.init = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL(5) | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL(5), /* BBA_BW_SEL and BBA2_BW_SEL */
    .ana_rx_tza.mask = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL_MASK,
    .ana_rx_tza.init = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL(5), /*TZA_BW_SEL */

    .phy_fsk_misc_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),
    .phy_fsk_misc_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),

    .phy_fsk_cfg_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),
    .phy_fsk_cfg_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),

    .phy_fsk_pd_cfg1_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0A) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),
    .phy_fsk_pd_cfg1_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0A) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),


    /* AGC configs */
    .agc_ctrl_0_init_26mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),
    .agc_ctrl_0_init_32mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(1) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),

    .agc_ctrl_1_init_26mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(17) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),
    .agc_ctrl_1_init_32mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(18) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),

    .agc_ctrl_2_init_26mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(17) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x18),
    .agc_ctrl_2_init_32mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(18) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x18),

    .agc_ctrl_3_init = XCVR_RX_DIG_AGC_CTRL_3_AGC_UNFREEZE_TIME(21),

    .dcoc_cal_gain_init = XCVR_RX_DIG_DCOC_CAL_GAIN_DCOC_LNA_CAL_GAIN2(7),
    .dcoc_cal_rcp_init = XCVR_RX_DIG_DCOC_CAL_RCP_ALPHA_CALC_RECIP(28),

    .dcoc_cal_iir_init_26mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(2) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(0),
    .dcoc_cal_iir_init_32mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(1) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(1),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ITER_FREEZE(3) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_NWIN(26) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_MIN_AGC_IDX(26),

    .dcoc_ctrl_1_init = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_IDX(1) |
                        XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_GS_IDX(2),

    /* All constant values are represented as 16 bits, register writes will remove unused bits */
    .rx_chf_coeffs_26mhz.rx_chf_coef_0 = 0x0003,
    .rx_chf_coeffs_26mhz.rx_chf_coef_1 = 0x0007,
    .rx_chf_coeffs_26mhz.rx_chf_coef_2 = 0x0007,
    .rx_chf_coeffs_26mhz.rx_chf_coef_3 = 0x0001,
    .rx_chf_coeffs_26mhz.rx_chf_coef_4 = 0xFFF5,
    .rx_chf_coeffs_26mhz.rx_chf_coef_5 = 0xFFE8,
    .rx_chf_coeffs_26mhz.rx_chf_coef_6 = 0xFFE3,
    .rx_chf_coeffs_26mhz.rx_chf_coef_7 = 0xFFEF,
    .rx_chf_coeffs_26mhz.rx_chf_coef_8 = 0x0010,
    .rx_chf_coeffs_26mhz.rx_chf_coef_9 = 0x003D,
    .rx_chf_coeffs_26mhz.rx_chf_coef_10 = 0x006B,
    .rx_chf_coeffs_26mhz.rx_chf_coef_11 = 0x0087,

    /* 32MHz Channel Filter  */
    .rx_chf_coeffs_32mhz.rx_chf_coef_0 = 0x0002,
    .rx_chf_coeffs_32mhz.rx_chf_coef_1 = 0x0000,
    .rx_chf_coeffs_32mhz.rx_chf_coef_2 = 0xFFF9,
    .rx_chf_coeffs_32mhz.rx_chf_coef_3 = 0xFFF8,
    .rx_chf_coeffs_32mhz.rx_chf_coef_4 = 0x0007,
    .rx_chf_coeffs_32mhz.rx_chf_coef_5 = 0x0018,
    .rx_chf_coeffs_32mhz.rx_chf_coef_6 = 0x000D,
    .rx_chf_coeffs_32mhz.rx_chf_coef_7 = 0xFFE0,
    .rx_chf_coeffs_32mhz.rx_chf_coef_8 = 0xFFC3,
    .rx_chf_coeffs_32mhz.rx_chf_coef_9 = 0xFFF3,
    .rx_chf_coeffs_32mhz.rx_chf_coef_10 = 0x006F,
    .rx_chf_coeffs_32mhz.rx_chf_coef_11 = 0x00DC,

    .rx_rccal_ctrl_0 = XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_MANUAL(31) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_DIS(1) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_RCCAL_SMP_DLY(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_RCCAL_COMP_INV(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_MANUAL(31) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_DIS(1),
    .rx_rccal_ctrl_1 = XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_MANUAL(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_DIS(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_MANUAL(31) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_DIS(1),

    .tx_fsk_scale_26mhz = XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_0(0x1627) | XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_1(0x09d9),
    .tx_fsk_scale_32mhz = XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_0(0x1800) | XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_1(0x0800),
};

const xcvr_mode_datarate_config_t xcvr_GFSK_BT_0p5_h_0p32_250kbps_config =
{
    .radio_mode = GFSK_BT_0p5_h_0p32,
    .data_rate = DR_250KBPS,

    .ana_sy_ctrl2.mask = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM_MASK,
    .ana_sy_ctrl2.init = XCVR_ANALOG_SY_CTRL_2_SY_VCO_KVM(0), /* VCO KVM */
    .ana_rx_bba.mask = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL_MASK | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL_MASK,
    .ana_rx_bba.init = XCVR_ANALOG_RX_BBA_RX_BBA_BW_SEL(5) | XCVR_ANALOG_RX_BBA_RX_BBA2_BW_SEL(5), /* BBA_BW_SEL and BBA2_BW_SEL */
    .ana_rx_tza.mask = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL_MASK,
    .ana_rx_tza.init = XCVR_ANALOG_RX_TZA_RX_TZA_BW_SEL(5), /*TZA_BW_SEL */

    .phy_fsk_misc_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),
    .phy_fsk_misc_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_MISC_EL_WIN_SZ(0xF) |
                                        XCVR_PHY_PHY_FSK_MISC_PD_THRESH_B(0xE0) |
                                        XCVR_PHY_PHY_FSK_MISC_EL_INTERVAL(0x10),

    .phy_fsk_cfg_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),
    .phy_fsk_cfg_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_CFG_PD_MODE_SW_EN(0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_A(0x0) |
                                       XCVR_PHY_PHY_FSK_CFG_PD_MODE_B(0x0),

    .phy_fsk_pd_cfg1_mode_datarate_26mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0D) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),
    .phy_fsk_pd_cfg1_mode_datarate_32mhz = XCVR_PHY_PHY_FSK_PD_CFG1_PD_FREQ_THRESH(0x0D) |
                                           XCVR_PHY_PHY_FSK_PD_CFG1_PD_THRESH(0xE0),


    /* AGC configs */
    .agc_ctrl_0_init_26mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),
    .agc_ctrl_0_init_32mhz = XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_EN(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_SLOW_AGC_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_UP_SRC(0) |
                             XCVR_RX_DIG_AGC_CTRL_0_AGC_DOWN_RSSI_THRESH(0x00),

    .agc_ctrl_1_init_26mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(22) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),
    .agc_ctrl_1_init_32mhz = XCVR_RX_DIG_AGC_CTRL_1_LNA_GAIN_SETTLE_TIME(22) |
                             XCVR_RX_DIG_AGC_CTRL_1_PRESLOW_EN(0),

    .agc_ctrl_2_init_26mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(22) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x30),
    .agc_ctrl_2_init_32mhz = XCVR_RX_DIG_AGC_CTRL_2_BBA_GAIN_SETTLE_TIME(22) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_LO(5) |
                             XCVR_RX_DIG_AGC_CTRL_2_BBA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_LO(3) |
                             XCVR_RX_DIG_AGC_CTRL_2_TZA_PDET_SEL_HI(6) |
                             XCVR_RX_DIG_AGC_CTRL_2_AGC_FAST_EXPIRE(0x30),

    .agc_ctrl_3_init = XCVR_RX_DIG_AGC_CTRL_3_AGC_UNFREEZE_TIME(21),

    .dcoc_cal_gain_init = XCVR_RX_DIG_DCOC_CAL_GAIN_DCOC_LNA_CAL_GAIN2(7),
    .dcoc_cal_rcp_init = XCVR_RX_DIG_DCOC_CAL_RCP_ALPHA_CALC_RECIP(28),

    .dcoc_cal_iir_init_26mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(0),
    .dcoc_cal_iir_init_32mhz = XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR3A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR2A_IDX(0) |
                               XCVR_RX_DIG_DCOC_CAL_IIR_DCOC_CAL_IIR1A_IDX(0),

    .dc_resid_ctrl_init = XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_ITER_FREEZE(3) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_NWIN(18) |
                          XCVR_RX_DIG_DC_RESID_CTRL_DC_RESID_MIN_AGC_IDX(26),

    .dcoc_ctrl_1_init = XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_IDX(0) |
                        XCVR_RX_DIG_DCOC_CTRL_1_DCOC_ALPHA_RADIUS_GS_IDX(1),

    /* All constant values are represented as 16 bits, register writes will remove unused bits */
    .rx_chf_coeffs_26mhz.rx_chf_coef_0 = 0xFFFD,
    .rx_chf_coeffs_26mhz.rx_chf_coef_1 = 0xFFFE,
    .rx_chf_coeffs_26mhz.rx_chf_coef_2 = 0x0004,
    .rx_chf_coeffs_26mhz.rx_chf_coef_3 = 0x000C,
    .rx_chf_coeffs_26mhz.rx_chf_coef_4 = 0x000B,
    .rx_chf_coeffs_26mhz.rx_chf_coef_5 = 0xFFFD,
    .rx_chf_coeffs_26mhz.rx_chf_coef_6 = 0xFFE6,
    .rx_chf_coeffs_26mhz.rx_chf_coef_7 = 0xFFDC,
    .rx_chf_coeffs_26mhz.rx_chf_coef_8 = 0xFFF1,
    .rx_chf_coeffs_26mhz.rx_chf_coef_9 = 0x0029,
    .rx_chf_coeffs_26mhz.rx_chf_coef_10 = 0x006F,
    .rx_chf_coeffs_26mhz.rx_chf_coef_11 = 0x00A0,

    /* 32MHz Channel Filter  */
    .rx_chf_coeffs_32mhz.rx_chf_coef_0 = 0xFFFE,
    .rx_chf_coeffs_32mhz.rx_chf_coef_1 = 0x0000,
    .rx_chf_coeffs_32mhz.rx_chf_coef_2 = 0x0006,
    .rx_chf_coeffs_32mhz.rx_chf_coef_3 = 0x0002,
    .rx_chf_coeffs_32mhz.rx_chf_coef_4 = 0xFFF1,
    .rx_chf_coeffs_32mhz.rx_chf_coef_5 = 0xFFF8,
    .rx_chf_coeffs_32mhz.rx_chf_coef_6 = 0x001C,
    .rx_chf_coeffs_32mhz.rx_chf_coef_7 = 0x0018,
    .rx_chf_coeffs_32mhz.rx_chf_coef_8 = 0xFFD1,
    .rx_chf_coeffs_32mhz.rx_chf_coef_9 = 0xFFBD,
    .rx_chf_coeffs_32mhz.rx_chf_coef_10 = 0x004B,
    .rx_chf_coeffs_32mhz.rx_chf_coef_11 = 0x0103,

    .rx_rccal_ctrl_0 = XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_MANUAL(31) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_BBA_RCCAL_DIS(1) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_RCCAL_SMP_DLY(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_RCCAL_COMP_INV(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_MANUAL(31) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL0_TZA_RCCAL_DIS(1),
    .rx_rccal_ctrl_1 = XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_MANUAL(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_ADC_RCCAL_DIS(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_OFFSET(0) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_MANUAL(31) |
                       XCVR_RX_DIG_RX_RCCAL_CTRL1_BBA2_RCCAL_DIS(1),

    .tx_fsk_scale_26mhz = XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_0(0x1627) | XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_1(0x09d9),
    .tx_fsk_scale_32mhz = XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_0(0x1800) | XCVR_TX_DIG_FSK_SCALE_FSK_MODULATION_SCALE_1(0x0800),
};



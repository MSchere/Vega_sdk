/*
 * Copyright 2018 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

#define PIN7_IDX                    7u      /*!< Pin number for pin 7 in a port */
#define PIN8_IDX                    8u      /*!< Pin number for pin 8 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core1, enableClock: 'true'}
- pin_list:
  - {pin_num: N2, peripheral: LPUART0, signal: RX, pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1}
  - {pin_num: P3, peripheral: LPUART0, signal: TX, pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortC);                        /* Clock Gate Control:0x01u */

    PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);         /* PORTC7 (pin N2) is configured as LPUART_RX */   
    PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);         /* PORTC8 (pin P3) is configured as LPUART0_TX */   
}

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitGT202Shield:
- options: {coreID: core1, enableClock: 'true'}
- pin_list:
  - {pin_num: E1, peripheral: LPSPI0, signal: PCS2, pin_signal: PTB6/LLWU_P7/LPSPI0_PCS2/LPI2C1_SDA/SAI0_RX_BCLK/FB_AD7/TPM0_CH4/RF0_BSM_FRAME}
  - {pin_num: D2, peripheral: LPSPI0, signal: OUT, pin_signal: PTB5/RF0_ACTIVE/LPSPI0_SOUT/LPUART1_RTS_b/SAI0_MCLK/FB_AD8/TPM0_CH3}
  - {pin_num: C2, peripheral: LPSPI0, signal: SCK, pin_signal: ADC0_SE1/PTB4/LLWU_P6/RF0_RF_OFF/RF0_DFT_RESET/LPSPI0_SCK/LPUART1_CTS_b/SAI0_TX_BCLK/FB_AD9/TPM0_CH2}
  - {pin_num: E2, peripheral: LPSPI0, signal: IN, pin_signal: ADC0_SE2/PTB7/LLWU_P8/LPSPI0_SIN/LPI2C1_SDAS/SAI0_RX_FS/FB_AD6/TPM0_CH5/RF0_BSM_DATA}
  - {pin_num: B1, peripheral: GPIOB, signal: 'GPIO, 2', pin_signal: PTB2/LLWU_P5/RF0_RFOSC_EN/LPSPI0_PCS1/LPUART1_RX/SAI0_TX_D0/FB_AD11/TPM0_CH0, direction: OUTPUT,
    pull_select: down, pull_enable: enable}
  - {pin_num: C3, peripheral: GPIOB, signal: 'GPIO, 1', pin_signal: PTB1/LLWU_P4/LPUART2_RX/LPSPI1_PCS0/SAI0_TX_D1/FB_AD12/LPTMR1_ALT3, direction: INPUT, pull_select: up,
    pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitGT202Shield
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitGT202Shield(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAsGpio);          /* PORTB1 (pin C3) is configured as PTB1 */
  PORTB->PCR[1] = ((PORTB->PCR[1] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
    );
  PORT_SetPinMux(PORTB, PIN2_IDX, kPORT_MuxAsGpio);          /* PORTB2 (pin B1) is configured as PTB2 */
  PORTB->PCR[2] = ((PORTB->PCR[2] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
    );
  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAlt2);            /* PORTB4 (pin C2) is configured as LPSPI0_SCK */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAlt2);            /* PORTB5 (pin D2) is configured as LPSPI0_SOUT */
  PORT_SetPinMux(PORTB, PIN6_IDX, kPORT_MuxAlt2);            /* PORTB6 (pin E1) is configured as LPSPI0_PCS2 */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAlt2);            /* PORTB7 (pin E2) is configured as LPSPI0_SIN */
}


#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSilex2401Shield:
- options: {coreID: core1, enableClock: 'true'}
- pin_list:
  - {pin_num: E1, peripheral: LPSPI0, signal: PCS2, pin_signal: PTB6/LLWU_P7/LPSPI0_PCS2/LPI2C1_SDA/SAI0_RX_BCLK/FB_AD7/TPM0_CH4/RF0_BSM_FRAME}
  - {pin_num: C2, peripheral: LPSPI0, signal: SCK, pin_signal: ADC0_SE1/PTB4/LLWU_P6/RF0_RF_OFF/RF0_DFT_RESET/LPSPI0_SCK/LPUART1_CTS_b/SAI0_TX_BCLK/FB_AD9/TPM0_CH2}
  - {pin_num: D2, peripheral: LPSPI0, signal: OUT, pin_signal: PTB5/RF0_ACTIVE/LPSPI0_SOUT/LPUART1_RTS_b/SAI0_MCLK/FB_AD8/TPM0_CH3}
  - {pin_num: E2, peripheral: LPSPI0, signal: IN, pin_signal: ADC0_SE2/PTB7/LLWU_P8/LPSPI0_SIN/LPI2C1_SDAS/SAI0_RX_FS/FB_AD6/TPM0_CH5/RF0_BSM_DATA}
  - {pin_num: G2, peripheral: GPIOB, signal: 'GPIO, 14', pin_signal: PTB14/LPUART2_RTS_b/LPI2C1_SCL/LPI2C0_SCLS/FB_AD24/TPM3_CH1/FXIO0_D4, direction: OUTPUT, pull_select: down,
    pull_enable: enable}
  - {pin_num: A3, peripheral: GPIOA, signal: 'GPIO, 27', pin_signal: PTA27/LPUART1_CTS_b/LPSPI3_SIN/FB_AD29, direction: INPUT, pull_select: up, pull_enable: enable}
  - {pin_num: B2, peripheral: GPIOA, signal: 'GPIO, 30', pin_signal: PTA30_1/LLWU_P3_1/LPUART2_CTS_b_1/LPSPI1_SOUT_1/FB_AD14_1/TPM1_CH0_1/LPTMR2_ALT2_1, direction: OUTPUT,
    pull_select: down, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSilex2401Shield
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSilex2401Shield(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN27_IDX, kPORT_MuxAsGpio);         /* PORTA27 (pin A3) is configured as PTA27 */
  PORTA->PCR[27] = ((PORTA->PCR[27] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
    );
  PORT_SetPinMux(PORTA, PIN30_IDX, kPORT_MuxAsGpio);         /* PORTA30 (pin B2) is configured as PTA30_1 */
  PORTA->PCR[30] = ((PORTA->PCR[30] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
    );
  PORT_SetPinMux(PORTB, PIN14_IDX, kPORT_MuxAsGpio);         /* PORTB14 (pin G2) is configured as PTB14 */
  PORTB->PCR[14] = ((PORTB->PCR[14] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
    );
  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAlt2);            /* PORTB4 (pin C2) is configured as LPSPI0_SCK */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAlt2);            /* PORTB5 (pin D2) is configured as LPSPI0_SOUT */
  PORT_SetPinMux(PORTB, PIN6_IDX, kPORT_MuxAlt2);            /* PORTB6 (pin E1) is configured as LPSPI0_PCS2 */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAlt2);            /* PORTB7 (pin E2) is configured as LPSPI0_SIN */
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
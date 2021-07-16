/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v3.0
processor: RV32M1
package_id: RV32M1
mcu_data: ksdk2_0
processor_version: 0.0.5
board: RV32M1_VEGA
pin_labels:
- {pin_num: R14, pin_signal: LPCMP1_IN4/PTE0/EWM_IN, label: LED_STS, identifier: LED_STS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 * 
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 * 
 *END**************************************************************************/
void BOARD_InitBootPins(void) {
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins_ri5cy:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */
#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins_ri5cy
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins_ri5cy(void)
{
    BOARD_InitLPUART();
    CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

    PORT_SetPinMux(PORTC, PIN29_IDX, kPORT_MuxAlt2);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
    PORTC->PCR[29] = ((PORTC->PCR[29] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
    PORT_SetPinMux(PORTC, PIN30_IDX, kPORT_MuxAlt2);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
    PORTC->PCR[30] = ((PORTC->PCR[30] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
}


/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins_cm4
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins_cm4(void)
{
    BOARD_InitLPUART();
    CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

    PORT_SetPinMux(PORTC, PIN29_IDX, kPORT_MuxAlt2);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
    PORTC->PCR[29] = ((PORTC->PCR[29] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
    PORT_SetPinMux(PORTC, PIN30_IDX, kPORT_MuxAlt2);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
    PORTC->PCR[30] = ((PORTC->PCR[30] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins_zero_riscy:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins_zero_riscy
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins_zero_riscy(void)
{
    CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

    PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAlt2);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
    PORTB->PCR[0] = ((PORTB->PCR[0] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
    PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAlt2);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
    PORTB->PCR[1] = ((PORTB->PCR[1] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
}

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins_cm0p
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins_cm0p(void)
{
    CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

    PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAlt2);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
    PORTB->PCR[0] = ((PORTB->PCR[0] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
    PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAlt2);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
    PORTB->PCR[1] = ((PORTB->PCR[1] &
      (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
        | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
        | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
        | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
        | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
      );
}

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitButtons:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: B10, peripheral: GPIOA, signal: 'GPIO, 0', pin_signal: PTA0/NMI_b, direction: INPUT, slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable,
    passive_filter: disable}
  - {pin_num: P16, peripheral: GPIOE, signal: 'GPIO, 8', pin_signal: ADC0_SE22/PTE8/LLWU_P23/SDHC0_D5/LPUART3_RX/LPSPI3_SIN/TPM1_CH0/LPTMR2_ALT1, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: N16, peripheral: GPIOE, signal: 'GPIO, 9', pin_signal: ADC0_SE23/PTE9/LLWU_P24/SDHC0_CMD/LPUART3_TX/LPSPI3_PCS0/TPM1_CH1/FXIO0_D0, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: L12, peripheral: GPIOE, signal: 'GPIO, 12', pin_signal: PTE12/LLWU_P26/SDHC0_D2/LPI2C3_SDAS/TPM3_CLKIN/FXIO0_D2, direction: INPUT, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitButtons
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitButtons(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t porta0_pinB10_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA0 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTA, PIN0_IDX, &porta0_pinB10_config); /* PORTA0 (pin B10) is configured as PTA0 */
  const port_pin_config_t porte12_pinL12_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE12 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN12_IDX, &porte12_pinL12_config); /* PORTE12 (pin L12) is configured as PTE12 */
  const port_pin_config_t porte8_pinP16_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE8 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN8_IDX, &porte8_pinP16_config); /* PORTE8 (pin P16) is configured as PTE8 */
  const port_pin_config_t porte9_pinN16_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE9 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN9_IDX, &porte9_pinN16_config); /* PORTE9 (pin N16) is configured as PTE9 */
}



#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port */
#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port */
#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLEDs:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: B6, peripheral: GPIOA, signal: 'GPIO, 22', pin_signal: PTA22/LLWU_P2/LPSPI2_PCS2/LPI2C2_HREQ/FB_AD16/TPM2_CH2, direction: OUTPUT, slew_rate: fast, open_drain: disable,
    pull_select: down, pull_enable: disable}
  - {pin_num: E6, peripheral: GPIOA, signal: 'GPIO, 23', pin_signal: PTA23/LPSPI2_SIN/LPSPI1_PCS3/LPI2C2_SDA/FB_AD15/TPM2_CH1, direction: OUTPUT, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: D6, peripheral: GPIOA, signal: 'GPIO, 24', pin_signal: PTA24/LPSPI2_PCS0/LPSPI1_SCK/LPI2C2_SCL/FB_OE_b/TPM2_CH0, direction: OUTPUT, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: R14, peripheral: GPIOE, signal: 'GPIO, 0', pin_signal: LPCMP1_IN4/PTE0/EWM_IN, direction: OUTPUT, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLEDs
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLEDs(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t porta22_pinB6_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA22 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTA, PIN22_IDX, &porta22_pinB6_config); /* PORTA22 (pin B6) is configured as PTA22 */
  const port_pin_config_t porta23_pinE6_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA23 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTA, PIN23_IDX, &porta23_pinE6_config); /* PORTA23 (pin E6) is configured as PTA23 */
  const port_pin_config_t porta24_pinD6_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA24 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTA, PIN24_IDX, &porta24_pinD6_config); /* PORTA24 (pin D6) is configured as PTA24 */
  const port_pin_config_t porte0_pinR14_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE0 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN0_IDX, &porte0_pinR14_config); /* PORTE0 (pin R14) is configured as PTE0 */
}


#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLPUART:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: N2, peripheral: LPUART0, signal: RX, pin_signal: LPCMP0_IN0/PTC7/LLWU_P15/LPSPI0_PCS3/LPUART0_RX/LPI2C1_HREQ/TPM0_CH0/LPTMR1_ALT1, slew_rate: fast,
    open_drain: disable, pull_select: down, pull_enable: disable}
  - {pin_num: P3, peripheral: LPUART0, signal: TX, pin_signal: LPCMP0_IN1/PTC8/LPSPI0_SCK/LPUART0_TX/LPI2C0_HREQ/TPM0_CH1, slew_rate: fast, open_drain: disable, pull_select: down,
    pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLPUART
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLPUART(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAlt3);            /* PORTC7 (pin N2) is configured as LPUART0_RX */
  PORTC->PCR[7] = ((PORTC->PCR[7] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
      | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
    );
  PORT_SetPinMux(PORTC, PIN8_IDX, kPORT_MuxAlt3);            /* PORTC8 (pin P3) is configured as LPUART0_TX */
  PORTC->PCR[8] = ((PORTC->PCR[8] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x00u)                                   /* Pull Select: 0x00u */
      | PORT_PCR_PE(0x00u)                                   /* Pull Enable: 0x00u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
    );
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitOSC:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: E16, peripheral: RTC, signal: EXTAL32, pin_signal: EXTAL32}
  - {pin_num: E17, peripheral: RTC, signal: XTAL32, pin_signal: XTAL32}
  - {pin_num: A11, peripheral: RF0, signal: XTAL_RF, pin_signal: XTAL_RF}
  - {pin_num: B11, peripheral: RF0, signal: EXTAL_RF, pin_signal: EXTAL_RF}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitOSC
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitOSC(void) {
}


#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */

#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port */
#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitACCEL:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: G17, peripheral: LPI2C3, signal: SCL, pin_signal: PTE30/LPUART3_TX/LPI2C3_SCL/TPM2_CLKIN/FXIO0_D31, slew_rate: fast, open_drain: enable, pull_select: up,
    pull_enable: enable}
  - {pin_num: G15, peripheral: LPI2C3, signal: SDA, pin_signal: PTE29/LPUART3_RX/LPI2C3_SDA/FXIO0_D30, slew_rate: fast, open_drain: enable, pull_select: up, pull_enable: enable}
  - {pin_num: R16, peripheral: GPIOE, signal: 'GPIO, 1', pin_signal: ADC0_SE18/PTE1/LLWU_P21/SDHC0_D1/LPI2C0_SDAS/LPSPI3_PCS1/EWM_OUT_b/LPTMR1_ALT2, direction: INPUT,
    slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: J16, peripheral: GPIOE, signal: 'GPIO, 22', pin_signal: PTE22/SAI0_RX_D1/LPI2C3_HREQ/TPM2_CH5/FXIO0_D11, direction: INPUT, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable}
  - {pin_num: H14, peripheral: GPIOE, signal: 'GPIO, 27', pin_signal: PTE27/LPUART3_CTS_b/LPI2C3_SDAS/FXIO0_D28, direction: OUTPUT, slew_rate: slow, open_drain: disable,
    pull_select: down, pull_enable: disable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitACCEL
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitACCEL(void) {
  CLOCK_EnableClock(kCLOCK_PortE);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t porte1_pinR16_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE1 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN1_IDX, &porte1_pinR16_config); /* PORTE1 (pin R16) is configured as PTE1 */
  const port_pin_config_t porte22_pinJ16_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE22 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN22_IDX, &porte22_pinJ16_config); /* PORTE22 (pin J16) is configured as PTE22 */
  const port_pin_config_t porte27_pinH14_config = {
    kPORT_PullDisable,                                       /* Internal pull-up/down resistor is disabled */
    kPORT_SlowSlewRate,                                      /* Slow slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTE27 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN27_IDX, &porte27_pinH14_config); /* PORTE27 (pin H14) is configured as PTE27 */
  const port_pin_config_t porte29_pinG15_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainEnable,                                   /* Open drain is enabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C3_SDA */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN29_IDX, &porte29_pinG15_config); /* PORTE29 (pin G15) is configured as LPI2C3_SDA */
  const port_pin_config_t porte30_pinG17_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainEnable,                                   /* Open drain is enabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt3,                                           /* Pin is configured as LPI2C3_SCL */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTE, PIN30_IDX, &porte30_pinG17_config); /* PORTE30 (pin G17) is configured as LPI2C3_SCL */
}



#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitLIGHT_SENSOR:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: F4, peripheral: GPIOB, signal: 'GPIO, 9', pin_signal: ADC0_SE3/PTB9/SPM_LPREQ/LPSPI0_PCS1/LPI2C1_SCL/SAI0_RX_D1/FB_RW_b/FXIO0_D0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitLIGHT_SENSOR
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitLIGHT_SENSOR(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN9_IDX, kPORT_MuxAsGpio);          /* PORTB9 (pin F4) is configured as PTB9 */
}


/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitUSB:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: T12, peripheral: USB0, signal: DM, pin_signal: USB0_DM}
  - {pin_num: T11, peripheral: USB0, signal: DP, pin_signal: USB0_DP}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitUSB
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitUSB(void) {
}


#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */

#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN8_IDX                         8u   /*!< Pin number for pin 8 in a port */

#define PIN9_IDX                         9u   /*!< Pin number for pin 9 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */

#define PIN27_IDX                       27u   /*!< Pin number for pin 27 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSDHC:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: R11, peripheral: SDHC0, signal: 'DATA, 2', pin_signal: ADC0_SE14/PTD11/SDHC0_D2/USB0_SOF_OUT/LPI2C1_SCL/CLKOUT/TPM2_CH0/FXIO0_D31, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: P11, peripheral: SDHC0, signal: 'DATA, 3', pin_signal: ADC0_SE13/PTD10/LLWU_P20/SDHC0_D3/LPSPI2_PCS0/LPI2C1_SDA/TRACE_CLK_OUT/TPM2_CH1/FXIO0_D30, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: U11, peripheral: SDHC0, signal: CMD, pin_signal: ADC0_SE12/PTD9/SDHC0_CMD/LPSPI2_SIN/LPI2C1_SCLS/TRACE_DATA0/TPM2_CH2/FXIO0_D29, slew_rate: fast, open_drain: disable,
    pull_select: up, pull_enable: enable}
  - {pin_num: T9, peripheral: SDHC0, signal: DCLK, pin_signal: ADC0_SE11/PTD8/LLWU_P19/SDHC0_DCLK/LPSPI2_PCS2/LPI2C1_SDAS/TRACE_DATA1/TPM2_CH3/FXIO0_D28, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: P10, peripheral: SDHC0, signal: 'DATA, 0', pin_signal: ADC0_SE10/PTD7/SDHC0_D0/LPSPI2_SOUT/EMVSIM0_PD/TRACE_DATA2/TPM2_CH4/FXIO0_D27, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: U9, peripheral: SDHC0, signal: 'DATA, 1', pin_signal: ADC0_SE9/PTD6/SDHC0_D1/LPSPI2_SCK/EMVSIM0_IO/TRACE_DATA3/TPM2_CH5/FXIO0_D26, slew_rate: fast,
    open_drain: disable, pull_select: up, pull_enable: enable}
  - {pin_num: P6, peripheral: GPIOC, signal: 'GPIO, 27', pin_signal: PTC27/TPM0_CH4, direction: INPUT, slew_rate: fast, open_drain: disable, pull_select: up, pull_enable: enable}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSDHC
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSDHC(void) {
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Clock Gate Control: 0x01u */

  const port_pin_config_t portc27_pinP6_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAsGpio,                                         /* Pin is configured as PTC27 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTC, PIN27_IDX, &portc27_pinP6_config); /* PORTC27 (pin P6) is configured as PTC27 */
  PORT_SetPinMux(PORTD, PIN10_IDX, kPORT_MuxAlt2);           /* PORTD10 (pin P11) is configured as SDHC0_D3 */
  PORTD->PCR[10] = ((PORTD->PCR[10] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
    );
  PORT_SetPinMux(PORTD, PIN11_IDX, kPORT_MuxAlt2);           /* PORTD11 (pin R11) is configured as SDHC0_D2 */
  PORTD->PCR[11] = ((PORTD->PCR[11] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
    );
  const port_pin_config_t portd6_pinU9_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_D1 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN6_IDX, &portd6_pinU9_config);  /* PORTD6 (pin U9) is configured as SDHC0_D1 */
  const port_pin_config_t portd7_pinP10_config = {
    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
    kPORT_LowDriveStrength,                                  /* Low drive strength is configured */
    kPORT_MuxAlt2,                                           /* Pin is configured as SDHC0_D0 */
    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
  };
  PORT_SetPinConfig(PORTD, PIN7_IDX, &portd7_pinP10_config); /* PORTD7 (pin P10) is configured as SDHC0_D0 */
  PORT_SetPinMux(PORTD, PIN8_IDX, kPORT_MuxAlt2);            /* PORTD8 (pin T9) is configured as SDHC0_DCLK */
  PORTD->PCR[8] = ((PORTD->PCR[8] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
    );
  PORT_SetPinMux(PORTD, PIN9_IDX, kPORT_MuxAlt2);            /* PORTD9 (pin U11) is configured as SDHC0_CMD */
  PORTD->PCR[9] = ((PORTD->PCR[9] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x00u)                                  /* Open Drain Enable: 0x00u */
    );
}



#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port */

#define PIN23_IDX                       23u   /*!< Pin number for pin 23 in a port */

#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitRGB:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: B6, peripheral: TPM2, signal: 'CH, 2', pin_signal: PTA22/LLWU_P2/LPSPI2_PCS2/LPI2C2_HREQ/FB_AD16/TPM2_CH2}
  - {pin_num: E6, peripheral: TPM2, signal: 'CH, 1', pin_signal: PTA23/LPSPI2_SIN/LPSPI1_PCS3/LPI2C2_SDA/FB_AD15/TPM2_CH1}
  - {pin_num: D6, peripheral: TPM2, signal: 'CH, 0', pin_signal: PTA24/LPSPI2_PCS0/LPSPI1_SCK/LPI2C2_SCL/FB_OE_b/TPM2_CH0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitRGB
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitRGB(void) {
  CLOCK_EnableClock(kCLOCK_PortA);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTA, PIN22_IDX, kPORT_MuxAlt6);           /* PORTA22 (pin B6) is configured as TPM2_CH2 */
  PORT_SetPinMux(PORTA, PIN23_IDX, kPORT_MuxAlt6);           /* PORTA23 (pin E6) is configured as TPM2_CH1 */
  PORT_SetPinMux(PORTA, PIN24_IDX, kPORT_MuxAlt6);           /* PORTA24 (pin D6) is configured as TPM2_CH0 */
}

#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

#define PIN20_IDX                       20u   /*!< Pin number for pin 20 in a port */
#define PIN21_IDX                       21u   /*!< Pin number for pin 21 in a port */

#define PIN22_IDX                       22u   /*!< Pin number for pin 22 in a port */

#define PIN24_IDX                       24u   /*!< Pin number for pin 24 in a port */

/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitSPI:
- options: {coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: J1, peripheral: LPSPI1, signal: SCK, pin_signal: PTB20/LLWU_P11/LPSPI1_SCK/LPUART2_CTS_b/FB_CS0_b/TPM1_CH0/FXIO0_D10}
  - {pin_num: J2, peripheral: LPSPI1, signal: OUT, pin_signal: PTB21/LPSPI1_SOUT/LPUART2_RTS_b/LPI2C2_HREQ/FB_AD4/TPM1_CH1/FXIO0_D11}
  - {pin_num: L1, peripheral: LPSPI1, signal: PCS2, pin_signal: PTB22/LLWU_P12/LPSPI1_PCS2/LPUART0_CTS_b/LPI2C2_SDA/FB_AD3/TPM2_CLKIN/FXIO0_D12}
  - {pin_num: L2, peripheral: LPSPI1, signal: IN, pin_signal: PTB24/LPSPI1_SIN/LPUART0_RTS_b/LPI2C2_SCL/FB_AD2/EWM_IN/FXIO0_D13}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitSPI
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitSPI(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTB, PIN20_IDX, kPORT_MuxAlt2);           /* PORTB20 (pin J1) is configured as LPSPI1_SCK */
  PORT_SetPinMux(PORTB, PIN21_IDX, kPORT_MuxAlt2);           /* PORTB21 (pin J2) is configured as LPSPI1_SOUT */
  PORT_SetPinMux(PORTB, PIN22_IDX, kPORT_MuxAlt2);           /* PORTB22 (pin L1) is configured as LPSPI1_PCS2 */
  PORT_SetPinMux(PORTB, PIN24_IDX, kPORT_MuxAlt2);           /* PORTB24 (pin L2) is configured as LPSPI1_SIN */
  
  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAlt2);           /* PORTB24 (pin L2) is configured as LPSPI1_SIN */
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAlt2);           /* PORTB24 (pin L2) is configured as LPSPI1_SIN */
  PORT_SetPinMux(PORTB, PIN6_IDX, kPORT_MuxAlt2);           /* PORTB24 (pin L2) is configured as LPSPI1_SIN */
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAlt2);           /* PORTB24 (pin L2) is configured as LPSPI1_SIN */
}

void BOARD_InitI2C(void) {
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Clock Gate Control: 0x01u */
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Clock Gate Control: 0x01u */

  PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_MuxAlt4);           /* PORTC10 (pin R2) is configured as LPI2C0_SCL */
  PORTC->PCR[10] = ((PORTC->PCR[10] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x01u)                                  /* Open Drain Enable: 0x01u */
     );
        
  PORT_SetPinMux(PORTC, PIN9_IDX, kPORT_MuxAlt4);            /* PORTC9 (pin R1) is configured as LPI2C0_SDA */
  PORTC->PCR[9] = ((PORTC->PCR[9] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_SRE_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(0x01u)                                   /* Pull Select: 0x01u */
      | PORT_PCR_PE(0x01u)                                   /* Pull Enable: 0x01u */
      | PORT_PCR_SRE(0x00u)                                  /* Slew Rate Enable: 0x00u */
      | PORT_PCR_ODE(0x01u)                                  /* Open Drain Enable: 0x01u */
     );
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

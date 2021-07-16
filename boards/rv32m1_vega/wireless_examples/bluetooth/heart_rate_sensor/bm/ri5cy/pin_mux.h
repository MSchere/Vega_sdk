/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Direction type  */
typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;

/*!
 * @addtogroup pin_mux
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins_ri5cy(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins_cm4(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins_zero_riscy(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins_cm0p(void);

/* PORTA0 (coord B10), BUTTON_NMI */
#define BOARD_INITBUTTONS_SW2_GPIO                                         GPIOA   /*!< GPIO device name: GPIOA */
#define BOARD_INITBUTTONS_SW2_PORT                                         PORTA   /*!< PORT device name: PORTA */
#define BOARD_INITBUTTONS_SW2_GPIO_PIN                                        0U   /*!< PORTA pin index: 0 */
#define BOARD_INITBUTTONS_SW2_PIN_NAME                                      PTA0   /*!< Pin name */
#define BOARD_INITBUTTONS_SW2_LABEL                                 "BUTTON_NMI"   /*!< Label */
#define BOARD_INITBUTTONS_SW2_NAME                                         "SW2"   /*!< Identifier name */
#define BOARD_INITBUTTONS_SW2_DIRECTION                  kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTE8 (coord P16), BUTTON_LLWUP23 */
#define BOARD_INITBUTTONS_SW3_GPIO                                         GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITBUTTONS_SW3_PORT                                         PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITBUTTONS_SW3_GPIO_PIN                                        8U   /*!< PORTE pin index: 8 */
#define BOARD_INITBUTTONS_SW3_PIN_NAME                                      PTE8   /*!< Pin name */
#define BOARD_INITBUTTONS_SW3_LABEL                             "BUTTON_LLWUP23"   /*!< Label */
#define BOARD_INITBUTTONS_SW3_NAME                                         "SW3"   /*!< Identifier name */
#define BOARD_INITBUTTONS_SW3_DIRECTION                  kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTE9 (coord N16), BUTTON_LLWUP24 */
#define BOARD_INITBUTTONS_SW4_GPIO                                         GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITBUTTONS_SW4_PORT                                         PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITBUTTONS_SW4_GPIO_PIN                                        9U   /*!< PORTE pin index: 9 */
#define BOARD_INITBUTTONS_SW4_PIN_NAME                                      PTE9   /*!< Pin name */
#define BOARD_INITBUTTONS_SW4_LABEL                             "BUTTON_LLWUP24"   /*!< Label */
#define BOARD_INITBUTTONS_SW4_NAME                                         "SW4"   /*!< Identifier name */
#define BOARD_INITBUTTONS_SW4_DIRECTION                  kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTE12 (coord L12), BUTTON_LLWUP26 */
#define BOARD_INITBUTTONS_SW5_GPIO                                         GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITBUTTONS_SW5_PORT                                         PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITBUTTONS_SW5_GPIO_PIN                                       12U   /*!< PORTE pin index: 12 */
#define BOARD_INITBUTTONS_SW5_PIN_NAME                                     PTE12   /*!< Pin name */
#define BOARD_INITBUTTONS_SW5_LABEL                             "BUTTON_LLWUP26"   /*!< Label */
#define BOARD_INITBUTTONS_SW5_NAME                                         "SW5"   /*!< Identifier name */
#define BOARD_INITBUTTONS_SW5_DIRECTION                  kPIN_MUX_DirectionInput   /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitButtons(void);

/* PORTA22 (coord B6), Q6[2]/LED_BLUE */
#define BOARD_INITLEDS_RGB_BLUE_GPIO                                       GPIOA   /*!< GPIO device name: GPIOA */
#define BOARD_INITLEDS_RGB_BLUE_PORT                                       PORTA   /*!< PORT device name: PORTA */
#define BOARD_INITLEDS_RGB_BLUE_GPIO_PIN                                     22U   /*!< PORTA pin index: 22 */
#define BOARD_INITLEDS_RGB_BLUE_PIN_NAME                                   PTA22   /*!< Pin name */
#define BOARD_INITLEDS_RGB_BLUE_LABEL                           "Q6[2]/LED_BLUE"   /*!< Label */
#define BOARD_INITLEDS_RGB_BLUE_NAME                                  "RGB_BLUE"   /*!< Identifier name */
#define BOARD_INITLEDS_RGB_BLUE_DIRECTION               kPIN_MUX_DirectionOutput   /*!< Direction */

/* PORTA23 (coord E6), Q7[5]/LED_GREEN */
#define BOARD_INITLEDS_RGB_GREEN_GPIO                                      GPIOA   /*!< GPIO device name: GPIOA */
#define BOARD_INITLEDS_RGB_GREEN_PORT                                      PORTA   /*!< PORT device name: PORTA */
#define BOARD_INITLEDS_RGB_GREEN_GPIO_PIN                                    23U   /*!< PORTA pin index: 23 */
#define BOARD_INITLEDS_RGB_GREEN_PIN_NAME                                  PTA23   /*!< Pin name */
#define BOARD_INITLEDS_RGB_GREEN_LABEL                         "Q7[5]/LED_GREEN"   /*!< Label */
#define BOARD_INITLEDS_RGB_GREEN_NAME                                "RGB_GREEN"   /*!< Identifier name */
#define BOARD_INITLEDS_RGB_GREEN_DIRECTION              kPIN_MUX_DirectionOutput   /*!< Direction */

/* PORTA24 (coord D6), Q7[2]/LED_RED */
#define BOARD_INITLEDS_RGB_RED_GPIO                                        GPIOA   /*!< GPIO device name: GPIOA */
#define BOARD_INITLEDS_RGB_RED_PORT                                        PORTA   /*!< PORT device name: PORTA */
#define BOARD_INITLEDS_RGB_RED_GPIO_PIN                                      24U   /*!< PORTA pin index: 24 */
#define BOARD_INITLEDS_RGB_RED_PIN_NAME                                    PTA24   /*!< Pin name */
#define BOARD_INITLEDS_RGB_RED_LABEL                             "Q7[2]/LED_RED"   /*!< Label */
#define BOARD_INITLEDS_RGB_RED_NAME                                    "RGB_RED"   /*!< Identifier name */
#define BOARD_INITLEDS_RGB_RED_DIRECTION                kPIN_MUX_DirectionOutput   /*!< Direction */

/* PORTE0 (coord R14), LED_STS */
#define BOARD_INITLEDS_LED_STS_GPIO                                        GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITLEDS_LED_STS_PORT                                        PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITLEDS_LED_STS_GPIO_PIN                                       0U   /*!< PORTE pin index: 0 */
#define BOARD_INITLEDS_LED_STS_PIN_NAME                                     PTE0   /*!< Pin name */
#define BOARD_INITLEDS_LED_STS_LABEL                                   "LED_STS"   /*!< Label */
#define BOARD_INITLEDS_LED_STS_NAME                                    "LED_STS"   /*!< Identifier name */
#define BOARD_INITLEDS_LED_STS_DIRECTION                kPIN_MUX_DirectionOutput   /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLEDs(void);

/* PORTC7 (coord N2), U40[1]/RV32M1_UART0_RX */
#define BOARD_INITLPUART_DEBUG_UART0_RX_PERIPHERAL                       LPUART0   /*!< Device name: LPUART0 */
#define BOARD_INITLPUART_DEBUG_UART0_RX_SIGNAL                                RX   /*!< LPUART0 signal: RX */
#define BOARD_INITLPUART_DEBUG_UART0_RX_PIN_NAME                      LPUART0_RX   /*!< Pin name */
#define BOARD_INITLPUART_DEBUG_UART0_RX_LABEL             "U40[1]/RV32M1_UART0_RX"   /*!< Label */
#define BOARD_INITLPUART_DEBUG_UART0_RX_NAME                    "DEBUG_UART0_RX"   /*!< Identifier name */

/* PORTC8 (coord P3), U11[1]/RV32M1_UART0_TX */
#define BOARD_INITLPUART_DEBUG_UART0_TX_PERIPHERAL                       LPUART0   /*!< Device name: LPUART0 */
#define BOARD_INITLPUART_DEBUG_UART0_TX_SIGNAL                                TX   /*!< LPUART0 signal: TX */
#define BOARD_INITLPUART_DEBUG_UART0_TX_PIN_NAME                      LPUART0_TX   /*!< Pin name */
#define BOARD_INITLPUART_DEBUG_UART0_TX_LABEL             "U11[1]/RV32M1_UART0_TX"   /*!< Label */
#define BOARD_INITLPUART_DEBUG_UART0_TX_NAME                    "DEBUG_UART0_TX"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLPUART(void);

/* EXTAL32 (coord E16), Y1[1]/EXTAL_32KHZ */
#define BOARD_INITOSC_EXTAL32_PERIPHERAL                                     RTC   /*!< Device name: RTC */
#define BOARD_INITOSC_EXTAL32_SIGNAL                                     EXTAL32   /*!< RTC signal: EXTAL32 */
#define BOARD_INITOSC_EXTAL32_PIN_NAME                                   EXTAL32   /*!< Pin name */
#define BOARD_INITOSC_EXTAL32_LABEL                          "Y1[1]/EXTAL_32KHZ"   /*!< Label */
#define BOARD_INITOSC_EXTAL32_NAME                                     "EXTAL32"   /*!< Identifier name */

/* XTAL32 (coord E17), Y1[2]/XTAL_32KHZ */
#define BOARD_INITOSC_XTAL32_PERIPHERAL                                      RTC   /*!< Device name: RTC */
#define BOARD_INITOSC_XTAL32_SIGNAL                                       XTAL32   /*!< RTC signal: XTAL32 */
#define BOARD_INITOSC_XTAL32_PIN_NAME                                     XTAL32   /*!< Pin name */
#define BOARD_INITOSC_XTAL32_LABEL                            "Y1[2]/XTAL_32KHZ"   /*!< Label */
#define BOARD_INITOSC_XTAL32_NAME                                       "XTAL32"   /*!< Identifier name */

/* XTAL_RF (coord A11), Y3[1]/XTAL_32M */
#define BOARD_INITOSC_XTAL_RF_PERIPHERAL                                     RF0   /*!< Device name: RF0 */
#define BOARD_INITOSC_XTAL_RF_SIGNAL                                     XTAL_RF   /*!< RF0 signal: XTAL_RF */
#define BOARD_INITOSC_XTAL_RF_PIN_NAME                                   XTAL_RF   /*!< Pin name */
#define BOARD_INITOSC_XTAL_RF_LABEL                             "Y3[1]/XTAL_32M"   /*!< Label */
#define BOARD_INITOSC_XTAL_RF_NAME                                     "XTAL_RF"   /*!< Identifier name */

/* EXTAL_RF (coord B11), Y3[3]/EXTAL_32M */
#define BOARD_INITOSC_EXTAL_RF_PERIPHERAL                                    RF0   /*!< Device name: RF0 */
#define BOARD_INITOSC_EXTAL_RF_SIGNAL                                   EXTAL_RF   /*!< RF0 signal: EXTAL_RF */
#define BOARD_INITOSC_EXTAL_RF_PIN_NAME                                 EXTAL_RF   /*!< Pin name */
#define BOARD_INITOSC_EXTAL_RF_LABEL                           "Y3[3]/EXTAL_32M"   /*!< Label */
#define BOARD_INITOSC_EXTAL_RF_NAME                                   "EXTAL_RF"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitOSC(void);

/* PORTE30 (coord G17), U14[4]/ACCEL_I2C3_SCL */
#define BOARD_INITACCEL_ACCEL_SCL_PERIPHERAL                              LPI2C3   /*!< Device name: LPI2C3 */
#define BOARD_INITACCEL_ACCEL_SCL_SIGNAL                                     SCL   /*!< LPI2C3 signal: SCL */
#define BOARD_INITACCEL_ACCEL_SCL_PIN_NAME                            LPI2C3_SCL   /*!< Pin name */
#define BOARD_INITACCEL_ACCEL_SCL_LABEL                  "U14[4]/ACCEL_I2C3_SCL"   /*!< Label */
#define BOARD_INITACCEL_ACCEL_SCL_NAME                               "ACCEL_SCL"   /*!< Identifier name */

/* PORTE29 (coord G15), U14[6]/ACCEL_I2C3_SDA */
#define BOARD_INITACCEL_ACCEL_SDA_PERIPHERAL                              LPI2C3   /*!< Device name: LPI2C3 */
#define BOARD_INITACCEL_ACCEL_SDA_SIGNAL                                     SDA   /*!< LPI2C3 signal: SDA */
#define BOARD_INITACCEL_ACCEL_SDA_PIN_NAME                            LPI2C3_SDA   /*!< Pin name */
#define BOARD_INITACCEL_ACCEL_SDA_LABEL                  "U14[6]/ACCEL_I2C3_SDA"   /*!< Label */
#define BOARD_INITACCEL_ACCEL_SDA_NAME                               "ACCEL_SDA"   /*!< Identifier name */

/* PORTE1 (coord R16), U14[11]/ACCEL_INT1 */
#define BOARD_INITACCEL_ACCEL_INT1_GPIO                                    GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITACCEL_ACCEL_INT1_PORT                                    PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITACCEL_ACCEL_INT1_GPIO_PIN                                   1U   /*!< PORTE pin index: 1 */
#define BOARD_INITACCEL_ACCEL_INT1_PIN_NAME                                 PTE1   /*!< Pin name */
#define BOARD_INITACCEL_ACCEL_INT1_LABEL                    "U14[11]/ACCEL_INT1"   /*!< Label */
#define BOARD_INITACCEL_ACCEL_INT1_NAME                             "ACCEL_INT1"   /*!< Identifier name */
#define BOARD_INITACCEL_ACCEL_INT1_DIRECTION             kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTE22 (coord J16), U14[9]/ACCEL_INT2 */
#define BOARD_INITACCEL_ACCEL_INT2_GPIO                                    GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITACCEL_ACCEL_INT2_PORT                                    PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITACCEL_ACCEL_INT2_GPIO_PIN                                  22U   /*!< PORTE pin index: 22 */
#define BOARD_INITACCEL_ACCEL_INT2_PIN_NAME                                PTE22   /*!< Pin name */
#define BOARD_INITACCEL_ACCEL_INT2_LABEL                     "U14[9]/ACCEL_INT2"   /*!< Label */
#define BOARD_INITACCEL_ACCEL_INT2_NAME                             "ACCEL_INT2"   /*!< Identifier name */
#define BOARD_INITACCEL_ACCEL_INT2_DIRECTION             kPIN_MUX_DirectionInput   /*!< Direction */

/* PORTE27 (coord H14), U14[16]/ACCEL_RST */
#define BOARD_INITACCEL_ACCEL_RST_GPIO                                     GPIOE   /*!< GPIO device name: GPIOE */
#define BOARD_INITACCEL_ACCEL_RST_PORT                                     PORTE   /*!< PORT device name: PORTE */
#define BOARD_INITACCEL_ACCEL_RST_GPIO_PIN                                   27U   /*!< PORTE pin index: 27 */
#define BOARD_INITACCEL_ACCEL_RST_PIN_NAME                                 PTE27   /*!< Pin name */
#define BOARD_INITACCEL_ACCEL_RST_LABEL                      "U14[16]/ACCEL_RST"   /*!< Label */
#define BOARD_INITACCEL_ACCEL_RST_NAME                               "ACCEL_RST"   /*!< Identifier name */
#define BOARD_INITACCEL_ACCEL_RST_DIRECTION             kPIN_MUX_DirectionOutput   /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitACCEL(void);

/* PORTB9 (coord F4), J4[6]/J47[2]/ARDUINO_A2/ADC0_SE3 */
#define BOARD_INITLIGHT_SENSOR_SNS_LIGHT_ADC_GPIO                          GPIOB   /*!< GPIO device name: GPIOB */
#define BOARD_INITLIGHT_SENSOR_SNS_LIGHT_ADC_PORT                          PORTB   /*!< PORT device name: PORTB */
#define BOARD_INITLIGHT_SENSOR_SNS_LIGHT_ADC_GPIO_PIN                         9U   /*!< PORTB pin index: 9 */
#define BOARD_INITLIGHT_SENSOR_SNS_LIGHT_ADC_PIN_NAME                       PTB9   /*!< Pin name */
#define BOARD_INITLIGHT_SENSOR_SNS_LIGHT_ADC_LABEL "J4[6]/J47[2]/ARDUINO_A2/ADC0_SE3" /*!< Label */
#define BOARD_INITLIGHT_SENSOR_SNS_LIGHT_ADC_NAME                "SNS_LIGHT_ADC"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitLIGHT_SENSOR(void);

/* USB0_DM (coord T12), J8[2]/RV32M1_USB_DN */
#define BOARD_INITUSB_USB0_DM_PERIPHERAL                                    USB0   /*!< Device name: USB0 */
#define BOARD_INITUSB_USB0_DM_SIGNAL                                          DM   /*!< USB0 signal: DM */
#define BOARD_INITUSB_USB0_DM_PIN_NAME                                   USB0_DM   /*!< Pin name */
#define BOARD_INITUSB_USB0_DM_LABEL                          "J8[2]/RV32M1_USB_DN"   /*!< Label */
#define BOARD_INITUSB_USB0_DM_NAME                                     "USB0_DM"   /*!< Identifier name */

/* USB0_DP (coord T11), J8[3]/RV32M1_USB_DP */
#define BOARD_INITUSB_USB0_DP_PERIPHERAL                                    USB0   /*!< Device name: USB0 */
#define BOARD_INITUSB_USB0_DP_SIGNAL                                          DP   /*!< USB0 signal: DP */
#define BOARD_INITUSB_USB0_DP_PIN_NAME                                   USB0_DP   /*!< Pin name */
#define BOARD_INITUSB_USB0_DP_LABEL                          "J8[3]/RV32M1_USB_DP"   /*!< Label */
#define BOARD_INITUSB_USB0_DP_NAME                                     "USB0_DP"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitUSB(void);

/* PORTD11 (coord R11), J9[P1]/SDHC0_D2 */
#define BOARD_INITSDHC_SDHC0_D2_PERIPHERAL                                 SDHC0   /*!< Device name: SDHC0 */
#define BOARD_INITSDHC_SDHC0_D2_SIGNAL                                      DATA   /*!< SDHC0 signal: DATA */
#define BOARD_INITSDHC_SDHC0_D2_CHANNEL                                        2   /*!< SDHC0 DATA channel: 2 */
#define BOARD_INITSDHC_SDHC0_D2_PIN_NAME                                SDHC0_D2   /*!< Pin name */
#define BOARD_INITSDHC_SDHC0_D2_LABEL                          "J9[P1]/SDHC0_D2"   /*!< Label */
#define BOARD_INITSDHC_SDHC0_D2_NAME                                  "SDHC0_D2"   /*!< Identifier name */

/* PORTD10 (coord P11), J9[P2]/SDHC0_D3 */
#define BOARD_INITSDHC_SDHC0_D3_PERIPHERAL                                 SDHC0   /*!< Device name: SDHC0 */
#define BOARD_INITSDHC_SDHC0_D3_SIGNAL                                      DATA   /*!< SDHC0 signal: DATA */
#define BOARD_INITSDHC_SDHC0_D3_CHANNEL                                        3   /*!< SDHC0 DATA channel: 3 */
#define BOARD_INITSDHC_SDHC0_D3_PIN_NAME                                SDHC0_D3   /*!< Pin name */
#define BOARD_INITSDHC_SDHC0_D3_LABEL                          "J9[P2]/SDHC0_D3"   /*!< Label */
#define BOARD_INITSDHC_SDHC0_D3_NAME                                  "SDHC0_D3"   /*!< Identifier name */

/* PORTD9 (coord U11), J9[P3]/SDHC0_CMD */
#define BOARD_INITSDHC_SDHC0_CMD_PERIPHERAL                                SDHC0   /*!< Device name: SDHC0 */
#define BOARD_INITSDHC_SDHC0_CMD_SIGNAL                                      CMD   /*!< SDHC0 signal: CMD */
#define BOARD_INITSDHC_SDHC0_CMD_PIN_NAME                              SDHC0_CMD   /*!< Pin name */
#define BOARD_INITSDHC_SDHC0_CMD_LABEL                        "J9[P3]/SDHC0_CMD"   /*!< Label */
#define BOARD_INITSDHC_SDHC0_CMD_NAME                                "SDHC0_CMD"   /*!< Identifier name */

/* PORTD8 (coord T9), J9[P5]/SDHC0_DCLK */
#define BOARD_INITSDHC_SDHC0_DCLK_PERIPHERAL                               SDHC0   /*!< Device name: SDHC0 */
#define BOARD_INITSDHC_SDHC0_DCLK_SIGNAL                                    DCLK   /*!< SDHC0 signal: DCLK */
#define BOARD_INITSDHC_SDHC0_DCLK_PIN_NAME                            SDHC0_DCLK   /*!< Pin name */
#define BOARD_INITSDHC_SDHC0_DCLK_LABEL                      "J9[P5]/SDHC0_DCLK"   /*!< Label */
#define BOARD_INITSDHC_SDHC0_DCLK_NAME                              "SDHC0_DCLK"   /*!< Identifier name */

/* PORTD7 (coord P10), J9[P7]/SDHC0_D0 */
#define BOARD_INITSDHC_SDHC0_D0_PERIPHERAL                                 SDHC0   /*!< Device name: SDHC0 */
#define BOARD_INITSDHC_SDHC0_D0_SIGNAL                                      DATA   /*!< SDHC0 signal: DATA */
#define BOARD_INITSDHC_SDHC0_D0_CHANNEL                                        0   /*!< SDHC0 DATA channel: 0 */
#define BOARD_INITSDHC_SDHC0_D0_PIN_NAME                                SDHC0_D0   /*!< Pin name */
#define BOARD_INITSDHC_SDHC0_D0_LABEL                          "J9[P7]/SDHC0_D0"   /*!< Label */
#define BOARD_INITSDHC_SDHC0_D0_NAME                                  "SDHC0_D0"   /*!< Identifier name */

/* PORTD6 (coord U9), J9[P8]/SDHC0_D1 */
#define BOARD_INITSDHC_SDHC0_D1_PERIPHERAL                                 SDHC0   /*!< Device name: SDHC0 */
#define BOARD_INITSDHC_SDHC0_D1_SIGNAL                                      DATA   /*!< SDHC0 signal: DATA */
#define BOARD_INITSDHC_SDHC0_D1_CHANNEL                                        1   /*!< SDHC0 DATA channel: 1 */
#define BOARD_INITSDHC_SDHC0_D1_PIN_NAME                                SDHC0_D1   /*!< Pin name */
#define BOARD_INITSDHC_SDHC0_D1_LABEL                          "J9[P8]/SDHC0_D1"   /*!< Label */
#define BOARD_INITSDHC_SDHC0_D1_NAME                                  "SDHC0_D1"   /*!< Identifier name */

/* PORTC27 (coord P6), J9[G1]/SD_DETECT */
#define BOARD_INITSDHC_SD_DETECT_GPIO                                      GPIOC   /*!< GPIO device name: GPIOC */
#define BOARD_INITSDHC_SD_DETECT_PORT                                      PORTC   /*!< PORT device name: PORTC */
#define BOARD_INITSDHC_SD_DETECT_GPIO_PIN                                    27U   /*!< PORTC pin index: 27 */
#define BOARD_INITSDHC_SD_DETECT_PIN_NAME                                  PTC27   /*!< Pin name */
#define BOARD_INITSDHC_SD_DETECT_LABEL                        "J9[G1]/SD_DETECT"   /*!< Label */
#define BOARD_INITSDHC_SD_DETECT_NAME                                "SD_DETECT"   /*!< Identifier name */
#define BOARD_INITSDHC_SD_DETECT_DIRECTION               kPIN_MUX_DirectionInput   /*!< Direction */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSDHC(void);

/* PORTA22 (coord B6), Q6[2]/LED_BLUE */
#define BOARD_INITRGB_RGB_BLUE_PERIPHERAL                                   TPM2   /*!< Device name: TPM2 */
#define BOARD_INITRGB_RGB_BLUE_SIGNAL                                         CH   /*!< TPM2 signal: CH */
#define BOARD_INITRGB_RGB_BLUE_CHANNEL                                         2   /*!< TPM2 channel: 2 */
#define BOARD_INITRGB_RGB_BLUE_PIN_NAME                                 TPM2_CH2   /*!< Pin name */
#define BOARD_INITRGB_RGB_BLUE_LABEL                            "Q6[2]/LED_BLUE"   /*!< Label */
#define BOARD_INITRGB_RGB_BLUE_NAME                                   "RGB_BLUE"   /*!< Identifier name */

/* PORTA23 (coord E6), Q7[5]/LED_GREEN */
#define BOARD_INITRGB_RGB_GREEN_PERIPHERAL                                  TPM2   /*!< Device name: TPM2 */
#define BOARD_INITRGB_RGB_GREEN_SIGNAL                                        CH   /*!< TPM2 signal: CH */
#define BOARD_INITRGB_RGB_GREEN_CHANNEL                                        1   /*!< TPM2 channel: 1 */
#define BOARD_INITRGB_RGB_GREEN_PIN_NAME                                TPM2_CH1   /*!< Pin name */
#define BOARD_INITRGB_RGB_GREEN_LABEL                          "Q7[5]/LED_GREEN"   /*!< Label */
#define BOARD_INITRGB_RGB_GREEN_NAME                                 "RGB_GREEN"   /*!< Identifier name */

/* PORTA24 (coord D6), Q7[2]/LED_RED */
#define BOARD_INITRGB_RGB_RED_PERIPHERAL                                    TPM2   /*!< Device name: TPM2 */
#define BOARD_INITRGB_RGB_RED_SIGNAL                                          CH   /*!< TPM2 signal: CH */
#define BOARD_INITRGB_RGB_RED_CHANNEL                                          0   /*!< TPM2 channel: 0 */
#define BOARD_INITRGB_RGB_RED_PIN_NAME                                  TPM2_CH0   /*!< Pin name */
#define BOARD_INITRGB_RGB_RED_LABEL                              "Q7[2]/LED_RED"   /*!< Label */
#define BOARD_INITRGB_RGB_RED_NAME                                     "RGB_RED"   /*!< Identifier name */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitRGB(void);

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitSPI(void);

void BOARD_InitI2C(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/

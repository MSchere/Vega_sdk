/*
 * Copyright 2018 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 *END**************************************************************************/
void BOARD_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_PortC);          /* Clock Gate Control: 0x01u */

    PORT_SetPinMux(PORTC,7,kPORT_MuxAlt3);   /* PORTC7 (pin N2) is configured as LPUART0_RX */
    PORT_SetPinMux(PORTC,8,kPORT_MuxAlt3);   /* PORTC8 (pin N3) is configured as LPUART0_TX */
}

#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */

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

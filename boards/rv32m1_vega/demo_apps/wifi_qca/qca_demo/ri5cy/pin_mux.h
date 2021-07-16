/*
 * Copyright 2018 NXP
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
    kPIN_MUX_DirectionInput         = 0U,  /*Input direction*/
    kPIN_MUX_DirectionOutput        = 1U,  /*Output direction*/
    kPIN_MUX_DirectionInputOrOutput = 2U   /*Input or Output direction*/     
}pin_mux_direction_t;

/*!
 * @addtogroup pin_mux_core1
 * @{
 */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif


/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#define BOARD_INITGT202SHIELD_GPIOB_2_DIRECTION         kPIN_MUX_DirectionOutput   /*!< Direction of GPIOB_2 signal */
#define BOARD_INITGT202SHIELD_GPIOB_1_DIRECTION          kPIN_MUX_DirectionInput   /*!< Direction of GPIOB_1 signal */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitGT202Shield(void);

#define BOARD_INITSILEX2401SHIELD_GPIOB_14_DIRECTION    kPIN_MUX_DirectionOutput   /*!< Direction of GPIOB_14 signal */
#define BOARD_INITSILEX2401SHIELD_GPIOA_27_DIRECTION     kPIN_MUX_DirectionInput   /*!< Direction of GPIOA_27 signal */
#define BOARD_INITSILEX2401SHIELD_GPIOA_30_DIRECTION    kPIN_MUX_DirectionOutput   /*!< Direction of GPIOA_30 signal */

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_CORE1_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
#ifndef PUBLIC__CONSOLE_DRV_IFACE_V1_H
#define PUBLIC__CONSOLE_DRV_IFACE_V1_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <public/config.h>
#include <platform/basic_types.h>

/*PROTECTED REGION ID(public_console_drv_iface_h) ENABLED START*/

/**
 *  @addtogroup DEBUG DEBUG
 *  @{
 */
/**
 *  @defgroup CONSOLE_DRV CONSOLE DRIVER
 *  @{
 */
/**
 * \brief	init the cosole driver.
 */
void console_init();
/**
 * \brief	send a character.
 * @param port serial port to write.
 * @param ch	character to send.
 */
void console_outbyte_polled(int port, unsigned char ch);

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
/*PROTECTED REGION END*/

#ifdef __cplusplus
}
#endif

#endif // PUBLIC__CONSOLE_DRV_IFACE_V1_H

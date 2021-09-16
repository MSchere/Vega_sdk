#ifndef PUBLIC__XPRINTF_IFACE_V1_H
#define PUBLIC__XPRINTF_IFACE_V1_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <public/config.h>
//#include <platform/basic_types.h>
#include <stdint.h>

/*PROTECTED REGION ID(public_xprintf_iface_h) ENABLED START*/
/**
 * @defgroup DEBUG DEBUG
 */
/**
 *  @addtogroup DEBUG DEBUG
 *  @{
 */
/**
 *  @defgroup XPRINTF XPRINTF
 *  @{
 */
/**
 * print a formatted string.
 * @param embdio_channel channel to transmit the formatted string.
 * @param fmt the formatted string to be sent.
 * @return 0 if successful transmission, -1 if an error occurs.
 */
int xprintf(int embdio_channel, const char *fmt,...);
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

#endif // PUBLIC__XPRINTF_IFACE_V1_H

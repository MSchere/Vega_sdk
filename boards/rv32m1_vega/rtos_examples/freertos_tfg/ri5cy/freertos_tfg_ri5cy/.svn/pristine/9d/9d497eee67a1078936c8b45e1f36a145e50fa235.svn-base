#include <platform/basic_types.h>
#include <xprintf_slib/config.h>

#include <public/xprintf_iface_v1.h>
#include <public/stdarg_iface_c99.h>
#include <stdio.h>

//#include <public/vprintf_iface_c99.h>

int xprintf(int embdio_channel, const char *fmt,...)
{

	int result = 0;
	va_list args;

//	if (embdio_channel < 0 ||
//		embdio_channel > CONFIG_SWI_XPRINTF_IFACE_V1_NB_MAX_CHANNELS)
//	{
//		return -1;
//	}

	va_start(args, fmt);
	result=vprintf(fmt, args);
	va_end(args);
	return result;

//	if (embdio_channel == 0)
//	{
//		if (CONFIG_SWP_XPRINTF_SLIB_CHANNEL_0_OUTPUT == CONFIG_SWP_XPRINTF_SLIB_CHANNEL_OUTPUT_NULL)
//		{
//			va_end(args);
//			return 0;
//		}
//		else if (CONFIG_SWP_XPRINTF_SLIB_CHANNEL_0_OUTPUT == CONFIG_SWP_XPRINTF_SLIB_CHANNEL_OUTPUT_STDOUT)
//		{
//			result = vprintf(fmt, args);
//			va_end(args);
//			return result;
//		}
//		else
//		{
//			va_end(args);
//			return -1;
//		}
//	}
//	else if (embdio_channel == 1)
//    {
//		if (CONFIG_SWP_XPRINTF_SLIB_CHANNEL_1_OUTPUT == CONFIG_SWP_XPRINTF_SLIB_CHANNEL_OUTPUT_NULL)
//		{
//			va_end(args);
//			return 0;
//		}
//		else if (CONFIG_SWP_XPRINTF_SLIB_CHANNEL_1_OUTPUT == CONFIG_SWP_XPRINTF_SLIB_CHANNEL_OUTPUT_STDOUT)
//		{
//			result = vprintf(fmt, args);
//			va_end(args);
//			return result;
//		}
//		else
//		{
//			va_end(args);
//			return -1;
//		}
//    }
//    else
//    {
//    	va_end(args);
//        return -1;
//    }
}

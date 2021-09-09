#include <public/edroomtc_iface_v1.h>
#include <public/xprintf_iface_v1.h>


static bool opened = 0;

CEDROOMstream::CEDROOMstream()
{
    if(!opened)
    {
        /*  Init the RTEMS filesyste    */

    	xprintf(CONFIG_SWI_XPRINTF_IFACE_V1_OUTPUT_CHANNEL_EDROOMBP_SLIB_HEAD_OUTPUT_CHANNEL_ID,"stream abierto(por pantalla...)\n");

        opened = 1;
    }
        
}

CEDROOMstream::CEDROOMstream(const char *string) 
{
    CEDROOMstream();
}

void CEDROOMstream::open(const char *string, int dummy)
{
    /*  NOTHING */
}

void CEDROOMstream::close(void) 
{
    /*  NOTHING */
}

void CEDROOMstream::reopen(void) 
{
    /*  NOTHING */
}

int CEDROOMstream::is_open(void) 
{
    return (opened);
}

int CEDROOMstream::good(void) 
{
    return (opened);
}
    
CEDROOMstream & CEDROOMstream::operator<<(const char *string) 
{
	xprintf(CONFIG_SWI_XPRINTF_IFACE_V1_OUTPUT_CHANNEL_EDROOMBP_SLIB_HEAD_OUTPUT_CHANNEL_ID, string);
    return (*this);
}

CEDROOMstream & CEDROOMstream::operator<<(const int &integer) 
{
    //char buffer[1024];
    
    xprintf(CONFIG_SWI_XPRINTF_IFACE_V1_OUTPUT_CHANNEL_EDROOMBP_SLIB_HEAD_OUTPUT_CHANNEL_ID, "%d",integer);
    return (*this);
}

CEDROOMstream & CEDROOMstream::operator<<(const unsigned int &uint) 
{
    //char buffer[1024];
    
    xprintf(CONFIG_SWI_XPRINTF_IFACE_V1_OUTPUT_CHANNEL_EDROOMBP_SLIB_HEAD_OUTPUT_CHANNEL_ID,"%d",uint);
    return (*this);
}

CEDROOMstream & CEDROOMstream::operator<<(const float &fnum) 
{
    //char buffer[1024];
    
    xprintf(CONFIG_SWI_XPRINTF_IFACE_V1_OUTPUT_CHANNEL_EDROOMBP_SLIB_HEAD_OUTPUT_CHANNEL_ID,"%f", fnum);
    return (*this);
}


#ifndef PUBLIC__EDROOMTC_IFACE_V1_H
#define PUBLIC__EDROOMTC_IFACE_V1_H

#include <public/config.h>
//#include <platform/basic_types.h>
#include <stdint.h>

/*PROTECTED REGION ID(public_edroomtc_iface_h) ENABLED START*/
/**
 *  @addtogroup ICUSW_SERVICE_MODULES ICUSw Service Modules
 *  @{
 */
/**
 *  @defgroup EDROOMTC EDROOMTC
 *  @{
 */

 class CEDROOMstream
{

    public:

        void open(const char *string, int dummy = 0);
        void reopen(void);
        void close(void);
        int is_open(void);
        int good(void);

        CEDROOMstream &operator<<(const char *string);
        CEDROOMstream &operator<<(const int &integer);
        CEDROOMstream &operator<<(const unsigned int &uint);
        CEDROOMstream &operator<<(const float &fnum);
        CEDROOMstream();
        CEDROOMstream(const char *string);
};

 /**
  * @}
  */
/**
 * @}
 */
/*PROTECTED REGION END*/

#endif // PUBLIC__EDROOMTC_IFACE_V1_H

#ifndef PUBLIC__EDROOM_TYPES_IFACE_V1_H
#define PUBLIC__EDROOM_TYPES_IFACE_V1_H

#include <public/config.h>
#include <platform/basic_types.h>

/*PROTECTED REGION ID(public_edroom_types_iface_h) ENABLED START*/
/**
 *  @addtogroup ICUSW_SERVICE_MODULES ICUSw Service Modules
 *  @{
 */
/**
 *  @addtogroup EDROOMSL EDROOM SERVICE LIBRARY
 *  @{
 */
/**
 *  @defgroup EDROOM_TYPES EDROOM TYPES
 *  @{
 */
#define EDROOMUINT32_MAX 0xFFFFFFFF

/*	EDROOM GENERIC TYPES*/
typedef bool_t              TEDROOMBool;
typedef uint8_t       		TEDROOMByte;
typedef uint16_t  			TEDROOMWord16;
typedef uint32_t        	TEDROOMWord32;
typedef uint64_t 		 	TEDROOMWord64;

typedef uint8_t       		TEDROOMUInt8;
typedef uint16_t  			TEDROOMUInt16;
typedef uint32_t        	TEDROOMUInt32;
typedef uint64_t  			TEDROOMUInt64;

typedef int8_t              TEDROOMInt8;
typedef int16_t           	TEDROOMInt16;
typedef int32_t             TEDROOMInt32;
typedef int64_t          	TEDROOMInt64;
typedef float				TEDROOMFloat;

#if 0

static inline TEDROOMUInt16 _edroom_switch16(TEDROOMInt16 input)
{
    return input<<8 | input>>8;
}

static inline TEDROOMUInt32 _edroom_switch32(TEDROOMUInt32 input)
{
    return input<<24 | input>>24 |
        (input & (TEDROOMUInt32)0x0000ff00UL)<<8 |
        (input & (TEDROOMUInt32)0x00ff0000UL)>>8;
}

static inline TEDROOMUInt64 _edroom_switch64(TEDROOMUInt64 input)
{
    return input<<56 | input>>56 |
        (input & (TEDROOMUInt64)0x000000000000ff00ULL)<<40 |
        (input & (TEDROOMUInt64)0x0000000000ff0000ULL)<<24 |
        (input & (TEDROOMUInt64)0x00000000ff000000ULL)<< 8 |
        (input & (TEDROOMUInt64)0x000000ff00000000ULL)>> 8 |
        (input & (TEDROOMUInt64)0x0000ff0000000000ULL)>>24 |
        (input & (TEDROOMUInt64)0x00ff000000000000ULL)>>40;
}

#ifndef CONFIG_ARCH_SPARC

#define edroom_htonll(x) 	_edroom_switch64(x)
#define edroom_htonl(x) 	_edroom_switch32(x)
#define edroom_htons(x) 	_edroom_switch16(x)

#define edroom_ntohll(x) 	_edroom_switch64(x)
#define edroom_ntohl(x) 	_edroom_switch32(x)
#define edroom_ntohs(x) 	_edroom_switch16(x)

#else

#define edroom_htonll(x) 	x
#define edroom_htonl(x) 	x
#define edroom_htons(x) 	x

#define edroom_ntohll(x) 	x
#define edroom_ntohl(x) 	x
#define edroom_ntohs(x) 	x

#endif

void TEDROOMUInt64_Serialize(TEDROOMUInt64 * input, TEDROOMUInt64 * output);
void TEDROOMUInt64_Deserialize(TEDROOMUInt64 * input, TEDROOMUInt64 * output);
void TEDROOMUInt32_Serialize(TEDROOMUInt32 * input, TEDROOMUInt32 * output);
void TEDROOMUInt32_Deserialize(TEDROOMUInt32 * input, TEDROOMUInt32 * output);
void TEDROOMUInt16_Serialize(TEDROOMUInt16 * input, TEDROOMUInt16 * output);
void TEDROOMUInt16_Deserialize(TEDROOMUInt16 * input, TEDROOMUInt16 * output);
void TEDROOMUInt8_Serialize(TEDROOMUInt8 * input, TEDROOMUInt8 * output);
void TEDROOMUInt8_Deserialize(TEDROOMUInt8 * input, TEDROOMUInt8 * output);

#define TEDROOMWord64_Serialize(x, y) TEDROOMUInt64_Serialize((TEDROOMUInt64 *)x, (TEDROOMUInt64 *)y)
#define TEDROOMWord32_Serialize(x, y) TEDROOMUInt32_Serialize((TEDROOMUInt32 *)x, (TEDROOMUInt32 *)y)
#define TEDROOMWord16_Serialize(x, y) TEDROOMUInt16_Serialize((TEDROOMUInt16 *)x, (TEDROOMUInt16 *)y)
#define TEDROOMFloat_Serialize(x, y) TEDROOMUInt32_Serialize((TEDROOMUInt32 *)x, (TEDROOMUInt32 *)y)
#define TEDROOMInt64_Serialize(x, y) TEDROOMUInt64_Serialize((TEDROOMUInt64 *)x, (TEDROOMUInt64 *)y)
#define TEDROOMInt32_Serialize(x, y) TEDROOMUInt32_Serialize((TEDROOMUInt32 *)x, (TEDROOMUInt32 *)y)
#define TEDROOMInt16_Serialize(x, y) TEDROOMUInt16_Serialize((TEDROOMUInt16 *)x, (TEDROOMUInt16 *)y)
#define TEDROOMByte_Serialize(x, y) TEDROOMUInt8_Serialize((TEDROOMUInt8 *)x, (TEDROOMUInt8 *)y)


#define TEDROOMWord64_Deserialize(x, y) TEDROOMUInt64_Deserialize((TEDROOMUInt64 *)x, (TEDROOMUInt64 *)y)
#define TEDROOMWord32_Deserialize(x, y) TEDROOMUInt32_Deserialize((TEDROOMUInt32 *)x, (TEDROOMUInt32 *)y)
#define TEDROOMWord16_Deserialize(x, y) TEDROOMUInt16_Deserialize((TEDROOMUInt16 *)x, (TEDROOMUInt16 *)y)
#define TEDROOMFloat_Deserialize(x, y) TEDROOMUInt32_Deserialize((TEDROOMUInt32 *)x, (TEDROOMUInt32 *)y)
#define TEDROOMInt64_Deserialize(x, y) TEDROOMUInt64_Deserialize((TEDROOMUInt64 *)x, (TEDROOMUInt64 *)y)
#define TEDROOMInt32_Deserialize(x, y) TEDROOMUInt32_Deserialize((TEDROOMUInt32 *)x, (TEDROOMUInt32 *)y)
#define TEDROOMInt16_Deserialize(x, y) TEDROOMUInt16_Deserialize((TEDROOMUInt16 *)x, (TEDROOMUInt16 *)y)
#define TEDROOMByte_Deserialize(x, y) TEDROOMUInt8_Deserialize((TEDROOMUInt8 *)x, (TEDROOMUInt8 *)y)

#endif

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

#endif // PUBLIC__EDROOM_TYPES_IFACE_V1_H

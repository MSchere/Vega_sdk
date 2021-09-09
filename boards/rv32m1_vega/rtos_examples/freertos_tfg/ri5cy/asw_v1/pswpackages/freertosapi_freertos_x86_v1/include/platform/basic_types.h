#ifndef X86_TYPES_H
#define X86_TYPES_H


#ifndef NULL
	#define NULL  0
#endif


#ifndef __cplusplus

	typedef unsigned char 		bool_t;

	#define true 	1
	#define false 	0

#else

	typedef bool 		bool_t;

#endif

typedef unsigned char 		byte_t;
typedef unsigned short int	word16_t;
typedef unsigned int		word32_t;
typedef unsigned long int	word64_t;

#endif /* LEON3_TYPES_H_ */

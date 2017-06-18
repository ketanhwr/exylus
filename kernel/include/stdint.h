/*
 * stdint.h
 *
 * This file is a part of Exylus.
 */

#ifndef STDINT_H
#define STDINT_H

/**
 * Definitions
 */

/* Definition: uint8 */
#ifndef __UINT8_T_
#define __UINT8_T_
typedef char uint8_t;
#endif

/* Definition: int8_t */
#ifndef __INT8_T_
#define __INT8_T_
typedef signed char int8_t;
#endif


/* Definition: uint16_t */
#ifndef __UINT16_T_
#define __UINT16_T_
typedef unsigned short uint16_t;
#endif

/* Definition: int16_t */
#ifndef __INT16_T_
#define __INT16_T_
typedef short int16_t;
#endif


/* Definition: uint32_t */
#ifndef __UINT32_T_
#define __UINT32_T_
typedef unsigned int uint32_t;
#endif

/* Definition: int32_t */
#ifndef __INT32_T_
#define __INT32_T_
typedef int int32_t;
#endif


/* Definition: uint64_t */
#ifndef __UINT64_T_
#define __UINT64_T_
typedef unsigned long long uint64_t;
#endif

/* Definition: int64_t */
#ifndef __INT64_T_
#define __INT64_T_
typedef long long int64_t;
#endif

#endif /* STDINT_H */

#ifndef _SPSF_TYPES_H__
#define _SPSF_TYPES_H__

#include <stdint.h>
#include <inttypes.h>

#define INLINE static inline

// Define types
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef intptr_t sptr;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef uintptr_t uptr;

typedef uint8_t boolean;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif



/* For gcc only? */
#define PACKSTRUCT	__attribute__ ((packed))
#define CALLBACK

#endif

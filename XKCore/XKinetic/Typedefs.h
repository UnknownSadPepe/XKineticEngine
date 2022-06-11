#pragma once

#define XK_NULL_HANDLE ((void*)0)

typedef enum {
	XK_SUCCESS													= 0,
	XK_ERROR_BAD_ALLOCATE								= -1,
	XK_ERROR_MODULE_NOT_PRESENT 				= -2,
	XK_ERROR_MODULE_SYMBOL_NOT_PRESENT 	= -3,
	XK_ERROR_RESOURCE_NOT_LOAD					= -4,
	XK_ERROR_RESOURCE_NOT_CREATE				= -5,
	XK_ERROR_CREATE_FAILED							= -6,
	XK_ERROR_INITIALIZE_FAILED					= -7,
	XK_ERROR_UNKNOWN										= -10
} XkResult;

typedef void* XkHandle;

typedef unsigned int XkBool32;

#define XK_FALSE 0
#define XK_TRUE 1

typedef char XkChar;
typedef unsigned short int XkWChar;

typedef XkChar* XkString;
typedef XkWChar* XkWString;

typedef signed char XkInt8;
typedef unsigned char XkUInt8;
typedef signed short int  XkInt16;
typedef unsigned short int XkUInt16;
typedef signed int XkInt32;
typedef unsigned int XkUInt32;
typedef signed long long int XkInt64;
typedef unsigned long long int XkUInt64;

typedef float XkFloat32;
typedef double XkFloat64;

typedef unsigned long int XkSize;

#define XK_INT8_MIN (-1-0x7f)
#define XK_INT8_MAX (0x7f)

#define XK_UINT8_MIN 0
#define XK_UINT8_MAX (0xff)

#define XK_INT16_MIN (-1-0x7fff)
#define XK_INT16_MAX (0x7fff)

#define XK_UINT16_MIN 0
#define XK_UINT16_MAX (0xffff)

#define XK_INT32_MIN (-1-0x7fffffff)
#define XK_INT32_MAX (0x7fffffff)

#define XK_UINT32_MIN 0
#define XK_UINT32_MAX (0xffffffffu)

#define XK_INT64_MIN (-1-0x7fffffffffffffff)
#define XK_INT64_MAX (0x7fffffffffffffff)

#define XK_UINT64_MIN 0
#define XK_UINT64_MAX (0xffffffffffffffffu)

#define XK_FLOAT32_MIN 1.17549435082228750797e-38F
#define XK_FLOAT32_MAX 3.40282346638528859812e+38F

#define XK_FLOAT64_MIN 2.22507385850720138309e-308
#define XK_FLOAT64_MAX 1.79769313486231570815e+308

#define XK_SIZE_MIN 0
#if defined(__LP64__)

	#define XK_SIZE_MAX (0xffffffffffffffffu)
#elif defined(__LP64__)
	#define XK_SIZE_MAX (0xffffffffu)
#endif // __LP64__

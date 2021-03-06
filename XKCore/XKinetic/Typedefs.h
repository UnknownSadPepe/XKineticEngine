#pragma once

#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_HANDLE_MIN 		(0)
#if defined(__LP64__) || defined(__LLP64__) || defined(_WIN64)
	#define XK_HANDLE_MAX 	(0xffffffffffffffffu)
#elif defined(__ILP32__) || (__LP32__) || defined(_WIN32)
	#define XK_HANDLE_MAX 	(0xffffffffu)
#endif // (__LP64__ || __LLP64__) || (__ILP32__ || __LP32__)

#if defined(__LP64__) || defined(__LLP64__) || defined(_WIN64)
	#define XK_HANDLE_WIDTH (64)
#elif defined(__ILP32__) || (__LP32__) || defined(_WIN32)
	#define XK_HANDLE_WIDTH (32
#endif // (__LP64__ || __LLP64__) || (__ILP32__ || __LP32__)

#define XK_BOOL8_MIN 			(0)
#define XK_BOOL8_MAX 			(0xff)

#define XK_BOOL8_WIDTH 		(8)

#define XK_BOOL32_MIN 		(0)
#define XK_BOOL32_MAX 		(0xffffffffu)

#define XK_BOOL32_WIDTH 	(32)

#define XK_FALSE 					(0)
#define XK_TRUE 					(1)

#define XK_INT8_MIN 			(-1-0x7f)
#define XK_INT8_MAX 			(0x7f)

#define XK_INT8_WIDTH 		(8)

#define XK_UINT8_MIN 			(0)
#define XK_UINT8_MAX 			(0xff)

#define XK_UINT8_WIDTH 		(8)

#define XK_INT16_MIN 			(-1-0x7fff)
#define XK_INT16_MAX 			(0x7fff)

#define XK_INT16_WIDTH 		(16)

#define XK_UINT16_MIN 		(0)
#define XK_UINT16_MAX 		(0xffff)

#define XK_UINT16_WIDTH 	(16)

#define XK_INT32_MIN 			(-1-0x7fffffff)
#define XK_INT32_MAX 			(0x7fffffff)

#define XK_INT32_WIDTH 		(32)

#define XK_UINT32_MIN 		(0)
#define XK_UINT32_MAX 		(0xffffffffu)

#define XK_UINT32_WIDTH 	(32)

#define XK_INT64_MIN 			(-1-0x7fffffffffffffff)
#define XK_INT64_MAX 			(0x7fffffffffffffff)

#define XK_INT64_WIDTH 		(64)

#define XK_UINT64_MIN 		(0)
#define XK_UINT64_MAX 		(0xffffffffffffffffu)

#define XK_UINT64_WIDTH 	(64)

#define XK_FLOAT32_MIN 		(1.17549435082228750797e-38F)
#define XK_FLOAT32_MAX 		(3.40282346638528859812e+38F)

#define XK_FLOAT32_WIDTH 	(32)

#define XK_FLOAT64_MIN 		(2.22507385850720138309e-308)
#define XK_FLOAT64_MAX 		(1.79769313486231570815e+308)

#define XK_FLOAT64_WIDTH 	(64)

#define XK_CHAR_MIN 			(-1-0x7f)
#define XK_CHAR_MAX 			(0x7f)

#define XK_CHAR_WIDTH 		(8)

#define XK_CHAR8_MIN 			XK_UINT8_MIN
#define XK_CHAR8_MAX 			XK_UINT8_MAX

#define XK_CHAR8_WIDTH 		XK_UINT8_WIDTH

#define XK_CHAR16_MIN 		XK_UINT16_MIN
#define XK_CHAR16_MAX 		XK_UINT16_MAX

#define XK_CHAR16_WIDTH 	XK_UINT16_WIDTH

#define XK_CHAR32_MIN 		XK_UINT32_MIN
#define XK_CHAR32_MAX 		XK_UINT32_MAX

#define XK_CHAR32_WIDTH 	XK_UINT32_WIDTH

#define XK_WCHAR_MIN 			(0)
#if defined(__LLP64__) || defined(__LP32__)
	#define XK_WCHAR_MAX 		(0xffff)
#elif defined(__ILP32__) || defined(__LP64__)
	#define XK_WCHAR_MAX 		(0xffffffffu)
#endif // __LLP64__ ||

#if defined(__LLP64__) || defined(__LP32__) || defined(_WIN32) || defined(_WIN64)
	#define XK_WCHAR_WIDTH (16)
#elif defined(__ILP32__) || defined(__LP64__)
	#define XK_WCHAR_WIDTH (32)
#endif // __LLP64__ ||

#define XK_SIZE_MIN 0
#if defined(__LP32__)  || defined(_WIN32) 
	#define XK_SIZE_MAX 		(0xffff)
#elif defined(__ILP32__) || defined(__LLP64__) || defined(_WIN64)
	#define XK_SIZE_MAX 		(0xffffffffu)
#elif defined(__LP64__)
	#define XK_SIZE_MAX 		(0xffffffffffffffffu)
#endif // __LP32__ || (__ILP32__ || __LLP64__) || __LP64__

#if defined(__LP32__)
	#define XK_SIZE_WIDTH 	(16)
#elif defined(__ILP32__) || defined(__LLP64__) || defined(_WIN64) || defined(_WIN32)
	#define XK_SIZE_WIDTH 	(32)
#elif defined(__LP64__)
	#define XK_SIZE_WIDTH 	(64)
#endif // __LP32__ || (__ILP32__ || __LLP64__) || __LP64__

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkResult_T {
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

xkStaticAssert((sizeof(XkHandle) * 8) == XK_HANDLE_WIDTH);

typedef _Bool XkBool8;

xkStaticAssert((sizeof(XkBool8) * 8) == XK_BOOL8_WIDTH);

#if defined(__LP32__) || defined(_WIN32)
	typedef unsigned long int XkBool32;
#elif defined(__ILP32__) || defined(__LP64__) || defined(__LLP64__) || defined(_WIN64)
	typedef unsigned int XkBool32;
#endif // __LP32__ || (__ILP32__ || __LP64__ || __LLP64__)

xkStaticAssert((sizeof(XkBool32) * 8) == XK_BOOL32_WIDTH);

#if defined(__ILP32__) || defined(__LP32__) || defined(__LLP64__) || defined(__LP64__) || defined(_WIN32) || defined(_WIN64) 
	typedef signed char XkInt8;
#endif // __ILP32__ || __LP32__ || __LLP64__ || __LP64__

xkStaticAssert((sizeof(XkInt8) * 8) == XK_INT8_WIDTH);

#if defined(__ILP32__) || defined(__LP32__) || defined(__LLP64__) || defined(__LP64__) || defined(_WIN32) || defined(_WIN64) 
	typedef unsigned char XkUInt8;
#endif // __ILP32__ || __LP32__ || __LLP64__ || __LP64__

xkStaticAssert((sizeof(XkUInt8) * 8) == XK_UINT8_WIDTH);

#if defined(__LP32__) || defined(__ILP32__) || defined(__LP64__) || defined(__LLP64__) || defined(_WIN32) || defined(_WIN64) 
	typedef signed short int  XkInt16;
#endif // __LP32__ || __ILP32__ || __LP64__ || __LLP64__

xkStaticAssert((sizeof(XkInt16) * 8) == XK_INT16_WIDTH);

#if defined(__LP32__) || defined(__ILP32__) || defined(__LP64__) || defined(__LLP64__) || defined(_WIN32) || defined(_WIN64) 
	typedef unsigned short int XkUInt16;
#endif // __LP32__ || __ILP32__ || __LP64__ || __LLP64__

xkStaticAssert((sizeof(XkUInt16) * 8) == XK_UINT16_WIDTH);

#if defined(__LP32__) || defined(_WIN32)
	typedef signed long int XkInt32;
#elif defined(__ILP32__) || defined(__LP64__) || defined(__LLP64__) || defined(_WIN64) 
	typedef signed int XkInt32;
#endif // __LP32__ || (__ILP32__ || __LP64__ || __LLP64__)

xkStaticAssert((sizeof(XkInt32) * 8) == XK_INT32_WIDTH);

#if defined(__LP32__) || defined(_WIN32)
	typedef unsigned long int XkUInt32;
#elif defined(__ILP32__) || defined(__LP64__) || defined(__LLP64__) || defined(_WIN64) 
	typedef unsigned int XkUInt32;
#endif // __LP32__ || (__ILP32__ || __LP64__ || __LLP64__)

xkStaticAssert((sizeof(XkUInt32) * 8) == XK_UINT32_WIDTH);

#if defined(__LP64__)
	typedef signed long int XkInt64;
#elif defined(__LP32__) || defined(__ILP32__) || defined(__LLP64__) || defined(_WIN32)  || defined(_WIN64)
	typedef signed long long int XkInt64;
#endif // __LP64__ || (__LP32__ || __ILP32__ || __LLP64__)

xkStaticAssert((sizeof(XkInt64) * 8) == XK_INT64_WIDTH);

#if defined(__LP64__)
	typedef unsigned long int XkUInt64;
#elif defined(__LP32__) || defined(__ILP32__) || defined(__LLP64__) || defined(_WIN32)  || defined(_WIN64)
	typedef unsigned long long int XkUInt64;
#endif // __LP64__ || (__LP32__ || __ILP32__ || __LLP64__)

xkStaticAssert((sizeof(XkUInt64) * 8) == XK_UINT64_WIDTH);

typedef float XkFloat32;

xkStaticAssert((sizeof(XkFloat32) * 8) == XK_FLOAT32_WIDTH);

typedef double XkFloat64;

xkStaticAssert((sizeof(XkFloat64) * 8) == XK_FLOAT64_WIDTH);

#if defined(__LP32__) || defined(_WIN32)
	typedef unsigned int XkSize;
#elif defined(__ILP32__) || defined(__LLP64__) || defined(_WIN64)
	typedef unsigned int XkSize;
#elif defined(__LP64__)
	typedef unsigned long int XkSize;
#endif // __LP32__ || (__ILP32__ || __LLP64__) || __LP64__

xkStaticAssert((sizeof(XkSize) * 8) == XK_SIZE_WIDTH);

#if defined(__ILP32__) || defined(__LP32__) || defined(__LLP64__) || defined(__LP64__) || defined(_WIN32)  || defined(_WIN64)
	typedef char XkChar;
#endif // __ILP32__ || __LP32__ || __LLP64__ || __LP64__

xkStaticAssert((sizeof(XkChar) * 8) == XK_CHAR_WIDTH);

typedef XkUInt8 XkChar8;

xkStaticAssert((sizeof(XkChar8) * 8) == XK_CHAR8_WIDTH);

typedef XkUInt16 XkChar16;

xkStaticAssert((sizeof(XkChar16) * 8) == XK_CHAR16_WIDTH);

typedef XkUInt32 XkChar32;

xkStaticAssert((sizeof(XkChar32) * 8) == XK_CHAR32_WIDTH);

#if defined(__LLP64__) || defined(__LP32__)  || defined(_WIN32)  || defined(_WIN64)
	typedef unsigned short int XkWChar;
#elif defined(__ILP32__) || defined(__LP64__)
	typedef unsigned int XkWChar;
#endif // (__LLP64__ || __LP32__) || (__ILP32__ || __LP64__)

xkStaticAssert((sizeof(XkWChar) * 8) == XK_WCHAR_WIDTH);

typedef XkChar* XkString;

typedef XkChar8* XkString8;

typedef XkChar16* XkString16;

typedef XkChar32* XkString32;

typedef XkWChar* XkWString;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

/* ########## TYPES MACROS SECTION ########## */
#define XK_NULL_HANDLE 		((XkHandle)0)

#define XK_INT8_C(x)    (XkInt8)(x)
#define XK_INT16_C(x)   (XkInt16)(x)
#define XK_INT32_C(x)   (XkInt32)(x)
#define XK_INT64_C(x)   (XkInt64)(x ## LL)

#define XK_UINT8_C(x)   (XkUint8)(x)
#define XK_UINT16_C(x)  (XkUint16)(x)
#define XK_UINT32_C(x)  (XkUint32)(x ## U)
#define XK_UINT64_C(x)  (XkUInt64)(x ## ULL)

#define XK_FLOAT32_C(x)	(XkFloat32)(x ## F)
#define XK_FLOAT64_C(x)	(XkFloat32)(x)

#define XK_CHAR_C(x)		(XkChar)(x)
#define XK_CHAR8_C(x)		(XkChar8)(u8 ## x)
#define XK_CHAR16_C(x)	(XkChar16)(u ## x)
#define XK_CHAR32_C(x)	(XkChar32)(U ## x)
#define XK_WCHAR_C(x)		(XkWChar)(L ## x)

#define XK_STRING_C(x)		(XkString)(x)
#define XK_STRING8_C(x)		(XkString8)(u8 ## x)
#define XK_STRING16_C(x)	(XkString16)(u ## x)
#define XK_STRING32_C(x)	(XkString32)(U ## x)
#define XK_WSTRING_C(x)		(XkWString)(L ## x)


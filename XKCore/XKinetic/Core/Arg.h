#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/* ########## MACROS SECTION ########## */
#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__) || defined(__MINGW32__) || defined(__MINGW64__)
	typedef __builtin_va_list XkArgs;
	#define xkStartArgs(args, param) 	__builtin_va_start(args, param)
	#define xkEndArgs(args) 					__builtin_va_end(args)
	#define xkNextArgs(args, type) 		__builtin_va_arg(args, type)
	#define xkCopyArgs(dst, src)			__builtin_va_copy(dst, src)
#elif defined(_MSC_VER)
	#include <vadefs.h>

	typedef va_list XkArgs;
	#define xkStartArgs(args, param) 	__crt_va_start(args, param)
	#define xkEndArgs(args) 					__crt_va_end(args)
	#define xkNextArgs(args, type) 		__crt_va_arg(args, type)
	#define xkCopyArgs(dst, src)			((dst) = (src))
#else
	#error Unknown compiler
#endif // (__GNUC__ || __clang__ || __TINYC__ | __MINGW32__ || __MINGW64__) || _MSC_VER

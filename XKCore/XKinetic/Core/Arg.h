#pragma once

#include "XKinetic/XKCore.h"

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__) || defined(__MINGW32__) || defined(__MINGW64__)
	typedef __builtin_va_list XkArgs;
	#define xkStartArgs(args, param) __builtin_va_start(args, param)
	#define xkEndArgs(args) __builtin_va_end(args)
	#define xkNextArgs(args, type) __builtin_va_arg(args, type)
#elif defined(_MSC_VER) 
	#include <stdarg.h>

	typedef va_list XkArgs;
	#define xkStartArgs(args, param) va_start(args, param)
	#define xkEndArgs(args) va_end(args)
	#define xkNextArgs(args, type) va_arg(args, type)
#else
	#error Unknown compiler
#endif // (__GNUC__ || __clang__ || __TINYC__ | __MINGW32__ || __MINGW64__) || _MSC_VER

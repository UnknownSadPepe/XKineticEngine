#pragma once

#if defined(__unix__)
	// Define unix platform.
	#define XK_UNIX 1
#else 
	// Undefine unix platform.
	#define XK_UNIX 0
#endif // __unix__

#if defined(_POSIX_VERSION)
	// Define posix standart.
	#define XK_POSIX 1
#else
	// Undefine posix standart.
	#define XK_POSIX 0
#endif // _POSIX_VERSION

#if defined(__linux__) || defined(__gnu_linux__) 
	// Define linux platform.
	#define XK_LINUX 1
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	// Define win32 platform.
	#define XK_WIN32 1

	#if defined(_WIN64)
		// Define win64 platform.
		#define XK_WIN64 1
	#else
		// Undefine win64 platform.
		#define XK_WIN64 0
	#endif // _WIN64
#else
	// Undefine linux platform.
	#define XK_LINUX 0
	// Undefine win32 platform.
	#define XK_WIN32 0
#endif // WIN32 || _WIN32 || __WIN32__

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	// Define shader library export function attribute.
	#define XK_EXPORT __attribute__((visibility("default")))
	// Define shader library import function attribute.
	#define XK_IMPORT
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	// Define shader library export function attribute.
	#define XK_EXPORT __declspec(dllexport)
	// Define shader library import function attribute.
	#define XK_IMPORT __declspec(dllimport)
#else
	#error Unknown compiler
#endif // __GNUC__ || __clang__ || __TINYC__

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	#define XK_INLINE __attribute__((always_inline)) inline
	#define XK_NOINLINE __attribute__((noinline)) 	

	#define __xkBreak() __builtin_trap()
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#include <intrin.h>
	#define XK_INLINE __forceinline
	#define XK_NOINLINE __declspec(noinline)

	#define __xkBreak() __debugbreak()
#else 
	#error Unknown compiler
#endif // __GNUC__ || __clang__ || __TINYC__

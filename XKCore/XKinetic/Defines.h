#pragma once

/* ########## MACROS SECTION ########## */
#if defined(__linux__) || defined(__gnu_linux__) 
	#define XK_LINUX
#elif defined(WIN64)
	#define XK_WIN64
#else
	#error Unknown platform
#endif // (__linux__ || __gnu_linux__) || (WIN64)

#if defined(__unix__) && !defined(WIN64)
	#define XK_UNIX
#endif // __unix__ && !WIN64

#if defined(_POSIX_VERSION)
	#define XK_POSIX
#endif // _POSIX_VERSION

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	#define XK_EXPORT __attribute__((visibility("default")))
	#define XK_IMPORT
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#define XK_EXPORT __declspec(dllexport)
	#define XK_IMPORT __declspec(dllimport)
#else
	#error Unknown compiler
#endif // (__GNUC__ || __clang__ || __TINYC__) || (_MSC_VER || __MINGW32__ || __MINGW64__)

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	#define XK_INLINE __attribute__((always_inline)) inline
	#define XK_NOINLINE __attribute__((noinline))
	#define XK_CLEANUP(function) __attribute__((cleanup(function)))

	#define __xkBreak() __builtin_trap()
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#include <intrin.h>
	#define XK_INLINE __forceinline
	#define XK_NOINLINE __declspec(noinline)
	#define XK_CLEANUP(function) __attribute__((cleanup(function)))

	#define __xkBreak() __debugbreak()
#else 
	#error Unknown compiler
#endif // (__GNUC__ || __clang__ || __TINYC__) || (_MSC_VER || __MINGW32__ || __MINGW64__)

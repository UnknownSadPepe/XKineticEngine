#pragma once

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	#if defined(__linux__) || defined(__gnu_linux__) 
		// Define linux platform.
		#define XK_PLATFORM_LINUX

		#define XK_API_EXPORT __attribute__((visibility("default")))
		#define XK_API_IMPORT __attribute__((visibility("hidden")))
	#elif defined(__unix__)
		// Define unix platform.
		#define XK_PLATFORM_UNIX

		#define XK_API_EXPORT __attribute__((visibility("default")))
		#define XK_API_IMPORT __attribute__((visibility("hidden")))
	#elif defined(_POSIX_VERSION)
		// Define posix standart.
		#define XK_PLATFORM_POSIX

		#define XK_API_EXPORT __attribute__((visibility("default")))
		#define XK_API_IMPORT __attribute__((visibility("hidden")))
	#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
		// Define win32 platform.
		#define XK_PLATFORM_WIN32

		#define XK_API_EXPORT __declspec(dllexport)
		#define XK_API_IMPORT __declspec(dllimport)

		#if defined(_WIN64)
			// Define win64 platform.
			#define XK_PLATFORM_WIN64
		#endif // _WIN64
	#else
		#error Unknown platform
	#endif // __linux__ || __gnu_linux__
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#if defined(__linux__) || defined(__gnu_linux__) 
		// Define linux platform.
		#define XK_PLATFORM_LINUX
	#elif defined(__unix__)
		// Define unix platform.
		#define XK_PLATFORM_UNIX
	#elif defined(_POSIX_VERSION)
		// Define posix standart.
		#define XK_PLATFORM_POSIX
	#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
		// Define win32 platform.
		#define XK_PLATFORM_WIN32
		#if defined(_WIN64)
			// Define win64 platform.
			#define XK_PLATFORM_WIN64
		#endif // _WIN64
	#else
		#error Unknown platform
	#endif // __linux__ || __gnu_linux__
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

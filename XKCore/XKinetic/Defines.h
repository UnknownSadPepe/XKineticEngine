#pragma once

/* ########## MACROS SECTION ########## */
#if defined(__linux__) || defined(__gnu_linux__) 
	#define XK_LINUX

	#if defined(__ANDROID__)
		#define XK_ANDROID
	#endif // __ANDROID__
#elif defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WIN64__) || defined(_WIN64) || defined(WIN64)
	#define XK_WINDOWS
#elif __APPLE__
	#define XK_APPLE

	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
		// iOS Simulator
		#define XK_IOS
		#define XK_IOS_SIMULATOR
	#elif TARGET_OS_IPHONE
		#define XK_IOS
		// iOS device
	#elif TARGET_OS_MAC
		#define XK_MACOS
	#else
		#error Unknown Apple platform
	#endif // TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || TARGET_OS_MAC
#else
	#error Unknown platform
#endif /* 
	(__linux__ || __gnu_linux__ ? __ANDROID__) 
	|| WIN64 
	|| (__APPLE__ ? TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE || TARGET_OS_MAC)
*/

#if defined(__unix__)
	#define XK_UNIX
#endif // __unix__

#if defined(_POSIX_VERSION)
	#define XK_POSIX
#endif // _POSIX_VERSION

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	#define XK_EXPORT		__attribute__((visibility("default")))
	#define XK_IMPORT

	//#define XK_EXPORT __attribute__((dllexport))
	//#define XK_IMPORT __attribute__((dllimport))

	#define XK_INLINE __attribute__((always_inline)) inline
	#define XK_NOINLINE __attribute__((noinline))
	#define XK_CLEANUP(function) __attribute__((cleanup(function)))

	#define XK_FASTCALL __attribute__((fastcall))
	#define XK_CDECL __attribute__((cdecl))
	#define XK_STDCALL __attribute__((stdcall))

	#define XK_PURE __attribute__((pure))
	
	#define XK_NONULL __attribute__((nonull))

	#define XK_VISIBILITY_DEFAULT		__attribute__((visibility("default")))
	#define XK_VISIBILITY_HIDDEN		__attribute__((visibility("hidden")))
	#define XK_VISIBILITY_PROTECTED	__attribute__((visibility("protected")))
	#define XK_VISIBILITY_INTERNAL	__attribute__((visibility("internal")))

	#define __xkBreak() __builtin_trap()
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#define XK_EXPORT __declspec(dllexport)
	#define XK_IMPORT __declspec(dllimport)

	#include <intrin.h>
	#define XK_INLINE __forceinline
	#define XK_NOINLINE __declspec(noinline)
	#define XK_CLEANUP(function) __attribute__((cleanup(function)))

	#define XK_FASTCALL __fastcall
	#define XK_CDECL 		__cdecl
	#define XK_STDCALL 	__stdcall

	#define XK_PURE __attribute__((pure))
	
	#define XK_NONULL __attribute__((nonull))

	#define XK_VISIBILITY_DEFAULT		__attribute__((visibility("default")))
	#define XK_VISIBILITY_HIDDEN		__attribute__((visibility("hidden")))
	#define XK_VISIBILITY_PROTECTED	__attribute__((visibility("protected")))
	#define XK_VISIBILITY_INTERNAL	__attribute__((visibility("internal")))

	#define __xkBreak() __debugbreak()
#else 
	#error Unknown compiler
#endif /* 
	(__GNUC__ || __clang__ || __TINYC__) 
	|| (_MSC_VER || __MINGW32__ || __MINGW64__)
*/

#define C11 201112L
#define C17 201710L
#define C23 202312L


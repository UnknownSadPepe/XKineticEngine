#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
#ifdef XK_DEBUG
extern XKCORE_API void __xkAssertion(const XkString, const XkString, const XkInt32);
#endif // XK_DEBUG

#if defined(__GNUC__) || defined(__clang__) || defined(__TINYC__)
	#if __STDC_VERSION__ >= C23
		#define xkStaticAssert(expr) 		static_assert(expr);
	#else
		#define xkStaticAssert(expr) 		static_assert(expr, "static assert failed");
	#endif // __STDC_VERSION__ >= C23
#elif defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
	#if __STDC_VERSION__ >= C23
		#define xkStaticAssert(expr) 		static_assert(expr);
	#else
		#define xkStaticAssert(expr) 		static_assert(expr, "static assert failed");
	#endif // __STDC_VERSION__ >= C23
#else 
	#error Unknown compiler
#endif // (__GNUC__ || __clang__ || __TINYC__) || (_MSC_VER || __MINGW32__ || __MINGW64__)

/* ########## FUNCTIONS MACROS SECTION ########## */
#ifdef XK_DEBUG
	#define xkAssert(expr)													\
	{																								\
		if(expr) {																		\
		} else {																			\
			__xkAssertion(#expr, __FILE__, __LINE__);		\
			__xkBreak();																\
		}																							\
	}
#else
	#define xkAssert(expr)
#endif // XK_DEBUG

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

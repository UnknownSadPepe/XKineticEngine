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

#define xkStaticAssert(expr) 			_Static_assert(expr);
//#define xkStaticAssert(expr, msg) _Static_assert(expr, msg);

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

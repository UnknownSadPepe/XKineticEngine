#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef XK_DEBUG

XKCORE_API void __xkAssertion(const XkString, const XkString, const XkInt32);

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

#ifdef __cplusplus
}
#endif // __cplusplus

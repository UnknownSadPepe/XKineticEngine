#pragma once

#include "XKinetic/XKCore.h"

#ifdef XK_DEBUG

XKCORE_API void __xkAssertion(const XkChar8*, const XkChar8*, const XkInt32);

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

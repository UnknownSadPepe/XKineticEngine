#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XKMATH_DEBUG__)
	#define XKMATH_DEBUG 
#endif // _DEBUG || __XKMATH_DEBUG__

#ifdef __XKMATH_BUILD__
	#define XKMATH_API XK_EXPORT
#else
	#define XKMATH_API XK_IMPORT
#endif // __XKMATH_BUILD__

#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XKCORE_DEBUG__)
	#define XKCORE_DEBUG 
#endif // _DEBUG || __XKCORE_DEBUG__

#ifdef __XKCORE_BUILD__
	#define XKCORE_API XK_EXPORT
#else
	#define XKCORE_API XK_IMPORT
#endif // __XKCORE_BUILD__

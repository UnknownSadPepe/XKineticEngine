#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XKCORE_DEBUG__)
	#define XKCORE_DEBUG 
#endif // _DEBUG || __XKCORE_DEBUG__

#ifdef __XKCORE_DLL_BUILD__
	#define XKCORE_API XK_API_EXPORT
#else
	#define XKCORE_API
#endif // __XKCORE_DLL_BUILD__

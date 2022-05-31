#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XKVULKAN_DEBUG__)
	#define XKVK_DEBUG 
#endif // _DEBUG || __XKVULKAN_DEBUG__

#ifdef __XKVULKAN_DLL_BUILD__
	#define XKVULKAN_API XK_API_EXPORT
#else
	#define XKVULKAN_API
#endif // __XKVULKAN_DLL_BUILD__

#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XK_DEBUG__)
	#define XK_DEBUG 
#endif // _DEBUG || __XK_DEBUG__

#ifdef __XK_DLL_BUILD__
	#define XK_API XK_API_EXPORT
#else
	#define XK_API
#endif // __XK_DLL_BUILD__

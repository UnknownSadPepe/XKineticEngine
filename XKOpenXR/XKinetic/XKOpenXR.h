#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XKOPENXR_DEBUG__)
	#define XKOPENXR_DEBUG
#endif // _DEBUG || __XKOPENXR_DEBUG__

#ifdef __XKOPENXR_BUILD__
	#define XKOPENXR_API XK_EXPORT
#else
	#define XKOPENXR_API XK_IMPORT
#endif // __XKOPENXR_BUILD__

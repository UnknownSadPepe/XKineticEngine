#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XK_DEBUG__)
	#define XK_DEBUG 
#endif // _DEBUG || __XK_DEBUG__

#ifdef __XK_BUILD__
	#define XK_API XK_EXPORT
#else
	#define XK_API XK_IMPORT
#endif // __XK_BUILD__

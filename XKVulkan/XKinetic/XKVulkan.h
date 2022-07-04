#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

/* ########## MACROS SECTION ########## */
#if defined(_DEBUG) || defined(__XKVULKAN_DEBUG__)
	#define XKVULKAN_DEBUG 
#endif // _DEBUG || __XKVULKAN_DEBUG__

#ifdef __XKVULKAN_BUILD__
	#define XKVULKAN_API XK_EXPORT
#else
	#define XKVULKAN_API XK_IMPORT
#endif // __XKVULKAN_BUILD__

#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

/* ########## MACROS SECTION ########## */
#if defined(_DEBUG) || defined(__XKD3D12_DEBUG__)
	#define XKD3D12_DEBUG 
#endif // _DEBUG || __XKDIRECTX12_DEBUG__

#ifdef __XKD3D12_BUILD__
	#define XKD3D12_API XK_EXPORT
#else
	#define XKD3D12_API XK_IMPORT
#endif // __XKD3D12_BUILD__

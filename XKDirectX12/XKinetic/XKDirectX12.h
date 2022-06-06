#pragma once

#include "XKinetic/Defines.h"
#include "XKinetic/Typedefs.h"

#if defined(_DEBUG) || defined(__XKDIRECTX12_DEBUG__)
	#define XKDIRECTX12_DEBUG 
#endif // _DEBUG || __XKDIRECTX12_DEBUG__

#ifdef __XKDIRECTX12_BUILD__
	#define XKDIRECTX12_API XK_EXPORT
#else
	#define XKDIRECTX12_API XK_IMPORT
#endif // __XKDIRECTX12_BUILD__

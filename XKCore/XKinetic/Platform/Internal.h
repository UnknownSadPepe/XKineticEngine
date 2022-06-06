#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/Internal.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/Internal.h"
#endif // XK_LINUX
#include "XKinetic/Platform/External.h"

typedef struct {
	XK_PLATFORM;
} XkPlatform;

extern XkPlatform _xkPlatform;

#define __xkErrorHandle(format) __xkErrorHandler("%s %s %d", format, __FILE__, __LINE__)
XK_IMPORT void __xkErrorHandler(const XkChar8* pFormat, ...);


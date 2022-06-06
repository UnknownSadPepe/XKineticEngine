#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

XK_EXPORT XkResult xkMemoryInitialize(void);
XK_EXPORT void xkMemoryTerminate(void);

XK_EXPORT XkHandle xkAllocateMemory(const XkSize);
XK_EXPORT XkHandle xkReallocateMemory(const XkHandle, const XkSize);
XK_EXPORT void xkFreeMemory(const XkHandle);

XK_EXPORT XkHandle xkCopyMemory(XkHandle, const XkHandle, const XkSize);
XK_EXPORT XkHandle xkMoveMemory(XkHandle, const XkHandle, const XkSize);
XK_EXPORT XkHandle xkZeroMemory(XkHandle, const XkSize);

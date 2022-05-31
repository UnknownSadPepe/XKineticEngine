#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkSize __xkGetTime(void) {
	return((XkSize)GetTickCount());
}

#endif // XK_PLATFORM_WIN32


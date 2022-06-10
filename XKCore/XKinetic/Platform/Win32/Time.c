#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkSize xkGetTime(void) {
	return((XkSize)(GetTickCount() / 1000));
}

#endif // XK_WIN32


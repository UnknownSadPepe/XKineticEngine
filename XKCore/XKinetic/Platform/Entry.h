#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_PLATFORM_LINUX)
	#include "XKinetic/Platform/Linux/Entry.h"
#elif defined(XK_PLATFORM_WIN32)
	#include "XKinetic/Platform/Win32/Entry.h"
#endif // XK_PLATFORM_LINUX

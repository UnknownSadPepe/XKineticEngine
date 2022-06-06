#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

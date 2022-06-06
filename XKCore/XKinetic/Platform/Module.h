#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

typedef XkHandle XkModule;
typedef void(*XkProcPfn)(void);

XK_EXPORT XkResult xkLoadModule(XkModule, const XkChar8*);
XK_EXPORT void xkUnloadModule(XkModule);
XK_EXPORT XkResult xkGetModuleSymbol(XkProcPfn, const XkChar8*, XkModule);

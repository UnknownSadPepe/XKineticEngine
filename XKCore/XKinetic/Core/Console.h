#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"
#include "XKinetic/Platform/External.h"

XK_API_EXPORT XkResult xkConsoleInitialize(void);
XK_API_EXPORT void xkConsoleTerminate(void);

XKCORE_API void xkColorConsole(const XkConsoleHandle, const XkConsoleColor);
XKCORE_API void xkFWriteConsole(const XkConsoleHandle, const XkChar8*, ...);
XKCORE_API void xkFReadConsole(XkChar8*, ...);
XKCORE_API void xkVWriteConsole(const XkConsoleHandle, const XkChar8*, XkArgs);
XKCORE_API void xkVReadConsole(XkChar8*, XkArgs);
XKCORE_API void xkWriteConsole(const XkConsoleHandle, const XkChar8*, const XkSize);
XKCORE_API void xkReadConsole(XkChar8*, const XkSize);

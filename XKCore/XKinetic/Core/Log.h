#pragma once

#include "XKinetic/XKCore.h"

XK_EXPORT XkResult xkLogInitialize(void);
XK_EXPORT void xkLogTerminate(void);

XKCORE_API void xkLogFatal(const XkString, ...);
XKCORE_API void xkLogError(const XkString, ...);
XKCORE_API void xkLogWarning(const XkString, ...);
XKCORE_API void xkLogTrace(const XkString, ...);
XKCORE_API void xkLogInfo(const XkString, ...);
XKCORE_API void xkLogNotice(const XkString, ...);
XKCORE_API void xkLogDebug(const XkString, ...);

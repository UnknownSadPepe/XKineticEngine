#pragma once

#include "XKinetic/XKCore.h"

XK_API_EXPORT XkResult xkLogInitialize(void);
XK_API_EXPORT void xkLogTerminate(void);

XKCORE_API void xkLogFatal(const XkChar8*, ...);
XKCORE_API void xkLogError(const XkChar8*, ...);
XKCORE_API void xkLogWarning(const XkChar8*, ...);
XKCORE_API void xkLogTrace(const XkChar8*, ...);
XKCORE_API void xkLogInfo(const XkChar8*, ...);
XKCORE_API void xkLogNotice(const XkChar8*, ...);
XKCORE_API void xkLogDebug(const XkChar8*, ...);

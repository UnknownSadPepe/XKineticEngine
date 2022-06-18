#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XK_EXPORT XkResult xkLogInitialize(void);
XK_EXPORT void xkLogTerminate(void);

XKCORE_API void xkLogFatal(const XkString, ...);
XKCORE_API void xkLogError(const XkString, ...);
XKCORE_API void xkLogWarning(const XkString, ...);
XKCORE_API void xkLogTrace(const XkString, ...);
XKCORE_API void xkLogInfo(const XkString, ...);
XKCORE_API void xkLogNotice(const XkString, ...);
#if defined(XK_DEBUG)
	XKCORE_API void xkLogDebug(const XkString, ...);
#else
	#define xkLogDebug(format, ...)
#endif // XK_DEBUG

#ifdef __cplusplus
}
#endif // __cplusplus

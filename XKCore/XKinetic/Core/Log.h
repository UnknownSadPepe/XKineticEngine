#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Arg.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XK_EXPORT XkResult 	xkInitializeLog();
extern XK_EXPORT void 			xkTerminateLog();

extern XKCORE_API void 			xkLogFatal(const XkString, ...);
extern XKCORE_API void 			xkLogError(const XkString, ...);
extern XKCORE_API void 			xkLogWarning(const XkString, ...);
extern XKCORE_API void 			xkLogTrace(const XkString, ...);
extern XKCORE_API void 			xkLogInfo(const XkString, ...);
extern XKCORE_API void 			xkLogNotice(const XkString, ...);
#if defined(XK_DEBUG)
extern XKCORE_API void 			xkLogDebug(const XkString, ...);
#endif // XK_DEBUG
	
/* ########## FUNCTIONS MACROS SECTION ########## */
#if !defined(XK_DEBUG)
	#define 									xkLogDebug(format, ...)
#endif // !XK_DEBUG

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

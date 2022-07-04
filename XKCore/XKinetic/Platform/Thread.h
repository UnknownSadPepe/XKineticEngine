#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkHandle(*XkThreadRoutinePfn)(XkHandle);
typedef struct XkThread_T* 	XkThread;
typedef struct XkMutex_T* 	XkMutex;

/* ########## FUNCTIONS SECTION ########## */
XKCORE_API XkResult 	xkCreateThread(XkThread*, const XkThreadRoutinePfn);
XKCORE_API void 			xkJoinThread(XkThread, XkInt32** const);
XKCORE_API void 			xkDetachThread(XkThread);
XKCORE_API void 			xkExitThread();
XKCORE_API void 			xkKillThread(XkThread);
XKCORE_API void 			xkThreadSleep(const XkSize);

XKCORE_API XkResult 	xkCreateMutex(XkMutex*);
XKCORE_API void 			xkDestroyMutex(XkMutex);
XKCORE_API void 			xkLockMutex(XkMutex);
XKCORE_API void 			xkUnlockMutex(XkMutex);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

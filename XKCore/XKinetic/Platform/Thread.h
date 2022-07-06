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
extern XKCORE_API XkResult 	xkCreateThread(XkThread*, const XkThreadRoutinePfn);
extern XKCORE_API void 			xkJoinThread(XkThread, XkInt32** const);
extern XKCORE_API void 			xkDetachThread(XkThread);
extern XKCORE_API void 			xkExitThread();
extern XKCORE_API void 			xkKillThread(XkThread);
extern XKCORE_API void 			xkThreadSleep(const XkSize);

extern XKCORE_API XkResult 	xkCreateMutex(XkMutex*);
extern XKCORE_API void 			xkDestroyMutex(XkMutex);
extern XKCORE_API void 			xkLockMutex(XkMutex);
extern XKCORE_API void 			xkUnlockMutex(XkMutex);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

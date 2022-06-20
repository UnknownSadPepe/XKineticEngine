#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef XkHandle(*XkThreadRoutinePfn)(XkHandle);
typedef struct XkThread* XkThread;
typedef struct XkMutex* XkMutex;

XKCORE_API XkResult xkCreateThread(XkThread*, const XkThreadRoutinePfn);
XKCORE_API void xkJoinThread(XkThread, XkInt32** const);
XKCORE_API void xkDetachThread(XkThread);
XKCORE_API void xkExitThread(void);
XKCORE_API void xkKillThread(XkThread);
XKCORE_API void xkThreadSleep(const XkSize);

XKCORE_API XkResult xkCreateMutex(XkMutex*);
XKCORE_API void xkDestroyMutex(XkMutex);
XKCORE_API void xkLockMutex(XkMutex);
XKCORE_API void xkUnlockMutex(XkMutex);

#ifdef __cplusplus
}
#endif // __cplusplus

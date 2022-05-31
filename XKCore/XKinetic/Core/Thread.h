#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/External.h"

XK_API_EXPORT XkResult xkThreadInitialize(void);
XK_API_EXPORT void xkThreadTerminate(void);

XKCORE_API XkResult xkCreateThread(XkThread*, XkThreadRoutinePfn);
XKCORE_API void xkJoinThread(XkThread, XkInt32* const);
XKCORE_API void xkDetachThread(XkThread);
XKCORE_API void xkExitThread(XkThread, const XkInt32);
XKCORE_API void xkKillThread(XkThread);
XKCORE_API XkThread xkThreadSelf(void);
XKCORE_API void xkThreadYield(void);
XKCORE_API void xkThreadSleep(const XkSize);

XKCORE_API XkResult xkCreateMutex(XkMutex*);
XKCORE_API void xkDestroyMutex(XkMutex);
XKCORE_API XkResult xkLockMutex(XkMutex);
XKCORE_API XkResult xkTrylockMutex(XkMutex);
XKCORE_API XkResult xkUnlockMutex(XkMutex);


#pragma once

#include "XKinetic/XKCore.h"

typedef XkHandle(*XkThreadRoutinePfn)(XkHandle);

typedef struct XkThread* XkThread;

typedef struct XkMutex* XkMutex;

XK_EXPORT XkResult xkCreateThread(XkThread*, const XkThreadRoutinePfn);
XK_EXPORT void xkJoinThread(XkThread, XkInt32** const);
XK_EXPORT void xkDetachThread(XkThread);
XK_EXPORT void xkExitThread(void);
XK_EXPORT void xkKillThread(XkThread);
XK_EXPORT void xkThreadSleep(const XkSize);

XK_EXPORT XkResult xkCreateMutex(XkMutex*);
XK_EXPORT void xkDestroyMutex(XkMutex);
XK_EXPORT void xkLockMutex(XkMutex);
XK_EXPORT void xkUnlockMutex(XkMutex);

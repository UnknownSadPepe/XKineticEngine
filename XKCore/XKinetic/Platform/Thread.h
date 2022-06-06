#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

typedef XkHandle(*XkThreadRoutinePfn)(XkHandle);

struct XkThread {
	XK_PLATFORM_THREAD;
};

typedef struct XkThread* XkThread;

struct XkMutex {
	XK_PLATFORM_MUTEX;
};

typedef struct XkMutex* XkMutex;

XK_EXPORT XkResult xkThreadInitialize(void);
XK_EXPORT void xkThreadTerminate(void);

XK_EXPORT XkResult xkCreateThread(XkThread, const XkThreadRoutinePfn);
XK_EXPORT void xkJoinThread(XkThread, XkInt32** const);
XK_EXPORT void xkDetachThread(XkThread);
XK_EXPORT void xkExitThread(void);
XK_EXPORT void xkKillThread(XkThread);
XK_EXPORT XkThread xkThreadSelf(void);
XK_EXPORT void xkThreadYield(void);
XK_EXPORT void xkThreadSleep(const XkSize);

XK_EXPORT XkResult xkCreateMutex(XkMutex);
XK_EXPORT void xkDestroyMutex(XkMutex);
XK_EXPORT XkResult xkLockMutex(XkMutex);
XK_EXPORT XkResult xkTrylockMutex(XkMutex);
XK_EXPORT XkResult xkUnlockMutex(XkMutex);

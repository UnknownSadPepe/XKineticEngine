#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/Memory.h"
#include "XKinetic/Core/Thread.h"

XkResult xkThreadInitialize(void) {
	XkResult result = XK_SUCCESS;

	result = __xkThreadInitialize();
	if(result != XK_SUCCESS) goto _catch;

	

_catch:
	return(result);
}

void xkThreadTerminate(void) {
	__xkThreadTerminate();
}


XkResult xkCreateThread(XkThread* pThread, XkThreadRoutinePfn pfnRoutine) {
	XkResult result = XK_SUCCESS;

	*pThread = xkAllocateMemory(sizeof(struct XkThread));
	if(!(*pThread)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkThread thread = *pThread;

	result = __xkCreateThread(thread, pfnRoutine);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, XkInt32* const pResult) {
	__xkJoinThread(thread, pResult);
}

void xkDetachThread(XkThread thread) {
	__xkDetachThread(thread);
}

void xkExitThread(XkThread thread, const XkInt32 result) {
	__xkExitThread(thread, result);
}

void xkKillThread(XkThread thread) {
	__xkKillThread(thread);
}

XkThread xkThreadSelf(void) {
	return(__xkThreadSelf());
}

void xkThreadYield(void) {
	__xkThreadYield();
}

void xkThreadSleep(const XkSize milliSeconds) {
	__xkThreadSleep(milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	XkResult result = XK_SUCCESS;

	*pMutex = xkAllocateMemory(sizeof(struct XkMutex));
	if(!(*pMutex)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkMutex mutex = *pMutex;

	result = __xkCreateMutex(mutex);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	__xkDestroyMutex(mutex);
	xkFreeMemory(mutex);
}

XkResult xkLockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	result = __xkLockMutex(mutex);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

XkResult xkTrylockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	result = __xkTrylockMutex(mutex);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

XkResult xkUnlockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	result = __xkUnlockMutex(mutex);
	if(result != XK_SUCCESS) goto _catch;
	
_catch:
	return(result);
}

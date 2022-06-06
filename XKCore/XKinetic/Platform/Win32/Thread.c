#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

#define XK_WIN32_THREAD_STACK_SIZE (1024 * 1024)

XkResult xkCreateThread(XkThread* pThread, const XkThreadRoutinePfn pfnRoutine) {
	XkResult result = XK_SUCCESS;

	*pThread = xkAllocateMemory(sizeof(struct XkThread));
	if(!(*pThread)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkThread thread = *pThread;

	thread->handle.pStack = xkAllocateMemory(XK_WIN32_THREAD_STACK_SIZE);
	if(!thread->handle.pStack) {
		__xkErrorHandle("Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	thread->handle.handle = CreateThread(NULL, XK_WIN32_THREAD_STACK_SIZE, pfnRoutine, thread->handle.pStack, 0, &thread->handle.id);
	if(!thread->handle.handle) {
		__xkErrorHandle("Failed to create thread");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, const XkInt32** ppResult) {
	/// TODO: implementation.
	WaitForSingleObject(thread->handle.handle, INFINITE);
	CloseHandle(thread->handle.handle);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	/// TODO: implementation.
	TerminateThread(thread->handle.handle, 0);
	CloseHandle(thread->handle.handle);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkExitThread() {
	/// TODO: implementation.
	XkThread thread = xkThreadSelf();
	ExitThread(0);
	CloseHandle(thread->handle.handle);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkKillThread(XkThread thread) {
	/// TODO: implementation.
	TerminateThread(thread->handle.handle, 0);
	CloseHandle(thread->handle.handle);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	Sleep(milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	XkResult result = XK_SUCCESS;

	*pMutex = xkAllocateMemory(sizeof(struct XkMutex));
	if(!(*pMutex)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkMutex mutex = *pMutex;

	InitializeCriticalSection(&mutex->handle.handle);

_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	DeleteCriticalSection(&mutex->handle.handle);
	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	EnterCriticalSection(&mutex->handle.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	LeaveCriticalSection(&mutex->handle.handle);
}

#endif // XK_WIN32

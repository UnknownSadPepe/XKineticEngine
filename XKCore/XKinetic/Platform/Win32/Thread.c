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

	thread->win32.pStack = xkAllocateMemory(XK_WIN32_THREAD_STACK_SIZE);
	if(!thread->win32.pStack) {
		__xkErrorHandle("Win32: Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	thread->win32.handle = CreateThread(NULL, XK_WIN32_THREAD_STACK_SIZE, (LPTHREAD_START_ROUTINE)pfnRoutine, thread->win32.pStack, 0, &thread->win32.id);
	if(!thread->win32.handle) {
		__xkErrorHandle("Win32: Failed to create thread");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, XkInt32** const ppResult) {
	WaitForSingleObject(thread->win32.handle, INFINITE);
	CloseHandle(thread->win32.handle);
	xkFreeMemory(thread->win32.pStack);
	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	TerminateThread(thread->win32.handle, 0);
	CloseHandle(thread->win32.handle);
	xkFreeMemory(thread->win32.pStack);
	xkFreeMemory(thread);
}

void xkExitThread() {
	ExitThread(0);
}

void xkKillThread(XkThread thread) {
	TerminateThread(thread->win32.handle, 0);
	CloseHandle(thread->win32.handle);
	xkFreeMemory(thread->win32.pStack);
	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	Sleep(milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	XkResult result = XK_SUCCESS;

	*pMutex = xkAllocateMemory(sizeof(struct XkMutex));
	if(!(*pMutex)) {
		__xkErrorHandle("Win32: Failed to create mutex");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkMutex mutex = *pMutex;

	InitializeCriticalSection(&mutex->win32.handle);

_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	DeleteCriticalSection(&mutex->win32.handle);
	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	EnterCriticalSection(&mutex->win32.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	LeaveCriticalSection(&mutex->win32.handle);
}

#endif // XK_WIN32

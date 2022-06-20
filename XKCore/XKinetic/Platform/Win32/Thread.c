#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

#define XK_WIN32_THREAD_STACK_SIZE (1024 * 1024)

XkResult xkCreateThread(XkThread* pThread, const XkThreadRoutinePfn pfnRoutine) {
	XkResult result = XK_SUCCESS;

	// Allocate thread.
	*pThread = xkAllocateMemory(sizeof(struct XkThread));
	if(!(*pThread)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	// Template thread.
	XkThread thread = *pThread;

	// Allocate thread stack memory.
	thread->win32.pStack = xkAllocateMemory(XK_WIN32_THREAD_STACK_SIZE);
	if(!thread->win32.pStack) {
		__xkErrorHandle("Win32: Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Create Win32 thread.
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
	// Wait for Win32 thread.
	WaitForSingleObject(thread->win32.handle, INFINITE);

	// Close Win32 thread.
	CloseHandle(thread->win32.handle);

	// Free thread stack memory.
	xkFreeMemory(thread->win32.pStack);

	// Free thread.
	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	// Terminate Win32 thread.
	TerminateThread(thread->win32.handle, (DWORD)0);

	// Close Win32 thread.
	CloseHandle(thread->win32.handle);

	// Free thread stack memory.
	xkFreeMemory(thread->win32.pStack);

	// Free thread.
	xkFreeMemory(thread);
}

void xkExitThread() {
	ExitThread(0);
}

void xkKillThread(XkThread thread) {
	// Terminate Win32 thread.
	TerminateThread(thread->win32.handle, (DWORD)0);

	// Close Win32 thread.
	CloseHandle(thread->win32.handle);

	// Free thread stack memory.
	xkFreeMemory(thread->win32.pStack);

	// Free thread.
	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	Sleep(milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	XkResult result = XK_SUCCESS;

	// Allocate mutex.
	*pMutex = xkAllocateMemory(sizeof(struct XkMutex));
	if(!(*pMutex)) {
		__xkErrorHandle("Win32: Failed to create mutex");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	// Template mutex.
	XkMutex mutex = *pMutex;

	// Initialize Win32 critical section.
	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	InitializeCriticalSection(&mutex->win32.handle);

_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	// Delete Win32 critical section.
	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	DeleteCriticalSection(&mutex->win32.handle);

	// Free mutex.
	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	// Enter Win32 critical section.
	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	EnterCriticalSection(&mutex->win32.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	// Leave Win32 critical section.
	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	LeaveCriticalSection(&mutex->win32.handle);
}

#endif // XK_WIN32

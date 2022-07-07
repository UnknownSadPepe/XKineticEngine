/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Thread.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_WINDOWS_THREAD_STACK_SIZE (1024 * 1024)

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateThread(XkThread* pThread, const XkThreadRoutinePfn pfnRoutine) {
	xkAssert(pThread);
	xkAssert(pfnRoutine);

	XkResult result = XK_SUCCESS;

	*pThread = xkAllocateMemory(sizeof(struct XkThread_T));
	if(!(*pThread)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkThread thread = *pThread;

	// Allocate thread stack memory.
	thread->stack = xkAllocateMemory(XK_WINDOWS_THREAD_STACK_SIZE);
	if(!thread->stack) {
		__xkErrorHandle("Win32: Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _free;
	}

	// Create Win32 thread.
	thread->windows.winapi.handle = CreateThread(NULL, XK_WINDOWS_THREAD_STACK_SIZE, (LPTHREAD_START_ROUTINE)pfnRoutine, thread->stack, 0, &thread->windows.winapi.id);
	if(!thread->windows.winapi.handle) {
		__xkErrorHandle("Win32: Failed to create thread");
		result = XK_ERROR_UNKNOWN;
		goto _free;
	}

_catch:
	return(result);

_free:
	if(thread) {
		xkFreeMemory(thread);
	}

	goto _catch;
}

void xkJoinThread(XkThread thread, XkInt32** const ppResult) {
	xkAssert(thread);

	WaitForSingleObject(thread->windows.winapi.handle, INFINITE);

	CloseHandle(thread->windows.winapi.handle);

	xkFreeMemory(thread->stack);

	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	xkAssert(thread);

	TerminateThread(thread->windows.winapi.handle, (DWORD)0);

	CloseHandle(thread->windows.winapi.handle);

	xkFreeMemory(thread->stack);

	xkFreeMemory(thread);
}

void xkExitThread() {
	ExitThread(0);
}

void xkKillThread(XkThread thread) {
	xkAssert(thread);

	TerminateThread(thread->windows.winapi.handle, (DWORD)0);

	CloseHandle(thread->windows.winapi.handle);

	xkFreeMemory(thread->stack);

	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	xkAssert(milliSeconds > 0);

	Sleep(milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	xkAssert(pMutex);

	XkResult result = XK_SUCCESS;

	*pMutex = xkAllocateMemory(sizeof(struct XkMutex_T));
	if(!(*pMutex)) {
		__xkErrorHandle("Win32: Failed to create mutex");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkMutex mutex = *pMutex;

	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	InitializeCriticalSection(&mutex->windows.winapi.handle);

_catch:
	return(result);

_free:
	if(mutex) {
		xkFreeMemory(mutex);
	}

	goto _catch;
}

void xkDestroyMutex(XkMutex mutex) {
	xkAssert(mutex);

	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	DeleteCriticalSection(&mutex->windows.winapi.handle);

	// Free mutex.
	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	xkAssert(mutex);

	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	EnterCriticalSection(&mutex->windows.winapi.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	xkAssert(mutex);

	/// NOTE: I using a critical section insted of mutex due to performance and not the need to support number of precesses.
	LeaveCriticalSection(&mutex->windows.winapi.handle);
}

#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

#define XK_WIN32_THREAD_STACK_SIZE (1024 * 1024)

XkResult __xkThreadInitialize(void) {
	XkResult result = XK_SUCCESS;

_catch:
	return(result);
}

void __xkThreadTerminate(void) {
}

XkResult __xkCreateThread(XkThread thread, const XkThreadRoutinePfn pfnRoutine) {
	XkResult result = XK_SUCCESS;

	thread->handle.pStack = __xkAllocateMemory(XK_WIN32_THREAD_STACK_SIZE);
	if(!thread->handle.pStack) {
		__xkErrorHandle("Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	thread->handle.handle = CreateThread(NULL, XK_WIN32_THREAD_STACK_SIZE, pfnRoutine, thread->handle.pStack, 0, &thread->handle.id);
	if(!thread->handle.handle) {
		__xkErrorHandle("Failed to create memory!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void __xkJoinThread(XkThread thread, const XkInt32* pResult) {
	// TODO: implementation.
	WaitForSingleObject(thread->handle.handle, INFINITE);
	CloseHandle(thread->handle.handle);
	__xkFreeMemory(thread->handle.pStack);
}

void __xkDetachThread(XkThread thread) {
	// TODO: implementation.
	TerminateThread(thread->handle.handle, 0);
	CloseHandle(thread->handle.handle);
	__xkFreeMemory(thread->handle.pStack);
}

void __xkExitThread(XkThread thread, XkInt32 result) {
	// TODO: implementation.
	ExitThread(result);
	CloseHandle(thread->handle.handle);
	__xkFreeMemory(thread->handle.pStack);
}

void __xkKillThread(XkThread thread) {
	// TODO: implementation.
	TerminateThread(thread->handle.handle, 0);
	CloseHandle(thread->handle.handle);
	__xkFreeMemory(thread->handle.pStack);
}

XkThread __xkThreadSelf(void) {
	// TODO: implementation.
	return(XK_NULL);
}

void __xkThreadYield(void) {
	SwitchToThread();
}

void __xkThreadSleep(const XkSize milliSeconds) {
	Sleep(milliSeconds);
}

XkResult __xkCreateMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	mutex->handle.handle = CreateMutex(NULL, FALSE, NULL);
	if(!mutex->handle.handle) {
		__xkErrorHandle("Failed to create mutex!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void __xkDestroyMutex(XkMutex mutex) {
	CloseHandle(mutex->handle.handle);
}

XkResult __xkLockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;
	
	DWORD waitResult = WaitForSingleObject(mutex->handle.handle, INFINITE);
	switch(waitResult) {
		case WAIT_OBJECT_0:
			break;

		case WAIT_ABANDONED:
			break;
	}

_catch:
	return(result);
}

XkResult __xkTrylockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	DWORD waitResult = WaitForSingleObject(mutex->handle.handle, INFINITE);

_catch:
	return(result);
}

XkResult __xkUnlockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;
	
	ReleaseMutex(mutex->handle.handle);

_catch:
	return(result);
}

#endif // XK_PLATFORM_WIN32

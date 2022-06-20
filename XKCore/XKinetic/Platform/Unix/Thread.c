#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Thread.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_POSIX)

#define _GNU_SOURCE
#include <signal.h>
#include <unistd.h>

#define XK_UNIX_THREAD_STACK_SIZE (1024 * 1024)

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

	// Allocate thread stack.
	thread->handle.pStack = xkAllocateMemory(XK_UNIX_THREAD_STACK_SIZE);
	if(!thread->handle.pStack) {
		__xkErrorHandle("Unix: Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Create Posix thread attribute.
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// Set Posix thread stack info.
	pthread_attr_setstack(&attr, thread->handle.pStack, XK_UNIX_THREAD_STACK_SIZE);

	// Create Posix thread.
	if(pthread_create(&thread->handle.handle, &attr, (void*(*)(void*))pfnRoutine, NULL) != 0) {
		__xkErrorHandle("Unix: Failed to create thread!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Destroy Posix thread attribute.
	pthread_attr_destroy(&attr);

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, XkInt32** const ppResult) {
	// Join Posix thread.
	pthread_join(thread->handle.handle, (void**)ppResult);

	// Free thread stack.
	xkFreeMemory(thread->handle.pStack);

	// Free thread.
	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	// Detach Posix thread.
	pthread_detach(thread->handle.handle);

	// Free thread stack.
	xkFreeMemory(thread->handle.pStack);

	// Free thread.
	xkFreeMemory(thread);
}

void xkExitThread(void) {
	// Exit Posix thread.
	pthread_exit(NULL);
}

void xkKillThread(XkThread thread) {
	// Kill Posix thread.
	pthread_kill(thread->handle.handle, 0);

	// Free thread stack.
	xkFreeMemory(thread->handle.pStack);

	// Free thread stack.
	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	usleep((unsigned int)milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	XkResult result = XK_SUCCESS;

	// Allocate mutex.
	*pMutex = xkAllocateMemory(sizeof(struct XkMutex));
	if(!(*pMutex)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	// Template mutex.
	XkMutex mutex = *pMutex;


	// Initialize Posix mutex.
	if(pthread_mutex_init(&mutex->handle.handle, NULL) != 0) {
		__xkErrorHandle("Unix: Failed to create mutex");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}
	
_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	// Destroy Posix mutex.
	pthread_mutex_destroy(&mutex->handle.handle);

	// Free mutex.
	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	// Lock Posix mutex.
	pthread_mutex_lock(&mutex->handle.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	// Unlock Posix mutex.
	pthread_mutex_unlock(&mutex->handle.handle);
}

#endif // XK_POSIX

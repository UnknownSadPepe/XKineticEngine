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
	
	*pThread = xkAllocateMemory(sizeof(struct XkThread));
	if(!(*pThread)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkThread thread = *pThread;

	thread->handle.pStack = xkAllocateMemory(XK_UNIX_THREAD_STACK_SIZE);
	if(!thread->handle.pStack) {
		__xkErrorHandle("Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstack(&attr, thread->handle.pStack, XK_UNIX_THREAD_STACK_SIZE);

	if(pthread_create(&thread->handle.handle, &attr, (void*(*)(void*))pfnRoutine, NULL) != 0) {
		__xkErrorHandle("Failed to create thread!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	pthread_attr_destroy(&attr);

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, XkInt32** const ppResult) {
	pthread_join(thread->handle.handle, (void**)ppResult);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	pthread_detach(thread->handle.handle);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkExitThread(void) {
	pthread_exit(NULL);
}

void xkKillThread(XkThread thread) {
	pthread_kill(thread->handle.handle, 0);
	xkFreeMemory(thread->handle.pStack);
	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	usleep((unsigned int)milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	XkResult result = XK_SUCCESS;

	*pMutex = xkAllocateMemory(sizeof(struct XkMutex));
	if(!(*pMutex)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkMutex mutex = *pMutex;

	if(pthread_mutex_init(&mutex->handle.handle, NULL) != 0) {
		__xkErrorHandle("Failed to create mutex");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}
	
_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	pthread_mutex_destroy(&mutex->handle.handle);
	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	pthread_mutex_lock(&mutex->handle.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	pthread_mutex_unlock(&mutex->handle.handle);
}

#endif // XK_POSIX

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Thread.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_POSIX_THREAD_STACK_SIZE (1024 * 1024)

#define _GNU_SOURCE
#include <signal.h>
#include <unistd.h>

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

	thread->stack = xkAllocateMemory(XK_POSIX_THREAD_STACK_SIZE);
	if(!thread->stack) {
		__xkErrorHandle("Posix: Failed to allocate thread stack memory");
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_attr_setstack(&attr, thread->stack, XK_POSIX_THREAD_STACK_SIZE);

	if(pthread_create(&thread->posix.handle, &attr, (void*(*)(void*))pfnRoutine, NULL) != 0) {
		__xkErrorHandle("Posix: Failed to create thread!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	pthread_attr_destroy(&attr);

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, XkInt32** const ppResult) {
	xkAssert(thread);

	pthread_join(thread->posix.handle, (void**)ppResult);

	xkFreeMemory(thread->stack);

	xkFreeMemory(thread);
}

void xkDetachThread(XkThread thread) {
	xkAssert(thread);

	pthread_detach(thread->posix.handle);

	xkFreeMemory(thread->stack);

	xkFreeMemory(thread);
}

void xkExitThread(void) {
	pthread_exit(NULL);
}

void xkKillThread(XkThread thread) {
	xkAssert(thread);

	pthread_kill(thread->posix.handle, 0);

	xkFreeMemory(thread->stack);

	xkFreeMemory(thread);
}

void xkThreadSleep(const XkSize milliSeconds) {
	xkAssert(milliSeconds > 0);

	usleep((unsigned int)milliSeconds);
}

XkResult xkCreateMutex(XkMutex* pMutex) {
	xkAssert(pMutex);

	XkResult result = XK_SUCCESS;

	*pMutex = xkAllocateMemory(sizeof(struct XkMutex_T));
	if(!(*pMutex)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkMutex mutex = *pMutex;

	if(pthread_mutex_init(&mutex->posix.handle, NULL) != 0) {
		__xkErrorHandle("Posix: Failed to create mutex");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}
	
_catch:
	return(result);
}

void xkDestroyMutex(XkMutex mutex) {
	xkAssert(mutex);

	pthread_mutex_destroy(&mutex->posix.handle);

	xkFreeMemory(mutex);
}

void xkLockMutex(XkMutex mutex) {
	xkAssert(mutex);

	pthread_mutex_lock(&mutex->posix.handle);
}

void xkUnlockMutex(XkMutex mutex) {
	xkAssert(mutex);

	pthread_mutex_unlock(&mutex->posix.handle);
}

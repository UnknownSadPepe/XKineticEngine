#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_LINUX)

#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include "XKinetic/Platform/Linux/Internal.h"

XkResult __xkThreadInitialize(void) {
	XkResult result = XK_SUCCESS;

_catch:
	return(result);
}

void __xkThreadTerminate(void) {
}

XkResult __xkCreateThread(XkThread thread, const XkThreadRoutinePfn pfnRoutine) {
	XkResult result = XK_SUCCESS;
	
	if(pthread_create(&thread->handle.handle, NULL, (void *(*)(void *))pfnRoutine, NULL) != 0) {
		__xkErrorHandle("Failed to create thread!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void __xkJoinThread(XkThread thread, XkInt32* pResult) {
	pthread_join(thread->handle.handle, pResult);
}

void __xkDetachThread(XkThread thread) {
	pthread_detach(thread->handle.handle);
}

void __xkExitThread(XkThread thread, XkInt32 result) {
	pthread_exit(XK_NULL);
}

void __xkKillThread(XkThread thread) {
	pthread_kill(thread->handle.handle, 0);
}

XkThread __xkThreadSelf(void) {
	// TODO: implementation.
	return(XK_NULL);
}

void __xkThreadYield(void) {
	// TODO: implementation.
	//pthread_yield();
}

void __xkThreadSleep(const XkSize milliSeconds) {
	usleep((unsigned int)milliSeconds);
}

XkResult __xkCreateMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_init(&mutex->handle.handle, NULL) != 0) {
		__xkErrorHandle("Failed to create mutex!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}
	
_catch:
	return(result);
}

void __xkDestroyMutex(XkMutex mutex) {
	pthread_mutex_destroy(&mutex->handle.handle);
}

XkResult __xkLockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_lock(&mutex->handle.handle) != 0) {
		__xkErrorHandle("Failed to lock mutex!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult __xkTrylockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_trylock(&mutex->handle.handle) != 0) {
		__xkErrorHandle("Failed to trylock mutex!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult __xkUnlockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_unlock(&mutex->handle.handle) != 0) {
		__xkErrorHandle("Failed to unlock mutex!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_PLATFORM_LINUX

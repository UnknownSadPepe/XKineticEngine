#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Thread.h"

#if defined(XK_UNIX)

#define _GNU_SOURCE
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

XkResult xkThreadInitialize(void) {
	XkResult result = XK_SUCCESS;

	/// NOTE: Nothing to do here.

_catch:
	return(result);
}

void xkThreadTerminate(void) {
	/// NOTE: Nothing to do here.
}

XkResult xkCreateThread(XkThread thread, const XkThreadRoutinePfn pfnRoutine) {
	XkResult result = XK_SUCCESS;
	
	if(pthread_create(&thread->handle.handle, NULL, (void*(*)(void*))pfnRoutine, NULL) != 0) {
		__xkErrorHandle("Failed to create thread!");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkJoinThread(XkThread thread, XkInt32** const ppResult) {
	pthread_join(thread->handle.handle, (void**)ppResult);
}

void xkDetachThread(XkThread thread) {
	pthread_detach(thread->handle.handle);
}

void xkExitThread(void) {
	pthread_exit(NULL);
}

void xkKillThread(XkThread thread) {
	pthread_kill(thread->handle.handle, 0);
}

XkThread xkThreadSelf(void) {
	/// TODO: implementation.
	return(XK_NULL_HANDLE);
}

void xkThreadYield(void) {
	/// TODO: implementation.
	//pthread_yield();
}

void xkThreadSleep(const XkSize milliSeconds) {
	usleep((unsigned int)milliSeconds);
}

XkResult xkCreateMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

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
}

XkResult xkLockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_lock(&mutex->handle.handle) != 0) {
		__xkErrorHandle("Failed to lock mutex");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult xkTrylockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_trylock(&mutex->handle.handle) != 0) {
		__xkErrorHandle("Failed to trylock mutex");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult xkUnlockMutex(XkMutex mutex) {
	XkResult result = XK_SUCCESS;

	if(pthread_mutex_unlock(&mutex->handle.handle) != 0) {
		__xkErrorHandle("Failed to unlock mutex");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_UNIX

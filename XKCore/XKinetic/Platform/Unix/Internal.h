#pragma once

/* ########## INCLUDE SECTION ########## */
#include <pthread.h>
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct __XkUnixFile_T {
	int handle;
} __XkUnixFile;

typedef struct __XkPThreadThread_T {
	pthread_t handle;
	XkHandle stack;
} __XkPThreadThread;

typedef struct __XkPThreadMutex_T {
	pthread_mutex_t handle;
} __XkPThreadMutex;

typedef struct __XkUnixModule_T {
	void* handle;
} __XkUnixModule;

/* ########## TYPES MACROS SECTION ########## */
#define XK_PLATFORM_FILE 		__XkUnixFile unix
#define XK_PLATFORM_THREAD 	__XkPThreadThread pthread
#define XK_PLATFORM_MUTEX 	__XkPThreadThread pthread
#define XK_PLATFORM_MODULE 	__XkUnixModule unix

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

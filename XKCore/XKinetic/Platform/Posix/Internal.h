#pragma once

/* ########## INCLUDE SECTION ########## */
#include <pthread.h>
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct __XkPosixFile_T {
	int handle;
} __XkPosixFile;

typedef struct __XkPosixThread_T {
	pthread_t handle;
} __XkPosixThread;

typedef struct __XkPosixMutex_T {
	pthread_mutex_t handle;
} __XkPosixMutex;

typedef struct __XkPosixModule_T {
	void* handle;
} __XkPosixModule;

/* ########## TYPES MACROS SECTION ########## */
#define XK_PLATFORM_FILE 		__XkPosixFile 		posix
#define XK_PLATFORM_THREAD 	__XkPosixThread 	posix
#define XK_PLATFORM_MUTEX 	__XkPosixMutex 		posix
#define XK_PLATFORM_MODULE 	__XkPosixModule 	posix

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

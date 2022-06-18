#pragma once

#include <pthread.h>
#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	int handle;
} __XkUnixFile;

#define XK_PLATFORM_FILE __XkUnixFile handle

typedef struct {
	pthread_t handle;
	XkHandle pStack;
} __XkUnixThread;

#define XK_PLATFORM_THREAD __XkUnixThread handle

typedef struct {
	pthread_mutex_t handle;
} __XkUnixMutex;

#define XK_PLATFORM_MUTEX __XkUnixMutex handle

typedef struct {
	void* handle;
} __XkUnixModule;

#define XK_PLATFORM_MODULE __XkUnixModule handle

#ifdef __cplusplus
}
#endif // __cplusplus

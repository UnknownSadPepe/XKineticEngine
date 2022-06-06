#pragma once

#include <pthread.h>
#include "XKinetic/XKCore.h"

typedef struct {
	int handle;
} __XkUnixFile;

#define XK_PLATFORM_FILE __XkUnixFile handle

typedef struct {
	pthread_t handle;
} __XkUnixThread;

#define XK_PLATFORM_THREAD __XkUnixThread handle

typedef struct {
	pthread_mutex_t handle;
} __XkUnixMutex;

#define XK_PLATFORM_MUTEX __XkUnixMutex handle

#pragma once

#include <windows.h>
#include "XKinetic/XKinetic.h"

typedef struct __XkWin32File {
	HFILE handle;
} __XkWin32File;

#define XK_PLATFORM_FILE __XkWin32File handle

typedef struct __XkWin32Thread {
	HANDLE handle;
	DWORD id;
	XkHandle pStack;
} __XkWin32Thread;

#define XK_PLATFORM_THREAD __XkWin32Thread handle

typedef struct __XkWin32Mutex {
	HANDLE handle;
} __XkWin32Mutex;

#define XK_PLATFORM_MUTEX __XkWin32Mutex handle

typedef struct __XkWin32Window {
	HWND handle;
  HICON bigIcon;
  HICON smallIcon;
} __XkWin32Window;

#define XK_PLATFORM_WINDOW __XkWin32Window handle


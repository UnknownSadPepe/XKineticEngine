#pragma once

#include <windows.h>
#include "XKinetic/XKCore.h"

typedef struct {
	HANDLE handle;
	OVERLAPPED overlapped;
} __XkWin32File;

#define XK_PLATFORM_FILE __XkWin32File handle

typedef struct {
	HANDLE handle;
	DWORD id;
	XkHandle pStack;
} __XkWin32Thread;

#define XK_PLATFORM_THREAD __XkWin32Thread handle

typedef struct {
	CRITICAL_SECTION handle;
} __XkWin32Mutex;

#define XK_PLATFORM_MUTEX __XkWin32Mutex handle

typedef struct {
	HWND handle;

  XkBool32 cursorTracked;
} __XkWin32Window;

#define XK_PLATFORM_WINDOW __XkWin32Window handle

typedef struct {
	HINSTANCE instance;
} __XkWin32Platform;

#define XK_PLATFORM __XkWin32Platform handle


#pragma once

#include <windows.h>
#include <dinput.h>
#include <xinput.h>
#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	HANDLE handle;
	OVERLAPPED overlapped;
} __XkWin32File;

#define XK_PLATFORM_FILE __XkWin32File win32

typedef struct {
	HANDLE handle;
	DWORD id;
	XkHandle pStack;
} __XkWin32Thread;

#define XK_PLATFORM_THREAD __XkWin32Thread win32

typedef struct {
	CRITICAL_SECTION handle;
} __XkWin32Mutex;

#define XK_PLATFORM_MUTEX __XkWin32Mutex win32

typedef struct {
	XkSize minWidth;
	XkSize minHeight;
	XkSize maxWidth;
	XkSize maxHeight;

	HWND handle;

  XkBool cursorTracked;

	HICON hBigIcon;
	HICON hSmallIcon;
	HCURSOR hCursor;
} __XkWin32Window;

#define XK_PLATFORM_WINDOW __XkWin32Window win32

typedef struct {
    int                     offset;
    int                     type;
} __XkDIJoystickObject;

typedef struct {
	__XkDIJoystickObject*  	objects;
	int                     objectCount;
	IDirectInputDevice8W*   device;
	DWORD                   index;
	GUID                    guid;
} __XkDIJoystick;

#define XK_PLATFORM_JOYSTICK __XkDIJoystick dinput

typedef struct {
	HMODULE handle;
} __XkWin32Module;

#define XK_PLATFORM_MODULE __XkWin32Module win32

typedef struct {
	HINSTANCE 			instance;
	IDirectInput8W 	dinput;
} __XkWin32Platform;

#define XK_PLATFORM __XkWin32Platform win32

#ifdef __cplusplus
}
#endif // __cplusplus

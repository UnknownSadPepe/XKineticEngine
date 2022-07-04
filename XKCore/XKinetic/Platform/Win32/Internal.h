#pragma once

/* ########## INCLUDE SECTION ########## */
#include <windows.h>
#include <dinput.h>
#include <xinput.h>
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct __XkWin32File_T {
	HANDLE 			handle;
	OVERLAPPED 	overlapped;
} __XkWin32File;

typedef struct __XkWin32Thread_T {
	HANDLE 		handle;
	DWORD 		id;
	XkHandle 	stack;
} __XkWin32Thread;

typedef struct __XkWin32Mutex_T {
	CRITICAL_SECTION handle;
} __XkWin32Mutex;

typedef struct __XkWin32Window_T {
	XkSize 		minWidth;
	XkSize 		minHeight;
	XkSize 		maxWidth;
	XkSize 		maxHeight;

	HWND			handle;

  XkBool 		cursorTracked;

	HICON 		hBigIcon;
	HICON 		hSmallIcon;
	HCURSOR 	hCursor;
} __XkWin32Window;

typedef struct __XkDIJoystickObject_T {
    int                     offset;
    int                     type;
} __XkDIJoystickObject;

typedef struct __XkDIJoystick_T {
	__XkDIJoystickObject*  	objects;
	int                     objectCount;
	IDirectInputDevice8W*   device;
	DWORD                   index;
	GUID                    guid;
} __XkDIJoystick;

typedef struct __XkWin32Module_T {
	HMODULE handle;
} __XkWin32Module;

typedef struct __XkWin32Platform_T {
	HINSTANCE 				instance;
	IDirectInput8W 		dinput;
} __XkWin32Platform;

/* ########## TYPES MACROS SECTION ########## */
#define XK_PLATFORM_FILE 			__XkWin32File win32
#define XK_PLATFORM_THREAD 		__XkWin32Thread win32
#define XK_PLATFORM_MUTEX 		__XkWin32Mutex win32
#define XK_PLATFORM_WINDOW 		__XkWin32Window win32
#define XK_PLATFORM_JOYSTICK 	__XkDIJoystick dinput
#define XK_PLATFORM_MODULE 		__XkWin32Module win32
#define XK_PLATFORM 					__XkWin32Platform win32

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

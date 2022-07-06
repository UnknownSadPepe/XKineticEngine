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
	struct {
		HANDLE 			handle;
		OVERLAPPED 	overlapped;
	} winapi;
} __XkWin32File;

typedef struct __XkWin32Thread_T {
	struct {
		HANDLE 		handle;
		DWORD 		id;
	} winapi;
} __XkWin32Thread;

typedef struct __XkWin32Mutex_T {
	struct winapi {
		CRITICAL_SECTION handle;
	}
} __XkWin32Mutex;

typedef struct __XkWin32Window_T {
	struct {
		XkSize 		minWidth;
		XkSize 		minHeight;
		XkSize 		maxWidth;
		XkSize 		maxHeight;

		HWND			handle;

  	XkBool8 		cursorTracked;

		HICON 		hBigIcon;
		HICON 		hSmallIcon;
		HCURSOR 	hCursor;
	} winapi;
} __XkWin32Window;

typedef struct __XkWin32JoystickObject_T {
	int	offset;
	int	type;
} __XkWin32JoystickObject;

typedef struct __XkWin32Joystick_T {
	struct {
		__XkWin32JoystickObject*  	objects;
		int                     		objectCount;
		IDirectInputDevice8W*   		diDevice;
	} dinput;

	DWORD                   index;
	GUID                    guid;
} __XkWin32Joystick;

typedef struct __XkWin32Module_T {
	struct {
		HMODULE handle;
	} winapi;
} __XkWin32Module;

typedef struct __XkWin32Platform_T {
	struct {
		HINSTANCE 				instance;
	} winapi;

	struct {
		IDirectInput8W 		handle;
	} dinput;
} __XkWin32Platform;

/* ########## TYPES MACROS SECTION ########## */
#define XK_PLATFORM_FILE 			__XkWin32File 		windows
#define XK_PLATFORM_THREAD 		__XkWin32Thread 	windows
#define XK_PLATFORM_MUTEX 		__XkWin32Mutex 		windows
#define XK_PLATFORM_WINDOW 		__XkWin32Window 	windows
#define XK_PLATFORM_JOYSTICK 	__XkWin32Joystick windows
#define XK_PLATFORM_MODULE 		__XkWin32Module 	windows
#define XK_PLATFORM 					__XkWin32Platform windows

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

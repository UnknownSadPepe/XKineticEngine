#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/Internal.h"
#elif defined(XK_WIN64)
	#include "XKinetic/Platform/Win32/Internal.h"
#endif // XK_LINUX
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Thread.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Module.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
struct XkFile_T {
	XK_PLATFORM_FILE;
};

struct XkThread_T {
	XK_PLATFORM_THREAD;
};

struct XkMutex_T {
	XK_PLATFORM_MUTEX;
};

struct XkWindow_T {
	XkBool 										decorated;
	XkBool 										resizable;
	XkBool 										floating;
	XkBool 										fullscreen;

	XkCursorMode 				cursorMode;

	XkString 									title;

	struct {
		XkWindowShowPfn 				show;
		XkWindowKeyPfn 					key;
		XkWindowButtonPfn 			button;
		XkWindowCursorPfn 			cursor;
		XkWindowCursorEnterPfn 	cursorEnter;
		XkWindowScrollPfn 			scroll;
		XkWindowClosePfn 				close;
		XkWindowPositionPfn 		position;
		XkWindowSizePfn 				size;
		XkWindowFocusPfn 				focus;
		XkWindowDropFilePfn 		dropFile;
	} callbacks;

	XK_PLATFORM_WINDOW;
};

typedef struct XkJoystickObject_T {
	struct {
		XkJoystickEventPfn 	event;
		XkJoystickAxisPfn 	axis;
		XkJoystickButtonPfn button;
		XkJoystickHatPfn 		hat;
	} callbacks;

	XK_PLATFORM_JOYSTICK;
} XkJoystickObject;

struct XkModule_T {
	XK_PLATFORM_MODULE;
};

typedef struct __XkPlatform_T {
	XkBool			initialized;

	XkInt16			keycodes[512];

	XkJoystickObject	joysticks[XK_JOYSTICK_16 + 1];

	XK_PLATFORM;
} __XkPlatform;

/* ########## EXTERN SECTION ########## */
extern __XkPlatform _xkPlatform;

/* ########## FUNCTIONS HELPERS SECTION ########## */
#if defined(XK_WIN64)
extern XKCORE_API HINSTANCE 					__xkWin32GetInstance();
extern XKCORE_API HWND 								__xkWin32GetHWND(const XkWindow);
#elif defined(XK_LINUX)
extern XKCORE_API struct wl_display* 	__xkWaylandGetDisplay();
extern XKCORE_API struct wl_surface* 	__xkWaylandGetSurface(const XkWindow);
#endif // XK_WIN64

extern XK_EXPORT void 								__xkErrorHandler(const XkString pFormat, ...);

/* ########## FUNCTIONS HELPERS MACROS SECTION ########## */
#define 															__xkErrorHandle(message) __xkErrorHandler("%s %s %d", message, __FILE__, __LINE__)

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#if defined(XK_POSIX)
	#include "XKinetic/Platform/Posix/Internal.h"
#endif // XK_POSIX

#if defined(XK_UNIX)
	#include "XKinetic/Platform/Unix/Internal.h"
#endif // XK_POSIX

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/Internal.h"
#elif defined(XK_APPLE)
	#include "XKinetic/Platform/Cocoa/Internal.h"
#elif defined(XK_WINDOWS)
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

	XkHandle stack;
};

struct XkMutex_T {
	XK_PLATFORM_MUTEX;
};

struct XkWindow_T {
	XkBool8 						decorated;
	XkBool8 						resizable;
	XkBool8 						floating;

	XkCursorMode 				cursorMode;

	XkString 						title;

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

typedef struct XkJoystick_T {
	XkJoystickId 		id;
	XkBool8 				connected;

	struct {
		XkJoystickEventPfn 	event;
		XkGamepadAxisPfn 	axis;
		XkGamepadButtonPfn button;
		XkGamepadHatPfn 		hat;
	} callbacks;

	XK_PLATFORM_JOYSTICK;
} XkJoystick;

struct XkModule_T {
	XK_PLATFORM_MODULE;
};

typedef struct __XkPlatform_T {
	XkInt16			keycodes[512];

	XkJoystick	joysticks[XK_JOYSTICK_16 + 1];

	XK_PLATFORM;
} __XkPlatform;

/* ########## EXTERN SECTION ########## */
extern __XkPlatform _xkPlatform;

/* ########## FUNCTIONS HELPERS SECTION ########## */
#if defined(XK_WINDOWS)
extern XKCORE_API HINSTANCE 					__xkWin32GetInstance();
extern XKCORE_API HWND 								__xkWin32GetHWND(const XkWindow);
#elif defined(XK_LINUX)
extern XKCORE_API struct wl_display* 	__xkWaylandGetDisplay();
extern XKCORE_API struct wl_surface* 	__xkWaylandGetSurface(const XkWindow);
#endif // XK_WINDOWS

extern XK_EXPORT void 								__xkErrorHandler(const XkString pFormat, ...);

/* ########## FUNCTIONS HELPERS MACROS SECTION ########## */
#define 															__xkErrorHandle(message) __xkErrorHandler("%s %s %d", message, __FILE__, __LINE__)

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

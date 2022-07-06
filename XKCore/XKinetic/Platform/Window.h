#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Event.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkWindowHint_T {
	XK_WINDOW_HINT_DECORATED_BIT 		= 0x0001,
	XK_WINDOW_HINT_RESIZABLE_BIT 		= 0x0002,
	XK_WINDOW_HINT_FLOATING_BIT 		= 0x0004,
} XkWindowHint;

typedef enum XkWindowShow_T {
	XK_WINDOW_SHOW_DEFAULT 			= 0,
	XK_WINDOW_SHOW_MAXIMIZED 		= 1,
	XK_WINDOW_SHOW_MINIMIZED 		= 2,
	XK_WINDOW_SHOW_FULLSCREEN 	= 3,
	XK_WINDOW_HIDE 							= 4
} XkWindowShow;

typedef struct XkWindow_T* XkWindow;

typedef void(*XkWindowShowPfn)(XkWindow, const XkWindowShow);
typedef void(*XkWindowKeyPfn)(XkWindow, const XkKey, const XkAction, const XkMod);
typedef void(*XkWindowButtonPfn)(XkWindow, const XkButton, const XkAction, const XkMod);
typedef void(*XkWindowCursorPfn)(XkWindow, const XkFloat64, const XkFloat64);
typedef void(*XkWindowCursorEnterPfn)(XkWindow, const XkBool8);
typedef void(*XkWindowScrollPfn)(XkWindow, const XkFloat64, const XkFloat64);
typedef void(*XkWindowClosePfn)(XkWindow);
typedef void(*XkWindowPositionPfn)(XkWindow, const XkInt32, const XkInt32);
typedef void(*XkWindowSizePfn)(XkWindow, const XkSize, const XkSize);
typedef void(*XkWindowFocusPfn)(XkWindow, const XkBool8);
typedef void(*XkWindowDropFilePfn)(XkWindow, const XkSize, const XkString*);

typedef struct XkWindowIcon_T {
	XkSize 		width;
	XkSize 		height;
	XkUInt8* 	pixels;
} XkWindowIcon;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 			xkInitializeWindow();
extern XKCORE_API void 					xkTerminateWindow();

extern XKCORE_API XkResult 			xkCreateWindow(XkWindow*, const XkString, const XkSize, const XkSize, const XkWindowHint);
extern XKCORE_API void 					xkDestroyWindow(XkWindow);

extern XKCORE_API void 					xkShowWindow(XkWindow, const XkWindowShow);

extern XKCORE_API void 					xkFocusWindow(XkWindow);

extern XKCORE_API void 					xkSetWindowSize(XkWindow, const XkSize, const XkSize);
extern XKCORE_API void 					xkGetWindowSize(XkWindow, XkSize* const, XkSize* const);

extern XKCORE_API void 					xkSetWindowSizeLimits(XkWindow, const XkSize, const XkSize, const XkSize, const XkSize);

extern XKCORE_API void 					xkSetWindowPosition(XkWindow, const XkInt32, const XkInt32);
extern XKCORE_API void 					xkGetWindowPosition(XkWindow, XkInt32* const, XkInt32* const);

extern XKCORE_API void 					xkSetWindowTitle(XkWindow, const XkString);
extern XKCORE_API XkString 			xkGetWindowTitle(XkWindow);

extern XKCORE_API void 					xkSetWindowIcon(XkWindow, const XkSize, const XkWindowIcon*);

extern XKCORE_API void 					xkSetWindowCursorMode(XkWindow, const XkCursorMode);
extern XKCORE_API XkCursorMode 	xkGetWindowCursorMode(XkWindow);

extern XKCORE_API void 					xkSetWindowCursorPosition(XkWindow, const XkFloat64, const XkFloat64);
extern XKCORE_API void 					xkGetWindowCursorPosition(XkWindow, XkFloat64* const, XkFloat64* const);

extern XKCORE_API void 					xkSetWindowCursor(XkWindow, const XkWindowIcon*);

extern XKCORE_API void 					xkSetWindowShowCallback(XkWindow, const XkWindowShowPfn);
extern XKCORE_API void 					xkSetWindowKeyCallback(XkWindow, const XkWindowKeyPfn);
extern XKCORE_API void 					xkSetWindowButtonCallback(XkWindow, const XkWindowButtonPfn);
extern XKCORE_API void 					xkSetWindowCursorCallback(XkWindow, const XkWindowCursorPfn);
extern XKCORE_API void 					xkSetWindowCursorEnterCallback(XkWindow, const XkWindowCursorEnterPfn);
extern XKCORE_API void 					xkSetWindowScrollCallback(XkWindow, const XkWindowScrollPfn);
extern XKCORE_API void 					xkSetWindowCloseCallback(XkWindow, const XkWindowClosePfn);
extern XKCORE_API void 					xkSetWindowPositionCallback(XkWindow, const XkWindowPositionPfn);
extern XKCORE_API void 					xkSetWindowSizeCallback(XkWindow, const XkWindowSizePfn);
extern XKCORE_API void 					xkSetWindowFocusCallback(XkWindow, const XkWindowFocusPfn);
extern XKCORE_API void 					xkSetWindowDropFileCallback(XkWindow, const XkWindowDropFilePfn);

extern XKCORE_API void 					xkPollWindowEvents();
extern XKCORE_API void 					xkWaitWindowEvents();
extern XKCORE_API void 					xkWaitWindowEventsTimeout(const XkFloat64);

/* ##### HELPER FUNCTIONS SECTION ##### */
extern XK_EXPORT void 					__xkInputWindowShow(XkWindow, const XkWindowShow);
extern XK_EXPORT void 					__xkInputWindowKey(XkWindow, const XkKey, const XkAction, const XkMod);
extern XK_EXPORT void 					__xkInputWindowButton(XkWindow, const XkButton, const XkAction, const XkMod);
extern XK_EXPORT void 					__xkInputWindowCursor(XkWindow, const XkFloat64, const XkFloat64);
extern XK_EXPORT void 					__xkInputWindowCursorEnter(XkWindow, const XkBool8);
extern XK_EXPORT void 					__xkInputWindowScroll(XkWindow, const XkFloat64, const XkFloat64);
extern XK_EXPORT void 					__xkInputWindowClose(XkWindow);
extern XK_EXPORT void 					__xkInputWindowPosition(XkWindow, const XkInt32, const XkInt32);
extern XK_EXPORT void 					__xkInputWindowSize(XkWindow, const XkSize, const XkSize);
extern XK_EXPORT void 					__xkInputWindowFocus(XkWindow, const XkBool8);
extern XK_EXPORT void 					__xkInputWindowDropFile(XkWindow, const XkSize, const XkString*);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

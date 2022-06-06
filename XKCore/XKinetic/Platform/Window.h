#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
#endif // XK_LINUX

typedef enum {
	XK_WINDOW_DECORATED_BIT 	= 1,
	XK_WINDOW_RESIZABLE_BIT 	= 2,
	XK_WINDOW_FLOATING_BIT 		= 4,
} XkWindowHint;

typedef enum {
	XK_WINDOW_SHOW_DEFAULT 			= 0,
	XK_WINDOW_SHOW_MAXIMIZED 		= 1,
	XK_WINDOW_SHOW_MINIMIZED 		= 2,
	XK_WINDOW_SHOW_FULLSCREEN 	= 3,
	XK_WINDOW_HIDE 							= 4
} XkWindowShow;

typedef enum {
	XK_WINDOW_KEY_UNKNOWN =						-1,
	XK_WINDOW_KEY_SPACE =             32,
	XK_WINDOW_KEY_APOSTROPHE =        39,
	XK_WINDOW_KEY_COMMA =             44,
	XK_WINDOW_KEY_MINUS =             45,
	XK_WINDOW_KEY_PERIOD =            46,
	XK_WINDOW_KEY_SLASH =             47,
	XK_WINDOW_KEY_0 =                 48,
	XK_WINDOW_KEY_1 =                 49,
	XK_WINDOW_KEY_2 =                 50,
	XK_WINDOW_KEY_3 =                 51,
	XK_WINDOW_KEY_4 =                 52,
	XK_WINDOW_KEY_5 =                 53,
	XK_WINDOW_KEY_6 =                 54,
	XK_WINDOW_KEY_7 =                 55,
	XK_WINDOW_KEY_8 =                 56,
	XK_WINDOW_KEY_9 =                 57,
	XK_WINDOW_KEY_SEMICOLON =         59,
	XK_WINDOW_KEY_EQUAL =             61,
	XK_WINDOW_KEY_A =                 65,
	XK_WINDOW_KEY_B =                 66,
	XK_WINDOW_KEY_C =                 67,
	XK_WINDOW_KEY_D =                 68,
	XK_WINDOW_KEY_E =                 69,
	XK_WINDOW_KEY_F =                 70,
	XK_WINDOW_KEY_G =                 71,
	XK_WINDOW_KEY_H =                 72,
	XK_WINDOW_KEY_I =                 73,
	XK_WINDOW_KEY_J =                 74,
	XK_WINDOW_KEY_K =                 75,
	XK_WINDOW_KEY_L =                 76,
	XK_WINDOW_KEY_M =                 77,
	XK_WINDOW_KEY_N =                 78,
	XK_WINDOW_KEY_O =                 79,
	XK_WINDOW_KEY_P =                 80,
	XK_WINDOW_KEY_Q =                 81,
	XK_WINDOW_KEY_R =                 82,
	XK_WINDOW_KEY_S =                 83,
	XK_WINDOW_KEY_T =                 84,
	XK_WINDOW_KEY_U =                 85,
	XK_WINDOW_KEY_V =                 86,
	XK_WINDOW_KEY_W =                 87,
	XK_WINDOW_KEY_X =                 88,
	XK_WINDOW_KEY_Y =                 89,
	XK_WINDOW_KEY_Z =                 90,
	XK_WINDOW_KEY_LEFT_BRACKET =      91,
	XK_WINDOW_KEY_BACKSLASH =         92,
	XK_WINDOW_KEY_RIGHT_BRACKET =     93,
	XK_WINDOW_KEY_GRAVE_ACCENT =      96,
	XK_WINDOW_KEY_WORLD_1 =           161,
	XK_WINDOW_KEY_WORLD_2 =           162,
	XK_WINDOW_KEY_ESCAPE =						256,
	XK_WINDOW_KEY_ENTER =							257,
	XK_WINDOW_KEY_TAB =								258,
	XK_WINDOW_KEY_BACKSPACE =					259,
	XK_WINDOW_KEY_INSERT =						260,
	XK_WINDOW_KEY_DELETE =						261,
	XK_WINDOW_KEY_RIGHT =							262,
	XK_WINDOW_KEY_LEFT =							263,
	XK_WINDOW_KEY_DOWN =							264,
	XK_WINDOW_KEY_UP =								265,
	XK_WINDOW_KEY_PAGE_UP =						266,
	XK_WINDOW_KEY_PAGE_DOWN =					267,
	XK_WINDOW_KEY_HOME =							268,
	XK_WINDOW_KEY_END =								269,
	XK_WINDOW_KEY_CAPS_LOCK =					280,
	XK_WINDOW_KEY_SCROLL_LOCK =				281,
	XK_WINDOW_KEY_NUM_LOCK =					282,
	XK_WINDOW_KEY_PRINT_SCREEN =			283,
	XK_WINDOW_KEY_PAUSE =							284,
	XK_WINDOW_KEY_F1 =								290,
	XK_WINDOW_KEY_F2 =								291,
	XK_WINDOW_KEY_F3 =								292,
	XK_WINDOW_KEY_F4 =								293,
	XK_WINDOW_KEY_F5 =								294,
	XK_WINDOW_KEY_F6 =								295,
	XK_WINDOW_KEY_F7 =								296,
	XK_WINDOW_KEY_F8 =								297,
	XK_WINDOW_KEY_F9 =								298,
	XK_WINDOW_KEY_F10 =								299,
	XK_WINDOW_KEY_F11 =								300,
	XK_WINDOW_KEY_F12 =								301,
	XK_WINDOW_KEY_F13 =								302,
	XK_WINDOW_KEY_F14 =								303,
	XK_WINDOW_KEY_F15 =								304,
	XK_WINDOW_KEY_F16 =								305,
	XK_WINDOW_KEY_F17 =								306,
	XK_WINDOW_KEY_F18 =								307,
	XK_WINDOW_KEY_F19 =								308,
	XK_WINDOW_KEY_F20 =								309,
	XK_WINDOW_KEY_F21 =								310,
	XK_WINDOW_KEY_F22 =								311,
	XK_WINDOW_KEY_F23 =								312,
	XK_WINDOW_KEY_F24 =								313,
	XK_WINDOW_KEY_F25 =								314,
	XK_WINDOW_KEY_KP_0 =							320,
	XK_WINDOW_KEY_KP_1 =							321,
	XK_WINDOW_KEY_KP_2 =							322,
	XK_WINDOW_KEY_KP_3 =							323,
	XK_WINDOW_KEY_KP_4 =							324,
	XK_WINDOW_KEY_KP_5 =							325,
	XK_WINDOW_KEY_KP_6 =							326,
	XK_WINDOW_KEY_KP_7 =							327,
	XK_WINDOW_KEY_KP_8 =							328,
	XK_WINDOW_KEY_KP_9 =							329,
	XK_WINDOW_KEY_KP_DECIMAL =				330,
	XK_WINDOW_KEY_KP_DIVIDE =					331,
	XK_WINDOW_KEY_KP_MULTIPLY =				332,
	XK_WINDOW_KEY_KP_SUBTRACT =				333,
	XK_WINDOW_KEY_KP_ADD =						334,
	XK_WINDOW_KEY_KP_ENTER =					335,
	XK_WINDOW_KEY_KP_EQUAL =					336,
	XK_WINDOW_KEY_LEFT_SHIFT =				340,
	XK_WINDOW_KEY_LEFT_CONTROL =			341,
	XK_WINDOW_KEY_LEFT_ALT =					342,
	XK_WINDOW_KEY_LEFT_SUPER =				343,
	XK_WINDOW_KEY_RIGHT_SHIFT =				344,
	XK_WINDOW_KEY_RIGHT_CONTROL =			345,
	XK_WINDOW_KEY_RIGHT_ALT =					346,
	XK_WINDOW_KEY_RIGHT_SUPER =				347,
	XK_WINDOW_KEY_MENU =							348
} XkWindowKey;

typedef enum {
	XK_RELEASE 	= 0,
	XK_PRESS 		= 1,
	XK_REPEAT 	= 2
} XkWindowAction;

typedef enum {
	XK_WINDOW_MOD_SHIFT 		= 0x0001,
	XK_WINDOW_MOD_CONTROL 	= 0x0002,
	XK_WINDOW_MOD_ALT 			= 0x0004,
	XK_WINDOW_MOD_SUPER 		= 0x0008,
	XK_WINDOW_MOD_CAPS_LOCK = 0x0010,
	XK_WINDOW_MOD_NUM_LOCK 	= 0x0020
} XkWindowMod;

typedef enum {
	XK_WINDOW_BUTTON_1 			= 0,
	XK_WINDOW_BUTTON_2 			= 1,
	XK_WINDOW_BUTTON_3 			= 2,
	XK_WINDOW_BUTTON_4 			= 3,
	XK_WINDOW_BUTTON_5 			= 4,
	XK_WINDOW_BUTTON_6 			= 5,
	XK_WINDOW_BUTTON_7 			= 6,
	XK_WINDOW_BUTTON_8 			= 7,
	XK_WINDOW_BUTTON_LEFT  	= XK_WINDOW_BUTTON_1,
	XK_WINDOW_BUTTON_RIGHT 	= XK_WINDOW_BUTTON_2,
	XK_WINDOW_BUTTON_MIDDLE = XK_WINDOW_BUTTON_3
} XkWindowButton;

typedef struct XkWindow* XkWindow;

typedef void(*XkWindowShowPfn)(XkWindow, const XkWindowShow);
typedef void(*XkWindowKeyPfn)(XkWindow, const XkWindowKey, const XkWindowAction, const XkWindowMod);
typedef void(*XkWindowButtonPfn)(XkWindow, const XkWindowButton, const XkWindowAction, const XkWindowMod);
typedef void(*XkWindowCursorPfn)(XkWindow, const XkFloat64, const XkFloat64);
typedef void(*XkWindowCursorEnterPfn)(XkWindow, const XkBool32);
typedef void(*XkWindowScrollPfn)(XkWindow, const XkFloat64, const XkFloat64);
typedef void(*XkWindowClosePfn)(XkWindow);
typedef void(*XkWindowPositionPfn)(XkWindow, const XkInt32, const XkInt32);
typedef void(*XkWindowSizePfn)(XkWindow, const XkSize, const XkSize);
typedef void(*XkWindowFocusPfn)(XkWindow, const XkBool32);

typedef struct XkWindowIcon {
	XkSize width;
	XkSize height;
	XkUInt8* pixels;
} XkWindowIcon;

struct XkWindow {
	XkSize width;
	XkSize height;
	XkSize xPos;
	XkSize yPos;

	XkBool32 maximized;
	XkBool32 minimized;
	XkBool32 fullscreen;
	XkBool32 activated;

	XkBool32 decorated;
	XkBool32 resizable;
	XkBool32 floating;

	XkHandle userPointer;

	XkBool32 closed;

	struct {
		XkWindowShowPfn show;
		XkWindowKeyPfn key;
		XkWindowButtonPfn button;
		XkWindowCursorPfn cursor;
		XkWindowCursorEnterPfn cursorEnter;
		XkWindowScrollPfn scroll;
		XkWindowClosePfn close;
		XkWindowPositionPfn position;
		XkWindowSizePfn size;
		XkWindowFocusPfn focus;
	} callbacks;

	XK_PLATFORM_WINDOW;
};

XK_EXPORT XkResult xkWindowInitialize(void);
XK_EXPORT void xkWindowTerminate(void);

XK_EXPORT XkResult xkCreateWindow(XkWindow, const XkChar8*, const XkSize, const XkSize, const XkWindowHint);
XK_EXPORT void xkDestroyWindow(XkWindow);

XK_EXPORT void xkShowWindow(XkWindow, const XkWindowShow);

XK_EXPORT void xkFocusWindow(XkWindow);

XK_EXPORT void xkSetWindowSize(XkWindow, const XkSize, const XkSize);
XK_EXPORT void xkGetWindowSize(XkWindow, XkSize* const, XkSize* const);

XK_EXPORT void xkSetWindowSizeLimits(XkWindow, const XkSize, const XkSize, const XkSize, const XkSize);

XK_EXPORT void xkSetWindowPosition(XkWindow, const XkInt32, const XkInt32);
XK_EXPORT void xkGetWindowPosition(XkWindow, XkInt32* const, XkInt32* const);

XK_EXPORT void xkSetWindowTitle(XkWindow, const XkChar8*);

XK_EXPORT void xkSetWindowIcon(XkWindow, const XkSize, const XkWindowIcon*);

XK_EXPORT void xkSetWindowShowCallback(XkWindow, const XkWindowShowPfn);
XK_EXPORT void xkSetWindowKeyCallback(XkWindow, const XkWindowKeyPfn);
XK_EXPORT void xkSetWindowButtonCallback(XkWindow, const XkWindowButtonPfn);
XK_EXPORT void xkSetWindowCursorCallback(XkWindow, const XkWindowCursorPfn);
XK_EXPORT void xkSetWindowCursorEnterCallback(XkWindow, const XkWindowCursorEnterPfn);
XK_EXPORT void xkSetWindowScrollCallback(XkWindow, const XkWindowScrollPfn);
XK_EXPORT void xkSetWindowCloseCallback(XkWindow, const XkWindowClosePfn);
XK_EXPORT void xkSetWindowPositionCallback(XkWindow, const XkWindowPositionPfn);
XK_EXPORT void xkSetWindowSizeCallback(XkWindow, const XkWindowSizePfn);
XK_EXPORT void xkSetWindowFocusCallback(XkWindow, const XkWindowFocusPfn);

XK_EXPORT XkBool32 xkShouldWindowClosed(XkWindow);
XK_EXPORT XkBool32 xkShouldWindowShowed(XkWindow, const XkWindowShow);

XK_EXPORT void xkPollWindowEvents(void);
XK_EXPORT void xkWaitWindowEvents(void);

XK_IMPORT void __xkInputWindowShow(XkWindow, const XkWindowShow);
XK_IMPORT void __xkInputWindowKey(XkWindow, const XkWindowKey, const XkWindowAction, const XkWindowMod);
XK_IMPORT void __xkInputWindowButton(XkWindow, const XkWindowButton, const XkWindowAction, const XkWindowMod);
XK_IMPORT void __xkInputWindowCursor(XkWindow, const XkFloat64, const XkFloat64);
XK_IMPORT void __xkInputWindowScroll(XkWindow, const XkFloat64, const XkFloat64);
XK_IMPORT void __xkInputWindowClose(XkWindow);
XK_IMPORT void __xkInputWindowPosition(XkWindow, const XkInt32, const XkInt32);
XK_IMPORT void __xkInputWindowSize(XkWindow, const XkSize, const XkSize);
XK_IMPORT void __xkInputWindowFocus(XkWindow, const XkBool32);

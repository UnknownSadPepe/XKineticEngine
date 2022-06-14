#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/Internal.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/Internal.h"
#endif // XK_LINUX
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Platform/Module.h"
#include "XKinetic/Platform/Thread.h"
#include "XKinetic/Platform/Time.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Joystick.h"

struct XkFile {
	XK_PLATFORM_FILE;
};

struct XkThread {
	XK_PLATFORM_THREAD;
};

struct XkMutex {
	XK_PLATFORM_MUTEX;
};

struct XkWindow {
	XkSize width;
	XkSize height;
	XkSize xPos;
	XkSize yPos;
	XkFloat64 xCursorPos;
	XkFloat64 yCursorPos;

	XkSize minWidth;
	XkSize minHeight;

	XkSize maxWidth;
	XkSize maxHeight;

	XkBool maximized;
	XkBool minimized;
	XkBool fullscreen;
	XkBool activated;

	XkBool decorated;
	XkBool resizable;
	XkBool floating;

	XkWindowCursorMode cursorMode;

	XkBool closed;

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

		XkWindowDropFilePfn dropFile;
	} callbacks;

	XK_PLATFORM_WINDOW;
};

typedef struct {
  XkUInt8         type;
  XkUInt8         index;
  XkInt8          axisScale;
  XkInt8          axisOffset;
} __xkJoystickMapElemets;

typedef struct
{
    char            name[128];
    char            guid[33];
    __xkJoystickMapElemets buttons[15];
    __xkJoystickMapElemets axes[6];
} __xkJoystickMapping;

struct XkJoystick {
	XkJoystickID 		id;
	XkBool        	connected;
	float*          axes;
	int             axisCount;
	unsigned char*  buttons;
	int             buttonCount;
	unsigned char*  hats;
	int             hatCount;
	char            name[128];
	void*           userPointer;
	char            guid[33];

	__xkJoystickMapping* mapping;

	struct {
		XkJoystickEventPfn event;
		XkJoystickAxisPfn axis;
		XkJoystickButtonPfn button;
		XkJoystickHatPfn hat;
	} callbacks;

	XK_PLATFORM_JOYSTICK;
};

struct XkWindowCursor {
	XK_PLATFORM_WINDOW_CURSOR;
};

typedef struct {
	XK_PLATFORM;

	XkInt16 keycodes[256];
} __XkPlatform;

extern __XkPlatform _xkPlatform;

#define __xkErrorHandle(format) __xkErrorHandler("%s %s %d", format, __FILE__, __LINE__)
XK_IMPORT void __xkErrorHandler(const XkString pFormat, ...);

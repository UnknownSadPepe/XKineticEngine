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

typedef struct {
	XK_PLATFORM;
} __XkPlatform;

extern __XkPlatform _xkPlatform;

#define __xkErrorHandle(format) __xkErrorHandler("%s %s %d", format, __FILE__, __LINE__)
XK_IMPORT void __xkErrorHandler(const XkChar8* pFormat, ...);

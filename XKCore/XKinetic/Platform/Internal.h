#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_PLATFORM_LINUX)
	#include "XKinetic/Platform/Linux/External.h"
	#include "XKinetic/Platform/Linux/Internal.h"
#elif defined(XK_PLATFORM_WIN32)
	#include "XKinetic/Platform/Win32/External.h"
	#include "XKinetic/Platform/Win32/Internal.h"
#endif // XK_PLATFORM_LINUX
#include "XKinetic/Platform/External.h"

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

	XkInt16 keycodes[256];
} XkPlatform;

extern XkPlatform _xkPlatform;

XK_API_IMPORT XkResult __xkMemoryInitialize(void);
XK_API_IMPORT void __xkMemoryTerminate(void);

XK_API_IMPORT XkHandle __xkAllocateMemory(const XkSize);
XK_API_IMPORT XkHandle __xkReallocateMemory(const XkHandle, const XkSize);
XK_API_IMPORT void __xkFreeMemory(const XkHandle);

XK_API_IMPORT XkResult __xkFileInitialize(void);
XK_API_IMPORT void __xkFileTerminate(void);

XK_API_IMPORT XkResult __xkOpenFile(XkFile, const XkChar8*, const XkFileFlag);
XK_API_IMPORT void __xkCloseFile(XkFile);

XK_API_IMPORT XkResult __xkCreateFile(XkFile, const XkChar8*);
XK_API_IMPORT void __xkRemoveFile(const XkChar8*);

XK_API_IMPORT void __xkRenameFile(const XkChar8*, const XkChar8*);

XK_API_IMPORT XkSize __xkSeekFile(XkFile, const XkInt32, const XkFileSeek);

XK_API_IMPORT void __xkWriteFile(XkFile, const XkChar8*, const XkSize);
XK_API_IMPORT void __xkReadFile(XkFile, XkChar8*, const XkSize);

XK_API_IMPORT XkResult __xkConsoleInitialize(void);
XK_API_IMPORT void __xkConsoleTerminate(void);

XK_API_IMPORT void __xkColorConsole(const XkConsoleHandle, const XkConsoleColor);
XK_API_IMPORT void __xkWriteConsole(const XkConsoleHandle, const XkChar8*, const XkSize);
XK_API_IMPORT void __xkReadConsole(XkChar8*, const XkSize);

XK_API_IMPORT XkResult __xkThreadInitialize(void);
XK_API_IMPORT void __xkThreadTerminate(void);

XK_API_IMPORT XkResult __xkCreateThread(XkThread, const XkThreadRoutinePfn);
XK_API_IMPORT void __xkJoinThread(XkThread, XkInt32* const);
XK_API_IMPORT void __xkDetachThread(XkThread);
XK_API_IMPORT void __xkExitThread(XkThread, const XkInt32);
XK_API_IMPORT void __xkKillThread(XkThread);
XK_API_IMPORT XkThread __xkThreadSelf(void);
XK_API_IMPORT void __xkThreadYield(void);
XK_API_IMPORT void __xkThreadSleep(const XkSize);

XK_API_IMPORT XkResult __xkCreateMutex(XkMutex);
XK_API_IMPORT void __xkDestroyMutex(XkMutex);
XK_API_IMPORT XkResult __xkLockMutex(XkMutex);
XK_API_IMPORT XkResult __xkTrylockMutex(XkMutex);
XK_API_IMPORT XkResult __xkUnlockMutex(XkMutex);

XK_API_IMPORT XkResult __xkWindowInitialize(void);
XK_API_IMPORT void __xkWindowTerminate(void);

XK_API_IMPORT XkResult __xkCreateWindow(XkWindow, const XkChar8*, const XkSize, const XkSize, const XkWindowHint);
XK_API_IMPORT void __xkDestroyWindow(XkWindow);

XK_API_IMPORT void __xkShowWindow(XkWindow, const XkWindowShow);

XK_API_IMPORT void __xkFocusWindow(XkWindow);

XK_API_IMPORT void __xkSetWindowSize(XkWindow, const XkSize, const XkSize);
XK_API_IMPORT void __xkGetWindowSize(XkWindow, XkSize* const, XkSize* const);

XK_API_IMPORT void __xkSetWindowSizeLimits(XkWindow, const XkSize, const XkSize, const XkSize, const XkSize);

XK_API_IMPORT void __xkSetWindowPosition(XkWindow, const XkInt32, const XkInt32);
XK_API_IMPORT void __xkGetWindowPosition(XkWindow, XkInt32* const, XkInt32* const);

XK_API_IMPORT void __xkSetWindowTitle(XkWindow, const XkChar8*);

XK_API_IMPORT void __xkSetWindowIcon(XkWindow, const XkSize, const XkWindowIcon*);

XK_API_IMPORT void __xkSetWindowShowCallback(XkWindow, const XkWindowShowPfn);
XK_API_IMPORT void __xkSetWindowKeyCallback(XkWindow, const XkWindowKeyPfn);
XK_API_IMPORT void __xkSetWindowButtonCallback(XkWindow, const XkWindowButtonPfn);
XK_API_IMPORT void __xkSetWindowCursorCallback(XkWindow, const XkWindowCursorPfn);
XK_API_IMPORT void __xkSetWindowCursorEnterCallback(XkWindow, const XkWindowCursorEnterPfn);
XK_API_IMPORT void __xkSetWindowScrollCallback(XkWindow, const XkWindowScrollPfn);
XK_API_IMPORT void __xkSetWindowCloseCallback(XkWindow, const XkWindowClosePfn);
XK_API_IMPORT void __xkSetWindowPositionCallback(XkWindow, const XkWindowPositionPfn);
XK_API_IMPORT void __xkSetWindowSizeCallback(XkWindow, const XkWindowSizePfn);
XK_API_IMPORT void __xkSetWindowFocusCallback(XkWindow, const XkWindowFocusPfn);

XK_API_IMPORT XkBool32 __xkShouldWindowClosed(XkWindow);
XK_API_IMPORT XkBool32 __xkShouldWindowShowed(XkWindow, const XkWindowShow);

XK_API_IMPORT void __xkPollWindowEvents(void);
XK_API_IMPORT void __xkWaitWindowEvents(void);

XK_API_IMPORT XkSize __xkGetTime(void);

#define __xkErrorHandle(format) __xkErrorHandler("%s %s %d", format, __FILE__, __LINE__)
XK_API_IMPORT void __xkErrorHandler(const XkChar8* pFormat, ...);

XK_API_IMPORT void __xkInputWindowShow(XkWindow, const XkWindowShow);
XK_API_IMPORT void __xkInputWindowKey(XkWindow, const XkWindowKey, const XkWindowAction, const XkWindowMod);
XK_API_IMPORT void __xkInputWindowButton(XkWindow, const XkWindowButton, const XkWindowAction, const XkWindowMod);
XK_API_IMPORT void __xkInputWindowCursor(XkWindow, const XkFloat64, const XkFloat64);
XK_API_IMPORT void __xkInputWindowScroll(XkWindow, const XkFloat64, const XkFloat64);
XK_API_IMPORT void __xkInputWindowClose(XkWindow);
XK_API_IMPORT void __xkInputWindowPosition(XkWindow, const XkInt32, const XkInt32);
XK_API_IMPORT void __xkInputWindowSize(XkWindow, const XkSize, const XkSize);
XK_API_IMPORT void __xkInputWindowFocus(XkWindow, const XkBool32);

XK_API_IMPORT XkModule __xkLoadModule(const XkChar8*);
XK_API_IMPORT void __xkFreeModule(XkModule);
XK_API_IMPORT XkProcPfn __xkGetModuleSymbol(XkModule, const XkChar8*);


#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/Memory.h"
#include "XKinetic/Core/Window.h"

#include "XKinetic/Core/Log.h"

XkResult xkWindowInitialize(void) {
	XkResult result = XK_SUCCESS;

	result = __xkWindowInitialize();
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkWindowTerminate(void) {
	__xkWindowTerminate();
}

XkResult xkCreateWindow(XkWindow* pWindow, const XkChar8* title, const XkSize width, const XkSize height, const XkWindowHint hint) {
	XkResult result = XK_SUCCESS;

	*pWindow = xkAllocateMemory(sizeof(struct XkWindow));
	if(!pWindow) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkWindow window = *pWindow;

	result = __xkCreateWindow(window, title, width, height, hint);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyWindow(XkWindow window) {
	__xkDestroyWindow(window);
	xkFreeMemory(window);
}

void xkShowWindow(XkWindow window, const XkWindowShow show) {
	__xkShowWindow(window, show);
}

void xkFocusWindow(XkWindow window) {
	__xkFocusWindow(window);
}

void xkSetWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	__xkSetWindowSize(window, width, height);
}

void xkGetWindowSize(XkWindow window, XkSize* const pWidth, XkSize* const pHeight) {
	__xkGetWindowSize(window, pWidth, pHeight);
}

void xkSetWindowSizeLimits(XkWindow window, const XkSize minWidth, const XkSize minHeight, const XkSize maxWidth, const XkSize maxHeight) {
	__xkSetWindowSizeLimits(window, minWidth, minHeight, maxWidth, maxHeight);
}

void xkSetWindowPosition(XkWindow window, const XkInt32 xPos, const XkInt32 yPos) {
	__xkSetWindowPosition(window, xPos, yPos);
}

void xkGetWindowPosition(XkWindow window, XkInt32* const pXPos, XkInt32* const pYPos) {
	__xkGetWindowPosition(window, pXPos, pYPos);
}

void xkSetWindowTitle(XkWindow window, const XkChar8* title) {
	__xkSetWindowTitle(window, title);
}

void xkSetWindowIcon(XkWindow window, const XkSize iconCount, const XkWindowIcon* pIcon) {
	__xkSetWindowIcon(window, iconCount, pIcon);
}

XkBool32 xkShouldWindowClosed(XkWindow window) {
	return(__xkShouldWindowClosed(window));
}

XkBool32 xkShouldWindowShowed(XkWindow window, const XkWindowShow show) {
	return(__xkShouldWindowShowed(window, show));
}

void xkSetWindowShowCallback(XkWindow window, const XkWindowShowPfn pfnCallback) {
	__xkSetWindowShowCallback(window, pfnCallback);
}

void xkSetWindowKeyCallback(XkWindow window, const XkWindowKeyPfn pfnCallback) {
	__xkSetWindowKeyCallback(window, pfnCallback);
}

void xkSetWindowButtonCallback(XkWindow window, const XkWindowButtonPfn pfnCallback) {
	__xkSetWindowButtonCallback(window, pfnCallback);
}

void xkSetWindowCursorCallback(XkWindow window, const XkWindowCursorPfn pfnCallback) {
	__xkSetWindowCursorCallback(window, pfnCallback);
}

void xkSetWindowScrollCallback(XkWindow window, const XkWindowScrollPfn pfnCallback) {
	__xkSetWindowScrollCallback(window, pfnCallback);
}

void xkSetWindowCloseCallback(XkWindow window, const XkWindowClosePfn pfnCallback) {
	__xkSetWindowCloseCallback(window, pfnCallback);
}

void xkSetWindowPositionCallback(XkWindow window, const XkWindowPositionPfn pfnCallback) {
	__xkSetWindowPositionCallback(window, pfnCallback);
}

void xkSetWindowSizeCallback(XkWindow window, const XkWindowSizePfn pfnCallback) {
	__xkSetWindowSizeCallback(window, pfnCallback);
}

void xkSetWindowFocusCallback(XkWindow window, const XkWindowFocusPfn pfnCallback) {
	__xkSetWindowFocusCallback(window, pfnCallback);
}

void xkPollWindowEvents(void) {
	__xkPollWindowEvents();
}

void xkWaitWindowEvents(void) {
	__xkWaitWindowEvents();
}


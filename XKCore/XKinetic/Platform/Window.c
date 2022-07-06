/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLE SECTION ########## */
__XkPlatform _xkPlatform;

/* ########## FUNCTIONS SECTION ########## */
XkCursorMode xkGetWindowCursorMode(XkWindow window) {
	xkAssert(window);

	return(window->cursorMode);
}

XkString xkGetWindowTitle(XkWindow window) {
	xkAssert(window);

	return(window->title);
}

void __xkInputWindowShow(XkWindow window, const XkWindowShow show) {
	xkAssert(window);

	if(window->callbacks.show) {
		window->callbacks.show(window, show);
	}
}

void __xkInputWindowKey(XkWindow window, const XkKey key, const XkAction action, const XkMod mod) {
	xkAssert(window);

	if(window->callbacks.key) {
		window->callbacks.key(window, key, action, mod);
	}
}

void __xkInputWindowButton(XkWindow window, const XkButton button, const XkAction action, const XkMod mod) {
	xkAssert(window);

	if(window->callbacks.button) {
		window->callbacks.button(window, button, action, mod);
	}
}

void __xkInputWindowCursor(XkWindow window, const XkFloat64 x, const XkFloat64 y) {
	xkAssert(window);

	if(window->callbacks.cursor) {
		window->callbacks.cursor(window, x, y);
	}
}

void __xkInputWindowCursorEnter(XkWindow window, const XkBool8 enter) {
	xkAssert(window);

	if(window->callbacks.cursorEnter) {
		window->callbacks.cursorEnter(window, enter);
	}
}

void __xkInputWindowScroll(XkWindow window, const XkFloat64 x, const XkFloat64 y) {
	xkAssert(window);

	if(window->callbacks.scroll) {
		window->callbacks.scroll(window, x, y);
	}
}

void __xkInputWindowClose(XkWindow window) {
	if(window->callbacks.close) {
		window->callbacks.close(window);
	}
}

void __xkInputWindowPosition(XkWindow window, const XkInt32 x, const XkInt32 y) {
	xkAssert(window);

	if(window->callbacks.position) {
		window->callbacks.position(window, x, y);
	}
}

void __xkInputWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	xkAssert(window);

	if(window->callbacks.size) {
		window->callbacks.size(window, width, height);
	}
}

void __xkInputWindowFocus(XkWindow window, const XkBool8 focused) {
	xkAssert(window);

	if(window->callbacks.focus) {
		window->callbacks.focus(window, focused);
	}
}

void __xkInputWindowDropFile(XkWindow window, const XkSize count, const XkString* paths) {
	xkAssert(window);
	xkAssert(count > 0);
	xkAssert(paths);

	if(window->callbacks.dropFile) {
		window->callbacks.dropFile(window, count, paths);
	}	
}

void xkSetWindowShowCallback(XkWindow window, const XkWindowShowPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.show = pfnCallback;
}

void xkSetWindowKeyCallback(XkWindow window, const XkWindowKeyPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.key = pfnCallback;
}

void xkSetWindowButtonCallback(XkWindow window, const XkWindowButtonPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.button = pfnCallback;
}

void xkSetWindowCursorCallback(XkWindow window, const XkWindowCursorPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.cursor = pfnCallback;
}

void xkSetWindowCursorEnterCallback(XkWindow window, const XkWindowCursorEnterPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.cursorEnter = pfnCallback;
}

void xkSetWindowScrollCallback(XkWindow window, const XkWindowScrollPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.scroll = pfnCallback;
}

void xkSetWindowCloseCallback(XkWindow window, const XkWindowClosePfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.close = pfnCallback;
}

void xkSetWindowPositionCallback(XkWindow window, const XkWindowPositionPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.position = pfnCallback;
}

void xkSetWindowSizeCallback(XkWindow window, const XkWindowSizePfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.size = pfnCallback;
}

void xkSetWindowFocusCallback(XkWindow window, const XkWindowFocusPfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.focus = pfnCallback;
}

void xkSetWindowDropFileCallback(XkWindow window, const XkWindowDropFilePfn pfnCallback) {
	xkAssert(window);
	xkAssert(pfnCallback);

	window->callbacks.dropFile = pfnCallback;	
}

#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Window.h"

__XkPlatform _xkPlatform;

XkWindowCursorMode xkGetWindowCursorMode(XkWindow window) {
	return(window->cursorMode);
}

XkString xkGetWindowTitle(XkWindow window) {
	return(window->title);
}

void __xkInputWindowShow(XkWindow window, const XkWindowShow show) {
	if(window->callbacks.show) {
		window->callbacks.show(window, show);
	}
}

void __xkInputWindowKey(XkWindow window, const XkWindowKey key, const XkWindowAction action, const XkWindowMod mod) {
	if(window->callbacks.key) {
		window->callbacks.key(window, key, action, mod);
	}
}

void __xkInputWindowButton(XkWindow window, const XkWindowButton button, const XkWindowAction action, const XkWindowMod mod) {
	if(window->callbacks.button) {
		window->callbacks.button(window, button, action, mod);
	}
}

void __xkInputWindowCursor(XkWindow window, const XkFloat64 x, const XkFloat64 y) {
	if(window->callbacks.cursor) {
		window->callbacks.cursor(window, x, y);
	}
}

void __xkInputWindowCursorEnter(XkWindow window, const XkBool enter) {
	if(window->callbacks.cursorEnter) {
		window->callbacks.cursorEnter(window, enter);
	}
}

void __xkInputWindowScroll(XkWindow window, const XkFloat64 x, const XkFloat64 y) {
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
	if(window->callbacks.position) {
		window->callbacks.position(window, x, y);
	}
}

void __xkInputWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	if(window->callbacks.size) {
		window->callbacks.size(window, width, height);
	}
}

void __xkInputWindowFocus(XkWindow window, const XkBool focused) {
	if(window->callbacks.focus) {
		window->callbacks.focus(window, focused);
	}
}

void __xkInputWindowDropFile(XkWindow window, const XkSize count, const XkString* paths) {
	if(window->callbacks.dropFile) {
		window->callbacks.dropFile(window, count, paths);
	}	
}

void xkSetWindowShowCallback(XkWindow window, const XkWindowShowPfn pfnCallback) {
	window->callbacks.show = pfnCallback;
}

void xkSetWindowKeyCallback(XkWindow window, const XkWindowKeyPfn pfnCallback) {
	window->callbacks.key = pfnCallback;
}

void xkSetWindowButtonCallback(XkWindow window, const XkWindowButtonPfn pfnCallback) {
	window->callbacks.button = pfnCallback;
}

void xkSetWindowCursorCallback(XkWindow window, const XkWindowCursorPfn pfnCallback) {
	window->callbacks.cursor = pfnCallback;
}

void xkSetWindowCursorEnterCallback(XkWindow window, const XkWindowCursorEnterPfn pfnCallback) {
	window->callbacks.cursorEnter = pfnCallback;
}

void xkSetWindowScrollCallback(XkWindow window, const XkWindowScrollPfn pfnCallback) {
	window->callbacks.scroll = pfnCallback;
}

void xkSetWindowCloseCallback(XkWindow window, const XkWindowClosePfn pfnCallback) {
	window->callbacks.close = pfnCallback;
}

void xkSetWindowPositionCallback(XkWindow window, const XkWindowPositionPfn pfnCallback) {
	window->callbacks.position = pfnCallback;
}

void xkSetWindowSizeCallback(XkWindow window, const XkWindowSizePfn pfnCallback) {
	window->callbacks.size = pfnCallback;
}

void xkSetWindowFocusCallback(XkWindow window, const XkWindowFocusPfn pfnCallback) {
	window->callbacks.focus = pfnCallback;
}

void xkSetWindowDropFileCallback(XkWindow window, const XkWindowDropFilePfn pfnCallback) {
	window->callbacks.dropFile = pfnCallback;	
}

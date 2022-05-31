#include "XKinetic/Platform/Internal.h"

XkPlatform _xkPlatform;

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

void __xkInputWindowFocus(XkWindow window, const XkBool32 focused) {
	if(window->callbacks.focus) {
		window->callbacks.focus(window, focused);
	}
}

void __xkSetWindowShowCallback(XkWindow window, const XkWindowShowPfn pfnCallback) {
	window->callbacks.show = pfnCallback;
}

void __xkSetWindowKeyCallback(XkWindow window, const XkWindowKeyPfn pfnCallback) {
	window->callbacks.key = pfnCallback;
}

void __xkSetWindowButtonCallback(XkWindow window, const XkWindowButtonPfn pfnCallback) {
	window->callbacks.button = pfnCallback;
}

void __xkSetWindowCursorCallback(XkWindow window, const XkWindowCursorPfn pfnCallback) {
	window->callbacks.cursor = pfnCallback;
}

void __xkSetWindowCursorEnterCallback(XkWindow window, const XkWindowCursorEnterPfn pfnCallback) {
	window->callbacks.cursorEnter = pfnCallback;
}

void __xkSetWindowScrollCallback(XkWindow window, const XkWindowScrollPfn pfnCallback) {
	window->callbacks.scroll = pfnCallback;
}

void __xkSetWindowCloseCallback(XkWindow window, const XkWindowClosePfn pfnCallback) {
	window->callbacks.close = pfnCallback;
}

void __xkSetWindowPositionCallback(XkWindow window, const XkWindowPositionPfn pfnCallback) {
	window->callbacks.position = pfnCallback;
}

void __xkSetWindowSizeCallback(XkWindow window, const XkWindowSizePfn pfnCallback) {
	window->callbacks.size = pfnCallback;
}

void __xkSetWindowFocusCallback(XkWindow window, const XkWindowFocusPfn pfnCallback) {
	window->callbacks.focus = pfnCallback;
}

XkBool32 __xkShouldWindowClosed(XkWindow window) {
	return(window->closed);
}

XkBool32 __xkShouldWindowShowed(XkWindow window, const XkWindowShow show) {
	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT:
			return(window->activated);
			break;

		case XK_WINDOW_SHOW_MAXIMIZED:
			return(window->maximized);
			break;

		case XK_WINDOW_SHOW_MINIMIZED:
			return(window->minimized);
			break;

		case XK_WINDOW_SHOW_FULLSCREEN:
			return(window->fullscreen);
			break;

		case XK_WINDOW_HIDE:
			return(!window->activated);
			break;
	}
	return(XK_FALSE);
}


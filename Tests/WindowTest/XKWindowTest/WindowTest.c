#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"

struct XkApplication {
	XkApplicationConfig config;

	XkWindow window;

	XkBool32 exit;
};

XkApplication _xkApplication;

static void __xkWindowShow(XkWindow window, const XkWindowShow show) {
	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT: 		xkLogNotice("show default"); break;
		case XK_WINDOW_SHOW_MAXIMIZED: 	xkLogNotice("show maximized"); break;
		case XK_WINDOW_SHOW_MINIMIZED: 	xkLogNotice("show minimized"); break;
		case XK_WINDOW_SHOW_FULLSCREEN: xkLogNotice("show fullscreen"); break;
		case XK_WINDOW_HIDE: 						xkLogNotice("hide"); break;
	}
}

static void __xkWindowKey(XkWindow window, const XkWindowKey key, const XkWindowAction action, const XkWindowMod mod) {
	XkChar8* actionStr = XK_NULL_HANDLE; 

	switch(action) {
		case XK_RELEASE: actionStr = "release";
		case XK_PRESS: actionStr = "press";
	}

	xkLogNotice("key %d action: %s mod: %d", key, actionStr, mod);
}

static void __xkWindowButton(XkWindow window, const XkWindowButton button, const XkWindowAction action, const XkWindowMod mod) {
	XkChar8* actionStr = XK_NULL_HANDLE; 

	switch(action) {
		case XK_RELEASE: actionStr = "release";
		case XK_PRESS: actionStr = "press";
	}

	xkLogNotice("button %d action: %s mod: %d", button, actionStr, mod);
}

static void __xkWindowCursor(XkWindow window, XkFloat64 x, XkFloat64 y) {
	xkLogNotice("cursor x: %f y: %f", x, y);
}

static void __xkWindowCursorEnter(XkWindow window, XkBool32 entered) {
	if(entered) {
		xkLogNotice("cursor entered");
	} else {
		xkLogNotice("cursor unentered");
	}
}

static void __xkWindowScroll(XkWindow window, XkFloat64 x, XkFloat64 y) {
	xkLogNotice("scroll x: %f y: %f", x, y);
}

static void __xkWindowClose(XkWindow window) {
	_xkApplication.exit = XK_TRUE;
}

static void __xkWindowSize(XkWindow window, XkSize width, XkSize height) {
	xkLogNotice("width: %ld height: %ld", width, height);
}

static void __xkWindowPosition(XkWindow window, XkInt32 x, XkInt32 y) {
	xkLogNotice("x: %d y: %d", x, y);
}

static void __xkWindowFocus(XkWindow window, XkBool32 focused) {
	if(focused) {
		xkLogNotice("focused");
	} else {
		xkLogNotice("unfocused");
	}
}

XkResult xkCreateApplication(const XkSize argc, const XkChar8** argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.pName = "XKWindowTest";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;
	_xkApplication.exit = XK_FALSE;

	result = xkLogInitialize();
	if(result != XK_SUCCESS) goto _catch;

	result = xkWindowInitialize();
	if(result != XK_SUCCESS) goto _catch;

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.config.pName, 1280, 720, XK_WINDOW_DECORATED_BIT | XK_WINDOW_RESIZABLE_BIT);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create window: %d", result);
		goto _catch;
	}

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_DEFAULT);

	xkSetWindowShowCallback(_xkApplication.window, __xkWindowShow);
	xkSetWindowKeyCallback(_xkApplication.window, __xkWindowKey);
	xkSetWindowButtonCallback(_xkApplication.window, __xkWindowButton);
	xkSetWindowCursorCallback(_xkApplication.window, __xkWindowCursor);
	xkSetWindowCursorEnterCallback(_xkApplication.window, __xkWindowCursorEnter);
	xkSetWindowScrollCallback(_xkApplication.window, __xkWindowScroll);
	xkSetWindowCloseCallback(_xkApplication.window, __xkWindowClose);
	xkSetWindowSizeCallback(_xkApplication.window, __xkWindowSize);
	xkSetWindowPositionCallback(_xkApplication.window, __xkWindowPosition);
	xkSetWindowFocusCallback(_xkApplication.window, __xkWindowFocus);

_catch:
	return(result);
}

void xkDestroyApplication() {
	xkDestroyWindow(_xkApplication.window);

	xkWindowTerminate();

	xkLogTerminate();
}

void xkUpdateApplication() {
	while(!_xkApplication.exit) {
		// Poll window events.
		xkPollWindowEvents();
	}
}

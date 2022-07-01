#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"

struct XkApplication {
	XkApplicationConfig config;

	XkWindow window;

	XkBool exit;
};

XkApplication _xkApplication;

static void __xkWindowClose(XkWindow window) {
	_xkApplication.exit = XK_TRUE;
}

static void __xkWindowDropFile(XkWindow window, const XkSize count, const XkString* files) {

}

XkResult xkCreateApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKEditor";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;
	_xkApplication.exit = XK_FALSE;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) goto _catch;

	result = xkInitializeWindow();
	if(result != XK_SUCCESS) goto _catch;

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.config.name, 1280, 720, XK_WINDOW_DECORATED_BIT | XK_WINDOW_RESIZABLE_BIT | XK_WINDOW_DRAG_DROP_BIT);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create editor main window");
		goto _catch;
	}

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_MAXIMIZED);

	xkSetWindowCloseCallback(_xkApplication.window, __xkWindowClose);
	xkSetWindowDropFileCallback(_xkApplication.window, __xkWindowDropFile);

_catch:
	return(result);
}

void xkDestroyApplication(void) {
	xkTerminateWindow();

	xkTerminateLog();
}

void xkUpdateApplication(void) {
	while(!_xkApplication.exit) {

		// Poll window events.
		xkPollWindowEvents();
	}
}

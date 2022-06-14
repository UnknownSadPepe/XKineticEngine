#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"

#include "XKinetic/Resources/Loaders/ImageLoader.h"

struct XkApplication {
	XkApplicationConfig config;

	XkWindow window;

	XkBool exit;

	XkImageLoader imageLoader;
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
	XkString actionStr = XK_NULL_HANDLE; 

	switch(action) {
		case XK_RELEASE: actionStr = "release"; break;
		case XK_PRESS: actionStr = "press"; break;
		case XK_REPEAT: actionStr = "repeat"; break;
	}

	if(mod & XK_MOD_SHIFT_BIT) {
		xkLogNotice("mod: %s", "shift");
	}
	if(mod & XK_MOD_CONTROL_BIT) {
		xkLogNotice("mod: %s", "control");		
	}
	if(mod & XK_MOD_ALT_BIT) {
		xkLogNotice("mod: %s", "alt");
	}
	if(mod & XK_MOD_SUPER_BIT) {
		xkLogNotice("mod: %s", "super");
	}
	if(mod & XK_MOD_CAPS_LOCK_BIT) {
		xkLogNotice("mod: %s", "caps lock");
	}
	if(mod & XK_MOD_NUM_LOCK_BIT) {
		xkLogNotice("mod: %s", "num lock");
	}

	if(mod & XK_MOD_CONTROL_BIT) {
		if(key == XK_KEY_R) {
			xkSetWindowSize(window, 800, 600);
		} else if(key == XK_KEY_L) {
			xkSetWindowSizeLimits(window, 800, 600, 1280, 720);
		} else if(key == XK_KEY_P) {
			xkSetWindowPosition(window, -1, -1);
		} else if(key == XK_KEY_T) {
			xkSetWindowTitle(window, "renamed window");
		}
	}

	xkLogNotice("key: %d action: %s", key, actionStr);
}

static void __xkWindowButton(XkWindow window, const XkWindowButton button, const XkWindowAction action, const XkWindowMod mod) {
	XkString actionStr = XK_NULL_HANDLE; 

	switch(action) {
		case XK_RELEASE: actionStr = "release"; break;
		case XK_PRESS: actionStr = "press"; break;
		case XK_REPEAT: actionStr = "repeat"; break;
	}

	if(mod & XK_MOD_SHIFT_BIT) {
		xkLogNotice("mod: %s", "shift");
	}
	if(mod & XK_MOD_CONTROL_BIT) {
		xkLogNotice("mod: %s", "control");		
	}
	if(mod & XK_MOD_ALT_BIT) {
		xkLogNotice("mod: %s", "alt");
	}
	if(mod & XK_MOD_SUPER_BIT) {
		xkLogNotice("mod: %s", "super");
	}
	if(mod & XK_MOD_CAPS_LOCK_BIT) {
		xkLogNotice("mod: %s", "caps lock");
	}
	if(mod & XK_MOD_NUM_LOCK_BIT) {
		xkLogNotice("mod: %s", "num lock");
	}

	xkLogNotice("button: %d action: %s", button, actionStr);
}

static void __xkWindowCursor(XkWindow window, XkFloat64 x, XkFloat64 y) {
	xkLogNotice("cursor x: %f y: %f", x, y);
}

static void __xkWindowCursorEnter(XkWindow window, XkBool entered) {
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

static void __xkWindowFocus(XkWindow window, XkBool focused) {
	if(focused) {
		xkLogNotice("focused");
	} else {
		xkLogNotice("unfocused");
	}
}

XkResult xkCreateApplication(const XkSize argc, const XkWString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKWindowTest";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;
	_xkApplication.exit = XK_FALSE;

	result = xkLogInitialize();
	if(result != XK_SUCCESS) goto _catch;

	result = xkWindowInitialize();
	if(result != XK_SUCCESS) goto _catch;

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.config.name, 1280, 720, XK_WINDOW_DECORATED_BIT | XK_WINDOW_RESIZABLE_BIT);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create window: %d", result);
		goto _catch;
	}

	// Create image loader.
	result = xkCreateImageLoader(&_xkApplication.imageLoader, "./");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create image loader");
		goto _catch;
	}

	// Load window icon.
	XkImageConfig iconConfig;
	result = xkLoadImage(_xkApplication.imageLoader, &iconConfig, "XKineticIcon.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window icon");
		goto _catch;	
	}

	// Load window small icon.
	XkImageConfig smallIconConfig;
	result = xkLoadImage(_xkApplication.imageLoader, &smallIconConfig, "XKineticIcon.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window small icon");
		goto _catch;	
	}

	XkWindowIcon icon = {
		.width = iconConfig.width,
		.height = iconConfig.height,
		.pixels = iconConfig.pixels
	};

	XkWindowIcon smallIcon = {
		.width = smallIconConfig.width,
		.height = smallIconConfig.height,
		.pixels = smallIconConfig.pixels
	};

	XkWindowIcon icons[2] = {icon, smallIcon};
	xkSetWindowIcon(_xkApplication.window, 2, icons);

/*
	XkWindowIcon cursor = {
		.
	};
	xkSetWindowCursor();
*/
	// Unload window icon.
	xkUnloadImage(_xkApplication.imageLoader, &iconConfig);

	// Unload window small icon.
	xkUnloadImage(_xkApplication.imageLoader, &smallIconConfig);

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_DEFAULT);

	xkSetWindowSizeLimits(_xkApplication.window, 800, 600, 1920, 1080);

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

	xkLogDebug("XKinetic Debug mode");

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
		xkWaitWindowEvents();
	}
}

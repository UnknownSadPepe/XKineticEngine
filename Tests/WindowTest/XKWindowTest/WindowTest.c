/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Joystick.h"

#include "XKinetic/Resources/Loaders/ImageLoader.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
XkApplication _xkApplication;

/* ########## FUNCTIONS SECTION ########## */
static void __xkWindowShow(XkWindow window, const XkWindowShow show) {
	xkAssert(window);

	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT: 		xkLogNotice("show default"); 			break;
		case XK_WINDOW_SHOW_MAXIMIZED: 	xkLogNotice("show maximized"); 		break;
		case XK_WINDOW_SHOW_MINIMIZED: 	xkLogNotice("show minimized"); 		break;
		case XK_WINDOW_SHOW_FULLSCREEN: xkLogNotice("show fullscreen"); 	break;
		case XK_WINDOW_HIDE: 						xkLogNotice("hide"); 							break;
		default: 																													break;
	}
}

static void __xkWindowKey(XkWindow window, const XkKey key, const XkAction action, const XkMod mod) {
	xkAssert(window);

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

		if(key == XK_KEY_C) {
			xkSetWindowCursorMode(window, XK_CURSOR_NORMAL);
			xkSetWindowCursorPosition(window, 0, 0);
		} else if(key == XK_KEY_V) {
			xkSetWindowCursorMode(window, XK_CURSOR_HIDDEN);
		} else if(key == XK_KEY_B) {
			xkSetWindowCursorMode(window, XK_CURSOR_DISABLED);
		}

		if (key == XK_KEY_X) {
			xkSetWindowCursor(window, XK_NULL_HANDLE);
		}

		if(key == XK_KEY_F) {
			xkShowWindow(window, XK_WINDOW_SHOW_FULLSCREEN);
		} else if(key == XK_KEY_M) {
			xkShowWindow(window, XK_WINDOW_SHOW_MAXIMIZED);
		} else if(key == XK_KEY_D) {
			xkShowWindow(window, XK_WINDOW_SHOW_DEFAULT);
		} else if(key == XK_KEY_H) {
			xkShowWindow(window, XK_WINDOW_HIDE);
		}
	}

	xkLogNotice("key: %d action: %s", key, action == XK_RELEASE ? "release" : action == XK_PRESS ? "press" : "repeat");
}

static void __xkWindowButton(XkWindow window, const XkButton button, const XkAction action, const XkMod mod) {
	xkAssert(window);

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

	xkLogNotice("button: %d action: %s", button, action == XK_RELEASE ? "release" : action == XK_PRESS ? "press" : "repeat");
}

static void __xkWindowCursor(XkWindow window, XkFloat64 x, XkFloat64 y) {
	xkAssert(window);

	xkLogNotice("cursor x: %f y: %f", x, y);
}

static void __xkWindowCursorEnter(XkWindow window, XkBool entered) {
	xkAssert(window);

	if(entered) {
		xkLogNotice("cursor entered");
	} else {
		xkLogNotice("cursor unentered");
	}
}

static void __xkWindowScroll(XkWindow window, XkFloat64 x, XkFloat64 y) {
	xkAssert(window);

	xkLogNotice("scroll x: %f y: %f", x, y);
}

static void __xkWindowClose(XkWindow window) {
	xkAssert(window);

	xkLogNotice("close");

	_xkApplication.exit = XK_TRUE;
}

static void __xkWindowSize(XkWindow window, XkSize width, XkSize height) {
	xkAssert(window);
	xkAssert(width > 0);
	xkAssert(height > 0);

	xkLogNotice("width: %ld height: %ld", width, height);
}

static void __xkWindowPosition(XkWindow window, XkInt32 x, XkInt32 y) {
	xkAssert(window);

	xkLogNotice("x: %d y: %d", x, y);
}

static void __xkWindowFocus(XkWindow window, XkBool focused) {
	xkAssert(window);

	if(focused) {
		xkLogNotice("focused");
	} else {
		xkLogNotice("unfocused");
	}
}

static void __xkWindowDropFile(XkWindow window, const XkSize count, const XkString* paths) {
	xkAssert(window);

	for(XkSize i = 0; i < count; i++) {
		xkLogNotice("file[%ld]: %s", i, paths[i]);
	}
}

static void __xkJoystickEvent(XkJoystick joystick, const XkJoystickEvent event) {
	xkAssert(j >= XK_JOYSTICK_1 && j < XK_JOYSTICK_16);

	if(event == XK_JOYSTICK_CONNECTED) {
		xkLogNotice("joystick%d disconnected", joystick);
	} else if(event == XK_JOYSTICK_DISCONNECTED) {
		xkLogNotice("joystick%d disconnected", joystick);
	}
}

static void __xkJoystickAxis(XkJoystick joystick, const XkJoystickAxis axis, const XkFloat32 value) {
	xkAssert(j >= XK_JOYSTICK_1 && j < XK_JOYSTICK_16);

	xkLogNotice("joystick%d axis: %d: value: %d", joystick, axis, value);
}

static void __xkJoystickButton(XkJoystick joystick, const XkJoystickButton button, const XkAction action) {
	xkAssert(j >= XK_JOYSTICK_1 && j < XK_JOYSTICK_16);

	xkLogNotice("joystick%d button: %d: action: %d", joystick, button, action);
}

static void __xkJoystickHat(XkJoystick joystick, const XkJoystickHat hat, const XkAction action) {
	xkAssert(j >= XK_JOYSTICK_1 && j < XK_JOYSTICK_16);

	xkLogNotice("joystick%d hat: %d: action: %d", joystick, hat, action);
}

XkResult xkInitializeApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.name = "XKWindowTest";
	_xkApplication.version.major = 0;
	_xkApplication.version.minor = 0;
	_xkApplication.version.patch = 1;
	_xkApplication.exit = XK_FALSE;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize log: %d", result);
		goto _catch;
	}

	result = xkInitializeWindow();
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize window: %d", result);
		goto _catch;
	}

	result = xkInitializeJoystick();
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize joystick: %d", result);
		goto _catch;
	}

	for(XkJoystick j = XK_JOYSTICK_1; j < XK_JOYSTICK_16; j++) {
		if(xkJoystickPresent(j)) {
			xkSetJoystickEventCallback(j, __xkJoystickEvent);
			xkSetJoystickAxisCallback(j, __xkJoystickAxis);
			xkSetJoystickButtonCallback(j, __xkJoystickButton);
			xkSetJoystickHatCallback(j, __xkJoystickHat);
		}
	}

	result = xkInitializeImageLoader("../../");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to initialize image loader: %d", result);
		goto _catch;
	}

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.name, 1280, 720, XK_WINDOW_HINT_DECORATED_BIT | XK_WINDOW_HINT_RESIZABLE_BIT);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create window: %d", result);
		goto _catch;
	}

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
	xkSetWindowDropFileCallback(_xkApplication.window, __xkWindowDropFile);

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_DEFAULT);

	XkImageConfig iconConfig;
	result = xkLoadImage(&iconConfig, "XKineticIcon.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window icon");
	}

	XkImageConfig smallIconConfig;
	result = xkLoadImage(&smallIconConfig, "XKineticIcon.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window small icon");	
	}

	XkImageConfig cursorConfig;
	result = xkLoadImage(&cursorConfig, "XKineticCursor.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window cursor");
	}

	XkWindowIcon icon = {};
	icon.width				= iconConfig.width;
	icon.height 			= iconConfig.height;
	icon.pixels 			= iconConfig.pixels;

	XkWindowIcon smallIcon 	= {};
	smallIcon.width 				= smallIconConfig.width;
	smallIcon.height 				= smallIconConfig.height;
	smallIcon.pixels 				= smallIconConfig.pixels;

	XkWindowIcon icons[2] = {icon, smallIcon};
	xkSetWindowIcon(_xkApplication.window, 2, icons);

	XkWindowIcon cursorIcon 	= {};
	cursorIcon.width 					= cursorConfig.width;
	cursorIcon.height 				= cursorConfig.height;
	cursorIcon.pixels 				= cursorConfig.pixels;

	xkSetWindowCursor(_xkApplication.window, &cursorIcon);

	xkUnloadImage(&cursorConfig);

	xkUnloadImage(&iconConfig);

	xkUnloadImage(&smallIconConfig);

_catch:
	return(result);
}

void xkTerminateApplication(void) {
	xkDestroyWindow(_xkApplication.window);

	xkTerminateImageLoader();

	xkTerminateJoystick();

	xkTerminateWindow();

	xkTerminateLog();
}

void xkUpdateApplication(void) {
	while(!_xkApplication.exit) {
		xkPollEvents();
	}
}

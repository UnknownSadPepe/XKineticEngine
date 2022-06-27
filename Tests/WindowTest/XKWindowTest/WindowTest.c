#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Joystick.h"

#include "XKinetic/Resources/Loaders/ImageLoader.h"

struct XkApplication {
	XkApplicationConfig config;

	XkWindow window;
	XkJoystick joystick1;
	XkJoystick joystick2;

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

		if(key == XK_KEY_C) {
			xkSetWindowCursorMode(window, XK_CURSOR_NORMAL);
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
	xkLogNotice("close");
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

static void __xkWindowDropFile(XkWindow window, const XkSize count, const XkString* paths) {
	for(XkSize i = 0; i < count; i++) {
		xkLogNotice("file[%ld]: %s", i, paths[i]);
	}
}

static void __xkJoystickEvent(XkJoystick joystick, const XkJoystickEvent event) {
	const XkJoystickID id = xkJoystickID(joystick);

	if(event == XK_JOYSTICK_CONNECTED) {
		xkLogNotice("joystick%d disconnected", id);
	} else if(event == XK_JOYSTICK_DISCONNECTED) {
		xkLogNotice("joystick%d disconnected", id);
	}
}

static void __xkJoystickAxis(XkJoystick joystick, const XkJoystickAxis axis, const XkFloat32 value) {
	const XkJoystickID id = xkJoystickID(joystick);

	xkLogNotice("joystick%d axis: %d: value: %d", axis, value);
}

static void __xkJoystickButton(XkJoystick joystick, const XkJoystickButton button, const XkJoystickAction action) {
	const XkJoystickID id = xkJoystickID(joystick);

	xkLogNotice("joystick%d button: %d: action: %d", button, action);
}

static void __xkJoystickHat(XkJoystick joystick, const XkJoystickHat hat, const XkJoystickAction action) {
	const XkJoystickID id = xkJoystickID(joystick);

	xkLogNotice("joystick%d hat: %d: action: %d", hat, action);
}

XkResult xkCreateApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKWindowTest";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;
	_xkApplication.exit = XK_FALSE;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) goto _catch;

	result = xkInitializeWindow();
	if(result != XK_SUCCESS) goto _catch;

	result = xkInitializeJoysticks();
	if (result != XK_SUCCESS) goto _catch;

	result = xkCreateJoystick(&_xkApplication.joystick1, XK_JOYSTICK_1);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create joystick1: %d", result);
	} else {
		xkSetJoystickEventCallback(_xkApplication.joystick1, __xkJoystickEvent);
		xkSetJoystickAxisCallback(_xkApplication.joystick1, __xkJoystickAxis);	
		xkSetJoystickButtonCallback(_xkApplication.joystick1, __xkJoystickButton);
		xkSetJoystickHatCallback(_xkApplication.joystick1, __xkJoystickHat);
	}

	result = xkCreateJoystick(&_xkApplication.joystick2, XK_JOYSTICK_2);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create joystick2: %d", result);
	} else {
		xkSetJoystickEventCallback(_xkApplication.joystick1, __xkJoystickEvent);
		xkSetJoystickAxisCallback(_xkApplication.joystick1, __xkJoystickAxis);	
		xkSetJoystickButtonCallback(_xkApplication.joystick1, __xkJoystickButton);
		xkSetJoystickHatCallback(_xkApplication.joystick1, __xkJoystickHat);
	}	

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.config.name, 1280, 720, XK_WINDOW_DECORATED_BIT | XK_WINDOW_RESIZABLE_BIT | XK_WINDOW_DRAG_DROP_BIT);
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
	xkSetWindowDropFileCallback(_xkApplication.window, __xkWindowDropFile);

	/*
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
	}

	// Load window small icon.
	XkImageConfig smallIconConfig;
	result = xkLoadImage(_xkApplication.imageLoader, &smallIconConfig, "XKineticIcon.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window small icon");	
	}

	// Load window small icon.
	XkImageConfig cursorConfig;
	result = xkLoadImage(_xkApplication.imageLoader, &cursorConfig, "XKineticCursor.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load window cursor");
	}

	// Set window icon.
	XkWindowIcon icon = {0};
	icon.width				= iconConfig.width;
	icon.height 			= iconConfig.height;
	icon.pixels 			= iconConfig.pixels;

	XkWindowIcon smallIcon 	= {0};
	smallIcon.width 				= smallIconConfig.width;
	smallIcon.height 				= smallIconConfig.height;
	smallIcon.pixels 				= smallIconConfig.pixels;

	XkWindowIcon icons[2] = {icon, smallIcon};
	xkSetWindowIcon(_xkApplication.window, 2, icons);

	// Set window cursor.
	XkWindowIcon cursorIcon = {0};
	cursorIcon.width = cursorConfig.width;
	cursorIcon.height = cursorConfig.height;
	cursorIcon.pixels = cursorConfig.pixels;

	xkSetWindowCursor(_xkApplication.window, &cursorIcon);

	// Unload window cursor.
	xkUnloadImage(_xkApplication.imageLoader, &cursorConfig);

	// Unload window icon.
	xkUnloadImage(_xkApplication.imageLoader, &iconConfig);

	// Unload window small icon.
	xkUnloadImage(_xkApplication.imageLoader, &smallIconConfig);
*/
_catch:
	return(result);
}

void xkDestroyApplication(void) {
	if(_xkApplication.joystick1) {
		xkDestroyJoystick(_xkApplication.joystick1);
	}

	if(_xkApplication.joystick2) {
		xkDestroyJoystick(_xkApplication.joystick2);
	}

	xkDestroyWindow(_xkApplication.window);

	xkTerminateJoysticks();

	xkTerminateWindow();

	xkTerminateLog();
}

void xkUpdateApplication(void) {
	while(_xkApplication.exit == XK_FALSE) {
		// Poll window events.
		xkPollWindowEvents();

		xkLogNotice("update");

		// Poll joysticks events.
		//if(_xkApplication.joystick1) {
		//	xkPollJoystickEvents(_xkApplication.joystick1);
		//}

		//if(_xkApplication.joystick2) {
		//	xkPollJoystickEvents(_xkApplication.joystick2);
		//}
	}
}

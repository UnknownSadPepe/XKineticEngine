/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Application.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
XkApplication _xkApplication;

/* ########## FUNCTIONS SECTION ########## */
static void __xkWindowClose(XkWindow window) {
	xkAssert(window);

	_xkApplication.exit = XK_TRUE;
}

static void __xkWindowSize(XkWindow window, XkSize width, XkSize height) {
	xkAssert(window);
	xkAssert(width > 0);
	xkAssert(height > 0);

	//xkResizeRenderer(_xkApplication.renderer, width, height);
}

XkResult xkInitializeApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.name = "XKVulkanTest";
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

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.name, 1280, 720, XK_WINDOW_HINT_DECORATED_BIT | XK_WINDOW_HINT_RESIZABLE_BIT);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create window: %d", result);
		goto _catch;
	}

	xkSetWindowCloseCallback(_xkApplication.window, __xkWindowClose);
	xkSetWindowSizeCallback(_xkApplication.window, __xkWindowSize);

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_MAXIMIZED);

	result = xkInitializeRenderer(XK_RENDERER_API_VULKAN);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize renderer: %d", result);
		goto _catch;
	}	

	result = xkCreateRenderer(&_xkApplication.renderer, _xkApplication.window, XK_RENDERER_HINT_DEPTH_TEST_BIT | XK_RENDERER_HINT_STENCIL_TEST_BIT | XK_RENDERER_HINT_SCISSOR_TEST_BIT);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create renderer: %d", result);
		goto _catch;
	}

	xkClearColorRenderer(_xkApplication.renderer, (XkVec4){{1.0f, 0.0f, 0.0f, 1.0f}});
	xkClearDepthRenderer(_xkApplication.renderer, (XkFloat64)1.0);
	xkClearStencilRenderer(_xkApplication.renderer, (XkInt32)0.0);

_catch:
	return(result);
}

void xkTerminateApplication() {
	xkDestroyRenderer(_xkApplication.renderer);

	xkDestroyWindow(_xkApplication.window);

	xkTerminateRenderer();

	xkTerminateWindow();

	xkTerminateLog();
}

void xkUpdateApplication() {
	while(!_xkApplication.exit) {
		xkPollWindowEvents();

		xkClearRenderer(_xkApplication.renderer);

		xkBeginRenderer(_xkApplication.renderer);

		/// TODO: Draw scene.

		xkEndRenderer(_xkApplication.renderer);
	}
}

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/Renderer.h"

/* ########## TYPES SECTION ########## */
struct XkApplication_T {
	XkApplicationConfig config;

	XkWindow window;
	XkRenderer renderer;

	XkBool exit;
};

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

	xkResizeRenderer(_xkApplication.renderer, width, height);
}

XkResult xkInitializeApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKD3D12Test";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;
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

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.config.name, 1280, 720, XK_WINDOW_HINT_DECORATED_BIT | XK_WINDOW_HINT_RESIZABLE_BIT);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create window: %d", result);
		goto _catch;
	}

	xkSetWindowCloseCallback(_xkApplication.window, __xkWindowClose);
	xkSetWindowSizeCallback(_xkApplication.window, __xkWindowSize);

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_MAXIMIZED);

	XkRendererConfig rendererConfig = {};
	rendererConfig.blending 				= XK_FALSE;
	rendererConfig.depthTest 				= XK_TRUE;
	rendererConfig.stencilTest 			= XK_TRUE;
	rendererConfig.scissorTest 			= XK_TRUE;

	result = xkInitializeRenderer();
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize renderer: %d", result);
		goto _catch;
	}	

	result = xkCreateRenderer(&_xkApplication.renderer, &rendererConfig, _xkApplication.window, XK_RENDERER_API_D3D12);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create renderer: %d", result);
		goto _catch;
	}

	xkClearColorRenderer(_xkApplication.renderer, (XkVec4){1.0f, 0.0f, 0.0f, 1.0f});
	xkClearDepthRenderer(_xkApplication.renderer, (XkFloat64)1.0);
	xkClearStencilRenderer(_xkApplication.renderer, (XkInt32)0.0);

_catch:
	return(result);
}

void xkTerminateApplication() {
	xkDestroyRenderer(_xkApplication.renderer);

	xkDestroyWindow(_xkApplication.window);

	xkTeminateRenderer();

	xkTerminateWindow();

	xkTerminateLog();
}

void xkUpdateApplication() {
	while(!_xkApplication.exit) {
		xkPollEvents();
		
		xkClearRenderer(_xkApplication.renderer);

		xkBeginRenderer(_xkApplication.renderer);

		/// TODO: Draw scene.

		xkEndRenderer(_xkApplication.renderer);
	}
}

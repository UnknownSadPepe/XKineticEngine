#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/Renderer.h"

struct XkApplication {
	XkApplicationConfig config;

	XkWindow window;
	XkRenderer renderer;

	XkBool exit;
};

XkApplication _xkApplication;

static void __xkWindowClose(XkWindow window) {
	_xkApplication.exit = XK_TRUE;
}

static void __xkWindowSize(XkWindow window, XkSize width, XkSize height) {
	xkResizeRenderer(_xkApplication.renderer, width, height);
}

XkResult xkCreateApplication(const XkSize argc, const XkWString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKVulkanTest";
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

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_DEFAULT);

	xkSetWindowCloseCallback(_xkApplication.window, __xkWindowClose);
	xkSetWindowSizeCallback(_xkApplication.window, __xkWindowSize);

	XkRendererConfig rendererConfig = {
		.blending = XK_FALSE,
		.depthTest = XK_TRUE,
		.stencilTest = XK_TRUE,
		.scissorTest = XK_TRUE
	};

	result = xkCreateRenderer(&_xkApplication.renderer, &rendererConfig, _xkApplication.window, XK_RENDERER_API_VK);
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

void xkDestroyApplication() {
	xkDestroyWindow(_xkApplication.window);
	xkDestroyRenderer(_xkApplication.renderer);

	xkWindowTerminate();

	xkLogTerminate();
}

void xkUpdateApplication() {
	while(!_xkApplication.exit) {
		xkClearRenderer(_xkApplication.renderer);

		xkBeginRenderer(_xkApplication.renderer);

		// Draw scene.

		xkEndRenderer(_xkApplication.renderer);

		// Poll window events.
		xkPollWindowEvents();
	}
}

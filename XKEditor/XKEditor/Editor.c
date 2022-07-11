/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Application.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/Renderer.h"

#include <math.h>

/* ########## GLOBAL VARIABLES SECTION ########## */
XkApplication _xkApplication;

/* ########## FUNCTIONS SECTION ########## */
static void __xkWindowClose(XkWindow window) {
	xkAssert(window);

	_xkApplication.exit = XK_TRUE;
}

static void __xkWindowDropFile(XkWindow window, const XkSize count, const XkString* files) {
	xkAssert(window);
}

XkResult xkInitializeApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.name = "XKEditor";
	_xkApplication.version.major = 0;
	_xkApplication.version.minor = 0;
	_xkApplication.version.patch = 1;
	_xkApplication.exit = XK_FALSE;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize log: %d", result);
		goto _catch;
	}

	xkLogNotice("xkSqrt(9.0f) = %f", xkSqrt(9.0f));

  xkLogNotice("ceil(+2.4) = %+.1f", ceil(2.4));
  xkLogNotice("ceil(-2.4) = %+.1f", ceil(-2.4));
  xkLogNotice("ceil(-0.0) = %+.1f", ceil(-0.0));
  xkLogNotice("ceil(-Inf) = %+f",   ceil(-INFINITY));

  xkLogNotice("xkCeil(+2.4) = %+.1f", xkCeil(2.4));
  xkLogNotice("xkCeil(-2.4) = %+.1f", xkCeil(-2.4));
  xkLogNotice("xkCeil(-0.0) = %+.1f", xkCeil(-0.0));
  xkLogNotice("xkCeil(-Inf) = %+f",   xkCeil(-INFINITY));

/*
  xkLogNotice("fmod(+5.1, +3.0) = %f\n", fmod(5.1,3));
  xkLogNotice("fmod(-5.1, +3.0) = %f\n", fmod(-5.1,3));
  xkLogNotice("fmod(+5.1, -3.0) = %f\n", fmod(5.1,-3));
  xkLogNotice("fmod(-5.1, -3.0) = %f\n", fmod(-5.1,-3)); 
  xkLogNotice("xkFMod(+5.1, +3.0) = %f\n", xkMod(5.1,3));
  xkLogNotice("xkFMod(-5.1, +3.0) = %f\n", xkMod(-5.1,3));
  xkLogNotice("xkFMod(+5.1, -3.0) = %f\n", xkMod(5.1,-3));
  xkLogNotice("xkFMod(-5.1, -3.0) = %f\n", xkMod(-5.1,-3)); 
*/
/*
	result = xkInitializeWindow();
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to initialize window: %d", result);
		goto _catch;
	}

	result = xkCreateWindow(&_xkApplication.window, _xkApplication.name, 1280, 720, XK_WINDOW_HINT_DECORATED_BIT | XK_WINDOW_HINT_RESIZABLE_BIT);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create window");
		goto _catch;
	}

	xkSetWindowCloseCallback(_xkApplication.window, __xkWindowClose);
	xkSetWindowDropFileCallback(_xkApplication.window, __xkWindowDropFile);

	xkShowWindow(_xkApplication.window, XK_WINDOW_SHOW_MAXIMIZED);
	

	result = xkInitializeRenderer(XK_RENDERER_API_DEFAULT);
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
*/
_catch:
	return(result);
}

void xkTerminateApplication(void) {
	/*
	xkDestroyRenderer(_xkApplication.renderer);

	xkDestroyWindow(_xkApplication.window);

	xkTerminateRenderer();

	xkTerminateWindow();
*/
	xkTerminateLog();
}

void xkUpdateApplication(void) {
	//while(!_xkApplication.exit) {
		//xkPollWindowEvents();

		//xkClearRenderer(_xkApplication.renderer);

		//xkBeginRenderer(_xkApplication.renderer);

		/// TODO: Draw scene.

		//xkEndRenderer(_xkApplication.renderer);
	//}
}

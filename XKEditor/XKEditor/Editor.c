#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"

#include <string.h>

struct XkApplication {
	XkApplicationConfig config;
};

XkApplication _xkApplication;

XkResult xkCreateApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKEditor";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyApplication(void) {
	xkTerminateLog();
}

void xkUpdateApplication(void) {

}

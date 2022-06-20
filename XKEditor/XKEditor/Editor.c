#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"

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

	XkFreeList freelist;
	result = xkCreateFreeList(&freelist, sizeof(XkUInt32) * 16);
	if(result != XK_SUCCESS) {
		xkLogError("failed to create freelist");
		goto _catch;
	}

	XkUInt32* p1 = xkFreeListAllocate(freelist, sizeof(XkUInt32));
	xkLogInfo("[%p] %d", p1, *p1);

	XkUInt32* p2 = xkFreeListAllocate(freelist, sizeof(XkUInt32) * 10);
	for (XkSize i = 0; i < 10; i++) {
		xkLogInfo("[%p] %d", &p2[i], p2[i]);
	}

	XkUInt32* p3 = xkFreeListAllocate(freelist, sizeof(XkUInt32) * 4);
	for (XkSize i = 0; i < 4; i++) {
		xkLogInfo("[%p] %d", &p3[i], p3[i]);
	}

	xkFreeListFree(freelist, p2);
	xkFreeListFree(freelist, p1);

	xkDestroyFreeList(freelist);

_catch:
	return(result);
}

void xkDestroyApplication(void) {
	xkTerminateLog();
}

void xkUpdateApplication(void) {
	while(XK_TRUE) {
		/// TODO: implementation.
	}
}

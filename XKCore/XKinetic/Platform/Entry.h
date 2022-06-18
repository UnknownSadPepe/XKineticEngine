#pragma once

#include "XKinetic/XKCore.h"

#if defined(XK_LINUX)
	#include "XKinetic/Platform/Linux/Entry.h"
#elif defined(XK_WIN32)
	#include "XKinetic/Platform/Win32/Entry.h"
#endif // XK_LINUX
#include "XKinetic/Application.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XkResult __xkEntry(const XkSize argc, const XkWString* argv) {
	XkResult result = XK_SUCCESS;

	result = xkCreateApplication(argc, argv);
	if(result != XK_SUCCESS) goto _catch;

	xkUpdateApplication();

	xkDestroyApplication();

_catch:
	return(result);
}

#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#if defined(XK_POSIX)
	#include "XKinetic/Platform/Posix/Entry.h"
#elif defined(XK_WINDOWS)
	#include "XKinetic/Platform/Win32/Entry.h"
#endif // XK_LINUX
#include "XKinetic/Application.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
	
/* ########## FUNCTIONS SECTION ########## */
XkResult __xkEntry(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	result = xkInitializeApplication(argc, argv);
	if(result != XK_SUCCESS) goto _catch;

	xkUpdateApplication();

	xkTerminateApplication();

_catch:
	return(result);
}

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

#include "XKinetic/Platform/Entry.h"
#include "XKinetic/Application.h"

XkResult __xkEntry(const XkSize argc, const XkChar8** argv) {
	XkResult result = XK_SUCCESS;

	result = xkCreateApplication(argc, argv);
	if(result != XK_SUCCESS) goto _catch;

	xkUpdateApplication();

	xkDestroyApplication();

_catch:
	return(result);
}

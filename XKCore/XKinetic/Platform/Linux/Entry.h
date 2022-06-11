#pragma once

#include "XKinetic/XKCore.h"

extern XK_IMPORT XkResult __xkEntry(const XkSize, const XkWString*);

int wmain(int argc, wchar_t** argv) {
	int res = 0;

	XkResult result = __xkEntry((const XkSize)argc, (const XkWString*)argv);
	if(result != XK_SUCCESS) {
		res = 1;
		goto _catch;
	}

_catch:
	return(res);
}

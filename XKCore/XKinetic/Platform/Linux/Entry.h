#pragma once

#include "XKinetic/XKCore.h"

extern XK_IMPORT XkResult __xkEntry(const XkSize, const XkChar8**);

int main(int argc, char** argv) {
	int res = 0;

	XkResult result = __xkEntry((const XkSize)argc, (const XkChar8**)argv);
	if(result != XK_SUCCESS) {
		res = 1;
		goto _catch;
	}

_catch:
	return(res);
}

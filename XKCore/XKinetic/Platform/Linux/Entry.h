#pragma once

#include <stdlib.h>
#include "XKinetic/XKCore.h"

extern XK_API_IMPORT XkResult __xkEntry(const XkSize, const XkChar8**);

int main(int argc, char** argv) {
	int res = EXIT_SUCCESS;

	XkResult result = __xkEntry((const XkSize)argc, (const XkChar8**)argv);
	if(result != XK_SUCCESS) {
		res = EXIT_FAILURE;
		goto _catch;
	}

_catch:
	return(res);
}

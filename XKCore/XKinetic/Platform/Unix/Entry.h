#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/* ########## FUNCTIONS SECTION ########## */
extern XkResult __xkEntry(const XkSize, const XkString*);

int main(int argc, char** argv) {
	int res = 0;

	XkResult result = __xkEntry((const XkSize)argc, (const XkString*)argv);
	if(result != XK_SUCCESS) {
		res = 1;
		goto _catch;
	}

_catch:
	return(res);
}

#pragma once

#include <windows.h>
#include "XKinetic/XKCore.h"

extern XK_IMPORT XkResult __xkEntry(const XkSize, const XkChar8**);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR cmdline, INT cmdshow) {
	int res = EXIT_SUCCESS;

  int argc = 0;
  LPWSTR* wArgv = CommandLineToArgvW(GetCommandLineW(), &argc);

	XkResult result = __xkEntry((const XkSize)argc, (const XkChar8**)wArgv);
	if(result != XK_SUCCESS) {
		res = EXIT_FAILURE;
		goto _catch;
	}

_catch:
	LocalFree(wArgv);
	return(res);
}

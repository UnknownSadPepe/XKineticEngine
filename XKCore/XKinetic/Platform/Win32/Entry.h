#pragma once

#include <stdio.h>
#include <windows.h>
#include "XKinetic/XKCore.h"

extern XK_IMPORT XkResult __xkEntry(const XkSize, const XkString*);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, INT nCmdShow) {
	int res = EXIT_SUCCESS;

	AllocConsole();

	int argc;
	/// TODO: CommandLineToArgvA().
	LPWSTR* wArgv = CommandLineToArgvW(GetCommandLineW(), &argc);

	XkResult result = __xkEntry((const XkSize)argc, (const XkString*)wArgv);
	if(result != XK_SUCCESS) {
		res = EXIT_FAILURE;
		goto _catch;
	}

_catch:
	FreeConsole();
	LocalFree(wArgv);

	return(res);
}

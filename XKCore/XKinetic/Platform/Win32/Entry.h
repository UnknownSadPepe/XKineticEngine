#pragma once

#include <stdio.h>
#include <windows.h>
#include "XKinetic/XKCore.h"

extern XkResult __xkEntry(const XkSize, const XkString*);

INT CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ INT nCmdShow) {
	int res = EXIT_SUCCESS;

	AllocConsole();
	
	int argc;
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

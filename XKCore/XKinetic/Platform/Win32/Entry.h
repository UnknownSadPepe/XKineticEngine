#pragma once

/* ########## INCLUDE SECTION ########## */
#if _WIN32_WINNT < 0x0501
	#define _WIN32_WINNT 0x0501
#endif // _WIN32_WINNT < 0x0501
#include <windows.h>
#include "XKinetic/XKCore.h"

/* ########## FUNCTIONS SECTION ########## */
extern XkResult __xkEntry(const XkSize, const XkString*);

INT CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR pCmdLine, _In_ INT nCmdShow) {
	int res = EXIT_SUCCESS;

	AttachConsole(ATTACH_PARENT_PROCESS);
	
	int argc;
	LPWSTR* wArgv = CommandLineToArgvW(GetCommandLineW(), &argc);

	XkString* argv = XK_NULL_HANDLE;
	argv = xkAllocateMemory(sizeof(XkChar*) * argc);

	for(int i = 0; i < argc; i++) {
		LPWSTR wArg = wArgv[i];

		int size = WideCharToMultiByte(CP_UTF8, 0, wArg, -1, NULL, 0, NULL, NULL);
  	if(size <= 0) {
    	__xkErrorHandle("Win32: Failed to convert wide string to UTF-8");
    	return(NULL);
  	}

  	CHAR* arg = xkAllocateMemory(size * sizeof(CHAR));

  	if(!WideCharToMultiByte(CP_UTF8, 0, wArg, -1, arg, size, NULL, NULL)) {
    	__xkErrorHandle("Win32: Failed to convert wide string to UTF-8");
    	xkFreeMemory(arg);
    	return(NULL);
  	}

  	argv[i] = arg;
	}

	XkResult result = __xkEntry((const XkSize)argc, (const XkString*)argv);
	if(result != XK_SUCCESS) {
		res = EXIT_FAILURE;
		goto _catch;
	}

_catch:
	for(int i = 0; i < argc; i++) {
		xkFreeMemory(argv[i]);
	}

	if(argv) {
		xkFreeMemory(argv);
	}
	LocalFree(wArgv);

	return(res);
}

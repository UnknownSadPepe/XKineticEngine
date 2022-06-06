#pragma once

#include <windows.h>
#include "XKinetic/XKCore.h"

extern XK_IMPORT XkResult __xkEntry(const XkSize, const XkChar8**);

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instance, PSTR cmdline, INT cmdshow) {
  int argc = 0;
  LPSTR* argv = CommandLineToArgvA(GetCommandLineA(), &argc);

	XkResult result = __xkEntry((const XkSize)argc, (const XkChar8**)argv);
	if(result != KSUCCESS) goto _catch;

	return(EXIT_SUCCESS);

_catch:
	return(EXIT_FAILURE);
}

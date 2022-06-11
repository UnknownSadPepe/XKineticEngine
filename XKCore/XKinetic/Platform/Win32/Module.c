#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>

XkResult xkLoadModule(XkModule* pModule, const XkString path) {
	XkResult result = XK_SUCCESS;

	*pModule = (XkModule)LoadLibraryA(path);
	if(!(*pModule)) {
		__xkErrorHandle("Win32: Failed to load module");
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	FreeLibrary((HMODULE)module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkString name, XkModule module) {
	XkResult result = XK_SUCCESS;

	*pPfnProc = (XkProcPfn)GetProcAddress((HMODULE)module, name);
	if(!(*pPfnProc)) {
		__xkErrorHandle("Win32: Failed to get module symbol");
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN32

#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>

XkResult xkLoadModule(XkModule* pModule, const XkChar8* path) {
	XkResult result = XK_SUCCESS;

	*pModule = (XkModule)LoadLibraryA(path);
	if(!(*pModule)) {
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	FreeLibrary((HMODULE)module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkChar8* name, XkModule module) {
	XkResult result = XK_SUCCESS;

	*pPfnProc = (XkProcPfn)GetProcAddress((HMODULE)module, name);
	if(!(*pPfnProc)) {
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN32


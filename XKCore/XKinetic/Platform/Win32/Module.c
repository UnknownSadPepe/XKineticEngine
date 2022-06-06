#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Linux/Internal.h"

XkResult xkLoadModule(XkModule module, const XkChar8* path) {
	XkResult result = XK_SUCCESS;

	module = (XkHandle)LoadLibraryA(path);
	if(!module) {
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	FreeLibrary((HMODULE)module);
}

XkResult xkGetModuleSymbol(XkProcPfn pfnProc, const XkChar8* name, XkModule module) {
	XkResult result = XK_SUCCESS;

	pfnProc = (XkProcPfn)GetProcAddress((HMODULE)module, name);
	if(!pfnProc) {
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN32


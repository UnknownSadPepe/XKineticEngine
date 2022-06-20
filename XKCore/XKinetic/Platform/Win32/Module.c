#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>

XkResult xkLoadModule(XkModule* pModule, const XkString path) {
	XkResult result = XK_SUCCESS;

	// Allocate module.
	*pModule = xkAllocateMemory(sizeof(struct XkModule));
	if(!(*pModule)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template module.
	XkModule module = *pModule;

	// Load Win32 library.
	module->win32.handle = LoadLibraryA(path);
	if(module->win32.handle == NULL) {
		xkFreeMemory(module);
		__xkErrorHandle("Win32: Failed to load module");
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	// Free Win32 linbary.
	FreeLibrary(module->win32.handle);

	// Free module.
	xkFreeMemory(module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkString name, XkModule module) {
	XkResult result = XK_SUCCESS;

	// Get Win32 process adress.
	*pPfnProc = (XkProcPfn)GetProcAddress(module->win32.handle, name);
	if(*pPfnProc == NULL) {
		__xkErrorHandle("Win32: Failed to get module symbol");
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN32

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Module.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult xkLoadModule(XkModule* pModule, const XkString path) {
	xkAssert(pModule);

	XkResult result = XK_SUCCESS;

	*pModule = xkAllocateMemory(sizeof(struct XkModule_T));
	if(!(*pModule)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkModule module = *pModule;

	module->windows.winapi.handle = LoadLibraryA(path);
	if(module->windows.winapi.handle == NULL) {
		__xkErrorHandle("Win32: Failed to load module");
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _free;
	}

_catch:
	return(result);

_free:
	if(module) {
		xkFreeMemory(module);
	}

	goto _catch;
}

void xkUnloadModule(XkModule module) {
	xkAssert(module);

	FreeLibrary(module->windows.winapi.handle);

	xkFreeMemory(module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkString name, XkModule module) {
	xkAssert(pPfnProc);
	xkAssert(module);

	XkResult result = XK_SUCCESS;

	*pPfnProc = (XkProcPfn)GetProcAddress(module->windows.winapi.handle, name);
	if(*pPfnProc == NULL) {
		__xkErrorHandle("Win32: Failed to get module symbol");
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Module.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

#include <dlfcn.h>

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

	module->posix.handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);
	if(!(*pModule)) {
		__xkErrorHandle("Posix: Failed to load module");
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	xkAssert(module);

	dlclose(module->posix.handle);

	xkFreeMemory(module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkString name, XkModule module) {
	xkAssert(pPfnProc);
	xkAssert(module);

	XkResult result = XK_SUCCESS;

	*pPfnProc = (XkProcPfn)dlsym(module->posix.handle, name);
	if(!(*pPfnProc)) {
		__xkErrorHandle("Posix: Failed to get module symbol");
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

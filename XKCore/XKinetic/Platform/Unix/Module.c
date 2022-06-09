#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Module.h"

#if defined(XK_UNIX)

#include <dlfcn.h>

XkResult xkLoadModule(XkModule* pModule, const XkChar8* path) {
	XkResult result = XK_SUCCESS;

	*pModule = (XkModule)dlopen(path, RTLD_LAZY | RTLD_LOCAL);
	if(!(*pModule)) {
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	dlclose(module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkChar8* name, XkModule module) {
	XkResult result = XK_SUCCESS;

	*pPfnProc = (XkProcPfn)dlsym(module, name);
	if(!(*pPfnProc)) {
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_UNIX

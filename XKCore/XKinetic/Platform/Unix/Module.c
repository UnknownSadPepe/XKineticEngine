#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Module.h"

#if defined(XK_UNIX)

#include <dlfcn.h>

XkResult xkLoadModule(XkModule* pModule, const XkString path) {
	XkResult result = XK_SUCCESS;

	*pModule = (XkModule)dlopen(path, RTLD_LAZY | RTLD_LOCAL);
	if(!(*pModule)) {
		__xkErrorHandle("Unix: Failed to load module");
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

void xkUnloadModule(XkModule module) {
	dlclose(module);
}

XkResult xkGetModuleSymbol(XkProcPfn* pPfnProc, const XkString name, XkModule module) {
	XkResult result = XK_SUCCESS;

	*pPfnProc = (XkProcPfn)dlsym(module, name);
	if(!(*pPfnProc)) {
		__xkErrorHandle("Unix: Failed to get module symbol");
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_UNIX

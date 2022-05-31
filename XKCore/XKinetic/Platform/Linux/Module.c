#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_LINUX)

#include <dlfcn.h>
#include "XKinetic/Platform/Linux/Internal.h"

XkModule __xkLoadModule(const XkChar8* path) {
	return(dlopen(path, RTLD_LAZY | RTLD_LOCAL));
}

void __xkFreeModule(XkModule module) {
	dlclose(module);
}

XkProcPfn __xkGetModuleSymbol(XkModule module, const XkChar8* name) {
	return(dlsym(module, name));
}

#endif // XK_PLATFORM_LINUX


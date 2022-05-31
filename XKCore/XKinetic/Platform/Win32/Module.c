#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Linux/Internal.h"

XkModule __xkLoadModule(const XkChar8* path) {
	return(LoadLibraryA(path));
}

void __xkFreeModule(XkModule module) {
	FreeLibrary((HMODULE)module);
}

XkProcPfn __xkGetModuleSymbol(XkModule module, const XkChar8* name) {
	return((XkProcPfn)GetProcAddress((HMODULE)module, name));
}

#endif // XK_PLATFORM_WIN32


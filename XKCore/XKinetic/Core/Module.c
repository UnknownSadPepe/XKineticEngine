#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/Module.h"

XkModule xkLoadModule(const XkChar8* path) {
	return(__xkLoadModule(path));
}

void xkFreeModule(XkModule module) {
	__xkFreeModule(module);
}

XkProcPfn xkGetModuleSymbol(XkModule module, const XkChar8* name) {
	return(__xkGetModuleSymbol(module, name));
}

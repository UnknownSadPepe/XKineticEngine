#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/External.h"

XKCORE_API XkModule xkLoadModule(const XkChar8*);
XKCORE_API void xkFreeModule(XkModule);
XKCORE_API XkProcPfn xkGetModuleSymbol(XkModule, const XkChar8*);


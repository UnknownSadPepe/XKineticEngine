#pragma once

#include "XKinetic/XKCore.h"

typedef XkHandle XkModule;
typedef void(*XkProcPfn)(void);

XK_EXPORT XkResult xkLoadModule(XkModule, const XkChar8*);
XK_EXPORT void xkUnloadModule(XkModule);
XK_EXPORT XkResult xkGetModuleSymbol(XkProcPfn, const XkChar8*, XkModule);

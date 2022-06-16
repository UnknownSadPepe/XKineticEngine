#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkModule* XkModule;
typedef void(*XkProcPfn)(void);

XK_EXPORT XkResult xkLoadModule(XkModule*, const XkString);
XK_EXPORT void xkUnloadModule(XkModule);
XK_EXPORT XkResult xkGetModuleSymbol(XkProcPfn*, const XkString, XkModule);

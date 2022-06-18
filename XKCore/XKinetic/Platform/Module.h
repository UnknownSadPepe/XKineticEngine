#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkModule* XkModule;
typedef void(*XkProcPfn)(void);

XK_EXPORT XkResult xkLoadModule(XkModule*, const XkString);
XK_EXPORT void xkUnloadModule(XkModule);
XK_EXPORT XkResult xkGetModuleSymbol(XkProcPfn*, const XkString, XkModule);

#ifdef __cplusplus
}
#endif // __cplusplus

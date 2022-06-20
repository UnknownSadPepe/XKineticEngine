#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkModule* XkModule;
typedef void(*XkProcPfn)(void);

XKCORE_API XkResult xkLoadModule(XkModule*, const XkString);
XKCORE_API void xkUnloadModule(XkModule);
XKCORE_API XkResult xkGetModuleSymbol(XkProcPfn*, const XkString, XkModule);

#ifdef __cplusplus
}
#endif // __cplusplus

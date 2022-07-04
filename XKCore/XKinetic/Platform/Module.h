#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkModule_T* XkModule;
typedef void(*XkProcPfn)(void);

/* ########## FUNCTIONS SECTION ########## */
XKCORE_API XkResult 	xkLoadModule(XkModule*, const XkString);
XKCORE_API void 			xkUnloadModule(XkModule);
XKCORE_API XkResult 	xkGetModuleSymbol(XkProcPfn*, const XkString, XkModule);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef void(*XkProcPfn)(void);
typedef struct XkModule_T* XkModule;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	xkLoadModule(XkModule*, const XkString);
extern XKCORE_API void 			xkUnloadModule(XkModule);
extern XKCORE_API XkResult 	xkGetModuleSymbol(XkProcPfn*, const XkString, XkModule);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Model.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkModelLoader_T* XkModelLoader;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkCreateModelLoader(XkModelLoader*, XkString);
extern XK_API void				xkDestroyModelLoader(XkModelLoader);
extern XK_API XkResult		xkLoadModel(XkModelLoader, XkModelConfig* const, XkString);
extern XK_API void				xkUnloadModel(XkModelLoader, const XkModelConfig* const);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

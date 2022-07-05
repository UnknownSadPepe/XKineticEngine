#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Model.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkInitializeModelLoader(XkString);
extern XK_API void				xkTerminateModelLoader();
extern XK_API XkResult		xkLoadModel(XkModelConfig* const, XkString);
extern XK_API void				xkUnloadModel(const XkModelConfig* const);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

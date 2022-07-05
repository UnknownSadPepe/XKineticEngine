#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Shader.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkInitializeShaderLoader(XkString);
extern XK_API void				xkTerminateShaderLoader();
extern XK_API XkResult		xkLoadShader(XkShaderConfig* const, XkString);
extern XK_API void				xkUnloadShader(const XkShaderConfig* const);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

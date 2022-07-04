#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Shader.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkShaderLoader_T* XkShaderLoader;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult 	xkCreateShaderLoader(XkShaderLoader*, XkString);
extern XK_API void 			xkDestroyShaderLoader(XkShaderLoader);
extern XK_API XkResult 	xkLoadShader(XkShaderLoader, XkShaderConfig* const, XkString);
extern XK_API void 			xkUnloadShader(XkShaderLoader, XkShaderConfig* const);

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

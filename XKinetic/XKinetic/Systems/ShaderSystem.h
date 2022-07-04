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
typedef XkUInt64 XkShaderId;

typedef struct XkShader_T* XkShader;

typedef struct XkShaderSystem_T* XkShaderSystem;

extern XK_API XkResult			xkCreateShaderSystem(XkShaderSystem*);
extern XK_API void					xkDestroyShaderSystem(XkShaderSystem);
extern XK_API XkShaderId		xkCreateShader(XkShaderSystem, const XkShaderConfig* const);
extern XK_API void					xkDestroyShader(XkShaderSystem, const XkShaderId);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

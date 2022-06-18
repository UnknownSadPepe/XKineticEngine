#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Shader.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef XkUInt64 XkShaderID;

typedef struct XkShaderSystem* XkShaderSystem;

XK_API XkResult xkCreateShaderSystem(XkShaderSystem*);
XK_API void xkDestroyShaderSystem(XkShaderSystem);
XK_API XkShaderID xkCreateShader(XkShaderSystem, XkShaderConfig* const);
XK_API void xkDestroyShader(XkShaderSystem, XkShaderID);

#ifdef __cplusplus
}
#endif // __cplusplus

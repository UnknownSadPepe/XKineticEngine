#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Shader.h"

typedef struct XkShaderLoader* XkShaderLoader;

XK_API XkResult xkCreateShaderLoader(XkShaderLoader*, XkString);
XK_API void xkDestroyShaderLoader(XkShaderLoader);
XK_API XkResult xkLoadShader(XkShaderLoader, XkShaderConfig* const, XkString);
XK_API void xkUnloadShader(XkShaderLoader, XkShaderConfig* const);

#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Model.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkModelLoader* XkModelLoader;

XK_API XkResult xkCreateModelLoader(XkModelLoader*, XkString);
XK_API void xkDestroyModelLoader(XkModelLoader);
XK_API XkResult xkLoadModel(XkModelLoader, XkModelConfig* const, XkString);
XK_API void xkUnloadModel(XkModelLoader, XkModelConfig* const);

#ifdef __cplusplus
}
#endif // __cplusplus

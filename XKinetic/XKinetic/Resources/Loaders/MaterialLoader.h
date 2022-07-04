#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Material.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkMaterialLoader* XkMaterialLoader;

XK_API XkResult xkCreateMaterialLoader(XkMaterialLoader*, XkString);
XK_API void xkDestroyMaterialLoader(XkMaterialLoader);
XK_API XkResult xkLoadMaterial(XkMaterialLoader, XkMaterialConfig* const, XkString);
XK_API void xkUnloadMaterial(XkMaterialLoader, XkMaterialConfig* const);

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

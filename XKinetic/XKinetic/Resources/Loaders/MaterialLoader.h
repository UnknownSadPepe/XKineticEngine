#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Material.h"

typedef struct XkMaterialLoader* XkMaterialLoader;

XK_API XkResult xkCreateMaterialLoader(XkMaterialLoader*, XkChar8*);
XK_API void xkDestroyMaterialLoader(XkMaterialLoader);
XK_API XkResult xkLoadMaterial(XkMaterialLoader, XkMaterialConfig* const, XkChar8*);
XK_API void xkUnloadMaterial(XkMaterialLoader, XkMaterialConfig* const);

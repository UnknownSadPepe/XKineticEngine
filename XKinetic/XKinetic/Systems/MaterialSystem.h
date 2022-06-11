#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Material.h"

typedef XkUInt64 XkMaterialID;

typedef struct XkMaterial* XkMaterial;

typedef struct XkMaterialSystem* XkMaterialSystem;

XK_API XkResult xkCreateMaterialSystem(XkMaterialSystem*);
XK_API void xkDestroyMaterialSystem(XkMaterialSystem);
XK_API XkMaterialID xkCreateMaterial(XkMaterialSystem, XkMaterialConfig* const);
XK_API void xkDestroyMaterial(XkMaterialSystem, XkMaterialID);

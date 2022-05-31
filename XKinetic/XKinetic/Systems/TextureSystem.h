#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Texture.h"

typedef XkInt32 XkTextureID;

typedef struct XkTextureSystem* XkTextureSystem;

XK_API XkResult xkCreateTextureSystem(XkTextureSystem*);
XK_API void xkDestroyTextureSystem(XkTextureSystem);
XK_API XkTextureID xkCreateTexture(XkTextureSystem, XkTextureConfig* const);
XK_API void xkDestroyTexture(XkTextureSystem, XkTextureID);

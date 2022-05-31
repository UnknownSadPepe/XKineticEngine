#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Texture.h"

typedef struct XkTextureLoader* XkTextureLoader;

XK_API XkResult xkCreateTextureLoader(XkTextureLoader*, XkChar8*);
XK_API void xkDestroyTextureLoader(XkTextureLoader);
XK_API XkResult xkLoadTexture(XkTextureLoader, XkTextureConfig* const, XkChar8*);
XK_API void xkUnloadTexture(XkTextureLoader, XkTextureConfig* const);

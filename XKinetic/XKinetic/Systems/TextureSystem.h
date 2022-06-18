#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Image.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef XkUInt64 XkTextureID;

typedef struct XkTexture* XkTexture;

typedef struct XkTextureSystem* XkTextureSystem;

XK_API XkResult xkCreateTextureSystem(XkTextureSystem*);
XK_API void xkDestroyTextureSystem(XkTextureSystem);
XK_API XkTextureID xkCreateTexture(XkTextureSystem, XkImageConfig* const);
XK_API void xkDestroyTexture(XkTextureSystem, XkTextureID);

#ifdef __cplusplus
}
#endif // __cplusplus

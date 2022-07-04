#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Image.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkUInt64 XkTextureId;

typedef struct XkTexture_T* XkTexture;

typedef struct XkTextureSystem_T* XkTextureSystem;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult			xkCreateTextureSystem(XkTextureSystem*);
extern XK_API void					xkDestroyTextureSystem(XkTextureSystem);
extern XK_API XkTextureId		xkCreateTexture(XkTextureSystem, const XkImageConfig* const);
extern XK_API void					xkDestroyTexture(XkTextureSystem, XkTextureId);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

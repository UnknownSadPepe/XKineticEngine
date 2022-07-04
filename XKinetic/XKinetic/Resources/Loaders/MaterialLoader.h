#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Material.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkMaterialLoader_T* XkMaterialLoader;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkCreateMaterialLoader(XkMaterialLoader*, XkString);
extern XK_API void				xkDestroyMaterialLoader(XkMaterialLoader);
extern XK_API XkResult		xkLoadMaterial(XkMaterialLoader, XkMaterialConfig* const, XkString);
extern XK_API void				xkUnloadMaterial(XkMaterialLoader, const XkMaterialConfig* const);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

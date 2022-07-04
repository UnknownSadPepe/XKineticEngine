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
typedef XkUInt64 XkMaterialId;

typedef struct XkMaterial_T* XkMaterial;

typedef struct XkMaterialSystem_T* XkMaterialSystem;

extern XK_API XkResult				xkCreateMaterialSystem(XkMaterialSystem*);
extern XK_API void						xkDestroyMaterialSystem(XkMaterialSystem);
extern XK_API XkMaterialId		xkCreateMaterial(XkMaterialSystem, const XkMaterialConfig* const);
extern XK_API void						xkDestroyMaterial(XkMaterialSystem, const XkMaterialId);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

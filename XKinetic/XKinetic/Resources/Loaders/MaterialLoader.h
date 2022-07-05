#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Material.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkInitializeMaterialLoader(XkString);
extern XK_API void				xkTerminateMaterialLoader();
extern XK_API XkResult		xkLoadMaterial(XkMaterialConfig* const, XkString);
extern XK_API void				xkUnloadMaterial(const XkMaterialConfig* const);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

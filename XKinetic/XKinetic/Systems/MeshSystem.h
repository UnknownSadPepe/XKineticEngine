#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Model.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkUInt64 XkMeshId;

typedef struct XkMesh_T* XkMesh;

typedef struct XkMeshSystem_T* XkMeshSystem;

extern XK_API XkResult	xkCreateMeshSystem(XkMeshSystem*);
extern XK_API void			xkDestroyMeshSystem(XkMeshSystem);
extern XK_API XkMeshId	xkCreateMesh(XkMeshSystem, const XkModelConfig* const);
extern XK_API void			xkDestroyMesh(XkMeshSystem, const XkMeshId);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

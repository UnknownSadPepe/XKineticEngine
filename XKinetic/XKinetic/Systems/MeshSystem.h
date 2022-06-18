#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Model.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef XkUInt64 XkMeshID;

typedef struct XkMesh* XkMesh;

typedef struct XkMeshSystem* XkMeshSystem;

XK_API XkResult xkCreateMeshSystem(XkMeshSystem*);
XK_API void xkDestroyMeshSystem(XkMeshSystem);
XK_API XkMeshID xkCreateMesh(XkMeshSystem, XkModelConfig* const);
XK_API void xkDestroyMesh(XkMeshSystem, XkMeshID);

#ifdef __cplusplus
}
#endif // __cplusplus

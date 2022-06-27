#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/MeshSystem.h"

#define XK_MESH_SYSTEM_ARRAY_SIZE 1024

struct XkMeshSystem {
  XkPoolAllocator meshs;

  XkMeshID meshID;
};

struct XkMesh {
  XkMeshID ID;
  /// TODO: Implementation.
};

XkResult xkCreateMeshSystem(XkMeshSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkMeshSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkMeshSystem system = *pSystem;

  system->meshID = 1;

  result = xkCreatePoolAllocator(&system->meshs, XK_MESH_SYSTEM_ARRAY_SIZE, struct XkMesh);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: Implementation.

_catch:
  return(result);
}

void xkDestroyMeshSystem(XkMeshSystem system) {
  /// TODO: Implementation.
  xkDestroyPoolAllocator(system->meshs);
}

XkMeshID xkCreateMesh(XkMeshSystem system, XkModelConfig* const pConfig) {
  /// TODO: Implementation.
  XkMeshID id = 0;

  id = ++system->meshID;

_catch:
  return(id);
}

void xkDestroyMesh(XkMeshSystem system, XkMeshID id) {
  /// TODO: Implementation.
}

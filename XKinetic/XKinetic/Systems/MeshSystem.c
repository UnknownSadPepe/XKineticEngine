/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/MeshSystem.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_MESH_SYSTEM_ARRAY_SIZE 1024

/* ########## TYPES SECTION ########## */
struct XkMeshSystem_T {
  XkPoolAllocator meshs;

  XkMeshId meshId;
};

struct XkMesh_T {
  XkMeshId id;
  /// TODO: Implementation.
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateMeshSystem(XkMeshSystem* pSystem) {
	xkAssert(pSystem);

  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkMeshSystem_T));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkMeshSystem system = *pSystem;

  system->meshId = 1;

  result = xkCreatePoolAllocator(&system->meshs, XK_MESH_SYSTEM_ARRAY_SIZE, struct XkMesh_T);
  if(result != XK_SUCCESS) {
		goto _free;
	}

  /// TODO: Implementation.

_catch:
  return(result);

_free:
	if(system) {
		xkFreeMemory(system);
	}

	goto _catch;
}

void xkDestroyMeshSystem(XkMeshSystem system) {
	xkAssert(system);
  /// TODO: Implementation.
  xkDestroyPoolAllocator(system->meshs);
	xkFreeMemory(system);
}

XkMeshId xkCreateMesh(XkMeshSystem system, const XkModelConfig* const pConfig) {
	xkAssert(system);
	xkAssert(pConfig)

  /// TODO: Implementation.
  XkMeshId id = 0;

  id = ++system->meshId;

_catch:
  return(id);
}

void xkDestroyMesh(XkMeshSystem system, XkMeshId id) {
	xkAssert(system);
  /// TODO: Implementation.
}

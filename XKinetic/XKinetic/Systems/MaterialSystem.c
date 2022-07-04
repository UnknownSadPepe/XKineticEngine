/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/MaterialSystem.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_MATERIAL_SYSTEM_ARRAY_SIZE 1024

/* ########## TYPES SECTION ########## */
struct XkMaterialSystem_T {
  XkPoolAllocator materials;

  XkMaterialId materialId;
};

struct XkMaterial_T {
  XkMaterialId id;
  /// TODO: Implementation.
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateMaterialSystem(XkMaterialSystem* pSystem) {
	xkAssert(pSystem)

  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkMaterialSystem_T));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkMaterialSystem system = *pSystem;

  system->materialId = 1;

  result = xkCreatePoolAllocator(&system->materials, XK_MATERIAL_SYSTEM_ARRAY_SIZE, struct XkMaterial_T);
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

void xkDestroyMaterialSystem(XkMaterialSystem system) {
	xkAssert(system);
  /// TODO: Implementation.
  xkDestroyPoolAllocator(system->materials);
	xkFreeMemory(system);
}

XkMaterialId xkCreateMaterial(XkMaterialSystem system, const XkMaterialConfig* const pConfig) {
	xkAssert(system);
	xkAssert(pConfig)

  /// TODO: Implementation.
  XkMaterialId id = 0;

  id = ++system->materialId;

_catch:
  return(id);
}

void xkDestroyMaterial(XkMaterialSystem system, XkMaterialId id) {
	xkAssert(system);
  /// TODO: Implementation.
}

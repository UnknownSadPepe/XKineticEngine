#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/MaterialSystem.h"

#define XK_MATERIAL_SYSTEM_ARRAY_SIZE 1024

struct XkMaterialSystem {
  XkPoolAllocator materials;

  XkMaterialID materialID;
};

struct XkMaterial {
  XkMaterialID ID;
  /// TODO: implementation.
};

XkResult xkCreateMaterialSystem(XkMaterialSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkMaterialSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkMaterialSystem system = *pSystem;

  system->materialID = 1;

  result = xkCreatePoolAllocator(&system->materials, XK_MATERIAL_SYSTEM_ARRAY_SIZE, struct XkMaterial);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyMaterialSystem(XkMaterialSystem system) {
  /// TODO: implementation.
  xkDestroyPoolAllocator(system->materials);
}

XkMaterialID xkCreateMaterial(XkMaterialSystem system, XkMaterialConfig* const pConfig) {
  /// TODO: implementation.
  XkMaterialID id = 0;

  id = ++system->materialID;

_catch:
  return(id);
}

void xkDestroyMaterial(XkMaterialSystem system, XkMaterialID id) {
  /// TODO: implementation.
}

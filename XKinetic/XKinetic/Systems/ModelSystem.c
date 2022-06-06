#include "XKinetic/Systems/ModelSystem.h"

#define XK_MODEL_SYSTEM_ARRAY_SIZE 1024

struct XkModelSystem {
  XkDynamicArray models;
};

XkResult xkCreateModelSystem(XkModelSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkModelSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkModelSystem system = *pSystem;

  result = xkCreateDynamicArrayCapacity(&system->models, XK_MODEL_SYSTEM_ARRAY_SIZE, XkModel);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: implementation.

  

_catch:
  return(result);
}

void xkDestroyModelSystem(XkModelSystem system) {
  /// TODO: implementation.
  xkDestroyDynamicArray(system->models);
}

XkModelID xkCreateModel(XkModelSystem system, XkModelConfig* const pConfig) {
  /// TODO: implementation.
  return(-1);
}

void xkDestroyModel(XkModelSystem system, XkModelID id) {
  /// TODO: implementation.
}

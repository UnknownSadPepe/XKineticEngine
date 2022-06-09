#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/ModelSystem.h"

#define XK_MODEL_SYSTEM_ARRAY_SIZE 1024

struct XkModelSystem {
  XkPoolAllocator models;

  XkModelID modelID;
};

XkResult xkCreateModelSystem(XkModelSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkModelSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkModelSystem system = *pSystem;

  system->modelID = 1;

  result = xkCreatePoolAllocator(&system->models, XK_MODEL_SYSTEM_ARRAY_SIZE, struct XkModel);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyModelSystem(XkModelSystem system) {
  /// TODO: implementation.
  xkDestroyPoolAllocator(system->models);
}

XkModelID xkCreateModel(XkModelSystem system, XkModelConfig* const pConfig) {
  /// TODO: implementation.
  XkModelID id = 0;

  id = ++system->modelID;

_catch:
  return(id);
}

void xkDestroyModel(XkModelSystem system, XkModelID id) {
  /// TODO: implementation.
}

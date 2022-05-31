#include "XKinetic/Systems/TextureSystem.h"

#define XK_TEXTURE_SYSTEM_ARRAY_SIZE 128

struct XkTextureSystem {
  XkDynamicArray textures;
};

XkResult xkCreateTextureSystem(XkTextureSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkTextureSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkTextureSystem system = *pSystem;

  result = xkCreateDynamicArrayCapacity(&system->textures, XK_TEXTURE_SYSTEM_ARRAY_SIZE, XkTexture);
  if(result != XK_SUCCESS) goto _catch;

  // TODO: implementation.

  

_catch:
  return(result);
}

void xkDestroyTextureSystem(XkTextureSystem system) {
  // TODO: implementation.
  xkDestroyDynamicArray(system->textures);
}

XkTextureID xkCreateTexture(XkTextureSystem system, XkTextureConfig* const pConfig) {
  // TODO: implementation.
  return(-1);
}

void xkDestroyTexture(XkTextureSystem system, XkTextureID id) {
  // TODO: implementation.
}

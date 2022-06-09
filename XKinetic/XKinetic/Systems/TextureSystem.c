#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/TextureSystem.h"

#define XK_TEXTURE_SYSTEM_ARRAY_SIZE 128

struct XkTextureSystem {
  XkPoolAllocator textures;

  XkTextureID textureID;
};

XkResult xkCreateTextureSystem(XkTextureSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkTextureSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkTextureSystem system = *pSystem;

  system->textureID = 1;

  result = xkCreatePoolAllocator(&system->textures, XK_TEXTURE_SYSTEM_ARRAY_SIZE, struct XkTexture);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyTextureSystem(XkTextureSystem system) {
  /// TODO: implementation.
  xkDestroyPoolAllocator(system->textures);
}

XkTextureID xkCreateTexture(XkTextureSystem system, XkTextureConfig* const pConfig) {
  /// TODO: implementation.
  XkTextureID id = 0;

  id = ++system->textureID;

_catch:
  return(id);
}

void xkDestroyTexture(XkTextureSystem system, XkTextureID id) {
  /// TODO: implementation.
}

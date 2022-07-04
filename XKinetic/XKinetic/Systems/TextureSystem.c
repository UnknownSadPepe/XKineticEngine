/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/TextureSystem.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_TEXTURE_SYSTEM_ARRAY_SIZE 128

/* ########## TYPES SECTION ########## */
struct XkTextureSystem_T {
  XkPoolAllocator textures;

  XkTextureId textureId;
};

struct XkTexture_T {
  XkTextureId id;
  /// TODO: Implementation.
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateTextureSystem(XkTextureSystem* pSystem) {
	xkAssert(pSystem);

  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkTextureSystem_T));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkTextureSystem system = *pSystem;

  system->textureId = 1;

  result = xkCreatePoolAllocator(&system->textures, XK_TEXTURE_SYSTEM_ARRAY_SIZE, struct XkTexture_T);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: Implementation.

_catch:
  return(result);
}

void xkDestroyTextureSystem(XkTextureSystem system) {
	xkAssert(system);
  /// TODO: Implementation.
  xkDestroyPoolAllocator(system->textures);
	xkFreeMemory(system);
}

XkTextureId xkCreateTexture(XkTextureSystem system, const XkImageConfig* const pConfig) {
	xkAssert(system);
	xkAssert(pConfig);

  /// TODO: Implementation.
  XkTextureId id = 0;

  id = ++system->textureId;

_catch:
  return(id);
}

void xkDestroyTexture(XkTextureSystem system, XkTextureId id) {
	xkAssert(system);
  /// TODO: Implementation.
}

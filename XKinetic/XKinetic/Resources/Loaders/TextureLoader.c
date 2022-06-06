#include "XKinetic/Resources/Loaders/TextureLoader.h"

#define XK_TEXTURE_LOADER_PATH_MAX_SIZE 64

struct XkTextureLoader {
  XkChar8 path[XK_TEXTURE_LOADER_PATH_MAX_SIZE];
};

XkResult xkCreateTextureLoader(XkTextureLoader* pLoader, XkChar8* path) {
  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkTextureLoader));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkTextureLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_TEXTURE_LOADER_PATH_MAX_SIZE);

  /// TODO: implementation.

  

_catch:
  return(result);
}

void xkDestroyTextureLoader(XkTextureLoader loader) {
  /// TODO: implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadTexture(XkTextureLoader loader, XkTextureConfig* const pConfig, XkChar8* name) {
  XkResult result = XK_SUCCESS;

  /// TODO: implementation.
  pConfig->width = 0;
  pConfig->height = 0;
  pConfig->pixels = XK_NULL_HANDLE;

_catch:
  return(result);
}

void xkUnloadTexture(XkTextureLoader loader, XkTextureConfig* const pConfig) {
  /// TODO: implementation.
}


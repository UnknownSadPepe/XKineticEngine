#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "XKinetic/Resources/Loaders/ImageLoader.h"

#define XK_IMAGE_LOADER_PATH_MAX_SIZE 64

struct XkImageLoader {
  XkChar path[XK_IMAGE_LOADER_PATH_MAX_SIZE];
};

XkResult xkCreateImageLoader(XkImageLoader* pLoader, XkString path) {
  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkImageLoader));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkImageLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_IMAGE_LOADER_PATH_MAX_SIZE);

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyImageLoader(XkImageLoader loader) {
  /// TODO: implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadImage(XkImageLoader loader, XkImageConfig* const pConfig, XkString name) {
  XkResult result = XK_SUCCESS;

	XkChar fullPath[XK_IMAGE_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_IMAGE_LOADER_PATH_MAX_SIZE, "%s%s", loader->path, name);

  /// TODO: implementation.
  pConfig->pixels = stbi_load(fullPath, (int*)&pConfig->width, (int*)&pConfig->height, XK_NULL_HANDLE, 4);

_catch:
  return(result);
}

void xkUnloadImage(XkImageLoader loader, XkImageConfig* const pConfig) {
  /// TODO: implementation.
  stbi_image_free(pConfig->pixels);
}

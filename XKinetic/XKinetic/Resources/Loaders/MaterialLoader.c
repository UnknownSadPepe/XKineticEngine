#include "XKinetic/Resources/Loaders/MaterialLoader.h"

#define XK_MATERIAL_LOADER_PATH_MAX_SIZE 64

struct XkMaterialLoader {
  XkChar path[XK_MATERIAL_LOADER_PATH_MAX_SIZE];
};

XkResult xkCreateMaterialLoader(XkMaterialLoader* pLoader, XkString path) {
  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkMaterialLoader));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkMaterialLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_MATERIAL_LOADER_PATH_MAX_SIZE);

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyMaterialLoader(XkMaterialLoader loader) {
  /// TODO: implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadMaterial(XkMaterialLoader loader, XkMaterialConfig* const pConfig, XkString name) {
  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_MATERIAL_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_MATERIAL_LOADER_PATH_MAX_SIZE, "%s%s", loader->path, name);

  /// TODO: implementation.

_catch:
  return(result); 
}

void xkUnloadMaterial(XkMaterialLoader loader, XkMaterialConfig* const pConfig) {
  /// TODO: implementation.
}

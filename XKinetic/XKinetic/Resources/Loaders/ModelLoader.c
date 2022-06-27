#include "XKinetic/Resources/Loaders/ModelLoader.h"

#define XK_MODEL_LOADER_PATH_MAX_SIZE 64

struct XkModelLoader {
  XkChar path[XK_MODEL_LOADER_PATH_MAX_SIZE];
};

XkResult xkCreateModelLoader(XkModelLoader* pLoader, XkString path) {
  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkModelLoader));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkModelLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_MODEL_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

_catch:
  return(result);
}

void xkDestroyModelLoader(XkModelLoader loader) {
  /// TODO: Implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadModel(XkModelLoader loader, XkModelConfig* const pConfig, XkString name) {
  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_MODEL_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_MODEL_LOADER_PATH_MAX_SIZE, "%s%s", loader->path, name);

  /// TODO: Implementation.
  pConfig->vertexCount = 0;
  pConfig->vertices = XK_NULL_HANDLE;
  pConfig->indexCount = 0;
  pConfig->indices = XK_NULL_HANDLE;

_catch:
  return(result); 
}

void xkUnloadModel(XkModelLoader loader, XkModelConfig* const pConfig) {
  /// TODO: Implementation.
}

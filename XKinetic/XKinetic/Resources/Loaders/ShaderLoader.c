#include "XKinetic/Resources/Loaders/ShaderLoader.h"

#define XK_SHADER_LOADER_PATH_MAX_SIZE 64

struct XkShaderLoader {
  XkChar8 path[XK_SHADER_LOADER_PATH_MAX_SIZE];
};

XkResult xkCreateShaderLoader(XkShaderLoader* pLoader, XkChar8* path) {
  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkShaderLoader));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkShaderLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_SHADER_LOADER_PATH_MAX_SIZE);

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyShaderLoader(XkShaderLoader loader) {
  /// TODO: implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadShader(XkShaderLoader loader, XkShaderConfig* const pConfig, XkChar8* name) {
  XkResult result = XK_SUCCESS;

  /// TODO: implementation.
  pConfig->size = 0;
  pConfig->code = XK_NULL_HANDLE;

_catch:
  return(result);
}

void xkUnloadShader(XkShaderLoader loader, XkShaderConfig* const pConfig) {
  /// TODO: implementation.
}


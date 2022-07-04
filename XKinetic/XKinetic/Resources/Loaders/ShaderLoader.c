/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Resources/Loaders/ShaderLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_SHADER_LOADER_PATH_MAX_SIZE 64

/* ########## TYPES SECTION ########## */
struct XkShaderLoader_T {
  XkChar path[XK_SHADER_LOADER_PATH_MAX_SIZE];
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateShaderLoader(XkShaderLoader* pLoader, XkString path) {
  xkAssert(pLoader);

  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkShaderLoader));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkShaderLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_SHADER_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

_catch:
  return(result);

_free:
  if(loader) {
    xkFreeMemory(loader);
  }

  goto _catch;
}

void xkDestroyShaderLoader(XkShaderLoader loader) {
  xkAssert(loader); 

  /// TODO: Implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadShader(XkShaderLoader loader, XkShaderConfig* const pConfig, XkString name) {
  xkAssert(loader);
  xkAssert(pConfig); 

  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_SHADER_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_SHADER_LOADER_PATH_MAX_SIZE, "%s%s", loader->path, name);

  /// TODO: Implementation.
  pConfig->size = 0;
  pConfig->code = XK_NULL_HANDLE;

_catch:
  return(result);
}

void xkUnloadShader(XkShaderLoader loader, XkShaderConfig* const pConfig) {
  xkAssert(loader);
  xkAssert(pConfig); 

  /// TODO: Implementation.
}


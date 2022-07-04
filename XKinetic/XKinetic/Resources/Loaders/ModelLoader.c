/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Resources/Loaders/ModelLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_MODEL_LOADER_PATH_MAX_SIZE 64

/* ########## TYPES SECTION ########## */
struct XkModelLoader_T {
  XkChar path[XK_MODEL_LOADER_PATH_MAX_SIZE];
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateModelLoader(XkModelLoader* pLoader, XkString path) {
	xkAssert(pLoader);

  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkModelLoader_T));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkModelLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_MODEL_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

_catch:
  return(result);

_free:
	if(loader) {
		xkFreeMemory(loader);
	}

	goto _catch;
}

void xkDestroyModelLoader(XkModelLoader loader) {
	xkAssert(loader);
  /// TODO: Implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadModel(XkModelLoader loader, XkModelConfig* const pConfig, XkString name) {
	xkAssert(loader);
	xkAssert(pConfig);

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

void xkUnloadModel(XkModelLoader loader, const XkModelConfig* const pConfig) {
	xkAssert(loader);
	xkAssert(pConfig);
  /// TODO: Implementation.
}

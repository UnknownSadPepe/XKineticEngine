/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Resources/Loaders/MaterialLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_MATERIAL_LOADER_PATH_MAX_SIZE 64

/* ########## TYPES SECTION ########## */
struct XkMaterialLoader_T {
  XkChar path[XK_MATERIAL_LOADER_PATH_MAX_SIZE];
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateMaterialLoader(XkMaterialLoader* pLoader, XkString path) {
	xkAssert(pLoader);

  XkResult result = XK_SUCCESS;

	*pLoader = xkAllocateMemory(sizeof(struct XkMaterialLoader_T));
	if(!(*pLoader)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkMaterialLoader loader = *pLoader;

  xkNCopyString(loader->path, path, XK_MATERIAL_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

_catch:
  return(result);

_free:
	if(loader) {
		xkFreeMemory(loader);
	}

	goto _catch;
}

void xkDestroyMaterialLoader(XkMaterialLoader loader) {
	xkAssert(loader);
  /// TODO: Implementation.
  xkFreeMemory(loader);
}

XkResult xkLoadMaterial(XkMaterialLoader loader, XkMaterialConfig* const pConfig, XkString name) {
	xkAssert(loader);
	xkAssert(pConfig);

  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_MATERIAL_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_MATERIAL_LOADER_PATH_MAX_SIZE, "%s%s", loader->path, name);

  /// TODO: Implementation.

_catch:
  return(result); 
}

void xkUnloadMaterial(XkMaterialLoader loader, const XkMaterialConfig* const pConfig) {
	xkAssert(loader);
	xkAssert(pConfig);
  /// TODO: Implementation.
}

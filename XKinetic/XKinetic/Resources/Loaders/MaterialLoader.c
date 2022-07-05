/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Resources/Loaders/MaterialLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_MATERIAL_LOADER_PATH_MAX_SIZE 128

/* ########## TYPES SECTION ########## */
typedef struct __XkMaterialLoader_T {
	XkBool initialized;

  XkChar path[XK_MATERIAL_LOADER_PATH_MAX_SIZE];
} __XkMaterialLoader;

/* ########## GLOBAL VARIABLES SECTION ########## */
static __XkMaterialLoader _xkMaterialLoader;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeMaterialLoader(XkString path) {
  XkResult result = XK_SUCCESS;

	if(_xkMaterialLoader.initialized) {
		goto _catch;
	}

  xkNCopyString(_xkMaterialLoader.path, path, XK_MATERIAL_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

	_xkMaterialLoader.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkTerminateMaterialLoader() {
	if(!_xkMaterialLoader.initialized) {
		return;
	}

  /// TODO: Implementation.

	_xkMaterialLoader.initialized = XK_FALSE;
}

XkResult xkLoadMaterial(XkMaterialConfig* const pConfig, XkString name) {
	xkAssert(pConfig);

  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_MATERIAL_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_MATERIAL_LOADER_PATH_MAX_SIZE, "%s%s", _xkMaterialLoader.path, name);

  /// TODO: Implementation.

_catch:
  return(result); 
}

void xkUnloadMaterial(const XkMaterialConfig* const pConfig) {
	xkAssert(pConfig);
  /// TODO: Implementation.
}

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Resources/Loaders/ModelLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_MODEL_LOADER_PATH_MAX_SIZE 128

/* ########## TYPES SECTION ########## */
typedef struct __XkModelLoader_T {
	XkBool initialized;

  XkChar path[XK_MODEL_LOADER_PATH_MAX_SIZE];
} __XkModelLoader;

/* ########## GLOBAL VARIABLES SECTION ########## */
static __XkModelLoader _xkModelLoader;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeModelLoader(XkString path) {
  XkResult result = XK_SUCCESS;

	if(_xkModelLoader.initialized) {
		goto _catch;
	}

  xkNCopyString(_xkModelLoader.path, path, XK_MODEL_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

	_xkModelLoader.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkTerminateModelLoader() {
	if(!_xkModelLoader.initialized) {
		return;
	}

  /// TODO: Implementation.

	_xkModelLoader.initialized = XK_FALSE;
}

XkResult xkLoadModel(XkModelConfig* const pConfig, XkString name) {
	xkAssert(pConfig);

  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_MODEL_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_MODEL_LOADER_PATH_MAX_SIZE, "%s%s", _xkModelLoader.path, name);

  /// TODO: Implementation.
  pConfig->vertexCount = 0;
  pConfig->vertices = XK_NULL_HANDLE;
  pConfig->indexCount = 0;
  pConfig->indices = XK_NULL_HANDLE;

_catch:
  return(result); 
}

void xkUnloadModel(const XkModelConfig* const pConfig) {
	xkAssert(pConfig);
  /// TODO: Implementation.
}

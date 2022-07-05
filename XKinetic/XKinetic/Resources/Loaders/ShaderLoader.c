/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Resources/Loaders/ShaderLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_SHADER_LOADER_PATH_MAX_SIZE 64

/* ########## TYPES SECTION ########## */
typedef struct __XkShaderLoader_T {
	XkBool initialized;

  XkChar path[XK_SHADER_LOADER_PATH_MAX_SIZE];
} __XkShaderLoader;

/* ########## GLOBAL VARIABLES SECTION ########## */
static __XkShaderLoader _xkShaderLoader;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeShaderLoader(XkString path) {
  XkResult result = XK_SUCCESS;

	if(_xkShaderLoader.initialized) {
		goto _catch;
	}

  xkNCopyString(_xkShaderLoader.path, path, XK_SHADER_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

	_xkShaderLoader.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkTerminateShaderLoader() {
	if(!_xkShaderLoader.initialized) {
		return;
	}

  /// TODO: Implementation.

	_xkShaderLoader.initialized = XK_FALSE;
}

XkResult xkLoadShader(XkShaderConfig* const pConfig, XkString name) {
  xkAssert(pConfig); 

  XkResult result = XK_SUCCESS;

  XkChar fullPath[XK_SHADER_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_SHADER_LOADER_PATH_MAX_SIZE, "%s%s", _xkShaderLoader.path, name);

  /// TODO: Implementation.
  pConfig->size = 0;
  pConfig->code = XK_NULL_HANDLE;

_catch:
  return(result);
}

void xkUnloadShader(const XkShaderConfig* const pConfig) {
  xkAssert(pConfig); 
  /// TODO: Implementation.
}


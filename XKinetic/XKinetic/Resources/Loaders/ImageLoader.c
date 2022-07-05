/* ########## INCLUDE SECTION ########## */
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "XKinetic/Resources/Loaders/ImageLoader.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_IMAGE_LOADER_PATH_MAX_SIZE 128

/* ########## TYPES SECTION ########## */
typedef struct __XkImageLoader_T {
	XkBool initialized;

  XkChar path[XK_IMAGE_LOADER_PATH_MAX_SIZE];
} __XkImageLoader;

/* ########## GLOABL VARIABLES SECTION ########## */
static __XkImageLoader _xkImageLoader;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeImageLoader(XkString path) {
  XkResult result = XK_SUCCESS;

	if(_xkImageLoader.initialized) {
		goto _catch;
	}

  xkNCopyString(_xkImageLoader.path, path, XK_IMAGE_LOADER_PATH_MAX_SIZE);

  /// TODO: Implementation.

	_xkImageLoader.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkTerminateImageLoader() {
	if(!_xkImageLoader.initialized) {
		return;
	}

  /// TODO: Implementation.

	_xkImageLoader.initialized = XK_FALSE;
}

XkResult xkLoadImage(XkImageConfig* const pConfig, XkString name) {
	xkAssert(pConfig);

  XkResult result = XK_SUCCESS;

	XkChar fullPath[XK_IMAGE_LOADER_PATH_MAX_SIZE];
  xkStringNFormat(fullPath, XK_IMAGE_LOADER_PATH_MAX_SIZE, "%s%s", _xkImageLoader.path, name);

  /// TODO: Implementation.
  pConfig->pixels = stbi_load(fullPath, (int*)&pConfig->width, (int*)&pConfig->height, XK_NULL_HANDLE, 4);
  if(!pConfig->pixels) {
    result = XK_ERROR_RESOURCE_NOT_LOAD;
    goto _catch;
  }

_catch:
  return(result);
}

void xkUnloadImage(const XkImageConfig* const pConfig) {
	xkAssert(pConfig);
  /// TODO: Implementation.
  stbi_image_free(pConfig->pixels);
}


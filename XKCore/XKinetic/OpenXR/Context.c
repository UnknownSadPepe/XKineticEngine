#include "XKinetic/OpenXR/Internal.h"

__XkXRContext _xkXRContext;

XkString __xkXRGetErrorString(const XrResult xrResult) {
  switch(xrResult) {
    case XR_SUCCESS:                        return "Success";
    default:                                return "unknown OpenXR error";
  };
}

XkResult __xkXRInitializeContext(void) {
  XkResult result = XK_SUCCESS;

  // If OpenXR context initialize return.
  if(_xkXRContext.initialized) goto _catch;

  // Create OpenXR instance.
  result = __xkXRCreateInstance();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR instance: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  // Success, OpenXR context initialized.
  _xkXRContext.initialized = XK_TRUE;

_catch:
  return(result);
}

void __xkXRTerminateContext(void) {
  // Destroy OpenXR instance.
  __xkXRDestroyInstance();
}

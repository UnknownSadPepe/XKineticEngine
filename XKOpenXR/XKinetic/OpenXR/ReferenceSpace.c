#include "XKinetic/OpenXR/Internal.h"

XkResult __xkXRCreateReferenceSpace(void) {
  XkResult result = XK_SUCCESS;

  // Initialize OpenXR reference space info.
  XrReferenceSpaceCreateInfo xrReferenceSpaceInfo   = {0};
  xrReferenceSpaceInfo.type                         = XR_TYPE_REFERENCE_SPACE_CREATE_INFO;
  xrReferenceSpaceInfo.next                         = XR_NULL_HANDLE;
  xrReferenceSpaceInfo.referenceSpaceType           = XR_REFERENCE_SPACE_TYPE_LOCAL;
  //xrReferenceSpaceInfo.poseInReferenceSpace         = /*TODO: implementation*/;

  // Create OpenXR reference space.
  XrResult xrResult = xrCreateReferenceSpace(_xkXRContext.xrInstance, &xrReferenceSpaceInfo, _xkXRContext.xrReferenceSpace);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR reference space: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkXRDestroyReferenceSpace(void) {
  // Destroy OpenXR reference space.
  if(_xkXRContext.xrReferenceSpace) {
    xrDestroySpace(_xkXRContext.xrReferenceSpace);

    _xkXRContext.xrReferenceSpace = XR_NULL_HANDLE;
  }
}

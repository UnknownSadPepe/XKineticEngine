#include "XKinetic/OpenXR/Internal.h"

XkResult __xkOpenXRCreateReferenceSpace(void) {
  XkResult result = XK_SUCCESS;

  // Initialize OpenXR reference space info.
  XrReferenceSpaceCreateInfo xrReferenceSpaceInfo   = {};
  xrReferenceSpaceInfo.type                         = XR_TYPE_REFERENCE_SPACE_CREATE_INFO;
  xrReferenceSpaceInfo.next                         = XR_NULL_HANDLE;
  xrReferenceSpaceInfo.referenceSpaceType           = XR_REFERENCE_SPACE_TYPE_LOCAL;
  //xrReferenceSpaceInfo.poseInReferenceSpace         = /*TODO: implementation*/;

  // Create OpenXR reference space.
  XrResult xrResult = xrCreateReferenceSpace(_xkOpenXRContext.xrInstance, &xrReferenceSpaceInfo, _xkOpenXRContext.xrReferenceSpace);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR reference space: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkOpenXRDestroyReferenceSpace(void) {w
  // Destroy OpenXR reference space.
  if(_xkOpenXRContext.xrReferenceSpace) {
    xrDestroySpace(_xkOpenXRContext.xrReferenceSpace);

    _xkOpenXRContext.xrReferenceSpace = XR_NULL_HANDLE;
  }
}

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkOpenXRCreateReferenceSpace() {
  XkResult result = XK_SUCCESS;

  XrReferenceSpaceCreateInfo xrReferenceSpaceInfo   = {0};
  xrReferenceSpaceInfo.type                         = XR_TYPE_REFERENCE_SPACE_CREATE_INFO;
  xrReferenceSpaceInfo.next                         = XR_NULL_HANDLE;
  xrReferenceSpaceInfo.referenceSpaceType           = XR_REFERENCE_SPACE_TYPE_LOCAL;
  //xrReferenceSpaceInfo.poseInReferenceSpace         = /*TODO: implementation*/;

  XrResult xrResult = xrCreateReferenceSpace(_xkOpenXRContext.xrSession, &xrReferenceSpaceInfo, &_xkOpenXRContext.xrReferenceSpace);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create reference space: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkOpenXRDestroyReferenceSpace() {
  if(_xkOpenXRContext.xrReferenceSpace) {
    xrDestroySpace(_xkOpenXRContext.xrReferenceSpace);

    _xkOpenXRContext.xrReferenceSpace = XR_NULL_HANDLE;
  }
}

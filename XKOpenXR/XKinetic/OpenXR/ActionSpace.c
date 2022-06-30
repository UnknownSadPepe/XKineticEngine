#include "XKinetic/OpenXR/Internal.h"

XkResult __xkXRCreateActionSpace(XrSpace* pXrSpace, XrAction xrAction, XrPath xrSubactionPath) {
  XkResult result = XK_SUCCESS;

  // Initialize OpenXR action space info.
  XrActionSpaceCreateInfo xrActionSpaceInfo   = {0};
  xrActionSpaceInfo.type                      = XR_TYPE_ACTION_SPACE_CREATE_INFO;
  xrActionSpaceInfo.next                      = XR_NULL_HANDLE;
  xrActionSpaceInfo.action                    = xrAction;
  xrActionSpaceInfo.subactionPath             = xrSubactionPath;
  //xrActionSpaceInfo.poseInActionSpace         = /*TODO: Implementation*/;

  // Create OpenXR action space.
  XrResult xrResult = xrCreateActionSpace(_xkXRContext.xrSession, &xrActionSpaceInfo, pXrSpace);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR action space: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkXRDestroyActionSpace(XrSpace xrSpace) {
  if(xrSpace) {
    xrDestroySpace(xrSpace);
  }
}

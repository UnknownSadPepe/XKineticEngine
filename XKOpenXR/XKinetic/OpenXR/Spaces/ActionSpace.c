/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkOpenXRCreateActionSpace(XrSpace* pXrSpace, XrAction xrAction, XrPath xrSubactionPath) {
  xkAssert(pXrSpace);
  xkAssert(xrAction);
  xkAssert(xrSubactionPath);

  XkResult result = XK_SUCCESS;

  XrActionSpaceCreateInfo xrActionSpaceInfo   = {0};
  xrActionSpaceInfo.type                      = XR_TYPE_ACTION_SPACE_CREATE_INFO;
  xrActionSpaceInfo.next                      = XR_NULL_HANDLE;
  xrActionSpaceInfo.action                    = xrAction;
  xrActionSpaceInfo.subactionPath             = xrSubactionPath;
  //xrActionSpaceInfo.poseInActionSpace         = /*TODO: Implementation*/;

  XrResult xrResult = xrCreateActionSpace(_xkOpenXRContext.xrSession, &xrActionSpaceInfo, pXrSpace);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create action space: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkOpenXRDestroyActionSpace(XrSpace xrSpace) {
  xkAssert(xrSpace);

  xrDestroySpace(xrSpace);
}

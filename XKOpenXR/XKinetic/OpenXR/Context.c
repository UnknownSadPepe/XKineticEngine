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

  result = __xkXRCreateActionSet(&_xkXRContext.xrActionSet, "place_hologram_action_set", "Placement");
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR action set: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  _xkXRContext.xrSubactionPaths[XKXR_LEFT_SIDE] = __xkXrGetPath("/user/hand/left");
  _xkXRContext.xrSubactionPaths[XKXR_RIGHT_SIDE] = __xkXrGetPath("/user/hand/right");

  result = __xkXRCreateAction(&_xkXRContext.xrPlaceAction, "place_hologram", "Place Hologram", XR_ACTION_TYPE_BOOLEAN_INPUT, _xkXRContext.subactionPathCount, _xkXRContext.xrSubactionPaths, _xkXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR place action: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkXRCreateAction(&_xkXRContext.xrPoseAction, "hand_pose", "Hand Pose", XR_ACTION_TYPE_POSE_INPUT, _xkXRContext.subactionPathCount, _xkXRContext.xrSubactionPaths, _xkXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR pose action: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkXRCreateAction(&_xkXRContext.xrVibrateAction, "vibrate", "Vibrate", XR_ACTION_TYPE_VIBRATION_OUTPUT, _xkXRContext.subactionPathCount, _xkXRContext.xrSubactionPaths, _xkXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR vibrate action: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkXRCreateAction(&_xkXRContext.xrExitAction, "exit_session", "Exit session", XR_ACTION_TYPE_BOOLEAN_INPUT, _xkXRContext.subactionPathCount, _xkXRContext.xrSubactionPaths, _xkXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR exit action: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  {
    XrActionSuggestedBinding xrLeftPlaceActionBinding     = {0};
    xrLeftPlaceActionBinding.action                       = _xkXRContext.xrPlaceAction;
    xrLeftPlaceActionBinding.binding                      = __xkXrGetPath("/user/hand/left/input/select/click");

    XrActionSuggestedBinding xrRightPlaceActionBinding     = {0};
    xrRightPlaceActionBinding.action                       = _xkXRContext.xrPlaceAction;
    xrRightPlaceActionBinding.binding                      = __xkXrGetPath("/user/hand/right/input/select/click");

    XrActionSuggestedBinding xrLeftPoseActionBinding      = {0};
    xrLeftPlaceActionBinding.action                       = _xkXRContext.xrPoseAction;
    xrLeftPlaceActionBinding.binding                      = __xkXrGetPath("/user/hand/left/input/grip/pose");

    XrActionSuggestedBinding xrRightPoseActionBinding     = {0};
    xrRightPlaceActionBinding.action                      = _xkXRContext.xrPoseAction;
    xrRightPlaceActionBinding.binding                     = __xkXrGetPath("/user/hand/right/input/grip/pose");

    XrActionSuggestedBinding xrLeftVibrateActionBinding   = {0};
    xrLeftPlaceActionBinding.action                       = _xkXRContext.xrPoseAction;
    xrLeftPlaceActionBinding.binding                      = __xkXrGetPath("/user/hand/left/output/haptic");

    XrActionSuggestedBinding xrRightVibrateActionBinding  = {0};
    xrRightPlaceActionBinding.action                      = _xkXRContext.xrPoseAction;
    xrRightPlaceActionBinding.binding                     = __xkXrGetPath("/user/hand/right/output/haptic");

    XrActionSuggestedBinding xrLeftExitActionBinding      = {0};
    xrLeftPlaceActionBinding.action                       = _xkXRContext.xrPoseAction;
    xrLeftPlaceActionBinding.binding                      = __xkXrGetPath("/user/hand/left/input/menu/click");

    XrActionSuggestedBinding xrRightExitActionBinding     = {0};
    xrRightPlaceActionBinding.action                      = _xkXRContext.xrPoseAction;
    xrRightPlaceActionBinding.binding                     = __xkXrGetPath("/user/hand/right/input/menu/click");

    XrActionSuggestedBinding xrActionBindings[] = {
      xrLeftPlaceActionBinding,
      xrRightPlaceActionBinding,
      xrLeftPoseActionBinding,
      xrRightPoseActionBinding,
      xrLeftVibrateActionBinding,
      xrRightVibrateActionBinding,
      xrLeftExitActionBinding,
      xrRightExitActionBinding
  };

    result = __xkXRProfileBindings(8, xrActionBindings, __xkXrGetPath("/interaction_profiles/khr/simple_controller"));
    if(result != XK_SUCCESS) {
      xkLogError("Failed to bind OpenXR profile: %d", result);
      result = XK_ERROR_INITIALIZE_FAILED;
      goto _catch;
    }
  }
  // Success, OpenXR context initialized.
  _xkXRContext.initialized = XK_TRUE;

_catch:
  return(result);
}

void __xkXRTerminateContext(void) {
  // Destroy OpenXR place action.
  __xkXRDestroyAction(_xkXRContext.xrPlaceAction);

  // Destroy OpenXR pose action.
  __xkXRDestroyAction(_xkXRContext.xrPoseAction);

  // Destroy OpenXR vibrate action.
  __xkXRDestroyAction(_xkXRContext.xrVibrateAction);

  // Destroy OpenXR exit action.
  __xkXRDestroyAction(_xkXRContext.xrExitAction);

  // Destroy OpenXR action set.
  __xkXRDestroyActionSet(_xkXRContext.xrActionSet);

  // Destroy OpenXR instance.
  __xkXRDestroyInstance();
}

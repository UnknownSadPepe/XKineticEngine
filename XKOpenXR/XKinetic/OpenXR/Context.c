#include "XKinetic/OpenXR/Internal.h"

__XkXRContext _xkOpenXRContext;

XkString __xkOpenXRGetResultString(const XrResult xrResult) {
  switch(xrResult) {
    case XR_SUCCESS:                        return "Success";
    default:                                return "unknown OpenXR error";
  };
}

XkResult xkOpenXRInitializeContext(void) {
  XkResult result = XK_SUCCESS;

  if(_xkOpenXRContext.initialized) {
    goto _catch;
  }

  result = __xkOpenXRCreateInstance();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create OpenXR instance: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

#ifdef XKOPENXR_DEBUG
  result = __xkOpenXRCreateDebugMessenger();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  } 
#endif // XKOPENXR_DEBUG

  result = __xkOpenXRCreateActionSet(&_xkOpenXRContext.xrActionSet, "place_hologram_action_set", "Placement");
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  _xkOpenXRContext.xrSubactionPaths[XKOPENXR_LEFT_SIDE]   = __xkOpenXRGetPath("/user/hand/left");
  _xkOpenXRContext.xrSubactionPaths[XKOPENXR_RIGHT_SIDE]  = __xkOpenXRGetPath("/user/hand/right");

  result = __xkOpenXRCreateAction(&_xkOpenXRContext.xrPlaceAction, "place_hologram", "Place Hologram", XR_ACTION_TYPE_BOOLEAN_INPUT, _xkOpenXRContext.subactionPathCount, _xkOpenXRContext.xrSubactionPaths, _xkOpenXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkOpenXRCreateAction(&_xkOpenXRContext.xrPoseAction, "hand_pose", "Hand Pose", XR_ACTION_TYPE_POSE_INPUT, _xkOpenXRContext.subactionPathCount, _xkOpenXRContext.xrSubactionPaths, _xkOpenXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkOpenXRCreateAction(&_xkOpenXRContext.xrVibrateAction, "vibrate", "Vibrate", XR_ACTION_TYPE_VIBRATION_OUTPUT, _xkOpenXRContext.subactionPathCount, _xkOpenXRContext.xrSubactionPaths, _xkOpenXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkOpenXRCreateAction(&_xkOpenXRContext.xrExitAction, "exit_session", "Exit session", XR_ACTION_TYPE_BOOLEAN_INPUT, _xkOpenXRContext.subactionPathCount, _xkOpenXRContext.xrSubactionPaths, _xkOpenXRContext.xrActionSet);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  {
    XrActionSuggestedBinding xrLeftPlaceActionBinding     = {0};
    xrLeftPlaceActionBinding.action                       = _xkOpenXRContext.xrPlaceAction;
    xrLeftPlaceActionBinding.binding                      = __xkOpenXRGetPath("/user/hand/left/input/select/click");

    XrActionSuggestedBinding xrRightPlaceActionBinding     = {0};
    xrRightPlaceActionBinding.action                       = _xkOpenXRContext.xrPlaceAction;
    xrRightPlaceActionBinding.binding                      = __xkOpenXRGetPath("/user/hand/right/input/select/click");

    XrActionSuggestedBinding xrLeftPoseActionBinding      = {0};
    xrLeftPlaceActionBinding.action                       = _xkOpenXRContext.xrPoseAction;
    xrLeftPlaceActionBinding.binding                      = __xkOpenXRGetPath("/user/hand/left/input/grip/pose");

    XrActionSuggestedBinding xrRightPoseActionBinding     = {0};
    xrRightPlaceActionBinding.action                      = _xkOpenXRContext.xrPoseAction;
    xrRightPlaceActionBinding.binding                     = __xkOpenXRGetPath("/user/hand/right/input/grip/pose");

    XrActionSuggestedBinding xrLeftVibrateActionBinding   = {0};
    xrLeftPlaceActionBinding.action                       = _xkOpenXRContext.xrPoseAction;
    xrLeftPlaceActionBinding.binding                      = __xkOpenXRGetPath("/user/hand/left/output/haptic");

    XrActionSuggestedBinding xrRightVibrateActionBinding  = {0};
    xrRightPlaceActionBinding.action                      = _xkOpenXRContext.xrPoseAction;
    xrRightPlaceActionBinding.binding                     = __xkOpenXRGetPath("/user/hand/right/output/haptic");

    XrActionSuggestedBinding xrLeftExitActionBinding      = {0};
    xrLeftPlaceActionBinding.action                       = _xkOpenXRContext.xrPoseAction;
    xrLeftPlaceActionBinding.binding                      = __xkOpenXRGetPath("/user/hand/left/input/menu/click");

    XrActionSuggestedBinding xrRightExitActionBinding     = {0};
    xrRightPlaceActionBinding.action                      = _xkOpenXRContext.xrPoseAction;
    xrRightPlaceActionBinding.binding                     = __xkOpenXRGetPath("/user/hand/right/input/menu/click");

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

    result = __xkOpenXRProfileBindings(8, xrActionBindings, __xkOpenXRGetPath("/interaction_profiles/khr/simple_controller"));
    if(result != XK_SUCCESS) {
      result = XK_ERROR_INITIALIZE_FAILED;
      goto _catch;
    }
  }

  _xkOpenXRContext.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkOpenXRTerminateContext(void) {
  if(!_xkOpenXRContext.initialized) {
    return;
  }

  __xkOpenXRDestroyAction(_xkOpenXRContext.xrPlaceAction);

  __xkOpenXRDestroyAction(_xkOpenXRContext.xrPoseAction);

  __xkOpenXRDestroyAction(_xkOpenXRContext.xrVibrateAction);

  __xkOpenXRDestroyAction(_xkOpenXRContext.xrExitAction);

  __xkOpenXRDestroyActionSet(_xkOpenXRContext.xrActionSet);

#ifdef XKOPENXR_DEBUG
  __xkOpenXRDestroyDebugMessenger();
#endif // XKOPENXR_DEBUG

  __xkOpenXRDestroyInstance();

  _xkOpenXRContext.initialized = XK_FALSE;
}

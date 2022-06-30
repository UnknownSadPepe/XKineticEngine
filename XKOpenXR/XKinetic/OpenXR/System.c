#include "XKinetic/OpenXR/Internal.h"

const XrEnvironmentBlendMode _xkXREnvironmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;

static XkBool __xkXRPickEnvironmentBlendMode(void);

XkResult __xkXRInitializeSystem(void) {
  XkResult result = XK_SUCCESS;

  // Initialize OpenXR system info.
  XrSystemGetInfo xrSystemInfo    = {0};
  xrSystemInfo.type               = XR_TYPE_SYSTEM_GET_INFO;
  xrSystemInfo.next               = XR_NULL_HANDLE;
  xrSystemInfo.formFactor         = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;

  // Get OpenXR system.
  XrResult xrResult = xrGetSystem(_xkXRContext.xrInstance, &xrSystemInfo, &_xkXRContext.xrSystemId);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to get OpenXR system: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
  }

  // Check OpenXR environment blend mode support.
  if(!__xkXRCheckEnvironmentBlendModeSupport()) {
    result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR environment blend mode doesn't support");
    goto _catch; 
  }

_catch:
  return(result);
}

XkBool __xkXRCheckEnvironmentBlendModeSupport(void) {
  XkBool result = XK_TRUE;

  // Get OpenXR environment blend mode count.
  uint32_t environmentBlendModeCount = 0;
  xrEnumerateEnvironmentBlendModes(_xkXRContext.xrInstance, _xkXRContext.xrSystemId, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &environmentBlendModeCount, XR_NULL_HANDLE);
	if (environmentBlendModeCount == 0) {
		xkLogError("Failed to enumerate OpenXR environment blend modes");
		result = XK_FALSE;
		goto _catch;
	}

  XrEnvironmentBlendMode* xrAvailableEnvironmentBlendModes = XK_NULL_HANDLE;
  xrAvailableEnvironmentBlendModes = xkAllocateMemory(sizeof(XrEnvironmentBlendMode) * environmentBlendModeCount);
	if(!xrAvailableEnvironmentBlendModes) {
		xkLogError("Failed to enumerate OpenXR environment blend modes");
		result = XK_FALSE;
		goto _catch;
	}

  // Get OpenXR environment blend modes. 
  xrEnumerateEnvironmentBlendModes(_xkXRContext.xrInstance, _xkXRContext.xrSystemId, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, environmentBlendModeCount, XR_NULL_HANDLE, xrAvailableEnvironmentBlendModes);

	// Helper boolean value.
	XkBool availableBlendModeFind = XK_FALSE;

  for(uint32_t i = 0; i < environmentBlendModeCount; i++) {
    if(xrAvailableEnvironmentBlendModes == _xkXREnvironmentBlendMode) {
      availableBlendModeFind = XK_TRUE;
      break;
    }
  }

  // If doesn't find available OpenXR environment blend mode.
  if(!availableBlendModeFind) {
    result = XK_FALSE;
	  goto _catch;
  }

_catch:
  if(xrAvailableEnvironmentBlendModes) {
    xkFreeMemory(xrAvailableEnvironmentBlendModes);
  }

  return(result);
}

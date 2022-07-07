/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
const XrEnvironmentBlendMode _xkOpenXREnvironmentBlendMode = XR_ENVIRONMENT_BLEND_MODE_OPAQUE;

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
static XkBool8 __xkOpenXRPickEnvironmentBlendMode();

XkResult __xkOpenXRInitializeSystem() {
  XkResult result = XK_SUCCESS;

  XrSystemGetInfo xrSystemInfo    = {0};
  xrSystemInfo.type               = XR_TYPE_SYSTEM_GET_INFO;
  xrSystemInfo.next               = XR_NULL_HANDLE;
  xrSystemInfo.formFactor         = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY;

  XrResult xrResult = xrGetSystem(_xkOpenXRContext.xrInstance, &xrSystemInfo, &_xkOpenXRContext.xrSystemId);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to get system: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

  if(!__xkOpenXRCheckEnvironmentBlendModeSupport()) {
    result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR: Environment blend mode doesn't support");
    goto _catch; 
  }

_catch:
  return(result);
}

XkBool8 __xkOpenXRCheckEnvironmentBlendModeSupport() {
  XkBool8 result = XK_TRUE;

  uint32_t environmentBlendModeCount = 0;
  xrEnumerateEnvironmentBlendModes(_xkOpenXRContext.xrInstance, _xkOpenXRContext.xrSystemId, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 0, &environmentBlendModeCount, XR_NULL_HANDLE);
	if (environmentBlendModeCount == 0) {
		xkLogError("OpenXR: Failed to enumerate environment blend modes");
		result = XK_FALSE;
		goto _catch;
	}

  XrEnvironmentBlendMode* xrAvailableEnvironmentBlendModes = XK_NULL_HANDLE;
  xrAvailableEnvironmentBlendModes = xkAllocateMemory(sizeof(XrEnvironmentBlendMode) * environmentBlendModeCount);
	if(!xrAvailableEnvironmentBlendModes) {
		xkLogError("OpenXR: Failed to allocate environment blend modes");
		result = XK_FALSE;
		goto _catch;
	}

  xrEnumerateEnvironmentBlendModes(_xkOpenXRContext.xrInstance, _xkOpenXRContext.xrSystemId, XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, environmentBlendModeCount, XR_NULL_HANDLE, xrAvailableEnvironmentBlendModes);

	XkBool8 availableBlendModeFind = XK_FALSE;

  for(uint32_t i = 0; i < environmentBlendModeCount; i++) {
    if(xrAvailableEnvironmentBlendModes == _xkOpenXREnvironmentBlendMode) {
      availableBlendModeFind = XK_TRUE;
      break;
    }
  }

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

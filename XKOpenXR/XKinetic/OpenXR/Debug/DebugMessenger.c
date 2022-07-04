/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
#if defined(XKOPENXR_DEBUG)
XrBool32 __xkOpenXRMessageCallback(XrDebugUtilsMessageSeverityFlagsEXT xrSeverity, XrDebugUtilsMessageTypeFlagsEXT xrRype, const XrDebugUtilsMessengerCallbackDataEXT* xrCallbackData, void* user) {
	if(vkSeverity & XR_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    xkLogNotice("OpenXR: %s", xrCallbackData->pMessage);
  }	else if(vkSeverity & XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)	{
    xkLogError("OpenXR: %s", xrCallbackData->pMessage);
  } else if(vkSeverity & XR_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)	{ 
    xkLogWarning("OpenXR %s", xrCallbackData->pMessage);
  } else if(vkSeverity & XR_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    xkLogInfo("OpenXR %s", xrCallbackData->pMessage);
  }

  return(XR_FALSE);
}

void __xkOpenXRPopulateDebugMessengerCreateInfo(XrDebugUtilsMessengerCreateInfoEXT* pXrDebugMessengerCreateInfo) {
  xkAssert(pXrDebugMessengerCreateInfo);

  *pXrDebugMessengerCreateInfo                      = (XrDebugUtilsMessengerCreateInfoEXT){};
  pXrDebugMessengerCreateInfo->sType                = XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  pXrDebugMessengerCreateInfo->pNext                = XR_NULL_HANDLE;
  pXrDebugMessengerCreateInfo->flags                = 0;
  pXrDebugMessengerCreateInfo->messageSeverity      = XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  pXrDebugMessengerCreateInfo->messageType          = XR_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
  pXrDebugMessengerCreateInfo->pfnUserCallback      = __xkOpenXRMessageCallback;
  pXrDebugMessengerCreateInfo->pUserData            = XR_NULL_HANDLE;
}

XkResult __xkOpenXRCreateDebugMessenger() {
	XkResult result = XK_SUCCESS;

	PFN_xrCreateDebugUtilsMessengerEXT xrCreateDebugUtilsMessengerEXT = XR_NULL_HANDLE;
	XrResult xrResult = xrGetInstanceProcAddr(_xkOpenXRContext.xrInstance, "xrCreateDebugUtilsMessengerEXT", &xrCreateDebugUtilsMessengerEXT);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to get process address xrCreateDebugUtilsMessengerEXT: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;   
  }

  XrDebugUtilsMessengerCreateInfoEXT xrDebugUtilsMessengerCreateInfo;
  __xkOpenXRPopulateDebugMessengerCreateInfo(&xrDebugUtilsMessengerCreateInfo)

  xrResult = xrCreateDebugUtilsMessengerEXT(_xkOpenXRContext.xrInstance, &xrDebugUtilsMessengerCreateInfo, &_xkOpenXRContext.xrDebugMessenger);
  if(vkResult != VK_SUCCESS) {
     result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create debug messenger: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;   
  }

_catch:
	return(result);
}

void __xkOpenXRDestroyDebugMessenger() {
	PFN_xrDestroyDebugUtilsMessengerEXT xrDestroyDebugUtilsMessengerEXT = XR_NULL_HANDLE;
	XrResult xrResult = xrGetInstanceProcAddr(_xkOpenXRContext.xrInstance, "xrDestroyDebugUtilsMessengerEXT", &xrDestroyDebugUtilsMessengerEXT);
  if(vkResult != VK_SUCCESS) {
     result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to get process address xrDestroyDebugUtilsMessengerEXT: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;   
  }

  if(_xkOpenXRContext.xrDebugMessenger) {
  	xrDestroyDebugUtilsMessengerEXT(_xkOpenXRContext.xrDebugMessenger);

  	_xkOpenXRContext.xrDebugMessenger = XR_NULL_HANDLE;
  }
}

#endif // XKOPENXR_DEBUG

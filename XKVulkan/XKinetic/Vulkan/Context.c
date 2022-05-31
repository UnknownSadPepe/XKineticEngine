#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Window.h"

__XkVkContext _xkVkContext;

XkResult __xkVkInitializeContext() {
  XkResult result = XK_SUCCESS;

  if(_xkVkContext.initialized) goto _catch;

  result = __xkVkCreateInstance();
  if(result != XK_SUCCESS) {
    xkLogError("Vulkan: Failed to create instance: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

#ifdef XKVK_DEBUG
  result = __xkVkCreateDebugMessenger();
  if(result != XK_SUCCESS) {
    xkLogError("Vulkan: Failed to create debug messenger: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  } 
#endif // XKVK_DEBUG

  XkWindow helperWindow;
	result = xkCreateWindow(&helperWindow, "Vulkan Helper Window", 1280, 720, 0);
	if(result != XK_SUCCESS) {
		xkLogFatal("Vulkan: Failed to create helper window: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
		goto _catch;
	}

  result = __xkVkCreateSurface(&_xkVkContext.vkHelperSurface, helperWindow);
   if(result != XK_SUCCESS) {
    xkLogError("Vulkan: Failed to create helper surface: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;  
    goto _catch;
  }  

  xkDestroyWindow(helperWindow);

  result = __xkVkPickPhysicalDevice();
  if(result != XK_SUCCESS) {
    xkLogError("Vulkan: Failed to pick physical device: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  } 

  result = __xkVkCreateLogicalDevice();
  if(result != XK_SUCCESS) {
    xkLogError("Vulkan: Failed to create logical device: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }  

  _xkVkContext.initialized = XK_TRUE;

_catch:
  return(result);  
}

void __xkVkTerminateContext() {
  __xkVkDestroyLogicalDevice();
  __xkVkDestroySurface(_xkVkContext.vkHelperSurface);
#ifdef XKVK_DEBUG
  __xkVkDestroyDebugMessenger();
#endif // XKVK_DEBUG
  __xkVkDestroyInstance();

  _xkVkContext.initialized = XK_FALSE;
}

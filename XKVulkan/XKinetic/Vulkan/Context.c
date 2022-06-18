#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Platform/Window.h"

__XkVkContext _xkVkContext;

XkResult __xkVkInitializeContext() {
  XkResult result = XK_SUCCESS;

  // If Vulkan context initialize return.
  if(_xkVkContext.initialized) goto _catch;

  // Create Vulkan context instance.
  result = __xkVkCreateInstance();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan instance: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  // If debug mode, create Vulkan context debug messenger.
#ifdef XKVULKAN_DEBUG
  result = __xkVkCreateDebugMessenger();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan debug messenger: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  } 
#endif // XKVULKAN_DEBUG

  // Create helper window for create helper Vulkan surface.
  XkWindow helperWindow;
	result = xkCreateWindow(&helperWindow, "Vulkan Helper Window", 1280, 720, 0);
	if(result != XK_SUCCESS) {
		xkLogFatal("Failed to create Vulkan helper window: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
		goto _catch;
	}

  // Create Vulkan context helper surface for pick physical device.
  result = __xkVkCreateSurface(&_xkVkContext.vkHelperSurface, helperWindow);
   if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan helper surface: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;  
    goto _catch;
  }  

  // Pick best Vulkan context physical device.
  result = __xkVkPickPhysicalDevice();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to choose Vulkan physical device: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  } 

  // Destroy Vulkan context helper surface(we don't need it because, we also pick physical device).
  __xkVkDestroySurface(_xkVkContext.vkHelperSurface);

  // Destroy helper window.
  xkDestroyWindow(helperWindow);

  // Create Vulkan context logical device.
  result = __xkVkCreateLogicalDevice();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan logical device: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }  

  // Create Vulkan context command pool for all renderers.
  result = __xkVkCreateCommandPool();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan command pool: %d", result);
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  } 

  // Success, Vulkan context initialized.
  _xkVkContext.initialized = XK_TRUE;

_catch:
  return(result);  
}

void __xkVkTerminateContext() {
  // Destroy Vulkan context command pool.
  __xkVkDestroyCommandPool();

  // Destroy Vulkan context logical device.
  __xkVkDestroyLogicalDevice();

  // If debug mode, destroy Vulkan context debug messenger. 
#ifdef XKVULKAN_DEBUG
  __xkVkDestroyDebugMessenger();
#endif // XKVULKAN_DEBUG

  // Destroy Vulkan context instance.
  __xkVkDestroyInstance();

  // Vulkan context released.
  _xkVkContext.initialized = XK_FALSE;
}

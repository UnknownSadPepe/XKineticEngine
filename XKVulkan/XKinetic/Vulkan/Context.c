#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Platform/Window.h"

__XkVkContext _xkVkContext;

XkString __xkVkGetErrorString(VkResult vkResult) {
  switch(vkResult) {
    case VK_SUCCESS:                        return "Success";
    case VK_NOT_READY:                      return "A Vulkan fence or query has not yet completed";
    case VK_TIMEOUT:                        return "A Vulkan wait operation has not completed in the specified time";
    case VK_EVENT_SET:                      return "A Vulkan event is signaled";
    case VK_EVENT_RESET:                    return "A Vulkan event is unsignaled";
    case VK_INCOMPLETE:                     return "A return Vulkan array was too small for the result";
    case VK_ERROR_OUT_OF_HOST_MEMORY:       return "A Vulkan host memory allocation has failed";
    case VK_ERROR_OUT_OF_DEVICE_MEMORY:     return "A Vulkan device memory allocation has failed";
    case VK_ERROR_INITIALIZATION_FAILED:    return "Initialization of an Vulkan object could not be completed for implementation-specific reasons";
    case VK_ERROR_DEVICE_LOST:              return "The Vulkan logical or physical device has been lost";
    case VK_ERROR_MEMORY_MAP_FAILED:        return "Mapping of a Vukan memory object has failed";
    case VK_ERROR_LAYER_NOT_PRESENT:        return "A requested Vulkan layer is not present or could not be loaded";
    case VK_ERROR_EXTENSION_NOT_PRESENT:    return "A requested Vulkan extension is not supported";
    case VK_ERROR_FEATURE_NOT_PRESENT:      return "A requested Vulkan feature is not supported";
    case VK_ERROR_INCOMPATIBLE_DRIVER:      return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
    case VK_ERROR_TOO_MANY_OBJECTS:         return "Too many Vulkan objects of the type have already been created";
    case VK_ERROR_FORMAT_NOT_SUPPORTED:     return "A Vulkan requested format is not supported on this device";
    case VK_ERROR_SURFACE_LOST_KHR:         return "A Vulkan surface is no longer available";
    case VK_ERROR_OUT_OF_POOL_MEMORY:       return "A Vulkan allocation failed due to having no more space in the descriptor pool";
    case VK_SUBOPTIMAL_KHR:                 return "A Vulkan swapchain no longer matches the surface properties exactly, but can still be used";
    case VK_ERROR_OUT_OF_DATE_KHR:          return "A Vulkan surface has changed in such a way that it is no longer compatible with the swapchain";
    case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "The display used by a Vulkan swapchain does not use the same presentable image layout";
    case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
    case VK_ERROR_VALIDATION_FAILED_EXT:    return "A Vulkan validation layer found an error";
    default:                                return "unknown Vulkan error";
  }
}

XkResult __xkVkInitializeContext(void) {
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

void __xkVkTerminateContext(void) {
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

#include "XKinetic/Vulkan/Internal.h"

#ifdef XKVULKAN_DEBUG
static VKAPI_ATTR VkBool32 VKAPI_CALL __xkVkMessageCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* data) {
	if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    xkLogNotice("Vulkan: %s", callbackData->pMessage);
  }	else if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)	{
    xkLogError("Vulkan: %s", callbackData->pMessage);
  } else if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)	{ 
    xkLogWarning("Vulkan %s", callbackData->pMessage);
  } else if(severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    xkLogInfo("Vulkan %s", callbackData->pMessage);
  }

  return(VK_FALSE);
}

void __xkVkPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* pVkDebugMessengerCreateInfo) {
  *pVkDebugMessengerCreateInfo                      = (VkDebugUtilsMessengerCreateInfoEXT){0};
  pVkDebugMessengerCreateInfo->sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  pVkDebugMessengerCreateInfo->pNext                = VK_NULL_HANDLE;
  pVkDebugMessengerCreateInfo->flags                = 0;
  pVkDebugMessengerCreateInfo->messageSeverity      = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  pVkDebugMessengerCreateInfo->messageType          = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
  pVkDebugMessengerCreateInfo->pfnUserCallback      = __xkVkMessageCallback;
  pVkDebugMessengerCreateInfo->pUserData            = VK_NULL_HANDLE;
}

XkResult __xkVkCreateDebugMessenger(void) {
  XkResult result = XK_SUCCESS;

  // Get Vulkan 'vkCreateDebugUtilsMessengerEXT' process adderss.
  PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_xkVkContext.vkInstance, "vkCreateDebugUtilsMessengerEXT");
  if(!vkCreateDebugUtilsMessenger) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to get instance proc address vkCreateDebugUtilsMessengerEXT: %s", __xkVkGetErrorString(VK_ERROR_EXTENSION_NOT_PRESENT));
    goto _catch;
  }

  // Initialize Vulkan debug utils messenger create info.
  VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfo;
  __xkVkPopulateDebugMessengerCreateInfo(&vkDebugUtilsMessengerCreateInfo);

  // Create Vulkan debug utils messenger.
  VkResult vkResult = vkCreateDebugUtilsMessenger(_xkVkContext.vkInstance, &vkDebugUtilsMessengerCreateInfo, VK_NULL_HANDLE, &_xkVkContext.vkDebugMessenger);
  if(vkResult != VK_SUCCESS) {
     result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create debug messenger: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

_catch:
  return(result);  
}

void __xkVkDestroyDebugMessenger(void) {
    // Get Vulkan 'vkDestroyDebugUtilsMessengerEXT' process adderss.
  PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_xkVkContext.vkInstance, "vkDestroyDebugUtilsMessengerEXT");
  if(!vkDestroyDebugUtilsMessenger) {
    xkLogError("Vulkan: Failed to get instance proc address vkDestroyDebugUtilsMessengerEXT: %s", __xkVkGetErrorString(VK_ERROR_EXTENSION_NOT_PRESENT));
    return;
  }

  // Destroy Vulkan debug utils messenger.
  vkDestroyDebugUtilsMessenger(_xkVkContext.vkInstance, _xkVkContext.vkDebugMessenger, VK_NULL_HANDLE);
}
#endif // XKVULKAN_DEBUG

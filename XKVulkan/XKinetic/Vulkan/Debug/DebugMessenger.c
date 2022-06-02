#include "XKinetic/Vulkan/Internal.h"

#ifdef XKVK_DEBUG
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
  *pVkDebugMessengerCreateInfo = (VkDebugUtilsMessengerCreateInfoEXT) {
    .sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
    .pNext                = VK_NULL_HANDLE,
    .flags                = 0,
    .messageSeverity      = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    .messageType          = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT,
    .pfnUserCallback      = __xkVkMessageCallback,
    .pUserData            = VK_NULL_HANDLE
  };
}

XkResult __xkVkCreateDebugMessenger(void) {
  XkResult result = XK_SUCCESS;

  // Get Vulkan 'vkCreateDebugUtilsMessengerEXT' proc adderss.
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
    // Get Vulkan 'vkDestroyDebugUtilsMessengerEXT' proc adderss.
  PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_xkVkContext.vkInstance, "vkDestroyDebugUtilsMessengerEXT");
  if(!vkDestroyDebugUtilsMessenger) {
    xkLogError("Vulkan: Failed to get instance proc address vkDestroyDebugUtilsMessengerEXT: %s", __xkVkGetErrorString(VK_ERROR_EXTENSION_NOT_PRESENT));
    return;
  }

  // Destroy Vulkan debug utils messenger.
  vkDestroyDebugUtilsMessenger(_xkVkContext.vkInstance, _xkVkContext.vkDebugMessenger, VK_NULL_HANDLE);
}
#endif // XKVK_DEBUG

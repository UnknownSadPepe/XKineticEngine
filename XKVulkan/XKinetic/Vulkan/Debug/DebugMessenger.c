/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
#if defined(XKVULKAN_DEBUG)
static VKAPI_ATTR VkBool32 VKAPI_CALL __xkVulkanMessageCallback(VkDebugUtilsMessageSeverityFlagBitsEXT vkSeverity, VkDebugUtilsMessageTypeFlagsEXT vkType, const VkDebugUtilsMessengerCallbackDataEXT* vkCallbackData, void* user) {
	if(vkSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    xkLogNotice("Vulkan: %s", vkCallbackData->pMessage);
  }	else if(vkSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)	{
    xkLogError("Vulkan: %s", vkCallbackData->pMessage);
  } else if(vkSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)	{ 
    xkLogWarning("Vulkan %s", vkCallbackData->pMessage);
  } else if(vkSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    xkLogInfo("Vulkan %s", vkCallbackData->pMessage);
  }

  return(VK_FALSE);
}

void __xkVulkanPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* pVkDebugMessengerCreateInfo) {
  xkAssert(pVkDebugMessengerCreateInfo);

  *pVkDebugMessengerCreateInfo                      = (VkDebugUtilsMessengerCreateInfoEXT){0};
  pVkDebugMessengerCreateInfo->sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  pVkDebugMessengerCreateInfo->pNext                = VK_NULL_HANDLE;
  pVkDebugMessengerCreateInfo->flags                = 0;
  pVkDebugMessengerCreateInfo->messageSeverity      = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  pVkDebugMessengerCreateInfo->messageType          = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
  pVkDebugMessengerCreateInfo->pfnUserCallback      = __xkVulkanMessageCallback;
  pVkDebugMessengerCreateInfo->pUserData            = VK_NULL_HANDLE;
}

XkResult __xkVulkanCreateDebugMessenger() {
  XkResult result = XK_SUCCESS;

  PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessenger = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_xkVulkanContext.vkInstance, "vkCreateDebugUtilsMessengerEXT");
  if(!vkCreateDebugUtilsMessenger) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to get process address vkCreateDebugUtilsMessengerEXT: %s", __xkVulkanGetResultString(VK_ERROR_EXTENSION_NOT_PRESENT));
    goto _catch;
  }

  VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfo;
  __xkVulkanPopulateDebugMessengerCreateInfo(&vkDebugUtilsMessengerCreateInfo);

  VkResult vkResult = vkCreateDebugUtilsMessenger(_xkVulkanContext.vkInstance, &vkDebugUtilsMessengerCreateInfo, VK_NULL_HANDLE, &_xkVulkanContext.vkDebugMessenger);
  if(vkResult != VK_SUCCESS) {
     result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create debug messenger: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;   
  }

_catch:
  return(result);  
}

void __xkVulkanDestroyDebugMessenger() {
  PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessenger = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(_xkVulkanContext.vkInstance, "vkDestroyDebugUtilsMessengerEXT");
  if(!vkDestroyDebugUtilsMessenger) {
    xkLogError("Vulkan: Failed to get process address vkDestroyDebugUtilsMessengerEXT: %s", __xkVulkanGetResultString(VK_ERROR_EXTENSION_NOT_PRESENT));
    return;
  }

  if(_xkVulkanContext.vkDebugMessenger) {
    vkDestroyDebugUtilsMessenger(_xkVulkanContext.vkInstance, _xkVulkanContext.vkDebugMessenger, VK_NULL_HANDLE);

    _xkVulkanContext.vkDebugMessenger = VK_NULL_HANDLE;
  }
}
#endif // XKVULKAN_DEBUG

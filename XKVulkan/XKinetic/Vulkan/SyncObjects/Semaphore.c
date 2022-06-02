#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateSemaphore(VkSemaphore* pVkSemaphore) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan semaphore create info.
  const VkSemaphoreCreateInfo vkSemaphoreCreateInfo = {
    .sType    = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .flags    = 0
  };

  // Create Vulkan semaphore.
  VkResult vkResult = vkCreateSemaphore(_xkVkContext.vkLogicalDevice, &vkSemaphoreCreateInfo, VK_NULL_HANDLE, pVkSemaphore);
  if(vkResult != VK_SUCCESS) {
		xkLogError("Failed to create Vulkan semaphore: %s", __xkVkGetErrorString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;  
  }

_catch:
  return(result);
}

void __xkVkDestroySemaphore(VkSemaphore vkSemaphore) {
  // Destroy Vulkan semaphore.
  vkDestroySemaphore(_xkVkContext.vkLogicalDevice, vkSemaphore, VK_NULL_HANDLE);
}


/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateSemaphore(VkSemaphore* pVkSemaphore) {
  xkAssert(pVkSemaphore);

  XkResult result = XK_SUCCESS;

  VkSemaphoreCreateInfo vkSemaphoreCreateInfo = {};
  vkSemaphoreCreateInfo.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
  vkSemaphoreCreateInfo.pNext                 = VK_NULL_HANDLE;
  vkSemaphoreCreateInfo.flags                 = 0;

  VkResult vkResult = vkCreateSemaphore(_xkVulkanContext.vkLogicalDevice, &vkSemaphoreCreateInfo, VK_NULL_HANDLE, pVkSemaphore);
  if(vkResult != VK_SUCCESS) {
		xkLogError("Vulkan: Failed to create semaphore: %s", __xkVulkanGetResultString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;  
  }

_catch:
  return(result);
}

void __xkVulkanDestroySemaphore(VkSemaphore vkSemaphore) {
  xkAssert(vkSemaphore);

  vkDestroySemaphore(_xkVulkanContext.vkLogicalDevice, vkSemaphore, VK_NULL_HANDLE);
}


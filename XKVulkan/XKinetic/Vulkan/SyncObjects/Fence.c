#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateFence(VkFence* pVkFence) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan fence create info.
  VkFenceCreateInfo vkFenceCreateInfo = {0};
  vkFenceCreateInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  vkFenceCreateInfo.pNext             = VK_NULL_HANDLE;
  vkFenceCreateInfo.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

  // Create Vulkan fence.
  VkResult vkResult = vkCreateFence(_xkVkContext.vkLogicalDevice, &vkFenceCreateInfo, VK_NULL_HANDLE, pVkFence);
  if(vkResult != VK_SUCCESS) {
		xkLogError("Failed to create Vulkan fence: %s", __xkVkGetErrorString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;  
  }

_catch:
  return(result);
}

void __xkVkDestroyFence(VkFence vkFence) {
  // Destroy Vulkan fence.
  vkDestroyFence(_xkVkContext.vkLogicalDevice, vkFence, VK_NULL_HANDLE);
}

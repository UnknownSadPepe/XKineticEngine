/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateFence(VkFence* pVkFence) {
  xkAssert(pVkFence);

  XkResult result = XK_SUCCESS;

  VkFenceCreateInfo vkFenceCreateInfo = {};
  vkFenceCreateInfo.sType             = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  vkFenceCreateInfo.pNext             = VK_NULL_HANDLE;
  vkFenceCreateInfo.flags             = VK_FENCE_CREATE_SIGNALED_BIT;

  VkResult vkResult = vkCreateFence(_xkVulkanContext.vkLogicalDevice, &vkFenceCreateInfo, VK_NULL_HANDLE, pVkFence);
  if(vkResult != VK_SUCCESS) {
		xkLogError("Vulkan: Failed to create fence: %s", __xkVulkanGetResultString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;  
  }

_catch:
  return(result);
}

void __xkVulkanDestroyFence(VkFence vkFence) {
  xkAssert(vkFence);

  vkDestroyFence(_xkVulkanContext.vkLogicalDevice, vkFence, VK_NULL_HANDLE);
}

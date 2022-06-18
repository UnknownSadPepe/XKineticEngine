#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateCommandBuffer(VkCommandBuffer* pVkCommandBuffer, const VkCommandBufferLevel vkCommandBufferLevel) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan command buffer allocate info.
	VkCommandBufferAllocateInfo vkCommandBufferAllocateInfo = {0};
  vkCommandBufferAllocateInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  vkCommandBufferAllocateInfo.pNext                       = VK_NULL_HANDLE;
	vkCommandBufferAllocateInfo.commandPool                 = _xkVkContext.vkCommandPool;
	vkCommandBufferAllocateInfo.level                       = vkCommandBufferLevel;
	vkCommandBufferAllocateInfo.commandBufferCount          = 1;
	
  // Allocate Vulkan command buffer.
	VkResult vkResult = vkAllocateCommandBuffers(_xkVkContext.vkLogicalDevice, &vkCommandBufferAllocateInfo, pVkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to allocate Vulkan command buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroyCommandBuffer(VkCommandBuffer vkCommandBuffer) {
  // Destroy Vulkan command buffer.
  vkFreeCommandBuffers(_xkVkContext.vkLogicalDevice, _xkVkContext.vkCommandPool, 1, &vkCommandBuffer);
}

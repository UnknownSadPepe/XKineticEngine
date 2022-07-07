/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateCommandBuffer(VkCommandBuffer* pVkCommandBuffer, const VkCommandBufferLevel vkCommandBufferLevel) {
  xkAssert(pVkCommandBuffer);

  XkResult result = XK_SUCCESS;

	VkCommandBufferAllocateInfo vkCommandBufferAllocateInfo = {0};
  vkCommandBufferAllocateInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  vkCommandBufferAllocateInfo.pNext                       = VK_NULL_HANDLE;
	vkCommandBufferAllocateInfo.commandPool                 = _xkVulkanContext.vkCommandPool;
	vkCommandBufferAllocateInfo.level                       = vkCommandBufferLevel;
	vkCommandBufferAllocateInfo.commandBufferCount          = 1;
	
	VkResult vkResult = vkAllocateCommandBuffers(_xkVulkanContext.vkLogicalDevice, &vkCommandBufferAllocateInfo, pVkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to allocate command buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroyCommandBuffer(VkCommandBuffer vkCommandBuffer) {
  xkAssert(vkCommandBuffer);

  vkFreeCommandBuffers(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.vkCommandPool, 1, &vkCommandBuffer);
}

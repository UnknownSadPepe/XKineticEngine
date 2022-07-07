/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateBuffer(VkBuffer* const pVkBuffer, VkDeviceMemory* const pVkBufferMemory, const VkDeviceSize vkSize, const VkBufferUsageFlags vkUsage, const VkMemoryPropertyFlags vkMemoryProperties, const void* data) {
  xkAssert(pVkBuffer);
  xkAssert(pVkBufferMemory);

  XkResult result = XK_SUCCESS;

  VkBufferCreateInfo vkBufferCreateInfo       = {0};
  vkBufferCreateInfo.sType                    = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  vkBufferCreateInfo.pNext                    = VK_NULL_HANDLE;
  vkBufferCreateInfo.flags                    = 0;
	vkBufferCreateInfo.size                     = vkSize;
	vkBufferCreateInfo.usage                    = vkUsage;
	vkBufferCreateInfo.sharingMode              = VK_SHARING_MODE_EXCLUSIVE;
	vkBufferCreateInfo.queueFamilyIndexCount    = 0;
	vkBufferCreateInfo.pQueueFamilyIndices      = VK_NULL_HANDLE;

  VkResult vkResult = vkCreateBuffer(_xkVulkanContext.vkLogicalDevice, &vkBufferCreateInfo, VK_NULL_HANDLE, pVkBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

  VkBuffer vkBuffer = *pVkBuffer;

	VkMemoryRequirements vkMemoryRequirements;
	vkGetBufferMemoryRequirements(_xkVulkanContext.vkLogicalDevice, vkBuffer, &vkMemoryRequirements);

  VkMemoryAllocateInfo vkMemoryAllocateInfo = {0};
	vkMemoryAllocateInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  vkMemoryAllocateInfo.pNext                = VK_NULL_HANDLE;
	vkMemoryAllocateInfo.allocationSize       = vkMemoryRequirements.size;
	vkMemoryAllocateInfo.memoryTypeIndex      = __xkVulkanFindMemoryType(vkMemoryRequirements.memoryTypeBits, vkMemoryProperties);

  vkResult = vkAllocateMemory(_xkVulkanContext.vkLogicalDevice, &vkMemoryAllocateInfo, VK_NULL_HANDLE, pVkBufferMemory);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to allocate buffer memory: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;   
  }

  VkDeviceMemory vkBufferMemory = *pVkBufferMemory;

	// If a pointer to the buffer data has been passed, map the Vulkan buffer and copy over the data.
	if (data) {
		__xkVulkanMapBuffer(vkBufferMemory, vkMemoryRequirements.size, data);
	}

	vkResult = vkBindBufferMemory(_xkVulkanContext.vkLogicalDevice, vkBuffer, vkBufferMemory, 0);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to bind buffer memory: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;   
  }

_catch:
  return(result);
}

void __xkVulkanDestroyBuffer(VkBuffer vkBuffer, VkDeviceMemory vkBufferMemory) {
  xkAssert(vkBuffer);
  xkAssert(vkBufferMemory);

	vkDestroyBuffer(_xkVulkanContext.vkLogicalDevice, vkBuffer, VK_NULL_HANDLE);
  
  vkFreeMemory(_xkVulkanContext.vkLogicalDevice, vkBufferMemory, VK_NULL_HANDLE);
}

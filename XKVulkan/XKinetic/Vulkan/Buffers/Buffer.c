#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateBuffer(VkBuffer* const pVkBuffer, VkDeviceMemory* const pVkBufferMemory, const VkDeviceSize vkSize, const VkBufferUsageFlags vkUsage, const VkMemoryPropertyFlags vkMemoryProperties, const void* data) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan buffer create info.
  VkBufferCreateInfo vkBufferCreateInfo       = {0};
  vkBufferCreateInfo.sType                    = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  vkBufferCreateInfo.pNext                    = VK_NULL_HANDLE;
  vkBufferCreateInfo.flags                    = 0;
	vkBufferCreateInfo.size                     = vkSize;
	vkBufferCreateInfo.usage                    = vkUsage;
	vkBufferCreateInfo.sharingMode              = VK_SHARING_MODE_EXCLUSIVE;
	vkBufferCreateInfo.queueFamilyIndexCount    = 0;
	vkBufferCreateInfo.pQueueFamilyIndices      = VK_NULL_HANDLE;

  // Create Vulkan buffer.
  VkResult vkResult = vkCreateBuffer(_xkVkContext.vkLogicalDevice, &vkBufferCreateInfo, VK_NULL_HANDLE, pVkBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

  // Template Vulkan buffer.
  VkBuffer vkBuffer = *pVkBuffer;

	// Get Vulkan buffer memory requirements.
	VkMemoryRequirements vkMemoryRequirements;
	vkGetBufferMemoryRequirements(_xkVkContext.vkLogicalDevice, vkBuffer, &vkMemoryRequirements);

  // Initialize Vulkan buffer memory allocate info.
  VkMemoryAllocateInfo vkMemoryAllocateInfo = {0};
	vkMemoryAllocateInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  vkMemoryAllocateInfo.pNext                = VK_NULL_HANDLE;
	vkMemoryAllocateInfo.allocationSize       = vkMemoryRequirements.size;
	vkMemoryAllocateInfo.memoryTypeIndex      = __xkVkFindMemoryType(vkMemoryRequirements.memoryTypeBits, vkMemoryProperties);

  // Allocate Vulkan buffer memory.
  vkResult = vkAllocateMemory(_xkVkContext.vkLogicalDevice, &vkMemoryAllocateInfo, VK_NULL_HANDLE, pVkBufferMemory);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to allocate Vulkan buffer memory: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

  // Template Vulkan buffer memory.
  VkDeviceMemory vkBufferMemory = *pVkBufferMemory;

	// If a pointer to the buffer data has been passed, map the Vulkan buffer and copy over the data.
	if (data) {
		__xkVkMapBuffer(vkBufferMemory, vkMemoryRequirements.size, data);
	}

  // Bind Vulkan buffer memory.
	vkResult = vkBindBufferMemory(_xkVkContext.vkLogicalDevice, vkBuffer, vkBufferMemory, 0);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to bind Vulkan buffer memory: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

_catch:
  return(result);
}

void __xkVkDestroyBuffer(VkBuffer vkBuffer, VkDeviceMemory vkBufferMemory) {
  // Destroy Vulkan bufer.
	vkDestroyBuffer(_xkVkContext.vkLogicalDevice, vkBuffer, VK_NULL_HANDLE);
  
  // Free Vulkan bufer memory.
  vkFreeMemory(_xkVkContext.vkLogicalDevice, vkBufferMemory, VK_NULL_HANDLE);
}

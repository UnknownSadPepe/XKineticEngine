#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateBuffer(VkBuffer* const pVkBuffer, VkDeviceMemory* const pVkBufferMemory, const VkDeviceSize vkSize, const VkBufferUsageFlags vkUsage, const VkMemoryPropertyFlags vkMemoryProperties, const void* data) {
  XkResult result = XK_SUCCESS;

  // Set Vulkan image sharing mode.
  // Set queue family index count.
  // Set queue family indices.
  VkSharingMode vkImageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  uint32_t queueFamilyIndexCount = 1;
  uint32_t queueFamilyIndices[] = {
    _xkVkContext.queueFamilyIndices.graphics,
    _xkVkContext.queueFamilyIndices.present
  };
  if(_xkVkContext.queueFamilyIndices.graphics != _xkVkContext.queueFamilyIndices.present) {
    vkImageSharingMode = VK_SHARING_MODE_CONCURRENT;
    queueFamilyIndexCount = 2;
  }

  // Initialize Vulkan buffer create info.
  const VkBufferCreateInfo vkBufferCreateInfo = {
    .sType                    = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .pNext                    = VK_NULL_HANDLE,
    .flags                    = 0,
	  .size                     = vkSize,
	  .usage                    = vkUsage,
	  .sharingMode              = vkImageSharingMode,
	  .queueFamilyIndexCount    = queueFamilyIndexCount,
	  .pQueueFamilyIndices      = queueFamilyIndices
  };

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
  const VkMemoryAllocateInfo vkMemoryAllocateInfo = {
	  .sType            = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext            = VK_NULL_HANDLE,
	  .allocationSize   = vkMemoryRequirements.size,
	  .memoryTypeIndex  = __xkVkFindMemoryType(vkMemoryRequirements.memoryTypeBits, vkMemoryProperties)
  };

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

XkResult __xkVkMapBuffer(VkDeviceMemory vkBufferMemory, const VkDeviceSize vkDeviceSize, const void* data) {
  XkResult result = XK_SUCCESS;

  void* mapped;
  // Map Vulkan buffer memory.
	VkResult vkResult = vkMapMemory(_xkVkContext.vkLogicalDevice, vkBufferMemory, 0, vkDeviceSize, 0, &mapped);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to map Vulkan buffer memory: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

  // Copy data.
	xkCopyMemory((XkHandle)mapped, (XkHandle)data, (XkSize)vkDeviceSize);

  // Unmap Vulkan buffer memory.
	vkUnmapMemory(_xkVkContext.vkLogicalDevice, vkBufferMemory);

_catch:
  return(result);
}

XkResult __xkVkCopyBuffer(VkBuffer vkDstBuffer, const VkBuffer vkSrcBuffer, const VkDeviceSize vkSize) {
  XkResult result = XK_SUCCESS;

  // Begin Vulkan single command buffer.
  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVkBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to begin Vulkan command buffer");
    goto _catch;   
  }

  // Initialize Vulkan buffer copy info.
  const VkBufferCopy vkBufferCopyInfo = {
    .srcOffset = 0,
    .dstOffset = 0,
    .size = vkSize
  };

  // Copy Vulkan buffer.
  vkCmdCopyBuffer(vkSingleCommandBuffer, vkSrcBuffer, vkDstBuffer, 1, &vkBufferCopyInfo);

  // End Vulkan single command buffer.
  result = __xkVkEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to end Vulkan command buffer");
    goto _catch;   
  }

_catch:
  return(result);
}

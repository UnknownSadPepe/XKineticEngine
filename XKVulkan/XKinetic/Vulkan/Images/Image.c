#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateImage(VkImage* const pVkImage, VkDeviceMemory* const pVkImageMemory, const VkImageType vkImageType, const VkFormat vkImageFormat, const VkExtent3D vkExtent, const VkSampleCountFlagBits vkSamples, const VkImageTiling vkTiling, const VkImageUsageFlags vkUsage, const VkMemoryPropertyFlags vkMemoryProperties, const uint32_t mipLevels) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan image create info.
	const VkImageCreateInfo vkImageCreateInfo = {
    .sType                  = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .pNext                  = VK_NULL_HANDLE,
	  .flags                  = 0,
	  .imageType              = vkImageType,
	  .format                 = vkImageFormat,
	  .extent                 = vkExtent,
	  .mipLevels              = mipLevels,
	  .arrayLayers            = 1,
	  .samples                = vkSamples,
	  .tiling                 = vkTiling,
	  .usage                  = vkUsage,
	  .sharingMode            = VK_SHARING_MODE_EXCLUSIVE,
    .queueFamilyIndexCount  = 0,
    .pQueueFamilyIndices    = VK_NULL_HANDLE,
	  .initialLayout          = VK_IMAGE_LAYOUT_UNDEFINED
  };
	
  // Create Vulkan image.
  VkResult vkResult = vkCreateImage(_xkVkContext.vkLogicalDevice, &vkImageCreateInfo, VK_NULL_HANDLE, pVkImage);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan image: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

  // Template Vulkan image.
  VkImage vkImage = *pVkImage;

  // Get Vulkan image memory requirements.
	VkMemoryRequirements vkMemoryRequirements;
	vkGetImageMemoryRequirements(_xkVkContext.vkLogicalDevice, *pVkImage, &vkMemoryRequirements);

  // Initialize Vulkan image memory allocate info.
  const VkMemoryAllocateInfo vkMemoryAllocateInfo = {
	  .sType            = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext            = VK_NULL_HANDLE,
	  .allocationSize   = vkMemoryRequirements.size,
	  .memoryTypeIndex  = __xkVkFindMemoryType(vkMemoryRequirements.memoryTypeBits, vkMemoryProperties)
  };

  // Allocate Vulkan image memory.
  vkResult = vkAllocateMemory(_xkVkContext.vkLogicalDevice, &vkMemoryAllocateInfo, VK_NULL_HANDLE, pVkImageMemory);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to allocate Vulkan image memory: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

  // Template Vulkan image memory.
  VkDeviceMemory vkImageMemory = *pVkImageMemory;

  // Bind Vulkan image memory.
	vkResult = vkBindImageMemory(_xkVkContext.vkLogicalDevice, vkImage, vkImageMemory, 0);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to bind Vulkan image memory: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

_catch:
  return(result);
}

void __xkVkDestroyImage(VkImage vkImage, VkDeviceMemory  vkImageMemory) {
  // Destroy Vulkan image.
	vkDestroyImage(_xkVkContext.vkLogicalDevice, vkImage, VK_NULL_HANDLE);
  // Free Vulkan image memory.
  vkFreeMemory(_xkVkContext.vkLogicalDevice, vkImageMemory, VK_NULL_HANDLE);
}

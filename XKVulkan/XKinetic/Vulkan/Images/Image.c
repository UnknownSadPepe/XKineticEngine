#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateImage(VkImage* const pVkImage, VkDeviceMemory* const pVkImageMemory, const VkImageType vkImageType, const VkFormat vkImageFormat, const VkExtent3D vkExtent, const VkSampleCountFlagBits vkSamples, const VkImageTiling vkTiling, const VkImageUsageFlags vkUsage, const VkMemoryPropertyFlags vkMemoryProperties, const uint32_t mipLevels) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan image create info.
	VkImageCreateInfo vkImageCreateInfo       = {0};
  vkImageCreateInfo.sType                   = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  vkImageCreateInfo.pNext                   = VK_NULL_HANDLE;
	vkImageCreateInfo.flags                   = 0;
	vkImageCreateInfo.imageType               = vkImageType;
	vkImageCreateInfo.format                  = vkImageFormat;
	vkImageCreateInfo.extent                  = vkExtent;
	vkImageCreateInfo.mipLevels               = mipLevels;
	vkImageCreateInfo.arrayLayers             = 1;
	vkImageCreateInfo.samples                 = vkSamples;
	vkImageCreateInfo.tiling                  = vkTiling;
	vkImageCreateInfo.usage                   = vkUsage;
	vkImageCreateInfo.sharingMode             = VK_SHARING_MODE_EXCLUSIVE;
  vkImageCreateInfo.queueFamilyIndexCount   = 0;
  vkImageCreateInfo.pQueueFamilyIndices     = VK_NULL_HANDLE;
	vkImageCreateInfo.initialLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
	
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
  VkMemoryAllocateInfo vkMemoryAllocateInfo = {0};
	vkMemoryAllocateInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  vkMemoryAllocateInfo.pNext                = VK_NULL_HANDLE;
	vkMemoryAllocateInfo.allocationSize       = vkMemoryRequirements.size;
	vkMemoryAllocateInfo.memoryTypeIndex      = __xkVkFindMemoryType(vkMemoryRequirements.memoryTypeBits, vkMemoryProperties);

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

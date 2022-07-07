/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateImage(VkImage* const pVkImage, VkDeviceMemory* const pVkImageMemory, const VkImageType vkImageType, const VkFormat vkImageFormat, const VkExtent3D vkExtent, const VkSampleCountFlagBits vkSamples, const VkImageTiling vkTiling, const VkImageUsageFlags vkUsage, const VkMemoryPropertyFlags vkMemoryProperties, const uint32_t mipLevels) {
  xkAssert(pVkImage);
  xkAssert(pVkImageMemory);
  xkAssert(mipLevels > 0);

  XkResult result = XK_SUCCESS;

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
	
  VkResult vkResult = vkCreateImage(_xkVulkanContext.vkLogicalDevice, &vkImageCreateInfo, VK_NULL_HANDLE, pVkImage);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create image: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

  VkImage vkImage = *pVkImage;

	VkMemoryRequirements vkMemoryRequirements;
	vkGetImageMemoryRequirements(_xkVulkanContext.vkLogicalDevice, *pVkImage, &vkMemoryRequirements);

  VkMemoryAllocateInfo vkMemoryAllocateInfo = {0};
	vkMemoryAllocateInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  vkMemoryAllocateInfo.pNext                = VK_NULL_HANDLE;
	vkMemoryAllocateInfo.allocationSize       = vkMemoryRequirements.size;
	vkMemoryAllocateInfo.memoryTypeIndex      = __xkVulkanFindMemoryType(vkMemoryRequirements.memoryTypeBits, vkMemoryProperties);

  vkResult = vkAllocateMemory(_xkVulkanContext.vkLogicalDevice, &vkMemoryAllocateInfo, VK_NULL_HANDLE, pVkImageMemory);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to allocate Vulkan image memory: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;   
  }

  VkDeviceMemory vkImageMemory = *pVkImageMemory;

	vkResult = vkBindImageMemory(_xkVulkanContext.vkLogicalDevice, vkImage, vkImageMemory, 0);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to bind image memory: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;   
  }

_catch:
  return(result);
}

void __xkVulkanDestroyImage(VkImage vkImage, VkDeviceMemory  vkImageMemory) {
  xkAssert(vkImage);
  xkAssert(vkImageMemory);

	vkDestroyImage(_xkVulkanContext.vkLogicalDevice, vkImage, VK_NULL_HANDLE);
  
  vkFreeMemory(_xkVulkanContext.vkLogicalDevice, vkImageMemory, VK_NULL_HANDLE);
}

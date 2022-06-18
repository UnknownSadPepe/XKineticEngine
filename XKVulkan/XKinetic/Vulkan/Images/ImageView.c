#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateImageView(VkImageView* const pVkImageView, VkImage vkImage, const VkFormat vkFormat, const VkImageAspectFlags vkAspectMask, const uint32_t mipLevels) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan image view create info.
	VkImageViewCreateInfo vkImageViewCreateInfo             = {0};
	vkImageViewCreateInfo.sType                             = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  vkImageViewCreateInfo.pNext                             = VK_NULL_HANDLE;
  vkImageViewCreateInfo.flags                             = 0;
	vkImageViewCreateInfo.image                             = vkImage;
	vkImageViewCreateInfo.viewType                          = VK_IMAGE_VIEW_TYPE_2D;
	vkImageViewCreateInfo.format                            = vkFormat;
  vkImageViewCreateInfo.components.r                      = VK_COMPONENT_SWIZZLE_R;
  vkImageViewCreateInfo.components.g                      = VK_COMPONENT_SWIZZLE_G; 
  vkImageViewCreateInfo.components.b                      = VK_COMPONENT_SWIZZLE_B; 
  vkImageViewCreateInfo.components.a                      = VK_COMPONENT_SWIZZLE_A;
  vkImageViewCreateInfo.subresourceRange.aspectMask       = vkAspectMask; 
  vkImageViewCreateInfo.subresourceRange.baseMipLevel     = 0; 
  vkImageViewCreateInfo.subresourceRange.levelCount       = mipLevels; 
  vkImageViewCreateInfo.subresourceRange.baseArrayLayer   = 0; 
  vkImageViewCreateInfo.subresourceRange.layerCount       = 1;

  // Create Vulkan image view.
	VkResult vkResult = vkCreateImageView(_xkVkContext.vkLogicalDevice, &vkImageViewCreateInfo, VK_NULL_HANDLE, pVkImageView);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan image view: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroyImageView(VkImageView vkImageView) {
  // Destroy Vulkan image view.
  vkDestroyImageView(_xkVkContext.vkLogicalDevice, vkImageView, VK_NULL_HANDLE);
}


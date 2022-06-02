#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateImageView(VkImageView* const pVkImageView, VkImage vkImage, const VkFormat vkFormat, const VkImageAspectFlags vkAspectMask, const uint32_t mipLevels) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan image view create info.
	const VkImageViewCreateInfo vkImageViewCreateInfo = {
	  .sType              = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .pNext              = VK_NULL_HANDLE,
    .flags              = 0,
	  .image              = vkImage,
	  .viewType           = VK_IMAGE_VIEW_TYPE_2D,
	  .format             = vkFormat,
	  .components         = {.r = VK_COMPONENT_SWIZZLE_R, .g = VK_COMPONENT_SWIZZLE_G, .b = VK_COMPONENT_SWIZZLE_B, .a = VK_COMPONENT_SWIZZLE_A},
	  .subresourceRange = {.aspectMask = vkAspectMask, .baseMipLevel = 0, .levelCount = mipLevels, .baseArrayLayer = 0, .layerCount = 1}
  };

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


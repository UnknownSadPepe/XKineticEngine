/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateImageView(VkImageView* const pVkImageView, VkImage vkImage, const VkFormat vkFormat, const VkImageAspectFlags vkAspectMask, const uint32_t mipLevels) {
  xkAssert(pVkImageView);
  xkAssert(vkImage);
  xkAssert(mipLevels > 0);

  XkResult result = XK_SUCCESS;

	VkImageViewCreateInfo vkImageViewCreateInfo             = {};
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

	VkResult vkResult = vkCreateImageView(_xkVulkanContext.vkLogicalDevice, &vkImageViewCreateInfo, VK_NULL_HANDLE, pVkImageView);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create image view: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroyImageView(VkImageView vkImageView) {
  xkAssert(vkImageView);

  vkDestroyImageView(_xkVulkanContext.vkLogicalDevice, vkImageView, VK_NULL_HANDLE);
}


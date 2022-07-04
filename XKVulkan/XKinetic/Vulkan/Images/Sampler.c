/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateSampler(VkSampler* pVkSampler, const VkFilter vkFilter, const VkSamplerAddressMode vkAddressMode, const VkBool32 vkAnisotropic, const uint32_t mipLevels) {
	xkAssert(pVkSampler);
	xkAssert(mipLevels > 0);

  XkResult result = XK_SUCCESS;

  VkSamplerCreateInfo vkSamplerCreateInfo       = {};
	vkSamplerCreateInfo.sType                     = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  vkSamplerCreateInfo.pNext                     = VK_NULL_HANDLE;
  vkSamplerCreateInfo.flags                     = 0;
	vkSamplerCreateInfo.magFilter                 = vkFilter;
	vkSamplerCreateInfo.minFilter                 = vkFilter;
	vkSamplerCreateInfo.mipmapMode                = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	vkSamplerCreateInfo.addressModeU              = vkAddressMode;
	vkSamplerCreateInfo.addressModeV              = vkAddressMode;
	vkSamplerCreateInfo.addressModeW              = vkAddressMode;
	vkSamplerCreateInfo.mipLodBias                = 0.0f;
  vkSamplerCreateInfo.anisotropyEnable          = (vkAnisotropic && _xkVulkanContext.vkDeviceFeatures.samplerAnisotropy) ? VK_TRUE : VK_FALSE;
	vkSamplerCreateInfo.maxAnisotropy             = (vkAnisotropic && _xkVulkanContext.vkDeviceFeatures.samplerAnisotropy) ? _xkVulkanContext.vkDeviceProperties.limits.maxSamplerAnisotropy : 1.0f;
	vkSamplerCreateInfo.compareEnable             = VK_FALSE;
	vkSamplerCreateInfo.compareOp                 = VK_COMPARE_OP_ALWAYS;
	vkSamplerCreateInfo.minLod                    = 0.0f;
	vkSamplerCreateInfo.maxLod                    = (float)mipLevels;
	vkSamplerCreateInfo.borderColor               = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
	vkSamplerCreateInfo.unnormalizedCoordinates   = VK_FALSE;

  VkResult vkResult = vkCreateSampler(_xkVulkanContext.vkLogicalDevice, &vkSamplerCreateInfo, VK_NULL_HANDLE, pVkSampler);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan sampler: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroySampler(VkSampler vkSampler) {
	xkAssert(vkSampler);

	vkDestroySampler(_xkVulkanContext.vkLogicalDevice, vkSampler, VK_NULL_HANDLE);
}
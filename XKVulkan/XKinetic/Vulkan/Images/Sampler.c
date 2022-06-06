#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateSampler(VkSampler* pVkSampler, const VkFilter vkFilter, const VkSamplerAddressMode vkAddressMode, const VkBool32 vkAnisotropic, const uint32_t mipLevels) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan sampler create info.
  const VkSamplerCreateInfo vkSamplerCreateInfo = {
	  .sType                    = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
    .pNext                    = VK_NULL_HANDLE,
    .flags                    = 0,
	  .magFilter                = vkFilter,
	  .minFilter                = vkFilter,
	  .mipmapMode               = VK_SAMPLER_MIPMAP_MODE_LINEAR,
	  .addressModeU             = vkAddressMode,
	  .addressModeV             = vkAddressMode,
	  .addressModeW             = vkAddressMode,
	  .mipLodBias               = 0.0f,
    .anisotropyEnable         = (vkAnisotropic && _xkVkContext.vkDeviceFeatures.samplerAnisotropy) ? VK_TRUE : VK_FALSE,
	  .maxAnisotropy            = (vkAnisotropic && _xkVkContext.vkDeviceFeatures.samplerAnisotropy) ? _xkVkContext.vkDeviceProperties.limits.maxSamplerAnisotropy : 1.0f,
	  .compareEnable            = VK_FALSE,
	  .compareOp                = VK_COMPARE_OP_ALWAYS,
	  .minLod                   = 0.0f,
	  .maxLod                   = (float)mipLevels,
	  .borderColor              = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
	  .unnormalizedCoordinates  = VK_FALSE
  };

  // Create Vulkan sampler.
  VkResult vkResult = vkCreateSampler(_xkVkContext.vkLogicalDevice, &vkSamplerCreateInfo, VK_NULL_HANDLE, pVkSampler);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan sampler: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroySampler(VkSampler vkSampler) {
  // Destroy Vulkan sampler.
	vkDestroySampler(_xkVkContext.vkLogicalDevice, vkSampler, VK_NULL_HANDLE);
}
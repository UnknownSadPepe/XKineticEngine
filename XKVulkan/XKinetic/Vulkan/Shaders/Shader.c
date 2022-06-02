#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateShader(VkShaderModule* pVkShaderModule, const uint32_t* code, const size_t size) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan shader module create info.
  const VkShaderModuleCreateInfo vkShaderModuleCreateInfo = {
    .sType        = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext        = VK_NULL_HANDLE,
    .flags        = 0,
    .codeSize     = size,
    .pCode        = code,
  };

  // Create Vulkan shader module.
  VkResult vkResult = vkCreateShaderModule(_xkVkContext.vkLogicalDevice, &vkShaderModuleCreateInfo, VK_NULL_HANDLE, pVkShaderModule);
  if(vkResult != VK_SUCCESS) {
		xkLogError("Failed to create Vulkan shader module: %s", __xkVkGetErrorString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroyShader(VkShaderModule vkShaderModule) {
  // Destroy Vulkan shader module.
  vkDestroyShaderModule(_xkVkContext.vkLogicalDevice, vkShaderModule, VK_NULL_HANDLE);
}

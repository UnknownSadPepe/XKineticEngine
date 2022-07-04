/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateShader(VkShaderModule* pVkShaderModule, const uint32_t* code, const size_t size) {
  xkAssert(pVkShaderModule);
  xkAssert(code);
  xkAssert(size > 0);

  XkResult result = XK_SUCCESS;

  VkShaderModuleCreateInfo vkShaderModuleCreateInfo = {};
  vkShaderModuleCreateInfo.sType                    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  vkShaderModuleCreateInfo.pNext                    = VK_NULL_HANDLE;
  vkShaderModuleCreateInfo.flags                    = 0;
  vkShaderModuleCreateInfo.codeSize                 = size;
  vkShaderModuleCreateInfo.pCode                    = code;

  VkResult vkResult = vkCreateShaderModule(_xkVulkanContext.vkLogicalDevice, &vkShaderModuleCreateInfo, VK_NULL_HANDLE, pVkShaderModule);
  if(vkResult != VK_SUCCESS) {
		xkLogError("Vulkan: Failed to create shader module: %s", __xkVulkanGetResultString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroyShader(VkShaderModule vkShaderModule) {
  xkAssert(vkShaderModule); 

  vkDestroyShaderModule(_xkVulkanContext.vkLogicalDevice, vkShaderModule, VK_NULL_HANDLE);
}

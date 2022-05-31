#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateCommandPool(void) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan command pool create info.
  const VkCommandPoolCreateInfo vkCommandPoolCreateInfo = {
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext = VK_NULL_HANDLE,
    .flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = _xkVkContext.queueFamilyIndices.graphics
  };

  // Create Vulkan command pool.
  VkResult vkResult = vkCreateCommandPool(_xkVkContext.vkLogicalDevice, &vkCommandPoolCreateInfo, VK_NULL_HANDLE, &_xkVkContext.vkCommandPool);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan instance: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }  

_catch:
  return(result);
}

void __xkVkDestroyCommandPool(void) {
  // Destroy Vulkan command pool.
  vkDestroyCommandPool(_xkVkContext.vkLogicalDevice, _xkVkContext.vkCommandPool, VK_NULL_HANDLE);
}

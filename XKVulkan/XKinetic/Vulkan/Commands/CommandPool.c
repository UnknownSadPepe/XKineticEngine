/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateCommandPool() {
  XkResult result = XK_SUCCESS;

  VkCommandPoolCreateInfo vkCommandPoolCreateInfo = {};
  vkCommandPoolCreateInfo.sType                   = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  vkCommandPoolCreateInfo.pNext                   = VK_NULL_HANDLE;
  vkCommandPoolCreateInfo.flags                   = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  vkCommandPoolCreateInfo.queueFamilyIndex        = _xkVulkanContext.queueFamilyIndices.graphics;

  VkResult vkResult = vkCreateCommandPool(_xkVulkanContext.vkLogicalDevice, &vkCommandPoolCreateInfo, VK_NULL_HANDLE, &_xkVulkanContext.vkCommandPool);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan instance: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }  

_catch:
  return(result);
}

void __xkVulkanDestroyCommandPool() {
  if(_xkVulkanContext.vkCommandPool) {
    vkDestroyCommandPool(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.vkCommandPool, VK_NULL_HANDLE);

    _xkVulkanContext.vkCommandPool = XK_NULL_HANDLE;
  }
}

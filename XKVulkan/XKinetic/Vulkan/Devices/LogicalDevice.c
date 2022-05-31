#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateLogicalDevice() {
  XkResult result = XK_SUCCESS;

  // TODO: implementation.

_catch:
  return(result);
}

void __xkVkDestroyLogicalDevice() {
  vkDestroyDevice(_xkVkContext.vkLogicalDevice, VK_NULL_HANDLE);
}

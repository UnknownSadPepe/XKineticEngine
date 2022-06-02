#include "XKinetic/Vulkan/Internal.h"

static VkSurfaceFormatKHR __xkVKChooseSurfaceFormat(VkSurfaceKHR, const VkSurfaceFormatKHR);
static VkPresentModeKHR __xkVKChoosePresentMode(VkSurfaceKHR, const VkPresentModeKHR);

XkResult __xkVkCreateSwapChain(VkSwapchainKHR* pVkSwapChain, VkSurfaceKHR vkSurface, VkExtent2D* const pVkExtent, VkFormat* const pVkFormat, VkImage* pVkImages, uint32_t* const pMinImageCount) {
  XkResult result = XK_SUCCESS;

  // Get Vulkan surface capabilities.
  VkSurfaceCapabilitiesKHR vkCapabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_xkVkContext.vkPhysicalDevice, vkSurface, &vkCapabilities);

  // Choose Vulkan surface format.
  VkSurfaceFormatKHR vkSurfaceFormat = __xkVKChooseSurfaceFormat(vkSurface, (VkSurfaceFormatKHR){VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR}); // NOTE: I don't know, should I check it out?

  // Choose Vulkan present mode.
  VkPresentModeKHR vkPresentMode = __xkVKChoosePresentMode(vkSurface, VK_PRESENT_MODE_MAILBOX_KHR); // NOTE: I don't know, should I check it out?

  // Set minimal image count.
  uint32_t minImageCount = vkCapabilities.minImageCount + 1;
  if (vkCapabilities.maxImageCount > 0 && minImageCount > vkCapabilities.maxImageCount) {
    minImageCount = vkCapabilities.maxImageCount;
  }

  // Set Vulkan image sharing mode.
  // Set queue family index count.
  // Set queue family indices.
  VkSharingMode vkImageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
  uint32_t queueFamilyIndexCount = 1;
  uint32_t queueFamilyIndices[] = {
    _xkVkContext.queueFamilyIndices.graphics,
    _xkVkContext.queueFamilyIndices.present
  };
  if(_xkVkContext.queueFamilyIndices.graphics != _xkVkContext.queueFamilyIndices.present) {
    vkImageSharingMode = VK_SHARING_MODE_CONCURRENT;
    queueFamilyIndexCount = 2;
  }
  
  // Initialize Vulkan swap chain create info.
  const VkSwapchainCreateInfoKHR vkSwapChainCreateInfo = {
    .sType                      = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .pNext                      = VK_NULL_HANDLE,
    .flags                      = 0,
    .surface                    = vkSurface,
    .minImageCount              = minImageCount,
    .imageFormat                = vkSurfaceFormat.format,
    .imageColorSpace            = vkSurfaceFormat.colorSpace,
    .imageExtent                = vkCapabilities.currentExtent,
    .imageArrayLayers           = 1,
    .imageUsage                 = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
    .imageSharingMode           = vkImageSharingMode,
    .queueFamilyIndexCount      = queueFamilyIndexCount,
    .pQueueFamilyIndices        = queueFamilyIndices,
    .preTransform               = vkCapabilities.currentTransform,
    .compositeAlpha             = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
    .presentMode                = vkPresentMode,
    .clipped                    = VK_TRUE,
    .oldSwapchain               = VK_NULL_HANDLE, // TODO: implementation 'oldSwapChain'.
  };

  // Create Vulkan swap chain.
  VkResult vkResult = vkCreateSwapchainKHR(_xkVkContext.vkLogicalDevice, &vkSwapChainCreateInfo, VK_NULL_HANDLE, pVkSwapChain);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan swap chain: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

  // Get Vulkan swap chain image count.
  vkResult = vkGetSwapchainImagesKHR(_xkVkContext.vkLogicalDevice, *pVkSwapChain, &minImageCount, VK_NULL_HANDLE);
  if(vkResult == VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to get Vulkan swap chain image count: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

  // Get Vulkan swap chain images.
  vkResult = vkGetSwapchainImagesKHR(_xkVkContext.vkLogicalDevice, *pVkSwapChain, &minImageCount, pVkImages);
  if(vkResult == VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to get Vulkan swap chain images: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  } 

  *pVkExtent = vkCapabilities.currentExtent;
  *pVkFormat = vkSurfaceFormat.format;
  *pMinImageCount = minImageCount;

_catch:
  return(result);
}

void __xkVkDestroySwapChain(VkSwapchainKHR vkSwapChain) {
  // Destroy Vulkan swap chain.
  vkDestroySwapchainKHR(_xkVkContext.vkLogicalDevice, vkSwapChain, VK_NULL_HANDLE);
}

static VkSurfaceFormatKHR __xkVKChooseSurfaceFormat(VkSurfaceKHR vkSurface, const VkSurfaceFormatKHR vkRequiredSurfaceFormat) {
  VkSurfaceFormatKHR vkSurfaceFormat = {
    .format       = VK_FORMAT_UNDEFINED,
    .colorSpace   = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
  };

  // Get Vulkan surface format count.
  uint32_t surfaceFormatCount = 0;
  vkGetPhysicalDeviceSurfaceFormatsKHR(_xkVkContext.vkPhysicalDevice, vkSurface, &surfaceFormatCount, VK_NULL_HANDLE);
  if(surfaceFormatCount == 0) {
    xkLogWarning("Failed to get Vulkan surface formats");
    goto _catch;
  }

  // Get Vulkan surface formats.
  VkSurfaceFormatKHR* vkSurfaceFormats = xkAllocateMemory(sizeof(VkSurfaceFormatKHR) * surfaceFormatCount);
  vkGetPhysicalDeviceSurfaceFormatsKHR(_xkVkContext.vkPhysicalDevice, vkSurface, &surfaceFormatCount, vkSurfaceFormats);

  // Template available Vulkan surface format.
  VkSurfaceFormatKHR vkAvailableSurfaceFormat = {0};

  // Choose Vulkan surface format.
  for(uint32_t i = 0; i < surfaceFormatCount; i++) {
    vkAvailableSurfaceFormat = vkSurfaceFormats[i];

    if((vkAvailableSurfaceFormat.format == vkRequiredSurfaceFormat.format) && (vkAvailableSurfaceFormat.colorSpace == vkRequiredSurfaceFormat.colorSpace)) {
      vkSurfaceFormat = vkAvailableSurfaceFormat;
      goto _catch;
    }
  }

_catch:
  if(vkSurfaceFormats) {
    xkFreeMemory(vkSurfaceFormats);
  }

  return(vkSurfaceFormat);
}

static VkPresentModeKHR __xkVKChoosePresentMode(VkSurfaceKHR vkSurface, const VkPresentModeKHR vkRequiredPresentMode) {
  VkPresentModeKHR vkPresentMode = VK_PRESENT_MODE_FIFO_KHR;

  // Get Vulkan present mode count.
  uint32_t presentModeCount = 0;
  vkGetPhysicalDeviceSurfacePresentModesKHR(_xkVkContext.vkPhysicalDevice, vkSurface, &presentModeCount, VK_NULL_HANDLE);
  if(presentModeCount == 0) {
    xkLogWarning("Failed to get Vulkan present modes");
    goto _catch;
  }

  // Get Vulkan present modes.
  VkPresentModeKHR* vkPresentModes = xkAllocateMemory(sizeof(VkPresentModeKHR) * presentModeCount);
  vkGetPhysicalDeviceSurfacePresentModesKHR(_xkVkContext.vkPhysicalDevice, vkSurface, &presentModeCount, vkPresentModes);

  // Template available Vulkan present mode.
  VkPresentModeKHR vkAvailablePresentMode = {0};

  // Choose Vulkan present mode.
  for(uint32_t i = 0; i < presentModeCount; i++) {
    vkAvailablePresentMode = vkPresentModes[i];

    if(vkAvailablePresentMode == vkRequiredPresentMode) {
      vkPresentMode = vkAvailablePresentMode;
      goto _catch;    
    }
  }

_catch:
  if(vkPresentModes) {
    xkFreeMemory(vkPresentModes);
  }

  return(vkPresentMode);
}


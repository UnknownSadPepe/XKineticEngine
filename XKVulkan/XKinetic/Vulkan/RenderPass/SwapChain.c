/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
static VkSurfaceFormatKHR   __xkVKChooseSurfaceFormat(VkSurfaceKHR, const VkSurfaceFormatKHR);
static VkPresentModeKHR     __xkVKChoosePresentMode(VkSurfaceKHR, const VkPresentModeKHR);

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateSwapChain(VkSwapchainKHR* pVkSwapChain, VkSurfaceKHR vkSurface, VkExtent2D* const pVkExtent, VkFormat* const pVkFormat, VkImage* pVkImages, uint32_t* const pMinImageCount) {
  xkAssert(pVkSwapChain);
  xkAssert(vkSurface);
  xkAssert(pVkExtent);
  xkAssert(pVkFormat);
  xkAssert(pVkImages);
  xkAssert(pMinImageCount);

  XkResult result = XK_SUCCESS;

  VkSurfaceCapabilitiesKHR vkCapabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_xkVulkanContext.vkPhysicalDevice, vkSurface, &vkCapabilities);

  VkSurfaceFormatKHR vkSurfaceFormat = __xkVKChooseSurfaceFormat(vkSurface, (VkSurfaceFormatKHR){VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR});

  VkPresentModeKHR vkPresentMode = __xkVKChoosePresentMode(vkSurface, VK_PRESENT_MODE_MAILBOX_KHR);

  uint32_t minImageCount = vkCapabilities.minImageCount + 1;
  if(vkCapabilities.maxImageCount > 0 && minImageCount > vkCapabilities.maxImageCount) {
    minImageCount = vkCapabilities.maxImageCount;
  }

  uint32_t queueFamilyIndices[] = {
    _xkVulkanContext.queueFamilyIndices.graphics,
    _xkVulkanContext.queueFamilyIndices.present
  };
  
  VkSwapchainCreateInfoKHR vkSwapChainCreateInfo  = {};
  vkSwapChainCreateInfo.sType                     = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  vkSwapChainCreateInfo.pNext                     = VK_NULL_HANDLE;
  vkSwapChainCreateInfo.flags                     = 0;
  vkSwapChainCreateInfo.surface                   = vkSurface;
  vkSwapChainCreateInfo.minImageCount             = minImageCount;
  vkSwapChainCreateInfo.imageFormat               = vkSurfaceFormat.format;
  vkSwapChainCreateInfo.imageColorSpace           = vkSurfaceFormat.colorSpace;
  vkSwapChainCreateInfo.imageExtent               = vkCapabilities.currentExtent;
  vkSwapChainCreateInfo.imageArrayLayers          = 1;
  vkSwapChainCreateInfo.imageUsage                = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  if(_xkVulkanContext.queueFamilyIndices.graphics != _xkVulkanContext.queueFamilyIndices.present) {
    vkSwapChainCreateInfo.imageSharingMode        = VK_SHARING_MODE_CONCURRENT;
    vkSwapChainCreateInfo.queueFamilyIndexCount   = 2;
  } else {
    vkSwapChainCreateInfo.imageSharingMode        = VK_SHARING_MODE_EXCLUSIVE;
    vkSwapChainCreateInfo.queueFamilyIndexCount   = 0;
  }
  vkSwapChainCreateInfo.pQueueFamilyIndices       = queueFamilyIndices;
  vkSwapChainCreateInfo.preTransform              = vkCapabilities.currentTransform;
  vkSwapChainCreateInfo.compositeAlpha            = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  vkSwapChainCreateInfo.presentMode               = vkPresentMode;
  vkSwapChainCreateInfo.clipped                   = VK_TRUE;
  vkSwapChainCreateInfo.oldSwapchain              = VK_NULL_HANDLE; /// TODO: Implementation 'oldSwapChain'.

  VkResult vkResult = vkCreateSwapchainKHR(_xkVulkanContext.vkLogicalDevice, &vkSwapChainCreateInfo, VK_NULL_HANDLE, pVkSwapChain);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create swap chain: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

  // Get Vulkan swap chain image count.
  vkResult = vkGetSwapchainImagesKHR(_xkVulkanContext.vkLogicalDevice, *pVkSwapChain, &minImageCount, VK_NULL_HANDLE);
  if(vkResult == VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to get swap chain image count: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

  // Get Vulkan swap chain images.
  vkResult = vkGetSwapchainImagesKHR(_xkVulkanContext.vkLogicalDevice, *pVkSwapChain, &minImageCount, pVkImages);
  if(vkResult == VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to get swap chain images: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  } 

  *pVkExtent = vkCapabilities.currentExtent;
  *pVkFormat = vkSurfaceFormat.format;
  *pMinImageCount = minImageCount;

_catch:
  return(result);
}

void __xkVulkanDestroySwapChain(VkSwapchainKHR vkSwapChain) {
  xkAssert(vkSwapChain);

  vkDestroySwapchainKHR(_xkVulkanContext.vkLogicalDevice, vkSwapChain, VK_NULL_HANDLE);
}

static VkSurfaceFormatKHR __xkVKChooseSurfaceFormat(VkSurfaceKHR vkSurface, const VkSurfaceFormatKHR vkRequiredSurfaceFormat) {
  xkAssert(vkSurface);

  VkSurfaceFormatKHR vkSurfaceFormat = {
    .format       = VK_FORMAT_UNDEFINED,
    .colorSpace   = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR
  };

  uint32_t surfaceFormatCount = 0;
  vkGetPhysicalDeviceSurfaceFormatsKHR(_xkVulkanContext.vkPhysicalDevice, vkSurface, &surfaceFormatCount, VK_NULL_HANDLE);
  if(surfaceFormatCount == 0) {
    xkLogWarning("Vulkan: Failed to get surface formats");
    goto _catch;
  }

  VkSurfaceFormatKHR* vkSurfaceFormats = XK_NULL_HANDLE;
  vkSurfaceFormats = xkAllocateMemory(sizeof(VkSurfaceFormatKHR) * surfaceFormatCount);
  if(!vkSurfaceFormats) {
    xkLogWarning("Vulkan: Failed to allocate surface formats");
    goto _catch;
  }

  vkGetPhysicalDeviceSurfaceFormatsKHR(_xkVulkanContext.vkPhysicalDevice, vkSurface, &surfaceFormatCount, vkSurfaceFormats);

  VkSurfaceFormatKHR vkAvailableSurfaceFormat = {};

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
  xkAssert(vkSurface);

  VkPresentModeKHR vkPresentMode = VK_PRESENT_MODE_FIFO_KHR;

  uint32_t presentModeCount = 0;
  vkGetPhysicalDeviceSurfacePresentModesKHR(_xkVulkanContext.vkPhysicalDevice, vkSurface, &presentModeCount, VK_NULL_HANDLE);
  if(presentModeCount == 0) {
    xkLogWarning("Vulkan: Failed to get present modes");
    goto _catch;
  }

  VkPresentModeKHR* vkPresentModes = XK_NULL_HANDLE;
  vkPresentModes = xkAllocateMemory(sizeof(VkPresentModeKHR) * presentModeCount);
  if(!vkPresentModes) {
    xkLogWarning("Vulkan: Failed to allocate present modes");
    goto _catch;
  }

  vkGetPhysicalDeviceSurfacePresentModesKHR(_xkVulkanContext.vkPhysicalDevice, vkSurface, &presentModeCount, vkPresentModes);

  VkPresentModeKHR vkAvailablePresentMode = {};

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


#include "XKinetic/Vulkan/Internal.h"

static XkBool32 __xkVkCheckPhysicalDeviceExtensionsSupport(const VkPhysicalDevice);
static XkBool32 __xkVkFindQueueFamilyIndices(__XkVkQueueFamilyIndices* const, const VkPhysicalDevice, const VkSurfaceKHR);
static uint32_t __xkVkScorePhysicalDevice(const VkPhysicalDevice);
static XkBool32 __xkVkPhysicalDeviceSuitable(const VkPhysicalDevice, const VkSurfaceKHR);
static VkPhysicalDevice __xkVkChoosePhysicalDevice(const VkPhysicalDevice*, const uint32_t);

XkResult __xkVkPickPhysicalDevice() {
  XkResult result = XK_SUCCESS;

  // Get Vulkan support physical device count.
  uint32_t vkPhysicalDeviceCount = 0;
  vkEnumeratePhysicalDevices(_xkVkContext.vkInstance, &vkPhysicalDeviceCount, VK_NULL_HANDLE);
  if(vkPhysicalDeviceCount == 0) {
    xkLogError("Failed to find GPUs with Vulkan support");
    result = XK_ERROR_UNKNOWN;
    goto _catch;
  }

  xkLogDebug("Vulkan support %d physical devices", vkPhysicalDeviceCount);

  // Get Vulkan support physical devices.
  VkPhysicalDevice* vkPhysicalDevices = xkAllocateMemory(sizeof(VkPhysicalDevice) * vkPhysicalDeviceCount);
  vkEnumeratePhysicalDevices(_xkVkContext.vkInstance, &vkPhysicalDeviceCount, vkPhysicalDevices);

  // Choose Vulkan physical device.
  _xkVkContext.vkPhysicalDevice = __xkVkChoosePhysicalDevice(vkPhysicalDevices, vkPhysicalDeviceCount);
  if(_xkVkContext.vkPhysicalDevice == VK_NULL_HANDLE) {
    xkLogError("Failed to choose Vulkan physical device");
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

  xkFreeMemory(vkPhysicalDevices);

  // Get Vulkan physical device properties and features.
  vkGetPhysicalDeviceProperties(_xkVkContext.vkPhysicalDevice, &_xkVkContext.vkDeviceProperties);
  vkGetPhysicalDeviceMemoryProperties(_xkVkContext.vkPhysicalDevice, &_xkVkContext.vkDeviceMemoryProperties);
  vkGetPhysicalDeviceFeatures(_xkVkContext.vkPhysicalDevice, &_xkVkContext.vkDeviceFeatures);
  __xkVkFindQueueFamilyIndices(&_xkVkContext.queueFamilyIndices, _xkVkContext.vkPhysicalDevice, _xkVkContext.vkHelperSurface);

  xkLogDebug("Vulkan Physical Device name: %s", _xkVkContext.vkDeviceProperties.deviceName);
  xkLogDebug("Vulkan Physical Device graphics queue: %d", _xkVkContext.queueFamilyIndices.graphics);
  xkLogDebug("Vulkan Physical Device present queue: %d", _xkVkContext.queueFamilyIndices.present);
  xkLogDebug("Vulkan Physical Device transfer queue: %d", _xkVkContext.queueFamilyIndices.transfer);
  xkLogDebug("Vulkan Physical Device compute queue: %d", _xkVkContext.queueFamilyIndices.compute);

  // TODO: implementation.

_catch:
  return(result);
}

static XkBool32 __xkVkCheckPhysicalDeviceExtensionsSupport(const VkPhysicalDevice vkPhysicalDevice) {
  XkBool32 result = XK_TRUE; 

  // Get Vulkan device extension properties count.
  uint32_t vkAvailableExtensionPropertiesCount = 0;
  vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, VK_NULL_HANDLE, &vkAvailableExtensionPropertiesCount, VK_NULL_HANDLE);
  if(vkAvailableExtensionPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan Device extension properties");
    result = XK_FALSE;
    goto _catch;    
  }

  // Get Vulkan device extension properties.
  VkExtensionProperties* vkAvailableExtensionProperties = xkAllocateMemory(sizeof(VkExtensionProperties) * vkAvailableExtensionPropertiesCount);
  vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, VK_NULL_HANDLE, &vkAvailableExtensionPropertiesCount, vkAvailableExtensionProperties);

  // Template available Vulkan extension.
  const char* vkAvailableExtension = XK_NULL;

  // Template required Vulkan extension.
  const char* vkRequiredExtension = XK_NULL;

  // Helper boolean value.
  XkBool32 vkAvailableExtensionFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVkDeviceExtensionCount; i++) {
    vkRequiredExtension = _xkVkDeviceExtensions[i];
    vkAvailableExtensionFind = XK_FALSE;

    for(uint32_t j = 0; j < vkAvailableExtensionPropertiesCount; j++) {
      vkAvailableExtension = vkAvailableExtensionProperties[j].extensionName;

      // Check Vulkan extension.
      if(xkCompareString(vkRequiredExtension, vkAvailableExtension)) {
        vkAvailableExtensionFind = XK_TRUE;
        break;
      }
    }

    // If doesn't find available Vulkan extension.
    if(!vkAvailableExtensionFind) {
      result = XK_FALSE;
      goto _catch;
    }
  }

_catch:
  if(vkAvailableExtensionProperties) {
    xkFreeMemory(vkAvailableExtensionProperties);
  }

  return(result);
}

static XkBool32 __xkVkFindQueueFamilyIndices(__XkVkQueueFamilyIndices* const pFamilyIndices, const VkPhysicalDevice vkPhysicalDevice, const VkSurfaceKHR vkSurface) {
  XkBool32 result = XK_TRUE; 

  // Get Vulkan queue family propesties count.
  uint32_t vkQueueFamilyPropertiesCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &vkQueueFamilyPropertiesCount, VK_NULL_HANDLE);
  if(vkQueueFamilyPropertiesCount == 0) {
    result = XK_FALSE;
    goto _catch;   
  }

  // Get Vulkan queue family propesties.
  VkQueueFamilyProperties vkQueueFamilyProperties[4];
  vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &vkQueueFamilyPropertiesCount, vkQueueFamilyProperties);

  // Template Vulkan queue properties.
  VkQueueFamilyProperties vkQueueProperties;

  // Check all Vulkan queues.
  for(uint32_t i = 0; i < vkQueueFamilyPropertiesCount; i++) {
    vkQueueProperties = vkQueueFamilyProperties[i];

    // Check Vulkan graphics queue.
    if((vkQueueProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) && !pFamilyIndices->graphicsFind) {
      pFamilyIndices->graphics = i;
      pFamilyIndices->graphicsFind = VK_TRUE;
    }

    // Check Vulkan present queue.
    VkBool32 vkPresentQueueSupport = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(vkPhysicalDevice, i, vkSurface, &vkPresentQueueSupport);
    if(vkPresentQueueSupport && !pFamilyIndices->presentFind) {
      pFamilyIndices->present = i;     
      pFamilyIndices->presentFind = VK_TRUE;  
    }
 
      // Check Vulkan transfer queue.
    if((vkQueueProperties.queueFlags & VK_QUEUE_TRANSFER_BIT) && !pFamilyIndices->transferFind) {
      pFamilyIndices->transfer = i;
      pFamilyIndices->transferFind = VK_TRUE;  
    }

    // Check Vulkan compute queue.
    if((vkQueueProperties.queueFlags & VK_QUEUE_COMPUTE_BIT) && !pFamilyIndices->computeFind) {
      pFamilyIndices->compute = i;
      pFamilyIndices->computeFind = VK_TRUE;  
    }

    // If all Vulkan queues find, break loop.
    if(pFamilyIndices->graphicsFind && pFamilyIndices->presentFind && pFamilyIndices->transferFind && pFamilyIndices->computeFind) {
      break;
    }
  }

_catch:
  return(result);
}

static uint32_t __xkVkScorePhysicalDevice(const VkPhysicalDevice vkPhysicalDevice) {
  uint32_t result = 0;

  // Get Vulkan physical device properties.
	VkPhysicalDeviceProperties vkPhysicalDeviceProperties;
  VkPhysicalDeviceMemoryProperties vkPhysicalDeviceMemoryProperties;
	VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures;
	vkGetPhysicalDeviceProperties(vkPhysicalDevice, &vkPhysicalDeviceProperties);
  vkGetPhysicalDeviceMemoryProperties(vkPhysicalDevice, &vkPhysicalDeviceMemoryProperties);
	vkGetPhysicalDeviceFeatures(vkPhysicalDevice, &vkPhysicalDeviceFeatures);

  // TODO: implement best physical device score.

  // Adds a large score boost for discrete GPUs (dedicated graphics cards).
	if(vkPhysicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		result += 1000;
  }

  // Gives a higher score to devices with a higher maximum texture size.
  result += vkPhysicalDeviceProperties.limits.maxImageDimension2D;

_catch:
  return(result);
}

static XkBool32 __xkVkPhysicalDeviceSuitable(const VkPhysicalDevice vkPhysicalDevice, const VkSurfaceKHR vkSurface) {
  XkBool32 result = XK_TRUE; 

  // Check Vulkan queue families support
  __XkVkQueueFamilyIndices familyIndices;
  XkBool32 queueFamiliesSupport = __xkVkFindQueueFamilyIndices(&familyIndices, vkPhysicalDevice, vkSurface);
  if(!queueFamiliesSupport) {
    result = XK_FALSE;
    goto _catch;
  }

  // Check Vulkan device extensions support.
  XkBool32 extensionsSupport = __xkVkCheckPhysicalDeviceExtensionsSupport(vkPhysicalDevice);
  if(!extensionsSupport) {
    result = XK_FALSE;
    goto _catch;
  }

  // Check Vulkan surface formats support.
  // NOTE: Can be done as a separate function.
  {
    uint32_t vkSurfaceFormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhysicalDevice, vkSurface, &vkSurfaceFormatCount, VK_NULL_HANDLE);
    if(vkSurfaceFormatCount == 0) {
      result = XK_FALSE;
      goto _catch;
    }
  }

  // Check Vulkan present mode support.
  // NOTE: Can be done as a separate function.
  {
    uint32_t vkPresentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(vkPhysicalDevice, vkSurface, &vkPresentModeCount, VK_NULL_HANDLE);
    if(vkPresentModeCount == 0) {
      result = XK_FALSE;
      goto _catch;
    }
  }

_catch:
  return(result);
}

static VkPhysicalDevice __xkVkChoosePhysicalDevice(const VkPhysicalDevice* vkPhysicalDevices, const uint32_t vkPhysicalDeviceCount) {
  // Template Vulkan physical device.
  VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;

  // If Vulkan physical devices count equal 1, return first physical device.
  if(vkPhysicalDeviceCount == 1) {
    vkPhysicalDevice = vkPhysicalDevices[0];
    goto _catch;
  }

  // Template Vulkan physical device score.
  uint32_t vkPhysicalDeviceScore = 0;

  // Template index of best Vulkan physical device.
  uint32_t vkBestPhysicalDeviceIndex = 0;

  // Template score of best Vulkan physical device.
  uint32_t vkBestPhysicalDeviceScore = 0;

  for(uint32_t i = 0; i < vkPhysicalDeviceCount; i++) {
    vkPhysicalDevice = vkPhysicalDevices[i];

    // Check Vulkan physical device suitable.
    if(__xkVkPhysicalDeviceSuitable(vkPhysicalDevice, _xkVkContext.vkHelperSurface)) {
      // Choose best Vulkan physical device.
      vkPhysicalDeviceScore = __xkVkScorePhysicalDevice(vkPhysicalDevice);
      if(vkBestPhysicalDeviceScore < vkPhysicalDeviceScore) {
        vkBestPhysicalDeviceScore = vkPhysicalDeviceScore;
        vkBestPhysicalDeviceIndex = i;
      }

      break;
    }
  }

  vkPhysicalDevice = vkPhysicalDevices[vkBestPhysicalDeviceIndex];

_catch:
  return(vkPhysicalDevice);
}

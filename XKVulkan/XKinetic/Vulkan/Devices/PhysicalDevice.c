/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
const char* _xkVulkanDeviceExtensions[] = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const uint32_t _xkVulkanDeviceExtensionCount = 1;

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
static XkBool8              __xkVulkanCheckPhysicalDeviceExtensionsSupport(const VkPhysicalDevice);
static XkBool8              __xkVulkanFindQueueFamilyIndices(__XkVkQueueFamilyIndices* const, const VkPhysicalDevice, const VkSurfaceKHR);
static uint32_t             __xkVulkanScorePhysicalDevice(const VkPhysicalDevice);
static XkBool8              __xkVulkanPhysicalDeviceSuitable(const VkPhysicalDevice, const VkSurfaceKHR);
static VkPhysicalDevice     __xkVulkanChoosePhysicalDevice(const VkPhysicalDevice*, const uint32_t);

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanPickPhysicalDevice() {
  XkResult result = XK_SUCCESS;

  uint32_t physicalDeviceCount = 0;
  vkEnumeratePhysicalDevices(_xkVulkanContext.vkInstance, &physicalDeviceCount, VK_NULL_HANDLE);
  if(physicalDeviceCount == 0) {
    xkLogError("Failed to find GPUs with Vulkan support");
    result = XK_ERROR_UNKNOWN;
    goto _catch;
  }

  xkLogDebug("Vulkan support %d physical devices", physicalDeviceCount);

  VkPhysicalDevice* vkPhysicalDevices = XK_NULL_HANDLE;
  vkPhysicalDevices = xkAllocateMemory(sizeof(VkPhysicalDevice) * physicalDeviceCount);
  vkEnumeratePhysicalDevices(_xkVulkanContext.vkInstance, &physicalDeviceCount, vkPhysicalDevices);

  _xkVulkanContext.vkPhysicalDevice = __xkVulkanChoosePhysicalDevice(vkPhysicalDevices, physicalDeviceCount);
  if(_xkVulkanContext.vkPhysicalDevice == VK_NULL_HANDLE) {
    xkLogError("Failed to choose Vulkan physical device");
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

  vkGetPhysicalDeviceProperties(_xkVulkanContext.vkPhysicalDevice, &_xkVulkanContext.vkDeviceProperties);
  vkGetPhysicalDeviceMemoryProperties(_xkVulkanContext.vkPhysicalDevice, &_xkVulkanContext.vkDeviceMemoryProperties);
  vkGetPhysicalDeviceFeatures(_xkVulkanContext.vkPhysicalDevice, &_xkVulkanContext.vkDeviceFeatures);
  __xkVulkanFindQueueFamilyIndices(&_xkVulkanContext.queueFamilyIndices, _xkVulkanContext.vkPhysicalDevice, _xkVulkanContext.vkHelperSurface);

  xkLogDebug("Vulkan physical device name: %s", _xkVulkanContext.vkDeviceProperties.deviceName);
  xkLogDebug("Vulkan physical device graphics queue: %d", _xkVulkanContext.queueFamilyIndices.graphics);
  xkLogDebug("Vulkan physical device present queue: %d", _xkVulkanContext.queueFamilyIndices.present);
  xkLogDebug("Vulkan physical device transfer queue: %d", _xkVulkanContext.queueFamilyIndices.transfer);
  xkLogDebug("Vulkan physical device compute queue: %d", _xkVulkanContext.queueFamilyIndices.compute);

_catch:
  if(vkPhysicalDevices) {
    xkFreeMemory(vkPhysicalDevices);  
  }

  return(result);
}

static XkBool8 __xkVulkanCheckPhysicalDeviceExtensionsSupport(const VkPhysicalDevice vkPhysicalDevice) {
  xkAssert(vkPhysicalDevice);

  XkBool8 result = XK_TRUE; 

  uint32_t availableExtensionPropertiesCount = 0;
  vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, VK_NULL_HANDLE, &availableExtensionPropertiesCount, VK_NULL_HANDLE);
  if(availableExtensionPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan physical device extension properties");
    result = XK_FALSE;
    goto _catch;    
  }

  VkExtensionProperties* vkAvailableExtensionProperties = XK_NULL_HANDLE;
  vkAvailableExtensionProperties = xkAllocateMemory(sizeof(VkExtensionProperties) * availableExtensionPropertiesCount);
	if(!vkAvailableExtensionProperties) {
		xkLogError("Failed to enumerate Vulkan physical device extension properties");
		result = XK_FALSE;
		goto _catch;
	}

  vkEnumerateDeviceExtensionProperties(vkPhysicalDevice, VK_NULL_HANDLE, &availableExtensionPropertiesCount, vkAvailableExtensionProperties);

  const char* availableExtension = XK_NULL_HANDLE;

  const char* requiredExtension = XK_NULL_HANDLE;

  XkBool8 availableExtensionFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVulkanDeviceExtensionCount; i++) {
    requiredExtension = _xkVulkanDeviceExtensions[i];
    availableExtensionFind = XK_FALSE;

    for(uint32_t j = 0; j < availableExtensionPropertiesCount; j++) {
      availableExtension = vkAvailableExtensionProperties[j].extensionName;

      if(xkCompareString((XkString)requiredExtension, (XkString)availableExtension)) {
        availableExtensionFind = XK_TRUE;
        break;
      }
    }

    if(!availableExtensionFind) {
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

static XkBool8 __xkVulkanFindQueueFamilyIndices(__XkVkQueueFamilyIndices* const pFamilyIndices, const VkPhysicalDevice vkPhysicalDevice, const VkSurfaceKHR vkSurface) {
  xkAssert(pFamilyIndices);
  xkAssert(vkPhysicalDevice);
  xkAssert(vkSurface);

  XkBool8 result = XK_TRUE; 

  uint32_t queueFamilyPropertiesCount = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyPropertiesCount, VK_NULL_HANDLE);
  if(queueFamilyPropertiesCount == 0) {
    result = XK_FALSE;
    goto _catch;   
  }

  VkQueueFamilyProperties* vkQueueFamilyProperties = XK_NULL_HANDLE;
  vkQueueFamilyProperties = xkAllocateMemory(sizeof(VkQueueFamilyProperties) * queueFamilyPropertiesCount);
  vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyPropertiesCount, vkQueueFamilyProperties);

  VkQueueFamilyProperties vkQueueProperties;

  for(uint32_t i = 0; i < queueFamilyPropertiesCount; i++) {
    vkQueueProperties = vkQueueFamilyProperties[i];

    if(vkQueueProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      pFamilyIndices->graphics = i;
      pFamilyIndices->supportedQueues |= VK_QUEUE_GRAPHICS_BIT;
    }

    VkBool32 vkPresentQueueSupport = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(vkPhysicalDevice, i, vkSurface, &vkPresentQueueSupport);
    if(vkPresentQueueSupport) {
      pFamilyIndices->present = i;     
      pFamilyIndices->supportPresentQueue = XK_TRUE;  
    }
 
    if(vkQueueProperties.queueFlags & VK_QUEUE_TRANSFER_BIT) {
      pFamilyIndices->transfer = i;
      pFamilyIndices->supportedQueues |= VK_QUEUE_TRANSFER_BIT;  
    }

    if(vkQueueProperties.queueFlags & VK_QUEUE_COMPUTE_BIT) {
      pFamilyIndices->compute = i;
      pFamilyIndices->supportedQueues |= VK_QUEUE_COMPUTE_BIT;  
    }

    if((pFamilyIndices->supportedQueues & VK_QUEUE_GRAPHICS_BIT) && 
        pFamilyIndices->supportPresentQueue && 
        (pFamilyIndices->supportedQueues & VK_QUEUE_TRANSFER_BIT) && 
        (pFamilyIndices->supportedQueues & VK_QUEUE_COMPUTE_BIT)) {
      break;
    }
  }

_catch:
  if(vkQueueFamilyProperties) {
    xkFreeMemory(vkQueueFamilyProperties);
  }

  return(result);
}

static uint32_t __xkVulkanScorePhysicalDevice(const VkPhysicalDevice vkPhysicalDevice) {
  xkAssert(vkPhysicalDevice);

  uint32_t result = 0;

	VkPhysicalDeviceProperties vkPhysicalDeviceProperties;
  vkGetPhysicalDeviceProperties(vkPhysicalDevice, &vkPhysicalDeviceProperties);

  VkPhysicalDeviceMemoryProperties vkPhysicalDeviceMemoryProperties;
  vkGetPhysicalDeviceMemoryProperties(vkPhysicalDevice, &vkPhysicalDeviceMemoryProperties);

	VkPhysicalDeviceFeatures vkPhysicalDeviceFeatures;
	vkGetPhysicalDeviceFeatures(vkPhysicalDevice, &vkPhysicalDeviceFeatures);

  /// TODO: Implement best physical device score.

  // Adds a large score boost for discrete GPUs (dedicated graphics cards).
	if(vkPhysicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		result += 1000;
  }

  // Gives a higher score to devices with a higher maximum texture size.
  result += vkPhysicalDeviceProperties.limits.maxImageDimension2D;

  return(result);
}

static XkBool8 __xkVulkanPhysicalDeviceSuitable(const VkPhysicalDevice vkPhysicalDevice, const VkSurfaceKHR vkSurface) {
  xkAssert(vkPhysicalDevice);
  xkAssert(vkSurface);

  XkBool8 result = XK_TRUE; 

  __XkVkQueueFamilyIndices familyIndices;
  XkBool8 queueFamiliesSupport = __xkVulkanFindQueueFamilyIndices(&familyIndices, vkPhysicalDevice, vkSurface);
  if(!queueFamiliesSupport) {
    result = XK_FALSE;
    goto _catch;
  }

  XkBool8 extensionsSupport = __xkVulkanCheckPhysicalDeviceExtensionsSupport(vkPhysicalDevice);
  if(!extensionsSupport) {
    result = XK_FALSE;
    goto _catch;
  }

  /// NOTE: Can be done as a separate function.
  {
    uint32_t surfaceFormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(vkPhysicalDevice, vkSurface, &surfaceFormatCount, VK_NULL_HANDLE);
    if(surfaceFormatCount == 0) {
      result = XK_FALSE;
      goto _catch;
    }
  }

  /// NOTE: Can be done as a separate function.
  {
    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(vkPhysicalDevice, vkSurface, &presentModeCount, VK_NULL_HANDLE);
    if(presentModeCount == 0) {
      result = XK_FALSE;
      goto _catch;
    }
  }

_catch:
  return(result);
}

static VkPhysicalDevice __xkVulkanChoosePhysicalDevice(const VkPhysicalDevice* vkPhysicalDevices, const uint32_t physicalDeviceCount) {
  xkAssert(vkPhysicalDevices);
  xkAssert(physicalDeviceCount > 0);

  VkPhysicalDevice vkPhysicalDevice = VK_NULL_HANDLE;

  if(physicalDeviceCount == 1) {
    vkPhysicalDevice = vkPhysicalDevices[0];
    goto _catch;
  }

  uint32_t physicalDeviceScore = 0;

  uint32_t bestPhysicalDeviceIndex = 0;

  uint32_t bestPhysicalDeviceScore = 0;

  for(uint32_t i = 0; i < physicalDeviceCount; i++) {
    vkPhysicalDevice = vkPhysicalDevices[i];

    if(__xkVulkanPhysicalDeviceSuitable(vkPhysicalDevice, _xkVulkanContext.vkHelperSurface)) {
      physicalDeviceScore = __xkVulkanScorePhysicalDevice(vkPhysicalDevice);
      if(bestPhysicalDeviceScore < physicalDeviceScore) {
        bestPhysicalDeviceScore = physicalDeviceScore;
        bestPhysicalDeviceIndex = i;
      }
    }
  }

  vkPhysicalDevice = vkPhysicalDevices[bestPhysicalDeviceIndex];

_catch:
  return(vkPhysicalDevice);
}

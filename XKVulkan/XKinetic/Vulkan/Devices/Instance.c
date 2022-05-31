#include "XKinetic/Vulkan/Internal.h"

static XkBool32 __xkVkCheckInstanceExtensionsSupport(void);
static XkBool32 __xkVkCheckInstanceLayersSupport(void);

XkResult __xkVkCreateInstance() {
  XkResult result = XK_SUCCESS;

  // Check Vulkan instance extensions support.
  if(!__xkVkCheckInstanceExtensionsSupport()) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan instance extensions doesn't support");
    goto _catch;   
  }

  // Check Vulkan instance layers support.
  if(!__xkVkCheckInstanceLayersSupport()) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan instance layers doesn't support");
    goto _catch;   
  }

  // Initialize Vulkan application info.
  const VkApplicationInfo vkApplicationInfo = {
    .sType            = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext            = VK_NULL_HANDLE,
    .pEngineName      = "XKineticEngine",
    .engineVersion    = VK_MAKE_VERSION(0, 0, 1),
    .apiVersion       = VK_API_VERSION_1_2
  };

#ifdef XKVK_DEBUG
  VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfo;
  __xkVkPopulateDebugMessengerCreateInfo(&vkDebugUtilsMessengerCreateInfo);
#endif // XKVK_DEBUG

  // Initialize Vulkan instance create info.
  const VkInstanceCreateInfo vkInstanceCreateInfo = {
    .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
#ifdef XKVK_DEBUG
    .pNext                      = (VkDebugUtilsMessengerCreateInfoEXT*)&vkDebugUtilsMessengerCreateInfo,
#else
    .pNext                      = VK_NULL_HANDLE,
#endif // XKVK_DEBUG
    .flags                      = 0,
    .pApplicationInfo           = &vkApplicationInfo,
    .enabledLayerCount          = _xkVkInstanceLayerCount,
    .ppEnabledLayerNames        = _xkVkInstanceLayers,
    .enabledExtensionCount      = _xkVkInstanceExtensionCount,
    .ppEnabledExtensionNames    = _xkVkInstanceExtensions
  };

  // Create Vulkan instance.
  VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, VK_NULL_HANDLE, &_xkVkContext.vkInstance);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan instance: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroyInstance() {
  // Destroy Vulkan instance.
  vkDestroyInstance(_xkVkContext.vkInstance, VK_NULL_HANDLE);
}

static XkBool32 __xkVkCheckInstanceExtensionsSupport(void) {
  XkBool32 result = XK_TRUE; 

  // Get Vulkan instance extension properties count.
  uint32_t vkAvailableExtensionPropertiesCount = 0;
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &vkAvailableExtensionPropertiesCount, VK_NULL_HANDLE);
  if(vkAvailableExtensionPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan instance extension properties");
    result = XK_FALSE;
    goto _catch;    
  }

  // Get Vulkan instance extension properties.
  VkExtensionProperties* vkAvailableExtensionProperties = xkAllocateMemory(sizeof(VkExtensionProperties) * vkAvailableExtensionPropertiesCount);
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &vkAvailableExtensionPropertiesCount, vkAvailableExtensionProperties);

  // Template available Vulkan extension.
  const char* vkAvailableExtension = XK_NULL;

  // Template required Vulkan extension.
  const char* vkRequiredExtension = XK_NULL;

  // Helper boolean value.
  XkBool32 vkAvailableExtensionFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVkInstanceExtensionCount; i++) {
    vkRequiredExtension = _xkVkInstanceExtensions[i];
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

static XkBool32 __xkVkCheckInstanceLayersSupport(void) {
  XkBool32 result = XK_TRUE; 

  // Get Vulkan instance layer properties count.
  uint32_t vkAvailableLayerPropertiesCount = 0;
  vkEnumerateInstanceLayerProperties(&vkAvailableLayerPropertiesCount, VK_NULL_HANDLE);
  if(vkAvailableLayerPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan instance layer properties");
    result = XK_FALSE;
    goto _catch;    
  }

  // Get Vulkan instance layer properties.
  VkLayerProperties* vkAvailableLayerProperties = xkAllocateMemory(sizeof(VkLayerProperties) * vkAvailableLayerPropertiesCount);;
  vkEnumerateInstanceLayerProperties(&vkAvailableLayerPropertiesCount, vkAvailableLayerProperties);

  // Template available Vulkan layer.
  const char* vkAvailableLayer = XK_NULL;

  // Template required Vulkan layer.
  const char* vkRequiredLayer = XK_NULL;

  // Helper boolean value.
  XkBool32 vkAvailableLayerFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVkInstanceLayerCount; i++) {
    vkRequiredLayer = _xkVkInstanceLayers[i];
    vkAvailableLayerFind = XK_FALSE;

    for(uint32_t j = 0; j < vkAvailableLayerPropertiesCount; j++) {
      vkAvailableLayer = vkAvailableLayerProperties[j].layerName;

      // Check Vulkan layer.
      if(xkCompareString(vkRequiredLayer, vkAvailableLayer)) {
        vkAvailableLayerFind = XK_TRUE;
        break;
      }
    }

    // If doesn't find available Vulkan layer.
    if(!vkAvailableLayerFind) {
      result = XK_FALSE;
      goto _catch;
    }
  }

_catch:
  if(vkAvailableLayerProperties) {
    xkFreeMemory(vkAvailableLayerProperties);
  }

  return(result);
}

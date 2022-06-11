#include "XKinetic/Vulkan/Internal.h"

const char* _xkVkInstanceExtensions[] = {
	VK_KHR_SURFACE_EXTENSION_NAME,

#if defined(XK_LINUX)
	VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#elif defined(XK_WIN32)
	VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif // XK_LINUX

#ifdef XKVULKAN_DEBUG
	VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif // XKVULKAN_DEBUG
};

#ifdef XKVULKAN_DEBUG
	const uint32_t _xkVkInstanceExtensionCount = 3;
#else
	const uint32_t _xkVkInstanceExtensionCount = 2;
#endif // XKVULKAN_DEBUG

#ifdef XKVULKAN_DEBUG
const char* _xkVkInstanceLayers[] = {
	"VK_LAYER_KHRONOS_validation"
};

const uint32_t _xkVkInstanceLayerCount = 1;
#else
const char* _xkVkInstanceLayers[] = {
};

const uint32_t _xkVkInstanceLayerCount = 0;
#endif // XKVULKAN_DEBUG

static XkBool32 __xkVkCheckInstanceExtensionsSupport(void);
static XkBool32 __xkVkCheckInstanceLayersSupport(void);

XkResult __xkVkCreateInstance(void) {
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
    .apiVersion       = VK_API_VERSION_1_3
  };

#ifdef XKVULKAN_DEBUG
  VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfo;
  __xkVkPopulateDebugMessengerCreateInfo(&vkDebugUtilsMessengerCreateInfo);
#endif // XKVULKAN_DEBUG

  // Initialize Vulkan instance create info.
  const VkInstanceCreateInfo vkInstanceCreateInfo = {
    .sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
#ifdef XKVULKAN_DEBUG
    .pNext                      = (VkDebugUtilsMessengerCreateInfoEXT*)&vkDebugUtilsMessengerCreateInfo,
#else
    .pNext                      = VK_NULL_HANDLE,
#endif // XKVULKAN_DEBUG
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

void __xkVkDestroyInstance(void) {
  // Destroy Vulkan instance.
  vkDestroyInstance(_xkVkContext.vkInstance, VK_NULL_HANDLE);
}

static XkBool32 __xkVkCheckInstanceExtensionsSupport(void) {
  XkBool32 result = XK_TRUE; 

  // Get Vulkan instance extension properties count.
  uint32_t availableExtensionPropertiesCount = 0;
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &availableExtensionPropertiesCount, VK_NULL_HANDLE);
  if(availableExtensionPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan instance extension properties");
    result = XK_FALSE;
    goto _catch;    
  }

  // Get Vulkan instance extension properties.
  VkExtensionProperties* vkAvailableExtensionProperties = xkAllocateMemory(sizeof(VkExtensionProperties) * availableExtensionPropertiesCount);
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &availableExtensionPropertiesCount, vkAvailableExtensionProperties);

  // Template available Vulkan extension.
  const char* availableExtension = XK_NULL_HANDLE;

  // Template required Vulkan extension.
  const char* requiredExtension = XK_NULL_HANDLE;

  // Helper boolean value.
  XkBool32 availableExtensionFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVkInstanceExtensionCount; i++) {
    requiredExtension = _xkVkInstanceExtensions[i];
    availableExtensionFind = XK_FALSE;

    for(uint32_t j = 0; j < availableExtensionPropertiesCount; j++) {
      availableExtension = vkAvailableExtensionProperties[j].extensionName;

      // Check Vulkan extension.
      if(xkCompareString((XkString)requiredExtension, (XkString)availableExtension)) {
        availableExtensionFind = XK_TRUE;
        break;
      }
    }

    // If doesn't find available Vulkan extension.
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

static XkBool32 __xkVkCheckInstanceLayersSupport(void) {
  XkBool32 result = XK_TRUE; 

  // Get Vulkan instance layer properties count.
  uint32_t availableLayerPropertiesCount = 0;
  vkEnumerateInstanceLayerProperties(&availableLayerPropertiesCount, VK_NULL_HANDLE);
  if(availableLayerPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan instance layer properties");
    result = XK_FALSE;
    goto _catch;    
  }

  // Get Vulkan instance layer properties.
  VkLayerProperties* vkAvailableLayerProperties = xkAllocateMemory(sizeof(VkLayerProperties) * availableLayerPropertiesCount);;
  vkEnumerateInstanceLayerProperties(&availableLayerPropertiesCount, vkAvailableLayerProperties);

  // Template available Vulkan layer.
  const char* availableLayer = XK_NULL_HANDLE;

  // Template required Vulkan layer.
  const char* requiredLayer = XK_NULL_HANDLE;

  // Helper boolean value.
  XkBool32 availableLayerFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVkInstanceLayerCount; i++) {
    requiredLayer = _xkVkInstanceLayers[i];
    availableLayerFind = XK_FALSE;

    for(uint32_t j = 0; j < availableLayerPropertiesCount; j++) {
      availableLayer = vkAvailableLayerProperties[j].layerName;

      // Check Vulkan layer.
      if(xkCompareString((XkString)requiredLayer, (XkString)availableLayer)) {
        availableLayerFind = XK_TRUE;
        break;
      }
    }

    // If doesn't find available Vulkan layer.
    if(!availableLayerFind) {
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

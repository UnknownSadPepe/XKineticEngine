#include "XKinetic/Vulkan/Internal.h"

const char* _xkVkInstanceExtensions[] = {
	VK_KHR_SURFACE_EXTENSION_NAME,

#if defined(XK_LINUX)
	VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#elif defined(XK_WIN32)
	VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif // XK_LINUX || XK_WIN32

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
const char* _xkVkInstanceLayers[] = {0};

const uint32_t _xkVkInstanceLayerCount = 0;
#endif // XKVULKAN_DEBUG

static XkBool __xkVkCheckInstanceExtensionsSupport(void);
static XkBool __xkVkCheckInstanceLayersSupport(void);

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
  VkApplicationInfo vkApplicationInfo = {0};
  vkApplicationInfo.sType             = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  vkApplicationInfo.pNext             = VK_NULL_HANDLE;
  vkApplicationInfo.pEngineName       = "XKineticEngine";
  vkApplicationInfo.engineVersion     = VK_MAKE_VERSION(0, 0, 1);
  vkApplicationInfo.apiVersion        = VK_API_VERSION_1_1;

#ifdef XKVULKAN_DEBUG
  VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfo;
  __xkVkPopulateDebugMessengerCreateInfo(&vkDebugUtilsMessengerCreateInfo);
#endif // XKVULKAN_DEBUG

  // Initialize Vulkan instance create info.
  VkInstanceCreateInfo vkInstanceCreateInfo       = {0};
  vkInstanceCreateInfo.sType                      = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
#ifdef XKVULKAN_DEBUG
  vkInstanceCreateInfo.pNext                      = (VkDebugUtilsMessengerCreateInfoEXT*)&vkDebugUtilsMessengerCreateInfo;
#else
  vkInstanceCreateInfo.pNext                      = VK_NULL_HANDLE;
#endif // XKVULKAN_DEBUG
  vkInstanceCreateInfo.flags                      = 0,
  vkInstanceCreateInfo.pApplicationInfo           = &vkApplicationInfo;
  vkInstanceCreateInfo.enabledLayerCount          = _xkVkInstanceLayerCount;
  vkInstanceCreateInfo.ppEnabledLayerNames        = _xkVkInstanceLayers;
  vkInstanceCreateInfo.enabledExtensionCount      = _xkVkInstanceExtensionCount;
  vkInstanceCreateInfo.ppEnabledExtensionNames    = _xkVkInstanceExtensions;

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
  if(_xkVkContext.vkInstance) {
    vkDestroyInstance(_xkVkContext.vkInstance, VK_NULL_HANDLE);

    _xkVkContext.vkInstance = VK_NULL_HANDLE; 
  }
}

static XkBool __xkVkCheckInstanceExtensionsSupport(void) {
  XkBool result = XK_TRUE; 

  // Get Vulkan instance extension properties count.
  uint32_t availableExtensionPropertiesCount = 0;
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &availableExtensionPropertiesCount, VK_NULL_HANDLE);
  if(availableExtensionPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan instance extension properties");
    result = XK_FALSE;
    goto _catch;    
  }

  VkExtensionProperties* vkAvailableExtensionProperties = XK_NULL_HANDLE;
  vkAvailableExtensionProperties = xkAllocateMemory(sizeof(VkExtensionProperties) * availableExtensionPropertiesCount);
	if(!vkAvailableExtensionProperties) {
		xkLogError("Failed to enumerate Vulkan instance extension properties");
		result = XK_FALSE;
		goto _catch;
	}

  // Get Vulkan instance extension properties.
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &availableExtensionPropertiesCount, vkAvailableExtensionProperties);

  // Template available Vulkan extension.
  const char* availableExtension = XK_NULL_HANDLE;

  // Template required Vulkan extension.
  const char* requiredExtension = XK_NULL_HANDLE;

  // Helper boolean value.
  XkBool availableExtensionFind = XK_FALSE;

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

static XkBool __xkVkCheckInstanceLayersSupport(void) {
  XkBool result = XK_TRUE; 

  // Get Vulkan instance layer properties count.
  uint32_t availableLayerPropertiesCount = 0;
  vkEnumerateInstanceLayerProperties(&availableLayerPropertiesCount, VK_NULL_HANDLE);
  if(availableLayerPropertiesCount == 0) {
    xkLogError("Failed to enumerate Vulkan instance layer properties");
    result = XK_FALSE;
    goto _catch;    
  }

  VkLayerProperties* vkAvailableLayerProperties = XK_NULL_HANDLE;
  vkAvailableLayerProperties = xkAllocateMemory(sizeof(VkLayerProperties) * availableLayerPropertiesCount);
	if(!vkAvailableLayerProperties) {
		xkLogError("Failed to enumerate Vulkan instance layer properties");
		result = XK_FALSE;
		goto _catch;
	}

  // Get Vulkan instance layer properties.
  vkEnumerateInstanceLayerProperties(&availableLayerPropertiesCount, vkAvailableLayerProperties);

  // Template available Vulkan layer.
  const char* availableLayer = XK_NULL_HANDLE;

  // Template required Vulkan layer.
  const char* requiredLayer = XK_NULL_HANDLE;

  // Helper boolean value.
  XkBool availableLayerFind = XK_FALSE;

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

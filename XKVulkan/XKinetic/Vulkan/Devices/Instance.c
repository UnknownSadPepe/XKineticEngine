/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
const char* _xkVulkanInstanceExtensions[] = {
	VK_KHR_SURFACE_EXTENSION_NAME,

#if defined(XK_LINUX)
	VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
#elif defined(XK_WINDOWS)
	VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif // XK_LINUX || XK_WINDOWS

#ifdef XKVULKAN_DEBUG
	VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif // XKVULKAN_DEBUG
};

#ifdef XKVULKAN_DEBUG
	const uint32_t _xkVulkanInstanceExtensionCount = 3;
#else
	const uint32_t _xkVulkanInstanceExtensionCount = 2;
#endif // XKVULKAN_DEBUG

#ifdef XKVULKAN_DEBUG
const char* _xkVulkanInstanceLayers[] = {
	"VK_LAYER_KHRONOS_validation"
};

const uint32_t _xkVulkanInstanceLayerCount = 1;
#else
const char* _xkVulkanInstanceLayers[] = {};

const uint32_t _xkVulkanInstanceLayerCount = 0;
#endif // XKVULKAN_DEBUG

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
static XkBool8 __xkVulkanCheckInstanceExtensionsSupport();
static XkBool8 __xkVulkanCheckInstanceLayersSupport();

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateInstance() {
  XkResult result = XK_SUCCESS;

  if(!__xkVulkanCheckInstanceExtensionsSupport()) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan instance extensions doesn't support");
    goto _catch;   
  }

  if(!__xkVulkanCheckInstanceLayersSupport()) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan instance layers doesn't support");
    goto _catch;   
  }

  VkApplicationInfo vkApplicationInfo = {};
  vkApplicationInfo.sType             = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  vkApplicationInfo.pNext             = VK_NULL_HANDLE;
  vkApplicationInfo.pEngineName       = "XKineticEngine";
  vkApplicationInfo.engineVersion     = VK_MAKE_VERSION(0, 0, 1);
  vkApplicationInfo.apiVersion        = VK_API_VERSION_1_3;

#ifdef XKVULKAN_DEBUG
  VkDebugUtilsMessengerCreateInfoEXT vkDebugUtilsMessengerCreateInfo;
  __xkVulkanPopulateDebugMessengerCreateInfo(&vkDebugUtilsMessengerCreateInfo);
#endif // XKVULKAN_DEBUG

  VkInstanceCreateInfo vkInstanceCreateInfo     = {};
  vkInstanceCreateInfo.sType                    = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
#ifdef XKVULKAN_DEBUG
  vkInstanceCreateInfo.pNext                    = (VkDebugUtilsMessengerCreateInfoEXT*)&vkDebugUtilsMessengerCreateInfo;
#else
  vkInstanceCreateInfo.pNext                    = VK_NULL_HANDLE;
#endif // XKVULKAN_DEBUG
  vkInstanceCreateInfo.flags                    = 0,
  vkInstanceCreateInfo.pApplicationInfo         = &vkApplicationInfo;
  vkInstanceCreateInfo.enabledLayerCount        = _xkVulkanInstanceLayerCount;
  vkInstanceCreateInfo.ppEnabledLayerNames      = _xkVulkanInstanceLayers;
  vkInstanceCreateInfo.enabledExtensionCount    = _xkVulkanInstanceExtensionCount;
  vkInstanceCreateInfo.ppEnabledExtensionNames  = _xkVulkanInstanceExtensions;

  VkResult vkResult = vkCreateInstance(&vkInstanceCreateInfo, VK_NULL_HANDLE, &_xkVulkanContext.vkInstance);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create instance: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroyInstance() {
  if(_xkVulkanContext.vkInstance) {
    vkDestroyInstance(_xkVulkanContext.vkInstance, VK_NULL_HANDLE);

    _xkVulkanContext.vkInstance = VK_NULL_HANDLE; 
  }
}

static XkBool8 __xkVulkanCheckInstanceExtensionsSupport() {
  XkBool8 result = XK_TRUE; 

  uint32_t availableExtensionPropertiesCount = 0;
  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &availableExtensionPropertiesCount, VK_NULL_HANDLE);
  if(availableExtensionPropertiesCount == 0) {
    xkLogError("Vulkan: Failed to enumerate instance extension properties");
    result = XK_FALSE;
    goto _catch;    
  }

  VkExtensionProperties* vkAvailableExtensionProperties = XK_NULL_HANDLE;
  vkAvailableExtensionProperties = xkAllocateMemory(sizeof(VkExtensionProperties) * availableExtensionPropertiesCount);
	if(!vkAvailableExtensionProperties) {
		xkLogError("Vulkan: Failed to allocate instance extension properties");
		result = XK_FALSE;
		goto _catch;
	}

  vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &availableExtensionPropertiesCount, vkAvailableExtensionProperties);

  const char* availableExtension = XK_NULL_HANDLE;

  const char* requiredExtension = XK_NULL_HANDLE;

  XkBool8 availableExtensionFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVulkanInstanceExtensionCount; i++) {
    requiredExtension = _xkVulkanInstanceExtensions[i];
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

static XkBool8 __xkVulkanCheckInstanceLayersSupport() {
  XkBool8 result = XK_TRUE; 

  uint32_t availableLayerPropertiesCount = 0;
  vkEnumerateInstanceLayerProperties(&availableLayerPropertiesCount, VK_NULL_HANDLE);
  if(availableLayerPropertiesCount == 0) {
    xkLogError("Vulkan: Failed to enumerate instance layer properties");
    result = XK_FALSE;
    goto _catch;    
  }

  VkLayerProperties* vkAvailableLayerProperties = XK_NULL_HANDLE;
  vkAvailableLayerProperties = xkAllocateMemory(sizeof(VkLayerProperties) * availableLayerPropertiesCount);
	if(!vkAvailableLayerProperties) {
		xkLogError("Vulkan: Failed to allocate instance layer properties");
		result = XK_FALSE;
		goto _catch;
	}

  vkEnumerateInstanceLayerProperties(&availableLayerPropertiesCount, vkAvailableLayerProperties);

  const char* availableLayer = XK_NULL_HANDLE;

  const char* requiredLayer = XK_NULL_HANDLE;

  XkBool8 availableLayerFind = XK_FALSE;

  for(uint32_t i = 0; i < _xkVulkanInstanceLayerCount; i++) {
    requiredLayer = _xkVulkanInstanceLayers[i];
    availableLayerFind = XK_FALSE;

    for(uint32_t j = 0; j < availableLayerPropertiesCount; j++) {
      availableLayer = vkAvailableLayerProperties[j].layerName;

      if(xkCompareString((XkString)requiredLayer, (XkString)availableLayer)) {
        availableLayerFind = XK_TRUE;
        break;
      }
    }

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

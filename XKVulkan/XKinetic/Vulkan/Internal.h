#pragma once

#include "XKinetic/XKVulkan.h"
#if defined(XK_PLATFORM_LINUX)
	#define VK_USE_PLATFORM_WAYLAND_KHR
	#include <vulkan/vulkan.h>
#elif defined(XK_PLATFORM_WIN32)
	#define VK_USE_PLATFORM_WIN32_KHR
	#include <vulkan/vulkan.h>
#endif // XK_PLATFORM_LINUX
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Core/Window.h"

static const char* _xkVkInstanceExtensions[] = {
	VK_KHR_SURFACE_EXTENSION_NAME,

#if defined(XK_PLATFORM_LINUX)

	VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,

#elif defined(XK_PLATFORM_WIN32)
	VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#endif // XK_PLATFORM_LINUX

#ifdef XKVK_DEBUG
	VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif // XKVK_DEBUG
};

#ifdef XKVK_DEBUG
	static const uint32_t _xkVkInstanceExtensionCount = 3;
#else
	static const uint32_t _xkVkInstanceExtensionCount = 2;
#endif // XKVK_DEBUG

#ifdef XKVK_DEBUG
static const char* _xkVkInstanceLayers[] = {
	"VK_LAYER_KHRONOS_validation"
};

static const uint32_t _xkVkInstanceLayerCount = 1;
#else
static const char* _xkVkInstanceLayers[] = {
};

static const uint32_t _xkVkInstanceLayerCount = 0;
#endif // XKVK_DEBUG

static const char* _xkVkDeviceExtensions[] = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

static const uint32_t _xkVkDeviceExtensionCount = 1;

typedef struct {
  uint32_t graphics;
  uint32_t present;
  uint32_t transfer;
  uint32_t compute;

	VkQueueFlags supportedQueues;
	XkBool32 supportPresentQueue;
} __XkVkQueueFamilyIndices;

typedef struct {
	VkSurfaceCapabilitiesKHR vkCapabilities;
	VkSurfaceFormatKHR vkSurfaceFormats;
	VkPresentModeKHR vkPresentMode;
} __XkVkSwapChainDetails;

struct XkVkBuffer {
	VkBuffer buffer;
	VkDeviceMemory memory;
	VkDeviceSize size;
};

struct XkVkTexture2D {
	VkImage image;
	VkDeviceMemory memory;
	VkImageView imageView;
	VkSampler sampler;
};

typedef struct {
	XkBool32 initialized;

	VkInstance vkInstance;
#ifdef XKVK_DEBUG
	VkDebugUtilsMessengerEXT vkDebugMessenger;
#else 
	VkDebugReportCallbackEXT vkDebugReport;
#endif // XKVK_DEBUG

	VkSurfaceKHR vkHelperSurface;

	VkPhysicalDevice vkPhysicalDevice;
	VkPhysicalDeviceProperties vkDeviceProperties;
	VkPhysicalDeviceMemoryProperties vkDeviceMemoryProperties;
	VkPhysicalDeviceFeatures vkDeviceFeatures;
	__XkVkQueueFamilyIndices queueFamilyIndices;

	VkDevice vkLogicalDevice;

	VkQueue vkPresentQueue;
	VkQueue vkGraphicsQueue;
	VkQueue vkTransferQueue;
	VkQueue vkComputeQueue;

	VkCommandPool vkCommandPool;
} __XkVkContext;

extern __XkVkContext _xkVkContext;

XK_API_IMPORT XkChar8* __xkVkGetErrorString(VkResult); 

XK_API_IMPORT XkResult __xkVkInitializeContext(void);
XK_API_IMPORT void __xkVkTerminateContext(void);

XK_API_IMPORT XkResult __xkVkCreateInstance(void);
XK_API_IMPORT void __xkVkDestroyInstance(void);

#ifdef XKVK_DEBUG
XK_API_IMPORT void __xkVkPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT*);
XK_API_IMPORT XkResult __xkVkCreateDebugMessenger(void);
XK_API_IMPORT void __xkVkDestroyDebugMessenger(void);
#endif // XKVK_DEBUG

XK_API_IMPORT XkResult __xkVkCreateSurface(VkSurfaceKHR*, XkWindow);
XK_API_IMPORT void __xkVkDestroySurface(VkSurfaceKHR);

XK_API_IMPORT XkResult __xkVkPickPhysicalDevice(void);

XK_API_IMPORT XkResult __xkVkCreateLogicalDevice(void);
XK_API_IMPORT void __xkVkDestroyLogicalDevice(void);

XK_API_IMPORT XkResult __xkVkCreateCommandPool(void);
XK_API_IMPORT void __xkVkDestroyCommandPool(void);

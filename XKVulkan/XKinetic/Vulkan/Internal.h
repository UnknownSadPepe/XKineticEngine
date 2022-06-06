#pragma once

#include "XKinetic/XKVulkan.h"
#if defined(XK_LINUX)
	#define VK_USE_PLATFORM_WAYLAND_KHR
	#include <vulkan/vulkan.h>
#elif defined(XK_WIN32)
	#define VK_USE_PLATFORM_WIN32_KHR
	#include <vulkan/vulkan.h>
#endif // XK_LINUX
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"

static const char* _xkVkInstanceExtensions[] = {
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
	static const uint32_t _xkVkInstanceExtensionCount = 3;
#else
	static const uint32_t _xkVkInstanceExtensionCount = 2;
#endif // XKVULKAN_DEBUG

#ifdef XKVULKAN_DEBUG
static const char* _xkVkInstanceLayers[] = {
	"VK_LAYER_KHRONOS_validation"
};

static const uint32_t _xkVkInstanceLayerCount = 1;
#else
static const char* _xkVkInstanceLayers[] = {
};

static const uint32_t _xkVkInstanceLayerCount = 0;
#endif // XKVULKAN_DEBUG

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
	VkBuffer vkBuffer;
	VkDeviceMemory vkMemory;
	VkDeviceSize vkSize;
};

struct XkVkTexture2D {
	VkImage vkImage;
	VkDeviceMemory vkMemory;
	VkImageView vkImageView;
	VkSampler vkSampler;
};

typedef struct {
	VkImage vkImage;
	VkDeviceMemory vkMemory;
	VkImageView vkImageView;
	VkSampler vkSampler;
} XkVkImage;

typedef struct {
	XkBool32 initialized;

	VkInstance vkInstance;
#ifdef XKVULKAN_DEBUG
	VkDebugUtilsMessengerEXT vkDebugMessenger;
#else 
	VkDebugReportCallbackEXT vkDebugReport;
#endif // XKVULKAN_DEBUG

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

XK_IMPORT XkChar8* __xkVkGetErrorString(VkResult); 

XK_IMPORT XkResult __xkVkInitializeContext(void);
XK_IMPORT void __xkVkTerminateContext(void);

XK_IMPORT XkResult __xkVkCreateInstance(void);
XK_IMPORT void __xkVkDestroyInstance(void);

#ifdef XKVULKAN_DEBUG
XK_IMPORT void __xkVkPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT*);
XK_IMPORT XkResult __xkVkCreateDebugMessenger(void);
XK_IMPORT void __xkVkDestroyDebugMessenger(void);
#endif // XKVULKAN_DEBUG

XK_IMPORT XkResult __xkVkCreateSurface(VkSurfaceKHR*, XkWindow);
XK_IMPORT void __xkVkDestroySurface(VkSurfaceKHR);

XK_IMPORT XkResult __xkVkPickPhysicalDevice(void);

XK_IMPORT XkResult __xkVkCreateLogicalDevice(void);
XK_IMPORT void __xkVkDestroyLogicalDevice(void);

XK_IMPORT uint32_t __xkVkFindMemoryType(uint32_t, const VkMemoryPropertyFlags);

XK_IMPORT XkResult __xkVkCreateCommandPool(void);
XK_IMPORT void __xkVkDestroyCommandPool(void);

XK_IMPORT XkResult __xkVkCreateSwapChain(VkSwapchainKHR*, VkSurfaceKHR, VkExtent2D* const, VkFormat* const, VkImage*, uint32_t* const);
XK_IMPORT void __xkVkDestroySwapChain(VkSwapchainKHR);

XK_IMPORT XkResult __xkVkCreateRenderPass(VkRenderPass* pVkRenderPass, VkAttachmentDescription*, const uint32_t, VkSubpassDescription*, const uint32_t, VkSubpassDependency*, const uint32_t);
XK_IMPORT void __xkVkDestroyeRenderPass(VkRenderPass);

XK_IMPORT XkResult __xkVkCreateFrameBuffer(VkFramebuffer*, VkRenderPass, const VkExtent2D, VkImageView*, const uint32_t);
XK_IMPORT void __xkVkDestroyFrameBuffer(VkFramebuffer);

XK_IMPORT XkResult __xkVkCreateCommandBuffer(VkCommandBuffer*, const VkCommandBufferLevel);
XK_IMPORT void __xkVkDestroyCommandBuffer(VkCommandBuffer);

XK_IMPORT XkResult __xkVkBeginSingleCommands(VkCommandBuffer*);
XK_IMPORT XkResult __xkVkEndSingleCommands(VkCommandBuffer);

XK_IMPORT XkResult __xkVkCreateSemaphore(VkSemaphore*);
XK_IMPORT void __xkVkDestroySemaphore(VkSemaphore);

XK_IMPORT XkResult __xkVkCreateFence(VkFence*);
XK_IMPORT void __xkVkDestroyFence(VkFence);

XK_IMPORT XkResult __xkVkCreateShader(VkShaderModule*, const uint32_t*, const size_t);
XK_IMPORT void __xkVkDestroyShader(VkShaderModule);

XK_IMPORT XkResult __xkVkCreateBuffer(VkBuffer* const, VkDeviceMemory* const, const VkDeviceSize, const VkBufferUsageFlags, const VkMemoryPropertyFlags, const void*);
XK_IMPORT void __xkVkDestroyBuffer(VkBuffer, VkDeviceMemory);

XK_IMPORT XkResult __xkVkCopyBuffer(VkBuffer, const VkBuffer, const VkDeviceSize);

XK_IMPORT XkResult __xkVkMapBuffer(VkDeviceMemory, const VkDeviceSize, const void*); 

XK_IMPORT XkResult __xkVkCreateImage(VkImage* const, VkDeviceMemory* const, const VkImageType, const VkFormat, const VkExtent3D, const VkSampleCountFlagBits, const VkImageTiling, const VkImageUsageFlags, const VkMemoryPropertyFlags, const uint32_t);
XK_IMPORT void __xkVkDestroyImage(VkImage, VkDeviceMemory);

XK_IMPORT XkResult __xkVkCreateImageView(VkImageView* const, VkImage, const VkFormat, const VkImageAspectFlags, const uint32_t);
XK_IMPORT void __xkVkDestroyImageView(VkImageView);

XK_IMPORT XkResult __xkVkCreateSampler(VkSampler*, const VkFilter, const VkSamplerAddressMode, const VkBool32, const uint32_t);
XK_IMPORT void __xkVkDestroySampler(VkSampler);

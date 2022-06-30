#pragma once

#include "XKinetic/XKVulkan.h"
#if defined(XK_LINUX)
	#define VK_USE_PLATFORM_WAYLAND_KHR
	#include <vulkan/vulkan.h>
#elif defined(XK_WIN32)
	#define VK_USE_PLATFORM_WIN32_KHR
	#include <vulkan/vulkan.h>
#endif // XK_LINUX || XK_WIN32
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"

#define XKVULKAN_FRAME_COUNT 2

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern const char* _xkVkInstanceExtensions[];
extern const uint32_t _xkVkInstanceExtensionCount;

extern const char* _xkVkInstanceLayers[];
extern const uint32_t _xkVkInstanceLayerCount;

extern const char* _xkVkDeviceExtensions[];
extern const uint32_t _xkVkDeviceExtensionCount;

typedef struct {
  uint32_t graphics;
  uint32_t present;
  uint32_t transfer;
  uint32_t compute;

	VkQueueFlags supportedQueues;
	XkBool supportPresentQueue;
} __XkVkQueueFamilyIndices;

typedef struct {
	VkSurfaceCapabilitiesKHR vkCapabilities;
	VkSurfaceFormatKHR vkSurfaceFormats;
	VkPresentModeKHR vkPresentMode;
} __XkVkSwapChainDetails;

typedef struct {
	XkBool initialized;

	VkInstance vkInstance;
#ifdef XKVULKAN_DEBUG
	VkDebugUtilsMessengerEXT vkDebugMessenger;
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

XK_EXPORT XkString __xkVkGetErrorString(VkResult); 

XK_EXPORT XkResult __xkVkInitializeContext(void);
XK_EXPORT void __xkVkTerminateContext(void);

XK_EXPORT XkResult __xkVkCreateInstance(void);
XK_EXPORT void __xkVkDestroyInstance(void);

#ifdef XKVULKAN_DEBUG
XK_EXPORT void __xkVkPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT*);
XK_EXPORT XkResult __xkVkCreateDebugMessenger(void);
XK_EXPORT void __xkVkDestroyDebugMessenger(void);
#endif // XKVULKAN_DEBUG

XK_EXPORT XkResult __xkVkCreateSurface(VkSurfaceKHR*, XkWindow);
XK_EXPORT void __xkVkDestroySurface(VkSurfaceKHR);

XK_EXPORT XkResult __xkVkPickPhysicalDevice(void);

XK_EXPORT XkResult __xkVkCreateLogicalDevice(void);
XK_EXPORT void __xkVkDestroyLogicalDevice(void);

XK_EXPORT uint32_t __xkVkFindMemoryType(uint32_t, const VkMemoryPropertyFlags);

XK_EXPORT XkResult __xkVkCreateCommandPool(void);
XK_EXPORT void __xkVkDestroyCommandPool(void);

XK_EXPORT XkResult __xkVkCreateSwapChain(VkSwapchainKHR*, VkSurfaceKHR, VkExtent2D* const, VkFormat* const, VkImage*, uint32_t* const);
XK_EXPORT void __xkVkDestroySwapChain(VkSwapchainKHR);

XK_EXPORT XkResult __xkVkCreateRenderPass(VkRenderPass* pVkRenderPass, VkAttachmentDescription*, const uint32_t, VkSubpassDescription*, const uint32_t, VkSubpassDependency*, const uint32_t);
XK_EXPORT void __xkVkDestroyeRenderPass(VkRenderPass);

XK_EXPORT XkResult __xkVkCreateFrameBuffer(VkFramebuffer*, VkRenderPass, const VkExtent2D, VkImageView*, const uint32_t);
XK_EXPORT void __xkVkDestroyFrameBuffer(VkFramebuffer);

XK_EXPORT XkResult __xkVkCreateCommandBuffer(VkCommandBuffer*, const VkCommandBufferLevel);
XK_EXPORT void __xkVkDestroyCommandBuffer(VkCommandBuffer);

XK_EXPORT XkResult __xkVkBeginSingleCommands(VkCommandBuffer*);
XK_EXPORT XkResult __xkVkEndSingleCommands(VkCommandBuffer);

XK_EXPORT XkResult __xkVkCreateSemaphore(VkSemaphore*);
XK_EXPORT void __xkVkDestroySemaphore(VkSemaphore);

XK_EXPORT XkResult __xkVkCreateFence(VkFence*);
XK_EXPORT void __xkVkDestroyFence(VkFence);

XK_EXPORT XkResult __xkVkCreateShader(VkShaderModule*, const uint32_t*, const size_t);
XK_EXPORT void __xkVkDestroyShader(VkShaderModule);

XK_EXPORT XkResult __xkVkCreateBuffer(VkBuffer* const, VkDeviceMemory* const, const VkDeviceSize, const VkBufferUsageFlags, const VkMemoryPropertyFlags, const void*);
XK_EXPORT void __xkVkDestroyBuffer(VkBuffer, VkDeviceMemory);

XK_EXPORT XkResult __xkVkCopyBuffer(VkBuffer, const VkBuffer, const VkDeviceSize);

XK_EXPORT XkResult __xkVkMapBuffer(VkDeviceMemory, const VkDeviceSize, const void*); 

XK_EXPORT XkResult __xkVkCreateImage(VkImage* const, VkDeviceMemory* const, const VkImageType, const VkFormat, const VkExtent3D, const VkSampleCountFlagBits, const VkImageTiling, const VkImageUsageFlags, const VkMemoryPropertyFlags, const uint32_t);
XK_EXPORT void __xkVkDestroyImage(VkImage, VkDeviceMemory);

XK_EXPORT XkResult __xkVkTransitionImageLayout(VkImage, const VkFormat, const VkImageLayout, const VkImageLayout, const uint32_t);
XK_EXPORT XkResult __xkVkCopyBufferToImage(VkBuffer, VkImage, const VkExtent3D);

XK_EXPORT XkResult __xkVkCreateImageView(VkImageView* const, VkImage, const VkFormat, const VkImageAspectFlags, const uint32_t);
XK_EXPORT void __xkVkDestroyImageView(VkImageView);

XK_EXPORT XkResult __xkVkCreateSampler(VkSampler*, const VkFilter, const VkSamplerAddressMode, const VkBool32, const uint32_t);
XK_EXPORT void __xkVkDestroySampler(VkSampler);

#ifdef __cplusplus
}
#endif // __cplusplus

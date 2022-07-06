#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKVulkan.h"
#if defined(XK_LINUX)
	#define VK_USE_PLATFORM_WAYLAND_KHR
#elif defined(XK_WINDOWS)
	#define VK_USE_PLATFORM_WIN32_KHR
#endif // XK_LINUX || XK_WINDOWS
#include <vulkan/vulkan.h>
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Core/Minimal.h"

/* ########## MACROS SECTION ########## */
#define XKVULKAN_FRAME_COUNT 2

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct __XkVkQueueFamilyIndices_T {
  uint32_t graphics;
  uint32_t present;
  uint32_t transfer;
  uint32_t compute;

	VkQueueFlags supportedQueues;
	XkBool8 supportPresentQueue;
} __XkVkQueueFamilyIndices;

typedef struct __XkVkSwapChainDetails_T {
	VkSurfaceCapabilitiesKHR vkCapabilities;
	VkSurfaceFormatKHR vkSurfaceFormats;
	VkPresentModeKHR vkPresentMode;
} __XkVkSwapChainDetails;

typedef struct __XkVkContext_T {
	XkBool8 initialized;

	VkInstance vkInstance;
#if defined(XKVULKAN_DEBUG)
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

/* ########## EXTERN SECTION ########## */
extern const char* _xkVulkanInstanceExtensions[];
extern const uint32_t _xkVulkanInstanceExtensionCount;

extern const char* _xkVulkanInstanceLayers[];
extern const uint32_t _xkVulkanInstanceLayerCount;

extern const char* _xkVulkanDeviceExtensions[];
extern const uint32_t _xkVulkanDeviceExtensionCount;

extern __XkVkContext _xkVulkanContext;

/* ########## FUNCTIONS SECTION ########## */
extern XK_EXPORT XkString 	__xkVulkanGetResultString(VkResult); 

extern XK_EXPORT XkResult 	__xkVulkanCreateInstance();
extern XK_EXPORT void 			__xkVulkanDestroyInstance();

#ifdef XKVULKAN_DEBUG
extern XK_EXPORT XkResult 	__xkVulkanCreateDebugMessenger();
extern XK_EXPORT void 			__xkVulkanDestroyDebugMessenger();
#endif // XKVULKAN_DEBUG

extern XK_EXPORT XkResult 	__xkVulkanCreateSurface(VkSurfaceKHR*, XkWindow);
extern XK_EXPORT void 			__xkVulkanDestroySurface(VkSurfaceKHR);

extern XK_EXPORT XkResult 	__xkVulkanPickPhysicalDevice();

extern XK_EXPORT XkResult 	__xkVulkanCreateLogicalDevice();
extern XK_EXPORT void 			__xkVulkanDestroyLogicalDevice();

extern XK_EXPORT XkResult 	__xkVulkanCreateCommandPool();
extern XK_EXPORT void 			__xkVulkanDestroyCommandPool();

extern XK_EXPORT XkResult 	__xkVulkanCreateSwapChain(VkSwapchainKHR*, VkSurfaceKHR, VkExtent2D* const, VkFormat* const, VkImage*, uint32_t* const);
extern XK_EXPORT void 			__xkVulkanDestroySwapChain(VkSwapchainKHR);

extern XK_EXPORT XkResult 	__xkVulkanCreateRenderPass(VkRenderPass* pVkRenderPass, VkAttachmentDescription*, const uint32_t, VkSubpassDescription*, const uint32_t, VkSubpassDependency*, const uint32_t);
extern XK_EXPORT void 			__xkVulkanDestroyeRenderPass(VkRenderPass);

extern XK_EXPORT XkResult 	__xkVulkanCreateFrameBuffer(VkFramebuffer*, VkRenderPass, const VkExtent2D, VkImageView*, const uint32_t);
extern XK_EXPORT void 			__xkVulkanDestroyFrameBuffer(VkFramebuffer);

extern XK_EXPORT XkResult 	__xkVulkanCreateCommandBuffer(VkCommandBuffer*, const VkCommandBufferLevel);
extern XK_EXPORT void 			__xkVulkanDestroyCommandBuffer(VkCommandBuffer);

extern XK_EXPORT XkResult 	__xkVulkanCreateSemaphore(VkSemaphore*);
extern XK_EXPORT void 			__xkVulkanDestroySemaphore(VkSemaphore);

extern XK_EXPORT XkResult 	__xkVulkanCreateFence(VkFence*);
extern XK_EXPORT void 			__xkVulkanDestroyFence(VkFence);

extern XK_EXPORT XkResult 	__xkVulkanCreateShader(VkShaderModule*, const uint32_t*, const size_t);
extern XK_EXPORT void 			__xkVulkanDestroyShader(VkShaderModule);

extern XK_EXPORT XkResult 	__xkVulkanCreateBuffer(VkBuffer* const, VkDeviceMemory* const, const VkDeviceSize, const VkBufferUsageFlags, const VkMemoryPropertyFlags, const void*);
extern XK_EXPORT void 			__xkVulkanDestroyBuffer(VkBuffer, VkDeviceMemory);

extern XK_EXPORT XkResult 	__xkVulkanCopyBuffer(VkBuffer, const VkBuffer, const VkDeviceSize);

extern XK_EXPORT XkResult 	__xkVulkanMapBuffer(VkDeviceMemory, const VkDeviceSize, const void*);

extern XK_EXPORT XkResult 	__xkVulkanCreateImage(VkImage* const, VkDeviceMemory* const, const VkImageType, const VkFormat, const VkExtent3D, const VkSampleCountFlagBits, const VkImageTiling, const VkImageUsageFlags, const VkMemoryPropertyFlags, const uint32_t);
extern XK_EXPORT void 			__xkVulkanDestroyImage(VkImage, VkDeviceMemory);

extern XK_EXPORT XkResult 	__xkVulkanCreateImageView(VkImageView* const, VkImage, const VkFormat, const VkImageAspectFlags, const uint32_t);
extern XK_EXPORT void 			__xkVulkanDestroyImageView(VkImageView);

extern XK_EXPORT XkResult 	__xkVulkanCreateSampler(VkSampler*, const VkFilter, const VkSamplerAddressMode, const VkBool32, const uint32_t);
extern XK_EXPORT void 			__xkVulkanDestroySampler(VkSampler);

/* ##### HELPER FUNCTIONS SECTION ##### */
#ifdef XKVULKAN_DEBUG
extern XK_EXPORT void 			__xkVulkanPopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT*);
#endif // XKVULKAN_DEBUG

extern XK_EXPORT uint32_t 	__xkVulkanFindMemoryType(uint32_t, const VkMemoryPropertyFlags);

extern XK_EXPORT XkResult 	__xkVulkanBeginSingleCommands(VkCommandBuffer*);
extern XK_EXPORT XkResult 	__xkVulkanEndSingleCommands(VkCommandBuffer);

extern XK_EXPORT XkResult 	__xkVulkanTransitionImageLayout(VkImage, const VkFormat, const VkImageLayout, const VkImageLayout, const uint32_t);
extern XK_EXPORT XkResult 	__xkVulkanCopyBufferToImage(VkBuffer, VkImage, const VkExtent3D);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
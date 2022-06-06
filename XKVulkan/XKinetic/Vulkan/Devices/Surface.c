#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Platform/Internal.h"

XkResult __xkVkCreateSurface(VkSurfaceKHR* pVkSurface, XkWindow window) {
  XkResult result = XK_SUCCESS;

#if defined(XK_LINUX)
	// Initialize Vulkan Wayland surface create info.
  const VkWaylandSurfaceCreateInfoKHR vkWaylandSurfaceCreateInfo = {
		.sType 				= VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
		.pNext 				= VK_NULL_HANDLE,
		.flags 				= 0,
		.display 			= _xkPlatform.handle.wlDisplay,
		.surface 			= window->handle.wlSurface
	};

	// Create Vulkan Wayland surface.
	VkResult vkResult = vkCreateWaylandSurfaceKHR(_xkVkContext.vkInstance, &vkWaylandSurfaceCreateInfo, VK_NULL_HANDLE, pVkSurface);
	if(vkResult != VK_SUCCESS) {
		xkLogError("Failed to create Vulkan Wayland surface: %s", __xkVkGetErrorString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}  
#elif defined(XK_WIN32)
	// Initialize Vulkan Win32 surface create info.
  const VkWin32SurfaceCreateInfoKHR vkWin32SurfaceCreateInfo = {
		.sType 				= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		.pNext 				= VK_NULL_HANDLE,
		.flags 				= 0,
		.hinstance 		= _xkPlatform.handle.instance,
		.hwnd 				= window->handle.handle
	};

	// Create Vulkan Win32 surface.
	VkResult vkResult = vkCreateWin32SurfaceKHR(_xkVkContext.vkInstance, &vkWin32SurfaceCreateInfo, VK_NULL_HANDLE, pVkSurface);
	if(vkResult != VK_SUCCESS) {
		xkLogError("Failed to create Vulkan Win32 surface: %s", __xkVkGetErrorString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}
#endif // XK_LINUX

_catch:
  return(result);
}

void __xkVkDestroySurface(VkSurfaceKHR vkSurface) {
	// Destroy Vulkan surface.
	vkDestroySurfaceKHR(_xkVkContext.vkInstance, vkSurface, VK_NULL_HANDLE);
}

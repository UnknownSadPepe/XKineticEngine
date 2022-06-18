#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Platform/Internal.h"

XkResult __xkVkCreateSurface(VkSurfaceKHR* pVkSurface, XkWindow window) {
  XkResult result = XK_SUCCESS;

#if defined(XK_LINUX)
	// Initialize Vulkan Wayland surface create info.
  VkWaylandSurfaceCreateInfoKHR vkWaylandSurfaceCreateInfo 	= {0};
	vkWaylandSurfaceCreateInfo.sType 													= VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
	vkWaylandSurfaceCreateInfo.pNext 													= VK_NULL_HANDLE;
	vkWaylandSurfaceCreateInfo.flags 													= 0;
	vkWaylandSurfaceCreateInfo.display 												= __xkWaylandGetDisplay();
	vkWaylandSurfaceCreateInfo.surface 												= __xkWaylandGetSurface(window);

	// Create Vulkan Wayland surface.
	VkResult vkResult = vkCreateWaylandSurfaceKHR(_xkVkContext.vkInstance, &vkWaylandSurfaceCreateInfo, VK_NULL_HANDLE, pVkSurface);
	if(vkResult != VK_SUCCESS) {
		xkLogError("Failed to create Vulkan Wayland surface: %s", __xkVkGetErrorString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}  
#elif defined(XK_WIN32)
	// Initialize Vulkan Win32 surface create info.
  VkWin32SurfaceCreateInfoKHR vkWin32SurfaceCreateInfo 				= {0};
	vkWin32SurfaceCreateInfo.sType 															= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	vkWin32SurfaceCreateInfo.pNext 															= VK_NULL_HANDLE;
	vkWin32SurfaceCreateInfo.flags 															= 0;
	vkWin32SurfaceCreateInfo.hinstance 													= __xkWin32GetInstance();
	vkWin32SurfaceCreateInfo.hwnd 															= __xkWin32GetHWND(window);
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

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateSurface(VkSurfaceKHR* pVkSurface, XkWindow window) {
	xkAssert(pVkSurface);
	xkAssert(window);

  XkResult result = XK_SUCCESS;

#if defined(XK_LINUX)
  VkWaylandSurfaceCreateInfoKHR vkWaylandSurfaceCreateInfo 	= {0};
	vkWaylandSurfaceCreateInfo.sType 													= VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
	vkWaylandSurfaceCreateInfo.pNext 													= VK_NULL_HANDLE;
	vkWaylandSurfaceCreateInfo.flags 													= 0;
	vkWaylandSurfaceCreateInfo.display 												= __xkWaylandGetDisplay();
	vkWaylandSurfaceCreateInfo.surface 												= __xkWaylandGetSurface(window);

	VkResult vkResult = vkCreateWaylandSurfaceKHR(_xkVulkanContext.vkInstance, &vkWaylandSurfaceCreateInfo, VK_NULL_HANDLE, pVkSurface);
	if(vkResult != VK_SUCCESS) {
		xkLogError("Vulkan: Failed to create Wayland surface: %s", __xkVulkanGetResultString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}  
#elif defined(XK_WINDOWS)
  VkWin32SurfaceCreateInfoKHR vkWin32SurfaceCreateInfo 				= {0};
	vkWin32SurfaceCreateInfo.sType 															= VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	vkWin32SurfaceCreateInfo.pNext 															= VK_NULL_HANDLE;
	vkWin32SurfaceCreateInfo.flags 															= 0;
	vkWin32SurfaceCreateInfo.hinstance 													= __xkWin32GetInstance();
	vkWin32SurfaceCreateInfo.hwnd 															= __xkWin32GetHWND(window);

	VkResult vkResult = vkCreateWin32SurfaceKHR(_xkVulkanContext.vkInstance, &vkWin32SurfaceCreateInfo, VK_NULL_HANDLE, pVkSurface);
	if(vkResult != VK_SUCCESS) {
		xkLogError("Vulkan: Failed to create Win32 surface: %s", __xkVulkanGetResultString(vkResult));
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}
#endif // XK_LINUX

_catch:
  return(result);
}

void __xkVulkanDestroySurface(VkSurfaceKHR vkSurface) {
	xkAssert(vkSurface);
	
	vkDestroySurfaceKHR(_xkVulkanContext.vkInstance, vkSurface, VK_NULL_HANDLE);
}

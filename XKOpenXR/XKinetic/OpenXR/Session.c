/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"
#if defined(XK_LINUX) || defined(XK_WINDOWS)
	#include "XKinetic/Vulkan/Internal.h"
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_WINDOWS)
	#include "XKinetic/D3D12/Internal.h"
#endif // XK_WINDOWS

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
XkResult __xkOpenXRCreateSession(const XkRendererApi api) {
  XkResult result = XK_SUCCESS;

	void* next = XR_NULL_HANDLE;

#if defined(XK_LINUX) || defined(XK_WINDOWS)
	XrGraphicsBindingVulkanKHR xrGraphicsBindingVulkan  = {0};
	if(api == XK_RENDERER_API_VULKAN) {
		next = &xrGraphicsBindingVulkan;

		xrGraphicsBindingVulkan.type                        = XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR;
		xrGraphicsBindingVulkan.next                        = XR_NULL_HANDLE; 
		xrGraphicsBindingVulkan.instance                    = _xkVulkanContext.vkInstance;
		xrGraphicsBindingVulkan.physicalDevice              = _xkVulkanContext.vkPhysicalDevice;
		xrGraphicsBindingVulkan.device                      = _xkVulkanContext.vkLogicalDevice;
		xrGraphicsBindingVulkan.queueFamilyIndex            = _xkVulkanContext.queueFamilyIndices.graphics;
		xrGraphicsBindingVulkan.queueIndex                  = 0; 
	}
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_WINDOWS)
	XrGraphicsBindingD3D12KHR xrGraphicsBindingD3D12    = {0};	
	if(api == XK_RENDERER_API_D3D12) {
		next = &xrGraphicsBindingD3D12;

		xrGraphicsBindingD3D12.type                         = XR_TYPE_GRAPHICS_BINDING_D3D12_KHR;
		xrGraphicsBindingD3D12.next                         = XR_NULL_HANDLE;
		xrGraphicsBindingD3D12.device                       = _xkD3D12Context.d3d12Device8;
		xrGraphicsBindingD3D12.queue                        = _xkD3D12Context.d3d12CommandQueue;
	}
#endif // XK_WINDOWS

  XrSessionCreateInfo xrSessionInfo   = {0};
  xrSessionInfo.type                  = XR_TYPE_SESSION_CREATE_INFO;
  xrSessionInfo.next                  = next;
  xrSessionInfo.createFlags           = 0;
  xrSessionInfo.systemId              = _xkOpenXRContext.xrSystemId;

  XrResult xrResult = xrCreateSession(_xkOpenXRContext.xrInstance, &xrSessionInfo, &_xkOpenXRContext.xrSession);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create session: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkOpenXRDestroySession() {
  if(_xkOpenXRContext.xrSession) {
    xrDestroySession(_xkOpenXRContext.xrSession);

    _xkOpenXRContext.xrSession = XR_NULL_HANDLE;
  }
}

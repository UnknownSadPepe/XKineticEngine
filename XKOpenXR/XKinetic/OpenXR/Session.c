#include "XKinetic/OpenXR/Internal.h"

XkResult __xkXRCreateSession(void) {
  XkResult result = XK_SUCCESS;

#if defined(XK_XRVULKAN)
  // Initialize OpenXR Vulkan graphics binding.
  XrGraphicsBindingVulkanKHR xrGraphicsBindingVulkan  = {0};
  xrGraphicsBindingVulkan.type                        = XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR;
  xrGraphicsBindingVulkan.next                        = XR_NULL_HANDLE; 
  xrGraphicsBindingVulkan.instance                    = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.physicalDevice              = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.device                      = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.queueFamilyIndex            = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.queueIndex                  = /*TOOD: implementation*/; 
#elif defined(XK_XRDIRECTX12)
  // Initialize OpenXR DirectX12 graphics binding.
  XrGraphicsBindingD3D12KHR xrGraphicsBindingD3D12    = {0};
  xrGraphicsBindingD3D12.type                         = XR_TYPE_GRAPHICS_BINDING_D3D12_KHR;
  xrGraphicsBindingD3D12.next                         = XR_NULL_HANDLE;
  //xrGraphicsBindingD3D12.device                       = /*TOOD: implementation*/;
  //xrGraphicsBindingD3D12.queue                        = /*TOOD: implementation*/;
#endif // XK_XRVULKAN || XK_XRDIRECTX12

  // Initialize OpenXR session info.
  XrSessionCreateInfo xrSessionInfo   = {0};
  xrSessionInfo.type                  = XR_TYPE_SESSION_CREATE_INFO;
#if defined(XK_XRVULKAN)
  xrSessionInfo.next                  = &xrGraphicsBindingVulkan;
#elif defined(XK_XRDIRECTX12)
  xrSessionInfo.next                  = &xrGraphicsBindingD3D12;
#endif // XK_XRVULKAN || XK_XRDIRECTX12
  xrSessionInfo.createFlags           = 0;
  xrSessionInfo.systemId              = _xkXRContext.xrSystemId;

  // Create OpenXR session.
  XrResult xrResult = xrCreateSession(_xkXRContext.xrInstance, &xrSessionInfo, &_xkXRContext.xrSession);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR session: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkXRDestroySession(void) {
  // Destroy OpenXR session.
  if(_xkXRContext.xrSession) {
    xrDestroySession(_xkXRContext.xrSession);

    _xkXRContext.xrSession = XR_NULL_HANDLE;
  }
}

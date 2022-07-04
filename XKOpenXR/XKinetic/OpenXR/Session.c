/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
XkResult __xkOpenXRCreateSession() {
  XkResult result = XK_SUCCESS;

#if defined(XK_XRVULKAN)
  XrGraphicsBindingVulkanKHR xrGraphicsBindingVulkan  = {};
  xrGraphicsBindingVulkan.type                        = XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR;
  xrGraphicsBindingVulkan.next                        = XR_NULL_HANDLE; 
  xrGraphicsBindingVulkan.instance                    = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.physicalDevice              = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.device                      = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.queueFamilyIndex            = /*TOOD: implementation*/;
  xrGraphicsBindingVulkan.queueIndex                  = /*TOOD: implementation*/; 
#elif defined(XK_XRDIRECTX12)
  XrGraphicsBindingD3D12KHR xrGraphicsBindingD3D12    = {};
  xrGraphicsBindingD3D12.type                         = XR_TYPE_GRAPHICS_BINDING_D3D12_KHR;
  xrGraphicsBindingD3D12.next                         = XR_NULL_HANDLE;
  //xrGraphicsBindingD3D12.device                       = /*TOOD: implementation*/;
  //xrGraphicsBindingD3D12.queue                        = /*TOOD: implementation*/;
#endif // XK_XRVULKAN || XK_XRDIRECTX12

  XrSessionCreateInfo xrSessionInfo   = {};
  xrSessionInfo.type                  = XR_TYPE_SESSION_CREATE_INFO;
#if defined(XK_XRVULKAN)
  xrSessionInfo.next                  = &xrGraphicsBindingVulkan;
#elif defined(XK_XRDIRECTX12)
  xrSessionInfo.next                  = &xrGraphicsBindingD3D12;
#endif // XK_XRVULKAN || XK_XRDIRECTX12
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

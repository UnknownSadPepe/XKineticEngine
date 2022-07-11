/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkOpenXRCreateSwapChain(XrSwapchain* pXrSwapChain,	
																	XrSwapchainImageBaseHeader* pXrImages,
																	const XrSwapchainCreateFlags xrCreateFlags, 
																	const XrSwapchainUsageFlags xrUsageFlags, 
																	const int64_t format, 
																	const uint32_t sampleCount, 
																	const uint32_t width, 
																	const uint32_t height, 
																	const uint32_t arraySize) {
  XkResult result = XK_SUCCESS;

	XrSwapchainCreateInfo xrSwapChainInfo		= {0};
	xrSwapChainInfo.type										= XR_TYPE_SWAPCHAIN_CREATE_INFO;
	xrSwapChainInfo.next										= XR_NULL_HANDLE;
	xrSwapChainInfo.createFlags							= xrCreateFlags;
	xrSwapChainInfo.usageFlags							= xrUsageFlags;
	xrSwapChainInfo.format									= format;
	xrSwapChainInfo.sampleCount							= sampleCount;
	xrSwapChainInfo.width										= width;
	xrSwapChainInfo.height									= height;
	xrSwapChainInfo.faceCount								= 1;
	xrSwapChainInfo.arraySize								= arraySize;
	xrSwapChainInfo.mipCount								= 1;

	XrResult xrResult = xrCreateSwapchain(_xkOpenXRContext.xrSession, &xrSwapChainInfo, pXrSwapChain);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create reference space: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

	XrSwapchain xrSwapChain = *pXrSwapChain;

	uint32_t imageCount = 0;
	xrResult = xrEnumerateSwapchainImages(xrSwapChain, 0, &imageCount, XR_NULL_HANDLE);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to enumerate swap chain images: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

#if defined(XK_LINUX) || defined(XK_WINDOWS)
	if(_xkOpenXRContext.api == XK_RENDERER_API_VULKAN) {
		pXrImages = xkAllocateMemory(sizeof(XrSwapchainImageVulkanKHR) * imageCount);
	}
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_WINDOWS)
	if(_xkOpenXRContext.api == XK_RENDERER_API_D3D12) {
		pXrImages = xkAllocateMemory(sizeof(XrSwapchainImageD3D12KHR) * imageCount);
	}
#endif // XK_WINDOWS

	xrResult = xrEnumerateSwapchainImages(xrSwapChain, imageCount, XR_NULL_HANDLE, (XrSwapchainImageBaseHeader*)pXrImages);
  if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to enumerate swap chain images: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkOpenXRDestroySwapChain(XrSwapchain xrSwapChain) {
	xkAssert(xrSwapChain);

	xrDestroySwapchain(xrSwapChain);
}

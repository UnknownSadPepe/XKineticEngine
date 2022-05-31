#include "XKinetic/Renderer/External.h"
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Vulkan/Renderer.h"

struct XkVkRenderer {
	XkRendererConfig config;
	
	struct {
		XkVec4 color;
		XkFloat64 depth;
		XkInt32 stencil;
	} clearValue;
};

XkChar8* __xkVkGetErrorString(VkResult error) {
	switch(error) {
		case VK_SUCCESS:												return "Success";
		case VK_NOT_READY:											return "A Vulkan fence or query has not yet completed";
		case VK_TIMEOUT:												return "A Vulkan wait operation has not completed in the specified time";
		case VK_EVENT_SET:											return "A Vulkan event is signaled";
		case VK_EVENT_RESET:										return "A Vulkan event is unsignaled";
		case VK_INCOMPLETE:											return "A return Vulkan array was too small for the result";
		case VK_ERROR_OUT_OF_HOST_MEMORY:				return "A Vulkan host memory allocation has failed";
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:			return "A Vulkan device memory allocation has failed";
		case VK_ERROR_INITIALIZATION_FAILED:		return "Initialization of an Vulkan object could not be completed for implementation-specific reasons";
		case VK_ERROR_DEVICE_LOST:							return "The Vulkan logical or physical device has been lost";
		case VK_ERROR_MEMORY_MAP_FAILED:				return "Mapping of a Vukan memory object has failed";
		case VK_ERROR_LAYER_NOT_PRESENT:				return "A requested Vulkan layer is not present or could not be loaded";
		case VK_ERROR_EXTENSION_NOT_PRESENT:		return "A requested Vulkan extension is not supported";
		case VK_ERROR_FEATURE_NOT_PRESENT:			return "A requested Vulkan feature is not supported";
		case VK_ERROR_INCOMPATIBLE_DRIVER:			return "The requested version of Vulkan is not supported by the driver or is otherwise incompatible";
		case VK_ERROR_TOO_MANY_OBJECTS:					return "Too many Vulkan objects of the type have already been created";
		case VK_ERROR_FORMAT_NOT_SUPPORTED:			return "A Vulkan requested format is not supported on this device";
		case VK_ERROR_SURFACE_LOST_KHR:					return "A Vulkan surface is no longer available";
		case VK_ERROR_OUT_OF_POOL_MEMORY:				return "A Vulkan allocation failed due to having no more space in the descriptor pool";
		case VK_SUBOPTIMAL_KHR:									return "A Vulkan swapchain no longer matches the surface properties exactly, but can still be used";
		case VK_ERROR_OUT_OF_DATE_KHR:					return "A Vulkan surface has changed in such a way that it is no longer compatible with the swapchain";
		case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:	return "The display used by a Vulkan swapchain does not use the same presentable image layout";
		case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:	return "The requested window is already connected to a VkSurfaceKHR, or to some other non-Vulkan API";
		case VK_ERROR_VALIDATION_FAILED_EXT:		return "A Vulkan validation layer found an error";
		default:																return "unknown Vulkan error";
	}
}

XkResult xkVkCreateRenderer(XkVkRenderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window) {
	// TODO: implementation.
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkVkRenderer));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkRenderer renderer = *pRenderer;

	renderer->config = *pConfig;

	result = __xkVkInitializeContext();
	if(result != XK_SUCCESS) {
		xkLogError("Failed to initialize Vulkan Context");
		goto _catch;
	}

	// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyRenderer(XkVkRenderer renderer) {
	// TODO: implementation.
	xkFreeMemory(renderer);
	
	__xkVkTerminateContext();
}

void xkVkClearColorRenderer(XkVkRenderer renderer, XkVec4 color) {
	// Set Vulkan renderer clear color.
	renderer->clearValue.color = color;
}

void xkVkClearDepthRenderer(XkVkRenderer renderer, XkFloat64 depth) {
	// Set Vulkan renderer clear depth.
	renderer->clearValue.depth = depth;
}

void xkVkClearStencilRenderer(XkVkRenderer renderer, XkInt32 stencil) {
	// Set Vulkan renderer clear stencil.
	renderer->clearValue.stencil = stencil;
}

void xkVkClearRenderer(XkVkRenderer renderer) {
	// TODO: implementation.
}

void xkVkTopologyRenderer(XkVkRenderer renderer, XkTopology topology) {
	// TODO: implementation.
}

void xkVkCullModeRenderer(XkVkRenderer renderer, XkCullMode cullMode) {
	// TODO: implementation.
}

void xkVkBeginRenderer(XkVkRenderer renderer) {
	// TODO: implementation.
}

void xkVkEndRenderer(XkVkRenderer renderer) {
	// TODO: implementation.
}

void xkVkResizeRenderer(XkVkRenderer renderer, XkSize width, XkSize height) {
	// TODO: implementation.
}

void xkVkScissorRenderer(XkVkRenderer renderer, XkSize x, XkSize y, XkSize width, XkSize height) {
	// TODO: implementation.
}

void xkVkDraw(XkVkRenderer renderer, XkSize vertexCount) {
	// TODO: implementation.
}

void xkVkDrawIndexed(XkVkRenderer renderer, XkSize indexCount) {
	// TODO: implementation.
}

XkResult xkVkCreateVertexBuffer(XkVkVertexBuffer* pBuffer, const XkSize size, XkHandle data, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkVertexBuffer buffer = *pBuffer;

	buffer->size = (VkDeviceSize)size;

	// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyVertexBuffer(XkVkVertexBuffer buffer) {
	// TODO: implementation.
	xkFreeMemory(buffer);
}

void xkVkBindVertexBuffer(XkVkVertexBuffer buffer) {
	// TODO: implementation.
}

void xkVkUnbindVertexBuffer(XkVkVertexBuffer buffer) {
	// TODO: implementation.
}

void xkVkSetVertexBuffer(XkVkIndexBuffer buffer, XkHandle data) {
	// TODO: implementation.
}

XkResult xkVkCreateIndexBuffer(XkVkIndexBuffer* pBuffer, const XkSize size, XkHandle data, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkIndexBuffer buffer = *pBuffer;

	buffer->size = (VkDeviceSize)size;

	// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyIndexBuffer(XkVkIndexBuffer buffer) {
	// TODO: implementation.
	xkFreeMemory(buffer);
}

void xkVkBindIndexBuffer(XkVkIndexBuffer buffer) {
	// TODO: implementation.
}

void xkVkUnbindIndexBuffer(XkVkIndexBuffer buffer) {
	// TODO: implementation.
}

void xkVkSetIndexBuffer(XkVkIndexBuffer buffer, XkHandle data) {
	// TODO: implementation.
}

XkResult xkVkCreateUniformBuffer(XkVkUniformBuffer* pBuffer, const XkSize size, const XkSize binding, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkUniformBuffer buffer = *pBuffer;

	buffer->size = (VkDeviceSize)size;

	// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyUniformBuffer(XkVkUniformBuffer buffer) {
	// TODO: implementation.
	xkFreeMemory(buffer);
}

void xkVkSetUniformBuffer(XkVkUniformBuffer buffer, XkHandle data, XkSize offset) {
	// TODO: implementation.
}

XkResult xkVkCreateTexture2D(XkVkTexture2D* pTexture, XkHandle* data, const XkSize width, const XkSize height, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkVkTexture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkTexture2D texture = *pTexture;

	// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyTexture2D(XkVkTexture2D texture) {
	// TODO: implementation.
	xkFreeMemory(texture);
}


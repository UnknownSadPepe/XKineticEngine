#include "XKinetic/Renderer/External.h"
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Vulkan/Renderer.h"

struct XkVkRenderer {
	XkRendererConfig config;

	VkClearValue vkClearValues[2];
	VkRect2D vkScissor;
	VkExtent2D vkExtent;
	VkCullModeFlags vkCullMode;
	VkPrimitiveTopology vkPrimitiveTopology;

	VkSurfaceKHR vkSurface;
	VkSwapchainKHR vkSwapChain;
	VkFormat vkSwapChainImageFormat;
	VkImage* vkSwapChainImages;
	VkImageView* vkSwapChainImageViews;
	uint32_t swapChainImageCount;
	VkFramebuffer* vkSwapChainFrameBuffer;

  VkSemaphore* vkAvailableSemaphores;
  VkSemaphore* vkFinishedSemaphores;
  VkFence* vkFlightFences;

	VkCommandBuffer* vkCommandBuffers;

	uint32_t frameIndex;
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
	/// TODO: implementation.
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkVkRenderer));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkRenderer renderer = *pRenderer;

	renderer->config = *pConfig;

	// Initialize Vulkan context.
	result = __xkVkInitializeContext();
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;  
		xkLogError("Failed to initialize Vulkan Context");
		goto _catch;
	}

	// Create Vulkan renderer surface.
	result = __xkVkCreateSurface(&renderer->vkSurface, window);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan surface: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
  }  

	// Create Vulkan renderer swap chain.
	renderer->vkSwapChainImages =  xkAllocateMemory(sizeof(VkImage) * 2);
	result = __xkVkCreateSwapChain(&renderer->vkSwapChain, renderer->vkSurface, &renderer->vkExtent, &renderer->vkSwapChainImageFormat, renderer->vkSwapChainImages, &renderer->swapChainImageCount);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan swap chain: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
  }

	// Create Vulkan renderer swap chain image views.
	renderer->vkSwapChainImageViews =  xkAllocateMemory(sizeof(VkImageView) * 2);
	for(uint32_t i = 0; i < 2; i++) {
		result = __xkVkCreateImageView(&renderer->vkSwapChainImageViews[i], renderer->vkSwapChainImages[i], renderer->vkSwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan swap chain image view: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}
	}

	// Create Vulkan command buffers.
	renderer->vkCommandBuffers =  xkAllocateMemory(sizeof(VkCommandBuffer) * 2);
	for(uint32_t i = 0; i < 2; i++) {
		result = __xkVkCreateCommandBuffer(&renderer->vkCommandBuffers[i], VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan command buffer: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}	
	}

	// Create Vulkan available semaphores.
	renderer->vkAvailableSemaphores = xkAllocateMemory(sizeof(VkSemaphore) * 2);
	for(uint32_t i = 0; i < 2; i++) {
		result = __xkVkCreateSemaphore(&renderer->vkAvailableSemaphores[i]);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan semaphore: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}		
	}

	// Create Vulkan finished semaphores.
  renderer->vkFinishedSemaphores = xkAllocateMemory(sizeof(VkSemaphore) * 2);
	for(uint32_t i = 0; i < 2; i++) {
		result = __xkVkCreateSemaphore(&renderer->vkFinishedSemaphores[i]);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan semaphore: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}		
	}

	// Create Vulkan fences.
  renderer->vkFlightFences = xkAllocateMemory(sizeof(VkFence) * 2);
	for(uint32_t i = 0; i < 2; i++) {
		result = __xkVkCreateFence(&renderer->vkFlightFences[i]);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan fence: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}		
	}	

	/// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyRenderer(XkVkRenderer renderer) {
	/// TODO: implementation.
	xkFreeMemory(renderer);
	
	// Destroy Vulkan flight fence.
	for(uint32_t i = 0; i < 2; i++) {
		__xkVkDestroyFence(renderer->vkFlightFences[i]);
	}

	// Destroy Vulkan available semaphores.
	for(uint32_t i = 0; i < 2; i++) {
		__xkVkDestroySemaphore(renderer->vkAvailableSemaphores[i]);
	}

	// Destroy Vulkan finished semaphores.
	for(uint32_t i = 0; i < 2; i++) {
		__xkVkDestroySemaphore(renderer->vkFinishedSemaphores[i]);
	}

	// Destroy Vulkan command buffers.
	for(uint32_t i = 0; i < 2; i++) {
		__xkVkDestroyCommandBuffer(renderer->vkCommandBuffers[i]);
	}	

	// Destroy Vulkan renderer swap chain image views.
	for(uint32_t i = 0; i < 2; i++) {
		__xkVkDestroyImageView(renderer->vkSwapChainImageViews[i]);
	}

	// Destroy Vulkan renderer swap chain.
	__xkVkDestroySwapChain(renderer->vkSwapChain);

	// Destroy Vulkan renderer surface.
	__xkVkDestroySurface(renderer->vkSurface);

	// Terminate Vulkan context.
	__xkVkTerminateContext();
}

void xkVkClearColorRenderer(XkVkRenderer renderer, XkVec4 color) {
	// Set Vulkan renderer clear color.
	renderer->vkClearValues[0].color.float32[0] = (float)color.r;
	renderer->vkClearValues[0].color.float32[1] = (float)color.g;
	renderer->vkClearValues[0].color.float32[2] = (float)color.b;
	renderer->vkClearValues[0].color.float32[3] = (float)color.a;
}

void xkVkClearDepthRenderer(XkVkRenderer renderer, XkFloat32 depth) {
	// Set Vulkan renderer clear depth.
	if(renderer->config.depthTest) {
		renderer->vkClearValues[1].depthStencil.depth = (float)depth;
	}
}

void xkVkClearStencilRenderer(XkVkRenderer renderer, XkUInt32 stencil) {
	// Set Vulkan renderer clear stencil.
	if(renderer->config.stencilTest) {
		renderer->vkClearValues[1].depthStencil.stencil = (uint32_t)stencil;
	}
}

void xkVkClearRenderer(XkVkRenderer renderer) {
	/// TODO: implementation.

	// Template Vulkan command buffer.
	VkCommandBuffer vkCommandBuffer = renderer->vkCommandBuffers[renderer->frameIndex];

	const VkViewport vkViewport = {
		.x 					= 0,
		.y 					= 0,
		.width 			= (float)renderer->vkExtent.width,
		.height 		= (float)renderer->vkExtent.height,
		.minDepth 	= 0.0f,
		.maxDepth 	= 1.0f
	};

  vkCmdSetViewport(vkCommandBuffer, 0, 1, &vkViewport);
  vkCmdSetScissor(vkCommandBuffer, 0, 1, &renderer->vkScissor);
	vkCmdSetPrimitiveTopology(vkCommandBuffer, renderer->vkPrimitiveTopology);
	vkCmdSetCullMode(vkCommandBuffer, renderer->vkCullMode);
}

void xkVkTopologyRenderer(XkVkRenderer renderer, XkTopology topology) {
	// Set Vulkan renderer topology.
	switch(topology) {
		case XK_TOPOLOGY_POINT_LIST: 			renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST; break;
		case XK_TOPOLOGY_LINE_LIST:				renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST; break;
		case XK_TOPOLOGY_LINE_STRIP: 			renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; break;
		case XK_TOPOLOGY_TRIANGLE_LIST: 	renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; break;
		case XK_TOPOLOGY_TRIANGLE_STRIP:	renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; break;
	}
}

void xkVkCullModeRenderer(XkVkRenderer renderer, XkCullMode cullMode) {
	// Set Vulkan renderer cull mode.
	switch(cullMode) {
		case XK_CULL_MODE_FRONT: 			renderer->vkCullMode = VK_CULL_MODE_FRONT_BIT; break;
		case XK_CULL_MODE_BACK: 			renderer->vkCullMode = VK_CULL_MODE_BACK_BIT; break;
		case XK_CULL_MODE_FRONT_BACK: renderer->vkCullMode = VK_CULL_MODE_FRONT_AND_BACK; break;
	}
}

void xkVkBeginRenderer(XkVkRenderer renderer) {
	/// TODO: implementation.
}

void xkVkEndRenderer(XkVkRenderer renderer) {
	/// TODO: implementation.
}

void xkVkResizeRenderer(XkVkRenderer renderer, XkSize width, XkSize height) {
	// Set Vulkan renderer extent.
	renderer->vkExtent.width 		= (uint32_t)width;
	renderer->vkExtent.height 	= (uint32_t)height;	
}

void xkVkScissorRenderer(XkVkRenderer renderer, XkInt32 x, XkInt32 y, XkSize width, XkSize height) {
	// Set Vulkan renderer scissor.
	if(renderer->config.scissorTest) {
		renderer->vkScissor.offset.x 				= (int32_t)x;
		renderer->vkScissor.offset.y 				= (int32_t)y;
		renderer->vkScissor.extent.width 		= (uint32_t)width;
		renderer->vkScissor.extent.height 	= (uint32_t)height;
	}
}

void xkVkDraw(XkVkRenderer renderer, XkSize vertexCount) {
	// Draw Vulkan.
	vkCmdDraw(renderer->vkCommandBuffers[renderer->frameIndex], (uint32_t)vertexCount, 1, 0, 0);
}

void xkVkDrawIndexed(XkVkRenderer renderer, XkSize indexCount) {
	// Draw indexed Vulkan.
	vkCmdDrawIndexed(renderer->vkCommandBuffers[renderer->frameIndex], (uint32_t)indexCount, 1, 0, 0, 0);
}

XkResult xkVkCreateVertexBuffer(XkVkVertexBuffer* pBuffer, const XkSize size, XkHandle data, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkVertexBuffer buffer = *pBuffer;

	buffer->vkSize = (VkDeviceSize)size;

	VkBuffer vkTransferBuffer;
	VkDeviceMemory vkTransferBufferMemory;
	result = __xkVkCreateBuffer(&vkTransferBuffer, &vkTransferBufferMemory, (VkDeviceSize)size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, data);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan transfer buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	result = __xkVkCreateBuffer(&buffer->vkBuffer, &buffer->vkMemory, buffer->vkSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, XK_NULL_HANDLE);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	result = __xkVkCopyBuffer(buffer->vkBuffer, vkTransferBuffer, buffer->vkSize);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to copy Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	__xkVkDestroyBuffer(vkTransferBuffer, vkTransferBufferMemory);

_catch:
	return(result);
}

void xkVkDestroyVertexBuffer(XkVkVertexBuffer buffer) {
	__xkVkDestroyBuffer(buffer->vkBuffer, buffer->vkMemory);
	xkFreeMemory(buffer);
}

void xkVkBindVertexBuffer(XkVkVertexBuffer buffer) {
	/// TODO: implementation.
}

void xkVkUnbindVertexBuffer(XkVkVertexBuffer buffer) {
	/// TODO: implementation.
}

void xkVkSetVertexBuffer(XkVkIndexBuffer buffer, XkHandle data) {
	/// TODO: implementation.
}

XkResult xkVkCreateIndexBuffer(XkVkIndexBuffer* pBuffer, const XkSize size, XkHandle data, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkIndexBuffer buffer = *pBuffer;

	buffer->vkSize = (VkDeviceSize)size;

	VkBuffer vkTransferBuffer;
	VkDeviceMemory vkTransferBufferMemory;
	result = __xkVkCreateBuffer(&vkTransferBuffer, &vkTransferBufferMemory, (VkDeviceSize)size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, data);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan transfer buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	result = __xkVkCreateBuffer(&buffer->vkBuffer, &buffer->vkMemory, buffer->vkSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, XK_NULL_HANDLE);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	result = __xkVkCopyBuffer(buffer->vkBuffer, vkTransferBuffer, buffer->vkSize);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to copy Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	__xkVkDestroyBuffer(vkTransferBuffer, vkTransferBufferMemory);

_catch:
	return(result);
}

void xkVkDestroyIndexBuffer(XkVkIndexBuffer buffer) {
	__xkVkDestroyBuffer(buffer->vkBuffer, buffer->vkMemory);
	xkFreeMemory(buffer);
}

void xkVkBindIndexBuffer(XkVkIndexBuffer buffer) {
	/// TODO: implementation.
}

void xkVkUnbindIndexBuffer(XkVkIndexBuffer buffer) {
	/// TODO: implementation.
}

void xkVkSetIndexBuffer(XkVkIndexBuffer buffer, XkHandle data) {
	/// TODO: implementation.
}

XkResult xkVkCreateUniformBuffer(XkVkUniformBuffer* pBuffer, const XkSize size, const XkSize binding, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkUniformBuffer buffer = *pBuffer;

	buffer->vkSize = (VkDeviceSize)size;

	result = __xkVkCreateBuffer(&buffer->vkBuffer, &buffer->vkMemory, buffer->vkSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, XK_NULL_HANDLE);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

_catch:
	return(result);
}

void xkVkDestroyUniformBuffer(XkVkUniformBuffer buffer) {
	__xkVkDestroyBuffer(buffer->vkBuffer, buffer->vkMemory);
	xkFreeMemory(buffer);
}

void xkVkSetUniformBuffer(XkVkUniformBuffer buffer, XkHandle data, XkSize offset) {
	/// TODO: implementation.
}

XkResult xkVkCreateTexture2D(XkVkTexture2D* pTexture, XkHandle* data, const XkSize width, const XkSize height, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkVkTexture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkTexture2D texture = *pTexture;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkVkDestroyTexture2D(XkVkTexture2D texture) {
	/// TODO: implementation.
	xkFreeMemory(texture);
}


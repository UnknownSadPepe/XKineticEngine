#include "XKinetic/Renderer/External.h"
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Vulkan/Renderer.h"

struct XkVkRenderer {
	XkRendererConfig config;

	VkClearValue vkClearValues[2];
	uint32_t clearValueCount;
	VkRect2D vkScissor;
	VkExtent2D vkExtent;
	VkCullModeFlags vkCullMode;
	VkPrimitiveTopology vkPrimitiveTopology;

	VkSurfaceKHR vkSurface;
	VkSwapchainKHR vkSwapChain;
	VkFormat vkSwapChainImageFormat;
	VkImage vkSwapChainImages[XKVULKAN_FRAME_COUNT];
	VkImageView vkSwapChainImageViews[XKVULKAN_FRAME_COUNT];
	uint32_t swapChainImageCount;
	VkFramebuffer vkFrameBuffers[XKVULKAN_FRAME_COUNT];

	VkRenderPass vkRenderPass;

  VkSemaphore vkAvailableSemaphores[XKVULKAN_FRAME_COUNT];
  VkSemaphore vkFinishedSemaphores[XKVULKAN_FRAME_COUNT];
  VkFence vkFlightFences[XKVULKAN_FRAME_COUNT];

	VkCommandBuffer vkCommandBuffers[XKVULKAN_FRAME_COUNT];

	uint32_t frameIndex;
	uint32_t imageIndex;
};

struct XkVkBuffer {
	XkVkRenderer renderer;

	VkBuffer vkBuffer;
	VkDeviceMemory vkMemory;
	VkDeviceSize vkSize;
};

struct XkVkTexture2D {
	XkVkRenderer renderer;

	VkImage vkImage;
	VkDeviceMemory vkMemory;
	VkImageView vkImageView;
	VkSampler vkSampler;
};

XkResult xkVkCreateRenderer(XkVkRenderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window) {
	/// TODO: Implementation.
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkVkRenderer));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkRenderer renderer = *pRenderer;

	renderer->config = *pConfig;
	renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	renderer->vkCullMode = VK_CULL_MODE_FRONT_AND_BACK;
	renderer->frameIndex = 0;
	renderer->imageIndex = 0;

	if(renderer->config.depthTest || renderer->config.stencilTest) {
		renderer->clearValueCount = 2;
	} else {
		renderer->clearValueCount = 1;
	}

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
	result = __xkVkCreateSwapChain(&renderer->vkSwapChain, renderer->vkSurface, &renderer->vkExtent, &renderer->vkSwapChainImageFormat, renderer->vkSwapChainImages, &renderer->swapChainImageCount);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan swap chain: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
  }

	// Create Vulkan renderer swap chain image views.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVkCreateImageView(&renderer->vkSwapChainImageViews[i], renderer->vkSwapChainImages[i], renderer->vkSwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan swap chain image view: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}
	}

	// Create Vulkan command buffers.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVkCreateCommandBuffer(&renderer->vkCommandBuffers[i], VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan command buffer: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}	
	}

	// Create Vulkan available semaphores.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVkCreateSemaphore(&renderer->vkAvailableSemaphores[i]);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan semaphore: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}		
	}

	// Create Vulkan finished semaphores.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVkCreateSemaphore(&renderer->vkFinishedSemaphores[i]);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan semaphore: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}		
	}

	// Create Vulkan fences.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVkCreateFence(&renderer->vkFlightFences[i]);
		if(result != XK_SUCCESS) {
    	xkLogError("Failed to create Vulkan fence: %d", result);
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _catch;
  	}		
	}

	/// TODO: Implementation.

_catch:
	return(result);
}

void xkVkDestroyRenderer(XkVkRenderer renderer) {
	/// TODO: Implementation.
	
	// Destroy Vulkan flight fence.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVkDestroyFence(renderer->vkFlightFences[i]);
	}

	// Destroy Vulkan available semaphores.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVkDestroySemaphore(renderer->vkAvailableSemaphores[i]);
	}

	// Destroy Vulkan finished semaphores.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVkDestroySemaphore(renderer->vkFinishedSemaphores[i]);
	}

	// Destroy Vulkan command buffers.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVkDestroyCommandBuffer(renderer->vkCommandBuffers[i]);
	}	

	// Destroy Vulkan renderer swap chain image views.
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVkDestroyImageView(renderer->vkSwapChainImageViews[i]);
	}

	// Destroy Vulkan renderer swap chain.
	__xkVkDestroySwapChain(renderer->vkSwapChain);

	// Destroy Vulkan renderer surface.
	__xkVkDestroySurface(renderer->vkSurface);

	xkFreeMemory(renderer);

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
	/// TODO: Implementation.

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
	/// TODO: acquire next Vulkan swap chain image.

	// Template Vulkan command buffer.
	VkCommandBuffer vkCommandBuffer = renderer->vkCommandBuffers[renderer->frameIndex];

	// Template Vulkan frame buffer.
	VkFramebuffer vkFrameBuffer = renderer->vkFrameBuffers[renderer->imageIndex];

	// Initialize Vulkan command buffer begin info.
  VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {0};
  vkCommandBufferBeginInfo.sType              			= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  vkCommandBufferBeginInfo.pNext              			= VK_NULL_HANDLE;
  vkCommandBufferBeginInfo.flags              			= 0;
  vkCommandBufferBeginInfo.pInheritanceInfo   			= VK_NULL_HANDLE;

  // Begin Vulkan command buffer.
  VkResult vkResult = vkBeginCommandBuffer(vkCommandBuffer, &vkCommandBufferBeginInfo);
  if(vkResult != VK_SUCCESS) {
    xkLogError("Failed to begin Vulkan command buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

	// Initialize Vulkan render pass begin info.
	VkRenderPassBeginInfo vkRenderPassBeginInfo = {0};
  vkRenderPassBeginInfo.sType 								= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	vkRenderPassBeginInfo.pNext 								= VK_NULL_HANDLE;
	vkRenderPassBeginInfo.renderPass 						= renderer->vkRenderPass;
	vkRenderPassBeginInfo.framebuffer				 		= vkFrameBuffer;
	vkRenderPassBeginInfo.renderArea.offset.x 	= 0;
	vkRenderPassBeginInfo.renderArea.offset.y 	= 0;
	vkRenderPassBeginInfo.renderArea.extent 		= renderer->vkExtent;
	vkRenderPassBeginInfo.clearValueCount 			= renderer->clearValueCount;
	vkRenderPassBeginInfo.pClearValues 					= renderer->vkClearValues;

	// Begin Vulkan render pass.
  vkCmdBeginRenderPass(vkCommandBuffer, &vkRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

_catch:
	return;
}

void xkVkEndRenderer(XkVkRenderer renderer) {
	// Template Vulkan command buffer.
	VkCommandBuffer vkCommandBuffer = renderer->vkCommandBuffers[renderer->frameIndex];

	// End Vulkan render pass.
	vkCmdEndRenderPass(vkCommandBuffer);

	// End Vulkan command buffer.
  VkResult vkResult = vkEndCommandBuffer(vkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    xkLogError("Failed to end Vulkan single command buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }  

	/// TODO: submit Vulkan command buffer.

	// Register frame index.
	renderer->frameIndex = (renderer->frameIndex + 1) % XKVULKAN_FRAME_COUNT;

_catch:
	return;
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

XkResult xkVkCreateBuffer(XkVkBuffer* pBuffer, const XkBufferUsage usage, const XkSize size, const XkHandle data, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkBuffer buffer = *pBuffer;

	buffer->vkSize = (VkDeviceSize)size;
	buffer->renderer = renderer;

	// Choose Vulkan buffer usage flag.
	VkBufferUsageFlags vkBufferUsage = {0};
	switch(usage) {
		case XK_BUFFER_USAGE_VERTEX: 	vkBufferUsage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT; break;
		case XK_BUFFER_USAGE_INDEX: 	vkBufferUsage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT; break;
		case XK_BUFFER_USAGE_UNIFORM: vkBufferUsage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT; break;
	}

	// Create Vulkan buffer.
	result = __xkVkCreateBuffer(&buffer->vkBuffer, &buffer->vkMemory, buffer->vkSize, vkBufferUsage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, data);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

_catch:
	return(result);
}

void xkVkDestroyBuffer(XkVkBuffer buffer) {
	// Destroy Vulkan buffer.
	__xkVkDestroyBuffer(buffer->vkBuffer, buffer->vkMemory);

	xkFreeMemory(buffer);
}

void xkVkBindVertexBuffer(XkVkBuffer buffer) {
	// Template Vulkan command buffer.
	VkCommandBuffer vkCommandBuffer = buffer->renderer->vkCommandBuffers[buffer->renderer->frameIndex];

	// Bind Vulkan vertex buffer.
  VkBuffer vkVertexBuffers[] = {buffer->vkBuffer};
  VkDeviceSize vkOffsets[] = {0};
  vkCmdBindVertexBuffers(vkCommandBuffer, 0, 1, vkVertexBuffers, vkOffsets);
}

void xkVkBindIndexBuffer(XkVkBuffer buffer) {
	// Template Vulkan command buffer.
	VkCommandBuffer vkCommandBuffer = buffer->renderer->vkCommandBuffers[buffer->renderer->frameIndex];

	// Bind Vulkan index buffer.
	vkCmdBindIndexBuffer(vkCommandBuffer, buffer->vkBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void xkVkMapBuffer(XkVkBuffer buffer, const XkHandle data) {
	// Map Vulkan buffer.
	__xkVkMapBuffer(buffer->vkMemory, buffer->vkSize, data);
}

XkResult xkVkCreateTexture2D(XkVkTexture2D* pTexture, XkHandle data, const XkSize width, const XkSize height, XkVkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkVkTexture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVkTexture2D texture = *pTexture;

	texture->renderer = renderer;

	/// TODO: Implementation.
	const VkDeviceSize vkSize = (width * height) * 4;

	/// TODO: Implementation.
	uint32_t mipLevels = 1; 

	VkExtent3D vkExtent 	= {0};
	vkExtent.width 				= (uint32_t)width;
	vkExtent.height 			= (uint32_t)height;
	vkExtent.depth 				= 1;

	// Create Vulkan transfer buffer.
	VkBuffer vkTransferBuffer;
	VkDeviceMemory vkTransferBufferMemory;
	result = __xkVkCreateBuffer(&vkTransferBuffer, &vkTransferBufferMemory, vkSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, data);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan transfer buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	// Create Vulkan image.
	result = __xkVkCreateImage(&texture->vkImage, &texture->vkMemory, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_SRGB, vkExtent, VK_SAMPLE_COUNT_1_BIT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mipLevels);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan image: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	__xkVkTransitionImageLayout(texture->vkImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
	__xkVkCopyBufferToImage(vkTransferBuffer, texture->vkImage, vkExtent);

	// Destroy Vulkan transfer buffer.
	__xkVkDestroyBuffer(vkTransferBuffer, vkTransferBufferMemory);

	// Create Vulkan image view.
	result = __xkVkCreateImageView(&texture->vkImageView, texture->vkImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan image view: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

	// Create Vulkan sampler.
	result = __xkVkCreateSampler(&texture->vkSampler, VK_FILTER_LINEAR, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_TRUE, mipLevels);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan smapler: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _catch;
	}

_catch:
	return(result);
}

void xkVkDestroyTexture2D(XkVkTexture2D texture) {
	// Destroy Vulkan sampler.
	__xkVkDestroySampler(texture->vkSampler);

	// Destroy Vulkan image view.
	__xkVkDestroyImageView(texture->vkImageView);

	// Destroy Vulkan image.
	__xkVkDestroyImage(texture->vkImage, texture->vkMemory);

	xkFreeMemory(texture);
}


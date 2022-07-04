/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Renderer/External.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Vulkan/Renderer.h"

/* ########## TYPES SECTION ########## */
struct XkVulkanRenderer_T {
	XkRendererConfig 			config;

	VkClearValue 					vkClearValues[2];
	uint32_t 							clearValueCount;

	VkRect2D 							vkScissor;
	VkExtent2D 						vkExtent;

	VkCullModeFlags 			vkCullMode;

	VkPrimitiveTopology 	vkPrimitiveTopology;

	VkSurfaceKHR 					vkSurface;
	VkSwapchainKHR 				vkSwapChain;
	VkFormat 							vkSwapChainImageFormat;
	VkImage 							vkSwapChainImages[XKVULKAN_FRAME_COUNT];
	VkImageView 					vkSwapChainImageViews[XKVULKAN_FRAME_COUNT];
	uint32_t 							swapChainImageCount;

	VkFramebuffer 				vkFrameBuffers[XKVULKAN_FRAME_COUNT];

	VkRenderPass 					vkRenderPass;

  VkSemaphore 					vkAvailableSemaphores[XKVULKAN_FRAME_COUNT];
  VkSemaphore 					vkFinishedSemaphores[XKVULKAN_FRAME_COUNT];
  VkFence 							vkFlightFences[XKVULKAN_FRAME_COUNT];

	VkCommandBuffer 			vkCommandBuffers[XKVULKAN_FRAME_COUNT];

	uint32_t 							frameIndex;
	uint32_t 							imageIndex;
};

struct XkVulkanBuffer_T {
	XkVulkanRenderer 	renderer;

	VkBuffer 					vkBuffer;
	VkDeviceMemory 		vkMemory;
	VkDeviceSize 			vkSize;
};

struct XkVulkanTexture2d_T {
	XkVulkanRenderer renderer;

	VkImage 				vkImage;
	VkDeviceMemory 	vkMemory;
	VkImageView 		vkImageView;
	VkSampler 			vkSampler;
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkVulkanCreateRenderer(XkVulkanRenderer* pRenderer, const XkRendererConfig* const pConfig, const XkWindow window) {
	xkAssert(pRenderer);
	xkAssert(pConfig);
	xkAssert(window);

	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkVulkanRenderer_T));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVulkanRenderer renderer = *pRenderer;

	renderer->config 									= *pConfig;

	if(renderer->config.depthTest || renderer->config.stencilTest) {
		renderer->clearValueCount 			= 2;
	} else {
		renderer->clearValueCount 			= 1;
	}

	renderer->vkScissor								= (VkRect2D){};
	renderer->vkExtent 								= (VkExtent2D){};
	renderer->vkCullMode 							= VK_CULL_MODE_FRONT_AND_BACK;
	renderer->vkPrimitiveTopology 		= VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	renderer->vkSurface 							= VK_NULL_HANDLE;
	renderer->vkSwapChain 						= VK_NULL_HANDLE;
	renderer->vkSwapChainImageFormat 	= 0;
	renderer->frameIndex 							= 0;
	renderer->imageIndex 							= 0;

	result = __xkVulkanCreateSurface(&renderer->vkSurface, window);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
  }  

	result = __xkVulkanCreateSwapChain(&renderer->vkSwapChain, renderer->vkSurface, &renderer->vkExtent, &renderer->vkSwapChainImageFormat, renderer->vkSwapChainImages, &renderer->swapChainImageCount);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
  }

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVulkanCreateImageView(&renderer->vkSwapChainImageViews[i], renderer->vkSwapChainImages[i], renderer->vkSwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		if(result != XK_SUCCESS) {
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _free;
  	}
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVulkanCreateCommandBuffer(&renderer->vkCommandBuffers[i], VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		if(result != XK_SUCCESS) {
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _free;
  	}	
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVulkanCreateSemaphore(&renderer->vkAvailableSemaphores[i]);
		if(result != XK_SUCCESS) {
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _free;
  	}		
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVulkanCreateSemaphore(&renderer->vkFinishedSemaphores[i]);
		if(result != XK_SUCCESS) {
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _free;
  	}		
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		result = __xkVulkanCreateFence(&renderer->vkFlightFences[i]);
		if(result != XK_SUCCESS) {
    	result = XK_ERROR_CREATE_FAILED;  
    	goto _free;
  	}		
	}

	/// TODO: Implementation.

_catch:
	return(result);

_free:
	if(renderer) {
		xkFreeMemory(renderer);
	}

	goto _catch;
}

void xkVulkanDestroyRenderer(XkVulkanRenderer renderer) {
	xkAssert(renderer);

	/// TODO: Implementation.
	
	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVulkanDestroyFence(renderer->vkFlightFences[i]);
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVulkanDestroySemaphore(renderer->vkAvailableSemaphores[i]);
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVulkanDestroySemaphore(renderer->vkFinishedSemaphores[i]);
	}

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVulkanDestroyCommandBuffer(renderer->vkCommandBuffers[i]);
	}	

	for(uint32_t i = 0; i < XKVULKAN_FRAME_COUNT; i++) {
		__xkVulkanDestroyImageView(renderer->vkSwapChainImageViews[i]);
	}

	__xkVulkanDestroySwapChain(renderer->vkSwapChain);

	__xkVulkanDestroySurface(renderer->vkSurface);

	xkFreeMemory(renderer);
}

void xkVulkanClearColorRenderer(XkVulkanRenderer renderer, XkVec4 color) {
	xkAssert(renderer);

	renderer->vkClearValues[0].color.float32[0] = (float)color.r;
	renderer->vkClearValues[0].color.float32[1] = (float)color.g;
	renderer->vkClearValues[0].color.float32[2] = (float)color.b;
	renderer->vkClearValues[0].color.float32[3] = (float)color.a;
}

void xkVulkanClearDepthRenderer(XkVulkanRenderer renderer, XkFloat32 depth) {
	xkAssert(renderer);

	if(renderer->config.depthTest) {
		renderer->vkClearValues[1].depthStencil.depth = (float)depth;
	}
}

void xkVulkanClearStencilRenderer(XkVulkanRenderer renderer, XkUInt32 stencil) {
	xkAssert(renderer);

	if(renderer->config.stencilTest) {
		renderer->vkClearValues[1].depthStencil.stencil = (uint32_t)stencil;
	}
}

void xkVulkanClearRenderer(XkVulkanRenderer renderer) {
	xkAssert(renderer);

	/// TODO: Implementation.

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

void xkVulkanTopologyRenderer(XkVulkanRenderer renderer, XkTopology topology) {
	xkAssert(renderer);

	switch(topology) {
		case XK_TOPOLOGY_POINT_LIST: 			renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST; break;
		case XK_TOPOLOGY_LINE_LIST:				renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST; break;
		case XK_TOPOLOGY_LINE_STRIP: 			renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP; break;
		case XK_TOPOLOGY_TRIANGLE_LIST: 	renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST; break;
		case XK_TOPOLOGY_TRIANGLE_STRIP:	renderer->vkPrimitiveTopology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP; break;
	}
}

void xkVulkanCullModeRenderer(XkVulkanRenderer renderer, XkCullMode cullMode) {
	xkAssert(renderer);

	switch(cullMode) {
		case XK_CULL_MODE_FRONT: 			renderer->vkCullMode = VK_CULL_MODE_FRONT_BIT; break;
		case XK_CULL_MODE_BACK: 			renderer->vkCullMode = VK_CULL_MODE_BACK_BIT; break;
		case XK_CULL_MODE_FRONT_BACK: renderer->vkCullMode = VK_CULL_MODE_FRONT_AND_BACK; break;
	}
}

void xkVulkanBeginRenderer(XkVulkanRenderer renderer) {
	xkAssert(renderer);

	/// TODO: Acquire next Vulkan swap chain image.

	VkCommandBuffer vkCommandBuffer = renderer->vkCommandBuffers[renderer->frameIndex];

	VkFramebuffer vkFrameBuffer = renderer->vkFrameBuffers[renderer->imageIndex];

  VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {};
  vkCommandBufferBeginInfo.sType              			= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  vkCommandBufferBeginInfo.pNext              			= VK_NULL_HANDLE;
  vkCommandBufferBeginInfo.flags              			= 0;
  vkCommandBufferBeginInfo.pInheritanceInfo   			= VK_NULL_HANDLE;

  VkResult vkResult = vkBeginCommandBuffer(vkCommandBuffer, &vkCommandBufferBeginInfo);
  if(vkResult != VK_SUCCESS) {
    xkLogError("Failed to begin Vulkan command buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

	VkRenderPassBeginInfo vkRenderPassBeginInfo = {};
  vkRenderPassBeginInfo.sType 								= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	vkRenderPassBeginInfo.pNext 								= VK_NULL_HANDLE;
	vkRenderPassBeginInfo.renderPass 						= renderer->vkRenderPass;
	vkRenderPassBeginInfo.framebuffer				 		= vkFrameBuffer;
	vkRenderPassBeginInfo.renderArea.offset.x 	= 0;
	vkRenderPassBeginInfo.renderArea.offset.y 	= 0;
	vkRenderPassBeginInfo.renderArea.extent 		= renderer->vkExtent;
	vkRenderPassBeginInfo.clearValueCount 			= renderer->clearValueCount;
	vkRenderPassBeginInfo.pClearValues 					= renderer->vkClearValues;

  vkCmdBeginRenderPass(vkCommandBuffer, &vkRenderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

_catch:
	return;
}

void xkVulkanEndRenderer(XkVulkanRenderer renderer) {
	xkAssert(renderer);

	VkCommandBuffer vkCommandBuffer = renderer->vkCommandBuffers[renderer->frameIndex];

	vkCmdEndRenderPass(vkCommandBuffer);

  VkResult vkResult = vkEndCommandBuffer(vkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    xkLogError("Failed to end Vulkan single command buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }  

	/// TODO: Submit Vulkan command buffer.

	renderer->frameIndex = (renderer->frameIndex + 1) % XKVULKAN_FRAME_COUNT;

_catch:
	return;
}

void xkVulkanResizeRenderer(XkVulkanRenderer renderer, XkSize width, XkSize height) {
	xkAssert(renderer);

	renderer->vkExtent.width 		= (uint32_t)width;
	renderer->vkExtent.height 	= (uint32_t)height;	
}

void xkVulkanScissorRenderer(XkVulkanRenderer renderer, XkInt32 x, XkInt32 y, XkSize width, XkSize height) {
	xkAssert(renderer);

	if(renderer->config.scissorTest) {
		renderer->vkScissor.offset.x 				= (int32_t)x;
		renderer->vkScissor.offset.y 				= (int32_t)y;
		renderer->vkScissor.extent.width 		= (uint32_t)width;
		renderer->vkScissor.extent.height 	= (uint32_t)height;
	}
}

void xkVulkanDraw(XkVulkanRenderer renderer, XkSize vertexCount) {
	xkAssert(renderer);
	xkAssert(vertexCount > 0);

	// Draw Vulkan.
	vkCmdDraw(renderer->vkCommandBuffers[renderer->frameIndex], (uint32_t)vertexCount, 1, 0, 0);
}

void xkVulkanDrawIndexed(XkVulkanRenderer renderer, XkSize indexCount) {
	xkAssert(renderer);
	xkAssert(indexCount > 0);

	// Draw indexed Vulkan.
	vkCmdDrawIndexed(renderer->vkCommandBuffers[renderer->frameIndex], (uint32_t)indexCount, 1, 0, 0, 0);
}

XkResult xkVulkanCreateBuffer(XkVulkanBuffer* pBuffer, const XkBufferUsage usage, const XkSize size, const XkHandle data, XkVulkanRenderer renderer) {
	xkAssert(pBuffer);
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkVulkanBuffer_T));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVulkanBuffer buffer = *pBuffer;

	buffer->vkSize = (VkDeviceSize)size;
	buffer->renderer = renderer;

	VkBufferUsageFlags vkBufferUsage = 0;
	switch(usage) {
		case XK_BUFFER_USAGE_VERTEX: 	vkBufferUsage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT; break;
		case XK_BUFFER_USAGE_INDEX: 	vkBufferUsage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT; break;
		case XK_BUFFER_USAGE_UNIFORM: vkBufferUsage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT; break;
	}

	result = __xkVulkanCreateBuffer(&buffer->vkBuffer, &buffer->vkMemory, buffer->vkSize, vkBufferUsage, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, data);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
	}

_catch:
	return(result);

_free:
	if(buffer) {
		xkFreeMemory(buffer);
	}

	goto _catch;
}

void xkVulkanDestroyBuffer(XkVulkanBuffer buffer) {
	xkAssert(pBuffer);

	__xkVulkanDestroyBuffer(buffer->vkBuffer, buffer->vkMemory);

	xkFreeMemory(buffer);
}

void xkVulkanBindVertexBuffer(XkVulkanBuffer buffer) {
	xkAssert(pBuffer);

	VkCommandBuffer vkCommandBuffer = buffer->renderer->vkCommandBuffers[buffer->renderer->frameIndex];

  VkBuffer vkVertexBuffers[] = {buffer->vkBuffer};
  VkDeviceSize vkOffsets[] = {};
  vkCmdBindVertexBuffers(vkCommandBuffer, 0, 1, vkVertexBuffers, vkOffsets);
}

void xkVulkanBindIndexBuffer(XkVulkanBuffer buffer) {
	xkAssert(pBuffer);

	VkCommandBuffer vkCommandBuffer = buffer->renderer->vkCommandBuffers[buffer->renderer->frameIndex];

	vkCmdBindIndexBuffer(vkCommandBuffer, buffer->vkBuffer, 0, VK_INDEX_TYPE_UINT32);
}

void xkVulkanMapBuffer(XkVulkanBuffer buffer, const XkHandle data) {
	xkAssert(pBuffer);

	__xkVulkanMapBuffer(buffer->vkMemory, buffer->vkSize, data);
}

XkResult xkVulkanCreateTexture2D(XkVulkanTexture2d* pTexture, XkHandle data, const XkSize width, const XkSize height, XkVulkanRenderer renderer) {
	xkAssert(pTexture);
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkVulkanTexture2d_T));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVulkanTexture2d texture = *pTexture;

	texture->renderer = renderer;

	const VkDeviceSize vkSize = (width * height) * 4;

	/// TODO: Implementation for miplevels.
	uint32_t mipLevels = 1; 

	VkExtent3D vkExtent 	= {};
	vkExtent.width 				= (uint32_t)width;
	vkExtent.height 			= (uint32_t)height;
	vkExtent.depth 				= 1;

	VkBuffer vkTransferBuffer;
	VkDeviceMemory vkTransferBufferMemory;
	result = __xkVulkanCreateBuffer(&vkTransferBuffer, &vkTransferBufferMemory, vkSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, data);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan transfer buffer: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
	}

	result = __xkVulkanCreateImage(&texture->vkImage, &texture->vkMemory, VK_IMAGE_TYPE_2D, VK_FORMAT_R8G8B8A8_SRGB, vkExtent, VK_SAMPLE_COUNT_1_BIT, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, mipLevels);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan image: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
	}

	__xkVulkanTransitionImageLayout(texture->vkImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
	__xkVulkanCopyBufferToImage(vkTransferBuffer, texture->vkImage, vkExtent);

	__xkVulkanDestroyBuffer(vkTransferBuffer, vkTransferBufferMemory);

	result = __xkVulkanCreateImageView(&texture->vkImageView, texture->vkImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan image view: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
	}

	result = __xkVulkanCreateSampler(&texture->vkSampler, VK_FILTER_LINEAR, VK_SAMPLER_ADDRESS_MODE_REPEAT, VK_TRUE, mipLevels);
	if(result != XK_SUCCESS) {
    xkLogError("Failed to create Vulkan smapler: %d", result);
    result = XK_ERROR_CREATE_FAILED;  
    goto _free;
	}

_catch:
	return(result);

_free:
	if(texture) {
		xkFreeMemory(texture);
	}

	goto _catch;
}

void xkVulkanDestroyTexture2D(XkVulkanTexture2d texture) {
	xkAssert(texture);

	__xkVulkanDestroySampler(texture->vkSampler);

	__xkVulkanDestroyImageView(texture->vkImageView);

	__xkVulkanDestroyImage(texture->vkImage, texture->vkMemory);

	xkFreeMemory(texture);
}


/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Module.h"
#include "XKinetic/Renderer/Renderer.h"
#include "XKinetic/Vulkan/Renderer.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#if defined(XK_LINUX)
	#define XKVULKAN_LIBRARY			"libXKVulkan.so"
#elif defined(XK_WIN64)
	#define XKVULKAN_LIBRARY			"XKVulkan.dll"
	#define XKD3D12_LIBRARY				"XKD3D12.dll"

	#define XKD3D12_CREATE_RENDERER					"xkD3D12CreateRenderer"
	#define XKD3D12_DESTROY_RENDERER				"xkD3D12DestroyRenderer"
	#define XKD3D12_CLEAR_COLOR_RENDERER		"xkD3D12ClearColorRenderer"
	#define XKD3D12_CLEAR_DEPTH_RENDERER		"xkD3D12ClearDepthRenderer"
	#define XKD3D12_CLEAR_STENCIL_RENDERER	"xkD3D12ClearStencilRenderer"
	#define XKD3D12_CLEAR_RENDERER					"xkD3D12ClearRenderer"
	#define XKD3D12_TOPOLOGY_RENDERER				"xkD3D12TopologyRenderer"
	#define XKD3D12_CULLMODE_RENDERER				"xkD3D12CullModeRenderer"
	#define XKD3D12_BEGIN_RENDERER					"xkD3D12BeginRenderer"
	#define XKD3D12_END_RENDERER						"xkD3D12EndRenderer"
	#define XKD3D12_RESIZE_RENDERER					"xkD3D12ResizeRenderer"
	#define XKD3D12_SCISSOR_RENDERER				"xkD3D12ScissorRenderer"
	#define XKD3D12_DRAW										"xkD3D12Draw"
	#define XKD3D12_DRAW_INDEXED						"xkD3D12DrawIndexed"
	#define XKD3D12_CREATE_BUFFER						"xkD3D12CreateBuffer"
	#define XKD3D12_DESTROY_BUFFER					"xkD3D12DestroyBuffer"
	#define XKD3D12_MAP_BUFFER							"xkD3D12MapBuffer"
	#define XKD3D12_BIND_VERTEX_BUFFER			"xkD3D12BindVertexBuffer"
	#define XKD3D12_BIND_INDEX_BUFFER				"xkD3D12BindIndexBuffer"
	#define XKD3D12_CREATE_TEXTURE2D				"xkD3D12CreateTexture2D"
	#define XKD3D12_DESTROY_TEXTURE2D				"xkD3D12DestroyTexture2D"
#endif // XK_LINUX

#if defined(XK_LINUX) || defined(XK_WIN64)
	#define XKVULKAN_CREATE_RENDERER				"xkVulkanCreateRenderer"
	#define XKVULKAN_DESTROY_RENDERER				"xkVulkanDestroyRenderer"
	#define XKVULKAN_CLEAR_COLOR_RENDERER		"xkVulkanClearColorRenderer"
	#define XKVULKAN_CLEAR_DEPTH_RENDERER		"xkVulkanClearDepthRenderer"
	#define XKVULKAN_CLEAR_STENCIL_RENDERER	"xkVulkanClearStencilRenderer"
	#define XKVULKAN_CLEAR_RENDERER					"xkVulkanClearRenderer"
	#define XKVULKAN_TOPOLOGY_RENDERER			"xkVulkanTopologyRenderer"
	#define XKVULKAN_CULLMODE_RENDERER			"xkVulkanCullModeRenderer"
	#define XKVULKAN_BEGIN_RENDERER					"xkVulkanBeginRenderer"
	#define XKVULKAN_END_RENDERER						"xkVulkanEndRenderer"
	#define XKVULKAN_RESIZE_RENDERER				"xkVulkanResizeRenderer"
	#define XKVULKAN_SCISSOR_RENDERER				"xkVulkanScissorRenderer"
	#define XKVULKAN_DRAW										"xkVulkanDraw"
	#define XKVULKAN_DRAW_INDEXED						"xkVulkanDrawIndexed"
	#define XKVULKAN_CREATE_BUFFER					"xkVulkanCreateBuffer"
	#define XKVULKAN_DESTROY_BUFFER					"xkVulkanDestroyBuffer"
	#define XKVULKAN_MAP_BUFFER							"xkVulkanMapBuffer"
	#define XKVULKAN_BIND_VERTEX_BUFFER			"xkVulkanBindVertexBuffer"
	#define XKVULKAN_BIND_INDEX_BUFFER			"xkVulkanBindIndexBuffer"
	#define XKVULKAN_CREATE_TEXTURE2D				"xkVulkanCreateTexture2D"
	#define XKVULKAN_DESTROY_TEXTURE2D			"xkVulkanDestroyTexture2D"
#endif // XK_LINUX || XK_WIN64

struct XkRenderer_T {
	XkHandle handle;

	XkModule module;

	struct {
		XkCreateRendererPfn 			create;
		XkDestroyRendererPfn 			destroy;

		XkClearColorRendererPfn 	clearColor;
		XkClearDepthRendererPfn 	clearDepth;
		XkClearStencilRendererPfn clearStencil;
		XkClearRendererPfn clear;

		XkTopologyRendererPfn 		topology;
		XkCullModeRendererPfn 		cullMode;

		XkBeginRendererPfn 				begin;
		XkEndRendererPfn 					end;

		XkResizeRendererPfn 			resize;
		XkScissorRendererPfn 			scissor;

		XkDrawPfn draw;
		XkDrawIndexedPfn 					drawIndexed;

		XkCreateBufferPfn 				createBuffer;
		XkDestroyBufferPfn 				destroyBuffer;

		XkMapBufferPfn 						mapBuffer;

		XkBindVertexBufferPfn 		bindVertexBuffer;
		XkBindIndexBufferPfn 			bindIndexBuffer;
		
		XkCreateTexture2dPfn 			createTexture2D;
		XkDestroyTexture2dPfn 		destroyTexture2D;
	} callbacks;
};

struct XkBuffer_T {
	XkRenderer 	renderer;

	XkHandle 		handle;
};

struct XkTexture2d_T {
	XkRenderer 	renderer;

	XkHandle 		handle;
};


#if defined(XK_WIN64) || defined(XK_LINUX)
	static XkResult __xkLoadVulkanModule(XkRenderer);
#endif // XK_WIN64 || XK_LINUX

#if defined(XK_WIN64)
	static XkResult __xkLoadD3D12Module(XkRenderer);
#endif // XK_WIN64

XkResult xkCreateRenderer(XkRenderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window, XkRendererApi api) {
	xkAssert(pRenderer);
	xkAssert(pConfig);
	xkAssert(window);

	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkRenderer));
	if(!(*pRenderer)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkRenderer renderer = *pRenderer;

	switch(api) {
		case XK_RENDERER_API_DEFAULT:
#if defined(XK_WIN64)
			result = __xkLoadD3D12Module(renderer);
			if(result != XK_SUCCESS) {
				goto _free;
			}
#elif defined(XK_LINUX)
			result = __xkLoadVulkanModule(renderer);
			if(result != XK_SUCCESS) {
				goto _free;
			}
#endif // XK_WIN64
			break;

#if defined(XK_WIN64) || defined(XK_LINUX)
		case XK_RENDERER_API_VK:
			result = __xkLoadVulkanModule(renderer);
			if(result != XK_SUCCESS) {
				goto _free;
			}
			break;
#endif // XK_WIN64 || XK_LINUX

#if defined(XK_WIN64)
		case XK_RENDERER_API_D3D12:
			result = __xkLoadD3D12Module(renderer);
			if(result != XK_SUCCESS) {
				goto _free;
			}
			break;
#endif // XK_WIN64
	}

	result = renderer->callbacks.create(&renderer->handle, pConfig, window);
	if(result != XK_SUCCESS) goto _free;

_catch:
	return(result);

_free:
	if(renderer) {
		xkFreeMemory(renderer);
	}

	goto _catch;
}

void xkDestroyRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	renderer->callbacks.destroy(renderer->handle);

	xkUnloadModule(renderer->module);

	xkFreeMemory(renderer);
}

void xkClearColorRenderer(XkRenderer renderer, XkVec4 color) {
	xkAssert(renderer);

	renderer->callbacks.clearColor(renderer->handle, color);
}

void xkClearDepthRenderer(XkRenderer renderer, XkFloat32 depth) {
	xkAssert(renderer);

	renderer->callbacks.clearDepth(renderer->handle, depth);
}

void xkClearStencilRenderer(XkRenderer renderer, XkUInt32 stencil) {
	xkAssert(renderer);

	renderer->callbacks.clearStencil(renderer->handle, stencil);
}

void xkClearRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	renderer->callbacks.clear(renderer->handle);
}

void xkTopologyRenderer(XkRenderer renderer, XkTopology topology) {
	xkAssert(renderer);

	renderer->callbacks.topology(renderer->handle, topology);
}

void xkCullModeRenderer(XkRenderer renderer, XkCullMode cullMode) {
	xkAssert(renderer);

	renderer->callbacks.cullMode(renderer->handle, cullMode);
}

void xkBeginRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	renderer->callbacks.begin(renderer->handle);
}

void xkEndRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	renderer->callbacks.end(renderer->handle);
}

void xkResizeRenderer(XkRenderer renderer, XkSize width, XkSize height) {
	xkAssert(renderer);

	renderer->callbacks.resize(renderer->handle, width, height);
}

void xkScissorRenderer(XkRenderer renderer, XkInt32 x, XkInt32 y, XkSize width, XkSize height) {
	xkAssert(renderer);

	renderer->callbacks.scissor(renderer->handle, x, y, width, height);
}

void xkDraw(XkRenderer renderer, XkSize vertexCount) {
	xkAssert(renderer);
	xkAssert(vertexCount > 0);

	renderer->callbacks.draw(renderer->handle, vertexCount);
}

void xkDrawIndexed(XkRenderer renderer, XkSize indexCount) {
	xkAssert(renderer);
	xkAssert(indexCount > 0);

	renderer->callbacks.drawIndexed(renderer->handle, indexCount);
}

XkResult xkCreateBuffer(XkBuffer* pBuffer, const XkSize size, XkHandle data, XkRenderer renderer) {
	xkAssert(pBuffer);
	xkAssert(size > 0);
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkBuffer buffer = *pBuffer;

	buffer->renderer = renderer;

	result = renderer->callbacks.createBuffer(&buffer->handle, size, data, renderer->handle);
	if(result != XK_SUCCESS) goto _free;

_catch:
	return(result);

_free:
	if(buffer) {
		xkFreeMemory(buffer);
	}

	goto _catch;
}

void xkDestroyBuffer(XkBuffer buffer) {
	xkAssert(buffer);

	buffer->renderer->callbacks.destroyBuffer(buffer->handle);

	xkFreeMemory(buffer);
}

void xkMapBuffer(XkBuffer buffer, const XkHandle data) {
	xkAssert(buffer);
	xkAssert(data);

	buffer->renderer->callbacks.mapBuffer(buffer->handle, data);
}

void xkBindVertexBuffer(XkBuffer buffer) {
	xkAssert(buffer);

	buffer->renderer->callbacks.bindVertexBuffer(buffer->handle);
}

void xkBindIndexBuffer(XkBuffer buffer) {
	xkAssert(buffer);

	buffer->renderer->callbacks.bindIndexBuffer(buffer->handle);
}

XkResult xkCreateTexture2D(XkTexture2D* pTexture, XkHandle data, const XkSize width, const XkSize height, XkRenderer renderer) {
	xkAssert(pTexture);
	xkAssert(data);
	xkAssert(width > 0);
	xkAssert(height > 0);
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkTexture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkTexture2D texture = *pTexture;

	texture->renderer = renderer;

	result = renderer->callbacks.createTexture2D(&texture->handle, data, width, height, renderer->handle);
	if(result != XK_SUCCESS) goto _free;

_catch:
	return(result);

_free:
	if(texture) {
		xkFreeMemory(texture);
	}

	goto _catch;
}

void xkDestroyTexture2D(XkTexture2D texture) {
	xkAssert(texture);

	texture->renderer->callbacks.destroyTexture2D(texture->handle);

	xkFreeMemory(texture);
}

#if defined(XK_WIN64) || defined(XK_LINUX)

XkResult __xkLoadVulkanModule(XkRenderer renderer) {
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	result = xkLoadModule(&renderer->module, XKVULKAN_LIBRARY);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKVULKAN_LIBRARY);
		goto _catch;
	}

	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.create, XKVULKAN_CREATE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroy, XKVULKAN_DESTROY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearColor, XKVULKAN_CLEAR_COLOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearDepth, XKVULKAN_CLEAR_DEPTH_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearStencil, XKVULKAN_CLEAR_STENCIL_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clear, XKVULKAN_CLEAR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.topology, XKVULKAN_TOPOLOGY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.cullMode, XKVULKAN_CULLMODE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.begin, XKVULKAN_BEGIN_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.end, XKVULKAN_END_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.resize, XKVULKAN_RESIZE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.scissor, XKVULKAN_SCISSOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.draw, XKVULKAN_DRAW, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.drawIndexed, XKVULKAN_DRAW_INDEXED, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.createBuffer, XKVULKAN_CREATE_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroyBuffer, XKVULKAN_DESTROY_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.mapBuffer, XKVULKAN_MAP_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.bindVertexBuffer, XKVULKAN_BIND_VERTEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.bindIndexBuffer, XKVULKAN_BIND_INDEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.createTexture2D, XKVULKAN_CREATE_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_TEXTURE2D);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroyTexture2D, XKVULKAN_DESTROY_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_TEXTURE2D);
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN64 || XK_LINUX

#if defined(XK_WIN64)

XkResult __xkLoadD3D12Module(XkRenderer renderer) {
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	result = xkLoadModule(&renderer->module, XKD3D12_LIBRARY);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKD3D12_LIBRARY);
		goto _catch;
	}
	
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.create, XKD3D12_CREATE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroy, XKD3D12_DESTROY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearColor, XKD3D12_CLEAR_COLOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearDepth, XKD3D12_CLEAR_DEPTH_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearStencil, XKD3D12_CLEAR_STENCIL_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clear, XKD3D12_CLEAR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.topology, XKD3D12_TOPOLOGY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.cullMode, XKD3D12_CULLMODE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.begin, XKD3D12_BEGIN_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.end, XKD3D12_END_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.resize, XKD3D12_RESIZE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.scissor, XKD3D12_SCISSOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.draw, XKD3D12_DRAW, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.drawIndexed, XKD3D12_DRAW_INDEXED, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.createBuffer, XKD3D12_CREATE_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroyBuffer, XKD3D12_DESTROY_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.mapBuffer, XKD3D12_MAP_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.bindVertexBuffer, XKD3D12_BIND_VERTEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.bindIndexBuffer, XKD3D12_BIND_INDEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.createTexture2D, XKD3D12_CREATE_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_TEXTURE2D);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroyTexture2D, XKD3D12_DESTROY_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_TEXTURE2D);
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN64

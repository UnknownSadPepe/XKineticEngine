#include "XKinetic/Platform/Module.h"
#include "XKinetic/Renderer/Renderer.h"
#include "XKinetic/Vulkan/Renderer.h"

#if defined(XK_LINUX)
	#define XKVULKAN_LIBRARY			"libXKVulkan.so"
#elif defined(XK_WIN32)
	#define XKVULKAN_LIBRARY			"XKVulkan.dll"
	#define XKDIRECTX12_LIBRARY		"XKDirectX12.dll"

	#define XKDIRECTX12_CREATE_RENDERER					"xkDX12CreateRenderer"
	#define XKDIRECTX12_DESTROY_RENDERER				"xkDX12DestroyRenderer"
	#define XKDIRECTX12_CLEAR_COLOR_RENDERER		"xkDX12ClearColorRenderer"
	#define XKDIRECTX12_CLEAR_DEPTH_RENDERER		"xkDX12ClearDepthRenderer"
	#define XKDIRECTX12_CLEAR_STENCIL_RENDERER	"xkDX12ClearStencilRenderer"
	#define XKDIRECTX12_CLEAR_RENDERER					"xkDX12ClearRenderer"
	#define XKDIRECTX12_TOPOLOGY_RENDERER				"xkDX12TopologyRenderer"
	#define XKDIRECTX12_CULLMODE_RENDERER				"xkDX12CullModeRenderer"
	#define XKDIRECTX12_BEGIN_RENDERER					"xkDX12BeginRenderer"
	#define XKDIRECTX12_END_RENDERER						"xkDX12EndRenderer"
	#define XKDIRECTX12_RESIZE_RENDERER					"xkDX12ResizeRenderer"
	#define XKDIRECTX12_SCISSOR_RENDERER				"xkDX12ScissorRenderer"
	#define XKDIRECTX12_DRAW										"xkDX12Draw"
	#define XKDIRECTX12_DRAW_INDEXED						"xkDX12DrawIndexed"
	#define XKDIRECTX12_CREATE_BUFFER						"xkDX12CreateBuffer"
	#define XKDIRECTX12_DESTROY_BUFFER					"xkDX12DestroyBuffer"
	#define XKDIRECTX12_MAP_BUFFER							"xkDX12MapBuffer"
	#define XKDIRECTX12_BIND_VERTEX_BUFFER			"xkDX12BindVertexBuffer"
	#define XKDIRECTX12_BIND_INDEX_BUFFER				"xkDX12BindIndexBuffer"
	#define XKDIRECTX12_CREATE_TEXTURE2D				"xkDX12CreateTexture2D"
	#define XKDIRECTX12_DESTROY_TEXTURE2D				"xkDX12DestroyTexture2D"
#endif // XK_LINUX

#if defined(XK_LINUX) || defined(XK_WIN32)
	#define XKVULKAN_CREATE_RENDERER				"xkVkCreateRenderer"
	#define XKVULKAN_DESTROY_RENDERER				"xkVkDestroyRenderer"
	#define XKVULKAN_CLEAR_COLOR_RENDERER		"xkVkClearColorRenderer"
	#define XKVULKAN_CLEAR_DEPTH_RENDERER		"xkVkClearDepthRenderer"
	#define XKVULKAN_CLEAR_STENCIL_RENDERER	"xkVkClearStencilRenderer"
	#define XKVULKAN_CLEAR_RENDERER					"xkVkClearRenderer"
	#define XKVULKAN_TOPOLOGY_RENDERER			"xkVkTopologyRenderer"
	#define XKVULKAN_CULLMODE_RENDERER			"xkVkCullModeRenderer"
	#define XKVULKAN_BEGIN_RENDERER					"xkVkBeginRenderer"
	#define XKVULKAN_END_RENDERER						"xkVkEndRenderer"
	#define XKVULKAN_RESIZE_RENDERER				"xkVkResizeRenderer"
	#define XKVULKAN_SCISSOR_RENDERER				"xkVkScissorRenderer"
	#define XKVULKAN_DRAW										"xkVkDraw"
	#define XKVULKAN_DRAW_INDEXED						"xkVkDrawIndexed"
	#define XKVULKAN_CREATE_BUFFER					"xkVkCreateBuffer"
	#define XKVULKAN_DESTROY_BUFFER					"xkVkDestroyBuffer"
	#define XKVULKAN_MAP_BUFFER							"xkVkMapBuffer"
	#define XKVULKAN_BIND_VERTEX_BUFFER			"xkVkBindVertexBuffer"
	#define XKVULKAN_BIND_INDEX_BUFFER			"xkVkBindIndexBuffer"
	#define XKVULKAN_CREATE_TEXTURE2D				"xkVkCreateTexture2D"
	#define XKVULKAN_DESTROY_TEXTURE2D			"xkVkDestroyTexture2D"
#endif // XK_LINUX || XK_WIN32

struct XkRenderer {
	XkHandle handle;

	XkModule module;

	struct {
		XkCreateRendererPfn create;
		XkDestroyRendererPfn destroy;

		XkClearColorRendererPfn clearColor;
		XkClearDepthRendererPfn clearDepth;
		XkClearStencilRendererPfn clearStencil;
		XkClearRendererPfn clear;

		XkTopologyRendererPfn topology;
		XkCullModeRendererPfn cullMode;

		XkBeginRendererPfn begin;
		XkEndRendererPfn end;

		XkResizeRendererPfn resize;
		XkScissorRendererPfn scissor;

		XkDrawPfn draw;
		XkDrawIndexedPfn drawIndexed;

		XkCreateBufferPfn createBuffer;
		XkDestroyBufferPfn destroyBuffer;

		XkMapBufferPfn mapBuffer;

		XkBindVertexBufferPfn bindVertexBuffer;
		XkBindIndexBufferPfn bindIndexBuffer;
		
		XkCreateTexture2DPfn createTexture2D;
		XkDestroyTexture2DPfn destroyTexture2D;
	} callbacks;
};

struct XkBuffer {
	XkRenderer renderer;

	XkHandle handle;
};

struct XkTexture2D {
	XkRenderer renderer;

	XkHandle handle;
};


#if defined(XK_WIN32) || defined(XK_LINUX)
	static XkResult __xkLoadVkModule(XkRenderer);
#endif // XK_WIN32 || XK_LINUX
			 //
#if defined(XK_WIN32)
	static XkResult __xkLoadDX12Module(XkRenderer);
#endif // XK_WIN32

XkResult xkCreateRenderer(XkRenderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window, XkRendererApi api) {
	XkResult result = XK_SUCCESS;

	// Allocate renderer.
	*pRenderer = xkAllocateMemory(sizeof(struct XkRenderer));
	if(!(*pRenderer)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template renderer.
	XkRenderer renderer = *pRenderer;

	// Select renderer api.
	switch(api) {
		case XK_RENDERER_API_DEFAULT:
#if defined(XK_WIN32)
			result = __xkLoadDX12Module(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}
#elif defined(XK_LINUX)
			result = __xkLoadVkModule(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}
#endif // XK_WIN32
			break;

#if defined(XK_WIN32) || defined(XK_LINUX)
		case XK_RENDERER_API_VK:
			result = __xkLoadVkModule(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}
			break;
#endif // XK_WIN32 || XK_LINUX

#if defined(XK_WIN32)
		case XK_RENDERER_API_DX12:
			result = __xkLoadDX12Module(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}
			break;
#endif // XK_WIN32
	}

	// Create renderer api.
	result = renderer->callbacks.create(&renderer->handle, pConfig, window);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyRenderer(XkRenderer renderer) {
	// Destroy renderer api.
	renderer->callbacks.destroy(renderer->handle);

	// Unload renderer api module.
	xkUnloadModule(renderer->module);

	// Free renderer.
	xkFreeMemory(renderer);
}

void xkClearColorRenderer(XkRenderer renderer, XkVec4 color) {
	renderer->callbacks.clearColor(renderer->handle, color);
}

void xkClearDepthRenderer(XkRenderer renderer, XkFloat32 depth) {
	renderer->callbacks.clearDepth(renderer->handle, depth);
}

void xkClearStencilRenderer(XkRenderer renderer, XkUInt32 stencil) {
	renderer->callbacks.clearStencil(renderer->handle, stencil);
}

void xkClearRenderer(XkRenderer renderer) {
	renderer->callbacks.clear(renderer->handle);
}

void xkTopologyRenderer(XkRenderer renderer, XkTopology topology) {
	renderer->callbacks.topology(renderer->handle, topology);
}

void xkCullModeRenderer(XkRenderer renderer, XkCullMode cullMode) {
	renderer->callbacks.cullMode(renderer->handle, cullMode);
}

void xkBeginRenderer(XkRenderer renderer) {
	renderer->callbacks.begin(renderer->handle);
}

void xkEndRenderer(XkRenderer renderer) {
	renderer->callbacks.end(renderer->handle);
}

void xkResizeRenderer(XkRenderer renderer, XkSize width, XkSize height) {
	renderer->callbacks.resize(renderer->handle, width, height);
}

void xkScissorRenderer(XkRenderer renderer, XkInt32 x, XkInt32 y, XkSize width, XkSize height) {
	renderer->callbacks.scissor(renderer->handle, x, y, width, height);
}

void xkDraw(XkRenderer renderer, XkSize vertexCount) {
	renderer->callbacks.draw(renderer->handle, vertexCount);
}

void xkDrawIndexed(XkRenderer renderer, XkSize indexCount) {
	renderer->callbacks.drawIndexed(renderer->handle, indexCount);
}

XkResult xkCreateBuffer(XkBuffer* pBuffer, const XkSize size, XkHandle data, XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkBuffer buffer = *pBuffer;

	buffer->renderer = renderer;

	result = renderer->callbacks.createBuffer(&buffer->handle, size, data, renderer->handle);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyBuffer(XkBuffer buffer) {
	buffer->renderer->callbacks.destroyBuffer(buffer->handle);
	xkFreeMemory(buffer);
}

void xkMapBuffer(XkBuffer buffer, const XkHandle data) {
	buffer->renderer->callbacks.mapBuffer(buffer->handle, data);
}

void xkBindVertexBuffer(XkBuffer buffer) {
	buffer->renderer->callbacks.bindVertexBuffer(buffer->handle);
}

void xkBindIndexBuffer(XkBuffer buffer) {
	buffer->renderer->callbacks.bindIndexBuffer(buffer->handle);
}

XkResult xkCreateTexture2D(XkTexture2D* pTexture, XkHandle data, const XkSize width, const XkSize height, XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkTexture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkTexture2D texture = *pTexture;

	texture->renderer = renderer;

	result = renderer->callbacks.createTexture2D(&texture->handle, data, width, height, renderer->handle);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyTexture2D(XkTexture2D texture) {
	texture->renderer->callbacks.destroyTexture2D(texture->handle);
	xkFreeMemory(texture);
}

#if defined(XK_WIN32) || defined(XK_LINUX)

XkResult __xkLoadVkModule(XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	// Load Vulkan module.
	result = xkLoadModule(&renderer->module, XKVULKAN_LIBRARY);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKVULKAN_LIBRARY);
		goto _catch;
	}

	// Load Vulkan module symbols.
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

#endif // XK_WIN32 || XK_LINUX

#if defined(XK_WIN32)

XkResult __xkLoadDX12Module(XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	// Load DirectX12 module.
	result = xkLoadModule(&renderer->module, XKDIRECTX12_LIBRARY);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKDIRECTX12_LIBRARY);
		goto _catch;
	}

	// Load DirectX12 module symbols.
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.create, XKDIRECTX12_CREATE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroy, XKDIRECTX12_DESTROY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearColor, XKDIRECTX12_CLEAR_COLOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearDepth, XKDIRECTX12_CLEAR_DEPTH_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clearStencil, XKDIRECTX12_CLEAR_STENCIL_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.clear, XKDIRECTX12_CLEAR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.topology, XKDIRECTX12_TOPOLOGY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.cullMode, XKDIRECTX12_CULLMODE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.begin, XKDIRECTX12_BEGIN_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.end, XKDIRECTX12_END_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.resize, XKDIRECTX12_RESIZE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.scissor, XKDIRECTX12_SCISSOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.draw, XKDIRECTX12_DRAW, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.drawIndexed, XKDIRECTX12_DRAW_INDEXED, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.createBuffer, XKDIRECTX12_CREATE_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroyBuffer, XKDIRECTX12_DESTROY_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.mapBuffer, XKDIRECTX12_MAP_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.bindVertexBuffer, XKDIRECTX12_BIND_VERTEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.bindIndexBuffer, XKDIRECTX12_BIND_INDEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.createTexture2D, XKDIRECTX12_CREATE_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CREATE_TEXTURE2D);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&renderer->callbacks.destroyTexture2D, XKDIRECTX12_DESTROY_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DESTROY_TEXTURE2D);
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WIN32

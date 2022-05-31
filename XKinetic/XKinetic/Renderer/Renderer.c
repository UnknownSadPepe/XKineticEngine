#include "XKinetic/Core/Module.h"
#include "XKinetic/Renderer/Renderer.h"
#include "XKinetic/Vulkan/Renderer.h"

#ifdef XK_PLATFORM_LINUX
	#define XKVULKAN_LIBRARY			"libXKVulkan.so"
	#define XKDIRECTX12_LIBRARY		"libXKDirectX12.dll"
#elif defined(XK_PLATFORM_WIN32)
	#define XKVULKAN_LIBRARY			"XKVulkan.dll"
	#define XKDIRECTX12_LIBRARY		"XKDirectX12.dll"
#endif // XK_PLATFORM_LINUX

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

struct XkRenderer {
	XkHandle handle;

	XkModule module;

	struct {
		XkRendererCreatePfn create;
		XkRendererDestroyPfn destroy;

		XkRendererClearColorPfn clearColor;
		XkRendererClearDepthPfn clearDepth;
		XkRendererClearStencilPfn clearStencil;
		XkRendererClearPfn clear;

		XkRendererTopologyPfn topology;
		XkRendererCullModePfn cullMode;

		XkRendererBeginPfn begin;
		XkRendererEndPfn end;

		XkRendererResizePfn resize;
		XkRendererScissorPfn scissor;

		XkRendererDrawPfn draw;
		XkRendererDrawIndexedPfn drawIndexed;

		XkBufferCreatePfn createBuffer;
		XkBufferDestroyPfn destroyBuffer;
		XkBufferBindPfn bindBuffer;
		XkBufferUnbindPfn unbindBuffer;
		XkBufferSetPfn setBuffer;

		XkUniformBufferCreatePfn createUniformBuffer;
		XkUniformBufferDestroyPfn destroyUniformBuffer;
		XkUniformBufferSetPfn setUniformBuffer;

		XkTexture2DCreatePfn createTexture2D;
		XkTexture2DDestroyPfn destroyTexture2D;
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

static XkResult __xkLoadVkModule(XkRenderer);
static XkResult __xkLoadDX12Module(XkRenderer);

XkResult xkCreateRenderer(XkRenderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window, XkRendererApi api) {
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkRenderer));
	if(!(*pRenderer)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkRenderer renderer = *pRenderer;

	switch(api) {
		case XK_RENDERER_API_DEFAULT:
#if defined(XK_PLATFORM_LINUX)
			result = __xkLoadVkModule(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}	
			break;
#elif defined(XK_PLATFORM_WIN32)
			result = __xkLoadDX12Module(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}	
			break;
#endif // XK_PLATFORM_LINUX

		case XK_RENDERER_API_VK:
			result = __xkLoadVkModule(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}
			break;

		case XK_RENDERER_API_DX12:
			result = __xkLoadDX12Module(renderer);
			if(result != XK_SUCCESS) {
				goto _catch;
			}
			break;
	}

	result = renderer->callbacks.create(&renderer->handle, pConfig, window);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyRenderer(XkRenderer renderer) {
	renderer->callbacks.destroy(renderer->handle);
	xkFreeModule(renderer->module);
	xkFreeMemory(renderer);
}

void xkClearColorRenderer(XkRenderer renderer, XkVec4 color) {
	renderer->callbacks.clearColor(renderer->handle, color);
}

void xkClearDepthRenderer(XkRenderer renderer, XkFloat64 depth) {
	renderer->callbacks.clearDepth(renderer->handle, depth);
}

void xkClearStencilRenderer(XkRenderer renderer, XkInt32 stencil) {
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

void xkScissorRenderer(XkRenderer renderer, XkSize x, XkSize y, XkSize width, XkSize height) {
	renderer->callbacks.scissor(renderer->handle, x, y, width, height);
}

void xkDraw(XkRenderer renderer, XkSize vertexCount) {
	renderer->callbacks.draw(renderer->handle, vertexCount);
}

void xkDrawIndexed(XkRenderer renderer, XkSize indexCount) {
	renderer->callbacks.drawIndexed(renderer->handle, indexCount);
}

XkResult xkCreateVertexBuffer(XkVertexBuffer* pBuffer, const XkSize size, XkHandle data, XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkVertexBuffer buffer = *pBuffer;

	buffer->renderer = renderer;

	result = renderer->callbacks.createBuffer(&buffer->handle, size, data, renderer->handle);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyVertexBuffer(XkVertexBuffer buffer) {
	buffer->renderer->callbacks.destroyBuffer(buffer->handle);
	xkFreeMemory(buffer);
}

void xkBindVertexBuffer(XkVertexBuffer buffer) {
	buffer->renderer->callbacks.bindBuffer(buffer->handle);
}

void xkUnbindVertexBuffer(XkVertexBuffer buffer) {
	buffer->renderer->callbacks.unbindBuffer(buffer->handle);
}

XkResult xkCreateIndexBuffer(XkIndexBuffer* pBuffer, const XkSize size, XkHandle data, XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkIndexBuffer buffer = *pBuffer;

	buffer->renderer = renderer;

	result = renderer->callbacks.createBuffer(&buffer->handle, size, data, renderer->handle);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyIndexBuffer(XkIndexBuffer buffer) {
	buffer->renderer->callbacks.destroyBuffer(buffer->handle);
	xkFreeMemory(buffer);
}

void xkBindIndexBuffer(XkIndexBuffer buffer) {
	buffer->renderer->callbacks.bindBuffer(buffer->handle);
}

void xkUnbindIndexBuffer(XkIndexBuffer buffer) {
	buffer->renderer->callbacks.unbindBuffer(buffer->handle);
}

XkResult xkCreateUniformBuffer(XkUniformBuffer* pBuffer, const XkSize size, const XkSize binding, XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkBuffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkUniformBuffer buffer = *pBuffer;

	buffer->renderer = renderer;

	result = renderer->callbacks.createUniformBuffer(&buffer->handle, size, binding, renderer->handle);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyUniformBuffer(XkUniformBuffer buffer) {
	buffer->renderer->callbacks.destroyUniformBuffer(buffer->handle);
	xkFreeMemory(buffer);
}

void xkSetUniformBuffer(XkUniformBuffer buffer, XkHandle data, const XkSize offset) {
	buffer->renderer->callbacks.setUniformBuffer(buffer->handle, data, offset);
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

XkResult __xkLoadVkModule(XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	// Load Vulkan module.
	renderer->module = xkLoadModule(XKVULKAN_LIBRARY);
	if(!renderer->module) {
		xkLogError("Failed to load module %s", XKVULKAN_LIBRARY);
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

	// Load Vulkan module symbols.
	renderer->callbacks.create = (XkRendererCreatePfn)xkGetModuleSymbol(renderer->module, XKVULKAN_CREATE_RENDERER);
	if(!renderer->callbacks.create) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.destroy = (XkRendererDestroyPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_DESTROY_RENDERER);
	if(!renderer->callbacks.destroy) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clearColor = (XkRendererClearColorPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_CLEAR_COLOR_RENDERER);
	if(!renderer->callbacks.clearColor) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_COLOR_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clearDepth = (XkRendererClearDepthPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_CLEAR_DEPTH_RENDERER);
	if(!renderer->callbacks.clearDepth) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_DEPTH_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clearStencil = (XkRendererClearStencilPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_CLEAR_STENCIL_RENDERER);
	if(!renderer->callbacks.clearStencil) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_STENCIL_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clear = (XkRendererClearPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_CLEAR_RENDERER);
	if(!renderer->callbacks.clear) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.topology = (XkRendererTopologyPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_TOPOLOGY_RENDERER);
	if(!renderer->callbacks.topology) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TOPOLOGY_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.cullMode = (XkRendererCullModePfn)xkGetModuleSymbol(renderer->module, XKVULKAN_CULLMODE_RENDERER);
	if(!renderer->callbacks.cullMode) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CULLMODE_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.begin = (XkRendererBeginPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_BEGIN_RENDERER);
	if(!renderer->callbacks.begin) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BEGIN_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.end = (XkRendererEndPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_END_RENDERER);
	if(!renderer->callbacks.end) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_END_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.resize = (XkRendererResizePfn)xkGetModuleSymbol(renderer->module, XKVULKAN_RESIZE_RENDERER);
	if(!renderer->callbacks.resize) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_RESIZE_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.scissor = (XkRendererScissorPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_SCISSOR_RENDERER);
	if(!renderer->callbacks.resize) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_SCISSOR_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.draw = (XkRendererDrawPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_DRAW);
	if(!renderer->callbacks.draw) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.drawIndexed = (XkRendererDrawIndexedPfn)xkGetModuleSymbol(renderer->module, XKVULKAN_DRAW_INDEXED);
	if(!renderer->callbacks.drawIndexed) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW_INDEXED);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

XkResult __xkLoadDX12Module(XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	// Load DirectX12 module.
	renderer->module = xkLoadModule(XKDIRECTX12_LIBRARY);
	if(!renderer->module) {
		xkLogError("Failed to load module %s", XKDIRECTX12_LIBRARY);
		result = XK_ERROR_MODULE_NOT_PRESENT;
		goto _catch;
	}

	// Load DirectX12 module symbols.
	renderer->callbacks.create = (XkRendererCreatePfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_CREATE_RENDERER);
	if(!renderer->callbacks.create) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CREATE_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.destroy = (XkRendererDestroyPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_DESTROY_RENDERER);
	if(!renderer->callbacks.destroy) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DESTROY_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clearColor = (XkRendererClearColorPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_CLEAR_COLOR_RENDERER);
	if(!renderer->callbacks.clearColor) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_COLOR_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clearDepth = (XkRendererClearDepthPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_CLEAR_DEPTH_RENDERER);
	if(!renderer->callbacks.clearDepth) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_DEPTH_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clearStencil = (XkRendererClearStencilPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_CLEAR_STENCIL_RENDERER);
	if(!renderer->callbacks.clearStencil) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_STENCIL_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.clear = (XkRendererClearPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_CLEAR_RENDERER);
	if(!renderer->callbacks.clear) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CLEAR_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.topology = (XkRendererTopologyPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_TOPOLOGY_RENDERER);
	if(!renderer->callbacks.topology) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_TOPOLOGY_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.cullMode = (XkRendererCullModePfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_CULLMODE_RENDERER);
	if(!renderer->callbacks.cullMode) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_CULLMODE_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.begin = (XkRendererBeginPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_BEGIN_RENDERER);
	if(!renderer->callbacks.begin) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_BEGIN_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.end = (XkRendererEndPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_END_RENDERER);
	if(!renderer->callbacks.end) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_END_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.resize = (XkRendererResizePfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_RESIZE_RENDERER);
	if(!renderer->callbacks.resize) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_RESIZE_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.scissor = (XkRendererScissorPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_SCISSOR_RENDERER);
	if(!renderer->callbacks.resize) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_SCISSOR_RENDERER);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.draw = (XkRendererDrawPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_DRAW);
	if(!renderer->callbacks.draw) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DRAW);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}
	renderer->callbacks.drawIndexed = (XkRendererDrawIndexedPfn)xkGetModuleSymbol(renderer->module, XKDIRECTX12_DRAW_INDEXED);
	if(!renderer->callbacks.drawIndexed) {
		xkLogError("Failed to load module %s symbol: %s", XKDIRECTX12_LIBRARY, XKDIRECTX12_DRAW_INDEXED);
		result = XK_ERROR_MODULE_SYMBOL_NOT_PRESENT;
		goto _catch;
	}

_catch:
	return(result);
}

#include "XKinetic/Platform/Module.h"
#include "XKinetic/Renderer/Renderer.h"
#include "XKinetic/Vulkan/Renderer.h"

#ifdef XK_LINUX
	#define XKVULKAN_LIBRARY			"libXKVulkan.so"
#elif defined(XK_WIN32)
	#define XKVULKAN_LIBRARY			"XKVulkan.dll"
#endif // XK_LINUX

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
#define XKVULKAN_BIND_VERTEX_BUFFER			"xkVkBindVertexBuffer"
#define XKVULKAN_BIND_INDEX_BUFFER			"xkVkBindIndexBuffer"
#define XKVULKAN_CREATE_TEXTURE2D				"xkVkCreateTexture2D"
#define XKVULKAN_DESTROY_TEXTURE2D			"xkVkDestroyTexture2D"

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

static XkResult __xkLoadVkModule(XkRenderer);

XkResult xkCreateRenderer(XkRenderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window, XkRendererApi api) {
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkRenderer));
	if(!(*pRenderer)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkRenderer renderer = *pRenderer;

	switch(api) {
		case XK_RENDERER_API_VK:
			result = __xkLoadVkModule(renderer);
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
	xkUnloadModule(renderer->module);
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

XkResult __xkLoadVkModule(XkRenderer renderer) {
	XkResult result = XK_SUCCESS;

	// Load Vulkan module.
	result = xkLoadModule(renderer->module, XKVULKAN_LIBRARY);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKVULKAN_LIBRARY);
		goto _catch;
	}

	// Load Vulkan module symbols.
	result = xkGetModuleSymbol(renderer->callbacks.create, XKVULKAN_CREATE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.destroy, XKVULKAN_DESTROY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.clearColor, XKVULKAN_CLEAR_COLOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.clearDepth, XKVULKAN_CLEAR_DEPTH_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.clearStencil, XKVULKAN_CLEAR_STENCIL_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.clear, XKVULKAN_CLEAR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.topology, XKVULKAN_TOPOLOGY_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.cullMode, XKVULKAN_CULLMODE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.begin, XKVULKAN_BEGIN_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.end, XKVULKAN_END_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.resize, XKVULKAN_RESIZE_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.scissor, XKVULKAN_SCISSOR_RENDERER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.draw, XKVULKAN_DRAW, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.drawIndexed, XKVULKAN_DRAW_INDEXED, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.createBuffer, XKVULKAN_CREATE_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.destroyBuffer, XKVULKAN_DESTROY_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.bindVertexBuffer, XKVULKAN_BIND_VERTEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.bindIndexBuffer, XKVULKAN_BIND_INDEX_BUFFER, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.createTexture2D, XKVULKAN_CREATE_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_TEXTURE2D);
		goto _catch;
	}
	result = xkGetModuleSymbol(renderer->callbacks.destroyTexture2D, XKVULKAN_DESTROY_TEXTURE2D, renderer->module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_TEXTURE2D);
		goto _catch;
	}

_catch:
	return(result);
}

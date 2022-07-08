/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Renderer/Internal.h"
#include "XKinetic/Renderer/Renderer.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
__XkRendererContext _xkRendererContext;

/* ########## MACROS SECTION ########## */
#if defined(XK_LINUX)
#define XKVULKAN_LIBRARY			"libXKVulkan.so"
#elif defined(XK_WINDOWS)
#define XKVULKAN_LIBRARY			"XKVulkan.dll"
#define XKD3D12_LIBRARY				"XKD3D12.dll"
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_LINUX) || defined(XK_WINDOWS)
#define XKVULKAN_INITIALIZE_RENDERER		"xkVulkanInitializeRenderer"
#define XKVULKAN_TERMINATE_RENDERER			"xkVulkanTerminateRenderer"
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
#define XKVULKAN_CREATE_TEXTURE					"xkVulkanCreateTexture"
#define XKVULKAN_DESTROY_TEXTURE				"xkVulkanDestroyTexture"
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_WINDOWS)
#define XKD3D12_INITIALIZE_RENDERER			"xkD3D12InitializeRenderer"
#define XKD3D12_TERMINATE_RENDERER			"xkD3D12TerminateRenderer"
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
#define XKD3D12_CREATE_TEXTURE					"xkD3D12CreateTexture"
#define XKD3D12_DESTROY_TEXTURE					"xkD3D12DestroyTexture"
#endif // XK_WINDOWS

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
#if defined(XK_WINDOWS) || defined(XK_LINUX)
static XkResult __xkLoadVulkanModule();
#endif // XK_WINDOWS || XK_LINUX

#if defined(XK_WINDOWS)
static XkResult __xkLoadD3D12Module();
#endif // XK_WINDOWS

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeRenderer(const XkRendererApi api) {
	XkResult result = XK_SUCCESS;

	if (_xkRendererContext.initialized) {
		goto _catch;
	}

	switch (api) {
	case XK_RENDERER_API_DEFAULT:
#if defined(XK_WINDOWS)
		result = __xkLoadD3D12Module();
		if (result != XK_SUCCESS) {
			goto _catch;
		}
#elif defined(XK_LINUX)
		result = __xkLoadVulkanModule();
		if (result != XK_SUCCESS) {
			goto _catch;
		}
#else
		result = XK_ERROR_UNKNOWN;
		goto _catch;
#endif // XK_WINDOWS || XK_LINUX
		break;

	case XK_RENDERER_API_VULKAN:
#if defined(XK_WINDOWS) || defined(XK_LINUX)
		result = __xkLoadVulkanModule();
		if (result != XK_SUCCESS) {
			goto _catch;
		}
#else
		result = XK_ERROR_UNKNOWN;
		goto _catch;
#endif // XK_WINDOWS || XK_LINUX
		break;

	case XK_RENDERER_API_D3D12:
#if defined(XK_WINDOWS)
		result = __xkLoadD3D12Module();
		if (result != XK_SUCCESS) {
			goto _catch;
		}
#else
		result = XK_ERROR_UNKNOWN;
		goto _catch;
#endif // XK_WINDOWS
		break;
	}

	result = _xkRendererContext.callbacks.initializeRenderer();
	if (result != XK_SUCCESS) goto _catch;

	_xkRendererContext.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateRenderer() {
	if (!_xkRendererContext.initialized) {
		return;
	}

	_xkRendererContext.callbacks.terminateRenderer();

	xkUnloadModule(_xkRendererContext.module);

	_xkRendererContext.initialized = XK_FALSE;
}

XkResult xkCreateRenderer(XkRenderer* pRenderer, XkWindow window, const XkRendererHint hint) {
	xkAssert(pRenderer);
	xkAssert(window);

	XkResult result = XK_SUCCESS;

	result = _xkRendererContext.callbacks.createRenderer(pRenderer, window, hint);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.destroyRenderer(renderer);
}

void xkClearColorRenderer(XkRenderer renderer, const XkVec4 color) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.clearRendererColor(renderer, color);
}

void xkClearDepthRenderer(XkRenderer renderer, const XkFloat32 depth) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.clearRendererDepth(renderer, depth);
}

void xkClearStencilRenderer(XkRenderer renderer, const XkUInt32 stencil) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.clearRendererStencil(renderer, stencil);
}

void xkClearRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.clearRenderer(renderer);
}

void xkTopologyRenderer(XkRenderer renderer, const XkTopology topology) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.topologyRenderer(renderer, topology);
}

void xkCullModeRenderer(XkRenderer renderer, const XkCullMode cullMode) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.cullModeRenderer(renderer, cullMode);
}

void xkBeginRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.beginRenderer(renderer);
}

void xkEndRenderer(XkRenderer renderer) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.endRenderer(renderer);
}

void xkResizeRenderer(XkRenderer renderer, const XkSize width, const XkSize height) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.resizeRenderer(renderer, width, height);
}

void xkScissorRenderer(XkRenderer renderer, const XkInt32 x, const XkInt32 y, const XkSize width, const XkSize height) {
	xkAssert(renderer);

	_xkRendererContext.callbacks.scissorRenderer(renderer, x, y, width, height);
}

void xkDraw(XkRenderer renderer, const XkSize vertexCount) {
	xkAssert(renderer);
	xkAssert(vertexCount > 0);

	_xkRendererContext.callbacks.draw(renderer, vertexCount);
}

void xkDrawIndexed(XkRenderer renderer, const XkSize indexCount) {
	xkAssert(renderer);
	xkAssert(indexCount > 0);

	_xkRendererContext.callbacks.drawIndexed(renderer, indexCount);
}

XkResult xkCreateRendererBuffer(XkRendererBuffer* pBuffer, const XkSize size, const XkHandle data, const XkBufferUsage usage) {
	xkAssert(pBuffer);
	xkAssert(size > 0);

	XkResult result = XK_SUCCESS;

	result = _xkRendererContext.callbacks.createBuffer(pBuffer, size, data, usage);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyRendererBuffer(XkRendererBuffer buffer) {
	xkAssert(buffer);

	_xkRendererContext.callbacks.destroyBuffer(buffer);
}

void xkMapRendererBuffer(XkRendererBuffer buffer, const XkHandle data) {
	xkAssert(buffer);
	xkAssert(data);

	_xkRendererContext.callbacks.mapBuffer(buffer, data);
}

void xkBindRendererVertexBuffer(XkRendererBuffer buffer, XkRenderer renderer) {
	xkAssert(buffer);
	xkAssert(renderer);

	_xkRendererContext.callbacks.bindVertexBuffer(buffer, renderer);
}

void xkBindRendererIndexBuffer(XkRendererBuffer buffer, XkRenderer renderer) {
	xkAssert(buffer);
	xkAssert(renderer);

	_xkRendererContext.callbacks.bindIndexBuffer(buffer, renderer);
}

XkResult xkCreateRendererTexture(XkRendererTexture* pTexture, const XkSize width, const XkSize height, const XkHandle data, XkTextureType type) {
	xkAssert(pTexture);
	xkAssert(data);
	xkAssert(width > 0);
	xkAssert(height > 0);
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	result = _xkRendererContext.callbacks.createTexture(pTexture, width, height, data, type);
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkDestroyRendererTexture(XkRendererTexture texture) {
	xkAssert(texture);

	_xkRendererContext.callbacks.destroyTexture(texture);
}

#if defined(XK_LINUX) || defined(XK_WINDOWS)

XkResult __xkLoadVulkanModule() {
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	result = xkLoadModule(&_xkRendererContext.module, XKVULKAN_LIBRARY);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKVULKAN_LIBRARY);
		goto _catch;
	}

	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.initializeRenderer, XKVULKAN_INITIALIZE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_INITIALIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.terminateRenderer, XKVULKAN_TERMINATE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TERMINATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.initializeRenderer, XKVULKAN_INITIALIZE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createRenderer, XKVULKAN_CREATE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyRenderer, XKVULKAN_DESTROY_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererColor, XKVULKAN_CLEAR_COLOR_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererDepth, XKVULKAN_CLEAR_DEPTH_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererStencil, XKVULKAN_CLEAR_STENCIL_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRenderer, XKVULKAN_CLEAR_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.topologyRenderer, XKVULKAN_TOPOLOGY_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.cullModeRenderer, XKVULKAN_CULLMODE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.beginRenderer, XKVULKAN_BEGIN_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.endRenderer, XKVULKAN_END_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.resizeRenderer, XKVULKAN_RESIZE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.scissorRenderer, XKVULKAN_SCISSOR_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.draw, XKVULKAN_DRAW, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.drawIndexed, XKVULKAN_DRAW_INDEXED, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createBuffer, XKVULKAN_CREATE_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyBuffer, XKVULKAN_DESTROY_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.mapBuffer, XKVULKAN_MAP_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindVertexBuffer, XKVULKAN_BIND_VERTEX_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindIndexBuffer, XKVULKAN_BIND_INDEX_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createTexture, XKVULKAN_CREATE_TEXTURE, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_TEXTURE);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyTexture, XKVULKAN_DESTROY_TEXTURE, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_TEXTURE);
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WINDOWS || XK_LINUX

#if defined(XK_WINDOWS)

XkResult __xkLoadD3D12Module() {
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	result = xkLoadModule(&_xkRendererContext.module, XKD3D12_LIBRARY);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKD3D12_LIBRARY);
		goto _catch;
	}

	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.initializeRenderer, XKD3D12_INITIALIZE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_INITIALIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.terminateRenderer, XKD3D12_TERMINATE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_TERMINATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createRenderer, XKD3D12_CREATE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyRenderer, XKD3D12_DESTROY_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererColor, XKD3D12_CLEAR_COLOR_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererDepth, XKD3D12_CLEAR_DEPTH_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererStencil, XKD3D12_CLEAR_STENCIL_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRenderer, XKD3D12_CLEAR_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.topologyRenderer, XKD3D12_TOPOLOGY_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.cullModeRenderer, XKD3D12_CULLMODE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.beginRenderer, XKD3D12_BEGIN_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.endRenderer, XKD3D12_END_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.resizeRenderer, XKD3D12_RESIZE_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.scissorRenderer, XKD3D12_SCISSOR_RENDERER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.draw, XKD3D12_DRAW, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.drawIndexed, XKD3D12_DRAW_INDEXED, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createBuffer, XKD3D12_CREATE_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyBuffer, XKD3D12_DESTROY_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.mapBuffer, XKD3D12_MAP_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindVertexBuffer, XKD3D12_BIND_VERTEX_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindIndexBuffer, XKD3D12_BIND_INDEX_BUFFER, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createTexture, XKD3D12_CREATE_TEXTURE, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_TEXTURE);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyTexture, XKD3D12_DESTROY_TEXTURE, _xkRendererContext.module);
	if (result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_TEXTURE);
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WINDOWS

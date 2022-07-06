/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Renderer/Internal.h"
#include "XKinetic/Platform/Module.h"
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
	#define XKVULKAN_CREATE_TEXTURE2D				"xkVulkanCreateTexture2d"
	#define XKVULKAN_DESTROY_TEXTURE2D			"xkVulkanDestroyTexture2d"
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_WINDOWS)
	#define XKVULKAN_INITIALIZE_RENDERER		"xkD3D12InitializeRenderer"
	#define XKVULKAN_TERMINATE_RENDERER			"xkD3D12TerminateRenderer"
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
	#define XKD3D12_CREATE_TEXTURE2D				"xkD3D12CreateTexture2d"
	#define XKD3D12_DESTROY_TEXTURE2D				"xkD3D12DestroyTexture2d"
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

	if(_xkRendererContext.initialized) {
		goto _catch;
	}

	switch(api) {
		case XK_RENDERER_API_DEFAULT:
#if defined(XK_WINDOWS)
			result = __xkLoadD3D12Module();
			if(result != XK_SUCCESS) {
				goto _catch;
			}
#elif defined(XK_LINUX)
			result = __xkLoadVulkanModule();
			if(result != XK_SUCCESS) {
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
			if(result != XK_SUCCESS) {
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
			if(result != XK_SUCCESS) {
				goto _catch;
			}
#else
			result = XK_ERROR_UNKNOWN;
			goto _catch;
#endif // XK_WINDOWS
			break;
	}

	result = _xkRendererContext.callbacks.initializeRenderer();
	if(result != XK_SUCCESS) goto _catch;

	_xkRendererContext.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateRenderer() {
	if(!_xkRendererContext.initialized) {
		return;
	}

	_xkRendererContext.callbacks.terminateRenderer();

	xkUnloadModule(_xkRendererContext.module);

	_xkRendererContext.initialized = XK_FALSE;
}

#if defined(XK_WINDOWS) || defined(XK_LINUX)

XkResult __xkLoadVulkanModule() {
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	result = xkLoadModule(&_xkRendererContext.module, XKVULKAN_LIBRARY);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKVULKAN_LIBRARY);
		goto _catch;
	}

	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.initializeRenderer, XKVULKAN_INITIALIZE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_INITIALIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.terminateRenderer, XKVULKAN_TERMINATE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TERMINATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.initializeRenderer, XKVULKAN_INITIALIZE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createRenderer, XKVULKAN_CREATE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyRenderer, XKVULKAN_DESTROY_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererColor, XKVULKAN_CLEAR_COLOR_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererDepth, XKVULKAN_CLEAR_DEPTH_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererStencil, XKVULKAN_CLEAR_STENCIL_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRenderer, XKVULKAN_CLEAR_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.topologyRenderer, XKVULKAN_TOPOLOGY_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.cullModeRenderer, XKVULKAN_CULLMODE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.beginRenderer, XKVULKAN_BEGIN_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.endRenderer, XKVULKAN_END_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.resizeRenderer, XKVULKAN_RESIZE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.scissorRenderer, XKVULKAN_SCISSOR_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.draw, XKVULKAN_DRAW, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.drawIndexed, XKVULKAN_DRAW_INDEXED, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createBuffer, XKVULKAN_CREATE_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyBuffer, XKVULKAN_DESTROY_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.mapBuffer, XKVULKAN_MAP_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindVertexBuffer, XKVULKAN_BIND_VERTEX_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindIndexBuffer, XKVULKAN_BIND_INDEX_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createTexture, XKVULKAN_CREATE_TEXTURE2D, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_CREATE_TEXTURE2D);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyTexture, XKVULKAN_DESTROY_TEXTURE2D, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKVULKAN_LIBRARY, XKVULKAN_DESTROY_TEXTURE2D);
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
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s", XKD3D12_LIBRARY);
		goto _catch;
	}

	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.initializeRenderer, XKD3D12_INITIALIZE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_INITIALIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.terminateRenderer, XKD3D12_TERMINATE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_TERMINATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createRenderer, XKD3D12_CREATE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyRenderer, XKD3D12_DESTROY_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererColor, XKD3D12_CLEAR_COLOR_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_COLOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererDepth, XKD3D12_CLEAR_DEPTH_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_DEPTH_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRendererStencil, XKD3D12_CLEAR_STENCIL_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_STENCIL_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.clearRenderer, XKD3D12_CLEAR_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CLEAR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.topologyRenderer, XKD3D12_TOPOLOGY_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_TOPOLOGY_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.cullModeRenderer, XKD3D12_CULLMODE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CULLMODE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.beginRenderer, XKD3D12_BEGIN_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BEGIN_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.endRenderer, XKD3D12_END_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_END_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.resizeRenderer, XKD3D12_RESIZE_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_RESIZE_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.scissorRenderer, XKD3D12_SCISSOR_RENDERER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_SCISSOR_RENDERER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.draw, XKD3D12_DRAW, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DRAW);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.drawIndexed, XKD3D12_DRAW_INDEXED, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DRAW_INDEXED);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createBuffer, XKD3D12_CREATE_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyBuffer, XKD3D12_DESTROY_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.mapBuffer, XKD3D12_MAP_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_MAP_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindVertexBuffer, XKD3D12_BIND_VERTEX_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BIND_VERTEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.bindIndexBuffer, XKD3D12_BIND_INDEX_BUFFER, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_BIND_INDEX_BUFFER);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.createTexture, XKD3D12_CREATE_TEXTURE2D, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_CREATE_TEXTURE2D);
		goto _catch;
	}
	result = xkGetModuleSymbol((XkProcPfn*)&_xkRendererContext.callbacks.destroyTexture, XKD3D12_DESTROY_TEXTURE2D, _xkRendererContext.module);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load module %s symbol: %s", XKD3D12_LIBRARY, XKD3D12_DESTROY_TEXTURE2D);
		goto _catch;
	}

_catch:
	return(result);
}

#endif // XK_WINDOWS

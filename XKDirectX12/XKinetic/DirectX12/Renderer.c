#include "XKinetic/Renderer/External.h"
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/DirectX12/Renderer.h"

struct XkDX12Renderer {
	XkRendererConfig config;

  /// TODO: implementation.
};

struct XkDX12Buffer {
  /// TODO: implementation.
};

struct XkDX12Texture2D {
  /// TODO: implementation.
};

XkResult xkDX12CreateRenderer(XkDX12Renderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window) {
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkDX12Renderer));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12Renderer renderer = *pRenderer;

	renderer->config = *pConfig;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyRenderer(XkDX12Renderer renderer) {
	/// TODO: implementation.
	xkFreeMemory(renderer);
}


void xkDX12ClearColorRenderer(XkDX12Renderer renderer, XkVec4 color) {
	/// TODO: implementation.
}

void xkDX12ClearDepthRenderer(XkDX12Renderer renderer, XkFloat32 depth) {
	/// TODO: implementation.
}

void xkDX12ClearStencilRenderer(XkDX12Renderer renderer, XkUInt32 stencil) {
	/// TODO: implementation.
}

void xkDX12ClearRenderer(XkDX12Renderer renderer) {
	/// TODO: implementation.
}

void xkDX12TopologyRenderer(XkDX12Renderer renderer, XkTopology topology) {
	/// TODO: implementation.
}

void xkDX12CullModeRenderer(XkDX12Renderer renderer, XkCullMode cullMode) {
	/// TODO: implementation.
}

void xkDX12BeginRenderer(XkDX12Renderer renderer) {
	/// TODO: implementation.
}

void xkDX12EndRenderer(XkDX12Renderer renderer) {
	/// TODO: implementation.
}

void xkDX12ResizeRenderer(XkDX12Renderer renderer, XkSize width, XkSize height) {
	/// TODO: implementation.
}

void xkDX12ScissorRenderer(XkDX12Renderer renderer, XkInt32 x, XkInt32 y, XkSize width, XkSize height) {
	/// TODO: implementation.
}

void xkDX12Draw(XkDX12Renderer renderer, XkSize vertexCount) {
	/// TODO: implementation.
}

void xkDX12DrawIndexed(XkDX12Renderer renderer, XkSize indexCount) {
	/// TODO: implementation.
}

XkResult xkDX12CreateVertexBuffer(XkDX12VertexBuffer* pBuffer, const XkSize size, XkHandle data, XkDX12Renderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkDX12Buffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12VertexBuffer buffer = *pBuffer;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyVertexBuffer(XkDX12VertexBuffer buffer) {
	/// TODO: implementation.
}

void xkDX12BindVertexBuffer(XkDX12VertexBuffer buffer) {
	/// TODO: implementation.
}

XkResult xkDX12CreateIndexBuffer(XkDX12IndexBuffer* pBuffer, const XkSize size, XkHandle data, XkDX12Renderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkDX12Buffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12IndexBuffer buffer = *pBuffer;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyIndexBuffer(XkDX12IndexBuffer buffer) {
	/// TODO: implementation.
}

void xkDX12BindIndexBuffer(XkDX12IndexBuffer buffer) {
	/// TODO: implementation.
}

XkResult xkDX12CreateUniformBuffer(XkDX12UniformBuffer* pBuffer, const XkSize size, const XkSize data, XkDX12Renderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkDX12Buffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12UniformBuffer buffer = *pBuffer;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyUniformBuffer(XkDX12UniformBuffer buffer) {
	/// TODO: implementation.
}

void xkDX12SetUniformBuffer(XkDX12UniformBuffer buffer, XkHandle data, XkSize size) {
	/// TODO: implementation.
}

XkResult xkDX12CreateTexture2D(XkDX12Texture2D* pTexture, XkHandle data, const XkSize width, const XkSize height, XkDX12Renderer renderer) {
	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkDX12Texture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12Texture2D texture = *pTexture;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyTexture2D(XkDX12Texture2D texture) {
	/// TODO: implementation.
	xkFreeMemory(texture);
}

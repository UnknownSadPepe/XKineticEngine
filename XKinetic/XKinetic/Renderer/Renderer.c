/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Renderer/Internal.h"
#include "XKinetic/Renderer/Renderer.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
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

	xkFreeMemory(renderer);
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


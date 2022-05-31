#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Core/Window.h"
#include "XKinetic/Renderer/External.h"

typedef struct XkRenderer* XkRenderer;
typedef struct XkBuffer* XkVertexBuffer;
typedef struct XkBuffer* XkIndexBuffer;
typedef struct XkBuffer* XkUniformBuffer;
typedef struct XkTexture2D* XkTexture2D;

typedef enum {
	XK_RENDERER_API_DEFAULT,
	XK_RENDERER_API_VK,
	XK_RENDERER_API_DX12
} XkRendererApi;

typedef XkResult(*XkRendererCreatePfn)(XkHandle*, XkRendererConfig* const, XkWindow);
typedef void(*XkRendererDestroyPfn)(XkHandle);

typedef void(*XkRendererClearColorPfn)(XkHandle, XkVec4);
typedef void(*XkRendererClearDepthPfn)(XkHandle, XkFloat64);
typedef void(*XkRendererClearStencilPfn)(XkHandle, XkInt32);
typedef void(*XkRendererClearPfn)(XkHandle);

typedef void(*XkRendererTopologyPfn)(XkHandle, XkTopology);
typedef void(*XkRendererCullModePfn)(XkHandle, XkCullMode);

typedef void(*XkRendererBeginPfn)(XkHandle);
typedef void(*XkRendererEndPfn)(XkHandle);

typedef void(*XkRendererResizePfn)(XkHandle, XkSize, XkSize);
typedef void(*XkRendererScissorPfn)(XkHandle, XkSize, XkSize, XkSize, XkSize);

typedef void(*XkRendererDrawPfn)(XkHandle, XkSize);
typedef void(*XkRendererDrawIndexedPfn)(XkHandle, XkSize);

typedef XkResult(*XkBufferCreatePfn)(XkHandle*, const XkSize, XkHandle, XkHandle);
typedef void(*XkBufferDestroyPfn)(XkHandle);
typedef void(*XkBufferBindPfn)(XkHandle);
typedef void(*XkBufferUnbindPfn)(XkHandle);
typedef void(*XkBufferSetPfn)(XkHandle, XkHandle);

typedef XkResult(*XkUniformBufferCreatePfn)(XkHandle*, const XkSize, const XkSize, XkHandle);
typedef void(*XkUniformBufferDestroyPfn)(XkHandle);
typedef void(*XkUniformBufferSetPfn)(XkHandle, XkHandle, XkSize);

typedef XkResult(*XkTexture2DCreatePfn)(XkHandle*, XkHandle, const XkSize, const XkSize, XkHandle);
typedef void(*XkTexture2DDestroyPfn)(XkHandle);

XK_API XkResult xkCreateRenderer(XkRenderer*, XkRendererConfig* const, XkWindow, XkRendererApi);
XK_API void xkDestroyRenderer(XkRenderer);

XK_API void xkClearColorRenderer(XkRenderer, XkVec4);
XK_API void xkClearDepthRenderer(XkRenderer, XkFloat64);
XK_API void xkClearStencilRenderer(XkRenderer, XkInt32);
XK_API void xkClearRenderer(XkRenderer);

XK_API void xkTopologyRenderer(XkRenderer, XkTopology);
XK_API void xkCullModeRenderer(XkRenderer, XkCullMode);

XK_API void xkBeginRenderer(XkRenderer);
XK_API void xkEndRenderer(XkRenderer);

XK_API void xkResizeRenderer(XkRenderer, XkSize, XkSize);
XK_API void xkScissorRenderer(XkRenderer, XkSize, XkSize, XkSize, XkSize);

XK_API void xkDraw(XkRenderer, XkSize);
XK_API void xkDrawIndexed(XkRenderer, XkSize);

XK_API XkResult xkCreateVertexBuffer(XkVertexBuffer*, const XkSize, XkHandle, XkRenderer);
XK_API void xkDestroyVertexBuffer(XkVertexBuffer);
XK_API void xkBindVertexBuffer(XkVertexBuffer);
XK_API void xkUnbindVertexBuffer(XkVertexBuffer);

XK_API XkResult xkCreateIndexBuffer(XkIndexBuffer*, const XkSize, XkHandle, XkRenderer);
XK_API void xkDestroyIndexBuffer(XkIndexBuffer);
XK_API void xkBindIndexBuffer(XkIndexBuffer);
XK_API void xkUnbindIndexBuffer(XkIndexBuffer);

XK_API XkResult xkCreateUniformBuffer(XkUniformBuffer*, const XkSize, const XkSize, XkRenderer);
XK_API void xkDestroyUniformBuffer(XkUniformBuffer);
XK_API void xkSetUniformBuffer(XkUniformBuffer, XkHandle, const XkSize);

XK_API XkResult xkCreateTexture2D(XkTexture2D*, XkHandle, const XkSize, const XkSize, XkRenderer);
XK_API void xkDestroyTexture2D(XkTexture2D);

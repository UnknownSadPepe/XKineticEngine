#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/External.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkRenderer* XkRenderer;
typedef struct XkBuffer* XkBuffer;
typedef struct XkTexture2D* XkTexture2D;

typedef enum {
	XK_RENDERER_API_DEFAULT,
	XK_RENDERER_API_VK,
#if defined(XK_WIN32)
	XK_RENDERER_API_DX12
#endif // XK_WIN32
} XkRendererApi;

typedef XkResult(*XkCreateRendererPfn)(XkHandle*, XkRendererConfig* const, XkWindow);
typedef void(*XkDestroyRendererPfn)(XkHandle);

typedef void(*XkClearColorRendererPfn)(XkHandle, XkVec4);
typedef void(*XkClearDepthRendererPfn)(XkHandle, XkFloat32);
typedef void(*XkClearStencilRendererPfn)(XkHandle, XkUInt32);
typedef void(*XkClearRendererPfn)(XkHandle);

typedef void(*XkTopologyRendererPfn)(XkHandle, XkTopology);
typedef void(*XkCullModeRendererPfn)(XkHandle, XkCullMode);

typedef void(*XkBeginRendererPfn)(XkHandle);
typedef void(*XkEndRendererPfn)(XkHandle);

typedef void(*XkResizeRendererPfn)(XkHandle, XkSize, XkSize);
typedef void(*XkScissorRendererPfn)(XkHandle, XkInt32, XkInt32, XkSize, XkSize);

typedef void(*XkDrawPfn)(XkHandle, XkSize);
typedef void(*XkDrawIndexedPfn)(XkHandle, XkSize);

typedef XkResult(*XkCreateBufferPfn)(XkHandle*, const XkSize, const XkHandle, XkHandle);
typedef void(*XkDestroyBufferPfn)(XkHandle);

typedef void(*XkMapBufferPfn)(XkHandle, const XkHandle);

typedef void(*XkBindVertexBufferPfn)(XkHandle);
typedef void(*XkBindIndexBufferPfn)(XkHandle);

typedef XkResult(*XkCreateTexture2DPfn)(XkHandle*, XkHandle, const XkSize, const XkSize, XkHandle);
typedef void(*XkDestroyTexture2DPfn)(XkHandle);

XK_API XkResult xkCreateRenderer(XkRenderer*, XkRendererConfig* const, XkWindow, XkRendererApi);
XK_API void xkDestroyRenderer(XkRenderer);

XK_API void xkClearColorRenderer(XkRenderer, XkVec4);
XK_API void xkClearDepthRenderer(XkRenderer, XkFloat32);
XK_API void xkClearStencilRenderer(XkRenderer, XkUInt32);
XK_API void xkClearRenderer(XkRenderer);

XK_API void xkTopologyRenderer(XkRenderer, XkTopology);
XK_API void xkCullModeRenderer(XkRenderer, XkCullMode);

XK_API void xkBeginRenderer(XkRenderer);
XK_API void xkEndRenderer(XkRenderer);

XK_API void xkResizeRenderer(XkRenderer, XkSize, XkSize);
XK_API void xkScissorRenderer(XkRenderer, XkInt32, XkInt32, XkSize, XkSize);

XK_API void xkDraw(XkRenderer, XkSize);
XK_API void xkDrawIndexed(XkRenderer, XkSize);

XK_API XkResult xkCreateBuffer(XkBuffer*, const XkSize, XkHandle, XkRenderer);
XK_API void xkDestroyBuffer(XkBuffer);

XK_API void xkMapBuffer(XkBuffer, const XkHandle);

XK_API void xkBindVertexBuffer(XkBuffer);
XK_API void xkBindIndexBuffer(XkBuffer);

XK_API XkResult xkCreateTexture2D(XkTexture2D*, XkHandle, const XkSize, const XkSize, XkRenderer);
XK_API void xkDestroyTexture2D(XkTexture2D);

#ifdef __cplusplus
}
#endif // __cplusplus

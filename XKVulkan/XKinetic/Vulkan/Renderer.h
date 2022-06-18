#pragma once

#include "XKinetic/XKVulkan.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/External.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkVkRenderer* XkVkRenderer;
typedef struct XkVkBuffer* XkVkBuffer;
typedef struct XkVkTexture2D* XkVkTexture2D;

XKVULKAN_API XkResult xkVkCreateRenderer(XkVkRenderer*, XkRendererConfig* const, XkWindow);
XKVULKAN_API void xkVkDestroyRenderer(XkVkRenderer);

XKVULKAN_API void xkVkClearColorRenderer(XkVkRenderer, XkVec4);
XKVULKAN_API void xkVkClearDepthRenderer(XkVkRenderer, XkFloat32);
XKVULKAN_API void xkVkClearStencilRenderer(XkVkRenderer, XkUInt32);
XKVULKAN_API void xkVkClearRenderer(XkVkRenderer);

XKVULKAN_API void xkVkTopologyRenderer(XkVkRenderer, XkTopology);
XKVULKAN_API void xkVkCullModeRenderer(XkVkRenderer, XkCullMode);

XKVULKAN_API void xkVkBeginRenderer(XkVkRenderer);
XKVULKAN_API void xkVkEndRenderer(XkVkRenderer);

XKVULKAN_API void xkVkResizeRenderer(XkVkRenderer, XkSize, XkSize);
XKVULKAN_API void xkVkScissorRenderer(XkVkRenderer, XkInt32, XkInt32, XkSize, XkSize);

XKVULKAN_API void xkVkDraw(XkVkRenderer, XkSize);
XKVULKAN_API void xkVkDrawIndexed(XkVkRenderer, XkSize);

XKVULKAN_API XkResult xkVkCreateBuffer(XkVkBuffer*, const XkBufferUsage, const XkSize, const XkHandle, XkVkRenderer);
XKVULKAN_API void xkVkDestroyBuffer(XkVkBuffer);

XKVULKAN_API void xkVkMapBuffer(XkVkBuffer, const XkHandle);

XKVULKAN_API void xkVkBindVertexBuffer(XkVkBuffer);
XKVULKAN_API void xkVkBindIndexBuffer(XkVkBuffer);

XKVULKAN_API XkResult xkVkCreateTexture2D(XkVkTexture2D*, XkHandle, const XkSize, const XkSize, XkVkRenderer);
XKVULKAN_API void xkVkDestroyTexture2D(XkVkTexture2D);

#ifdef __cplusplus
}
#endif // __cplusplus

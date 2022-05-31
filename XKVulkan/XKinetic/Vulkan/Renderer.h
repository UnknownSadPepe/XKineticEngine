#pragma once

#include "XKinetic/XKVulkan.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Core/Window.h"
#include "XKinetic/Renderer/External.h"

#ifdef XK_DEBUG
	#define XK_VK_DEBUG
#endif // XK_DEBUG

typedef struct XkVkRenderer* XkVkRenderer;
typedef struct XkVkBuffer* XkVkVertexBuffer;
typedef struct XkVkBuffer* XkVkIndexBuffer;
typedef struct XkVkBuffer* XkVkUniformBuffer;
typedef struct XkVkTexture2D* XkVkTexture2D;

XKVULKAN_API XkResult xkVkCreateRenderer(XkVkRenderer*, XkRendererConfig* const, XkWindow);
XKVULKAN_API void xkVkDestroyRenderer(XkVkRenderer);

XKVULKAN_API void xkVkClearColorRenderer(XkVkRenderer, XkVec4);
XKVULKAN_API void xkVkClearDepthRenderer(XkVkRenderer, XkFloat64);
XKVULKAN_API void xkVkClearStencilRenderer(XkVkRenderer, XkInt32);
XKVULKAN_API void xkVkClearRenderer(XkVkRenderer);

XKVULKAN_API void xkVkTopologyRenderer(XkVkRenderer, XkTopology);
XKVULKAN_API void xkVkCullModeRenderer(XkVkRenderer, XkCullMode);

XKVULKAN_API void xkVkBeginRenderer(XkVkRenderer);
XKVULKAN_API void xkVkEndRenderer(XkVkRenderer);

XKVULKAN_API void xkVkResizeRenderer(XkVkRenderer, XkSize, XkSize);
XKVULKAN_API void xkVkScissorRenderer(XkVkRenderer, XkSize, XkSize, XkSize, XkSize);

XKVULKAN_API void xkVkDraw(XkVkRenderer, XkSize);
XKVULKAN_API void xkVkDrawIndexed(XkVkRenderer, XkSize);

XKVULKAN_API XkResult xkVkCreateVertexBuffer(XkVkVertexBuffer*, const XkSize, XkHandle, XkVkRenderer);
XKVULKAN_API void xkVkDestroyVertexBuffer(XkVkVertexBuffer);
XKVULKAN_API void xkVkBindVertexBuffer(XkVkVertexBuffer);
XKVULKAN_API void xkVkUnbindVertexBuffer(XkVkVertexBuffer);

XKVULKAN_API XkResult xkVkCreateIndexBuffer(XkVkIndexBuffer*, const XkSize, XkHandle, XkVkRenderer);
XKVULKAN_API void xkVkDestroyIndexBuffer(XkVkIndexBuffer);
XKVULKAN_API void xkVkBindIndexBuffer(XkVkIndexBuffer);
XKVULKAN_API void xkVkUnbindIndexBuffer(XkVkIndexBuffer);

XKVULKAN_API XkResult xkVkCreateUniformBuffer(XkVkUniformBuffer*, const XkSize, const XkSize, XkVkRenderer);
XKVULKAN_API void xkVkDestroyUniformBuffer(XkVkUniformBuffer);
XKVULKAN_API void xkVkSetUniformBuffer(XkVkUniformBuffer, XkHandle, XkSize);

XKVULKAN_API XkResult xkVkCreateTexture2D(XkVkTexture2D*, XkHandle*, const XkSize, const XkSize, XkVkRenderer);
XKVULKAN_API void xkVkDestroyTexture2D(XkVkTexture2D);


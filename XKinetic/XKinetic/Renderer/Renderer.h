#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/External.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkHandle XkRenderer;
typedef XkHandle XkRendererBuffer;
typedef XkHandle XkRendererTexture;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult	xkInitializeRenderer(const XkRendererApi);
extern XK_API void			xkTerminateRenderer();

extern XK_API XkResult 	xkCreateRenderer(XkRenderer*, XkWindow, const XkRendererHint);
extern XK_API void 			xkDestroyRenderer(XkRenderer);

extern XK_API void 			xkClearColorRenderer(XkRenderer, const XkVec4);
extern XK_API void 			xkClearDepthRenderer(XkRenderer, const XkFloat32);
extern XK_API void 			xkClearStencilRenderer(XkRenderer, const XkUInt32);
extern XK_API void 			xkClearRenderer(XkRenderer);

extern XK_API void 			xkTopologyRenderer(XkRenderer, const XkTopology);
extern XK_API void 			xkCullModeRenderer(XkRenderer, const XkCullMode);

extern XK_API void 			xkBeginRenderer(XkRenderer);
extern XK_API void 			xkEndRenderer(XkRenderer);

extern XK_API void 			xkResizeRenderer(XkRenderer, const XkSize, const XkSize);
extern XK_API void 			xkScissorRenderer(XkRenderer, const XkInt32, const XkInt32, const XkSize, const XkSize);

extern XK_API void 			xkDraw(XkRenderer, const XkSize);
extern XK_API void 			xkDrawIndexed(XkRenderer, const XkSize);

extern XK_API XkResult 	xkCreateRendererBuffer(XkRendererBuffer*, const XkSize, const XkHandle, const XkBufferUsage);
extern XK_API void 			xkDestroyRendererBuffer(XkRendererBuffer);

extern XK_API void 			xkMapRendererBuffer(XkRendererBuffer, const XkHandle);

extern XK_API void 			xkBindRendererVertexBuffer(XkRendererBuffer, XkRenderer);
extern XK_API void 			xkBindRendererIndexBuffer(XkRendererBuffer, XkRenderer);

extern XK_API XkResult 	xkCreateRendererTexture(XkRendererTexture*, const XkSize, const XkSize, const XkHandle, const XkTextureType);
extern XK_API void 			xkDestroyRendererTexture(XkRendererTexture);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

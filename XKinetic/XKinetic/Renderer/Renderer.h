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
typedef struct XkRenderer_T* XkRenderer;
typedef struct XkBuffer_T* XkBuffer;
typedef struct XkTexture2d_T* XkTexture2d;

typedef enum XkRendererApi_T {
	XK_RENDERER_API_DEFAULT,
	XK_RENDERER_API_VULKAN,
#if defined(XK_WIN64)
	XK_RENDERER_API_D3D12
#endif // XK_WIN64
} XkRendererApi;

typedef XkResult(*XkInitializeRendererPfn)();
typedef void(*XkTerminateRendererPfn)();

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

typedef XkResult(*XkCreateTexture2dPfn)(XkHandle*, XkHandle, const XkSize, const XkSize, XkHandle);
typedef void(*XkDestroyTexture2dPfn)(XkHandle);

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult	xkInitializeRenderer();
extern XK_API void			xkTerminateRenderer();

extern XK_API XkResult 	xkCreateRenderer(XkRenderer*, XkRendererConfig* const, XkWindow, XkRendererApi);
extern XK_API void 			xkDestroyRenderer(XkRenderer);

extern XK_API void 			xkClearColorRenderer(XkRenderer, XkVec4);
extern XK_API void 			xkClearDepthRenderer(XkRenderer, XkFloat32);
extern XK_API void 			xkClearStencilRenderer(XkRenderer, XkUInt32);
extern XK_API void 			xkClearRenderer(XkRenderer);

extern XK_API void 			xkTopologyRenderer(XkRenderer, XkTopology);
extern XK_API void 			xkCullModeRenderer(XkRenderer, XkCullMode);

extern XK_API void 			xkBeginRenderer(XkRenderer);
extern XK_API void 			xkEndRenderer(XkRenderer);

extern XK_API void 			xkResizeRenderer(XkRenderer, XkSize, XkSize);
extern XK_API void 			xkScissorRenderer(XkRenderer, XkInt32, XkInt32, XkSize, XkSize);

extern XK_API void 			xkDraw(XkRenderer, XkSize);
extern XK_API void 			xkDrawIndexed(XkRenderer, XkSize);

extern XK_API XkResult 	xkCreateBuffer(XkBuffer*, const XkSize, XkHandle, XkRenderer);
extern XK_API void 			xkDestroyBuffer(XkBuffer);

extern XK_API void 			xkMapBuffer(XkBuffer, const XkHandle);

extern XK_API void 			xkBindVertexBuffer(XkBuffer);
extern XK_API void 			xkBindIndexBuffer(XkBuffer);

extern XK_API XkResult 	xkCreateTexture2d(XkTexture2d*, XkHandle, const XkSize, const XkSize, XkRenderer);
extern XK_API void 			xkDestroyTexture2d(XkTexture2d);

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

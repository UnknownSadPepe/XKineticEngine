#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKVulkan.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Renderer/External.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkVulkanRenderer_T* XkVulkanRenderer;

typedef struct XkVulkanBuffer_T* XkVulkanBuffer;

typedef struct XkVulkanTexture2d_T* XkVulkanTexture2d;

/* ########## FUNCTIONS SECTION ########## */
extern XKVULKAN_API XkResult 	xkVulkanInitialize();
extern XKVULKAN_API void			xkVulkanTerminate();

extern XKVULKAN_API XkResult 	xkVulkanCreateRenderer(XkVulkanRenderer*, const XkRendererConfig* const, const XkWindow);
extern XKVULKAN_API void 			xkVulkanDestroyRenderer(XkVulkanRenderer);

extern XKVULKAN_API void 			xkVulkanClearColorRenderer(XkVulkanRenderer, const XkVec4);
extern XKVULKAN_API void 			xkVulkanClearDepthRenderer(XkVulkanRenderer, const XkFloat32);
extern XKVULKAN_API void 			xkVulkanClearStencilRenderer(XkVulkanRenderer, const XkUInt32);
extern XKVULKAN_API void 			xkVulkanClearRenderer(XkVulkanRenderer);

extern XKVULKAN_API void 			xkVulkanTopologyRenderer(XkVulkanRenderer, const XkTopology);
extern XKVULKAN_API void 			xkVulkanCullModeRenderer(XkVulkanRenderer, const XkCullMode);

extern XKVULKAN_API void 			xkVulkanBeginRenderer(XkVulkanRenderer);
extern XKVULKAN_API void 			xkVulkanEndRenderer(XkVulkanRenderer);

extern XKVULKAN_API void 			xkVulkanResizeRenderer(XkVulkanRenderer, const XkSize, const XkSize);
extern XKVULKAN_API void 			xkVulkanScissorRenderer(XkVulkanRenderer, const XkInt32, const XkInt32, const XkSize, const XkSize);

extern XKVULKAN_API void 			xkVulkanDraw(XkVulkanRenderer, const XkSize);
extern XKVULKAN_API void 			xkVulkanDrawIndexed(XkVulkanRenderer, const XkSize);

extern XKVULKAN_API XkResult 	xkVulkanCreateBuffer(XkVulkanBuffer*, const XkBufferUsage, const XkSize, const XkHandle, XkVulkanRenderer);
extern XKVULKAN_API void 			xkVulkanDestroyBuffer(XkVulkanBuffer);

extern XKVULKAN_API void 			xkVulkanMapBuffer(XkVulkanBuffer, const XkHandle);

extern XKVULKAN_API void 			xkVulkanBindVertexBuffer(XkVulkanBuffer);
extern XKVULKAN_API void 			xkVulkanBindIndexBuffer(XkVulkanBuffer);

extern XKVULKAN_API XkResult 	xkVulkanCreateTexture2d(XkVulkanTexture2d*, XkHandle, const XkSize, const XkSize, XkVulkanRenderer);
extern XKVULKAN_API void 			xkVulkanDestroyTexture2d(XkVulkanTexture2d);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

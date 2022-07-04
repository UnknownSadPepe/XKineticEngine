#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKD3D12.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Renderer/External.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkD3D12Renderer_T* 	XkD3D12Renderer;

typedef struct XkD3D12Buffer_T* 		XkD3D12Buffer;

typedef struct XkD3D12Texture2d_T* 	XkD3D12Texture2d;

/* ########## FUNCTIONS SECTION ########## */
extern XKD3D12_API XkResult 	xkD3D12InitializeContext();
extern XKD3D12_API void 			xkD3D12TerminateContext();

extern XKD3D12_API XkResult 	xkD3D12CreateRenderer(XkD3D12Renderer*, const XkRendererConfig* const, const XkWindow);
extern XKD3D12_API void 			xkD3D12DestroyRenderer(XkD3D12Renderer);

extern XKD3D12_API void 			xkD3D12ClearColorRenderer(XkD3D12Renderer, const XkVec4);
extern XKD3D12_API void 			xkD3D12ClearDepthRenderer(XkD3D12Renderer, const XkFloat32);
extern XKD3D12_API void 			xkD3D12ClearStencilRenderer(XkD3D12Renderer, const XkUInt32);
extern XKD3D12_API void 			xkD3D12ClearRenderer(XkD3D12Renderer);

extern XKD3D12_API void 			xkD3D12TopologyRenderer(XkD3D12Renderer, const XkTopology);
extern XKD3D12_API void 			xkD3D12CullModeRenderer(XkD3D12Renderer, const XkCullMode);

extern XKD3D12_API void 			xkD3D12BeginRenderer(XkD3D12Renderer);
extern XKD3D12_API void 			xkD3D12EndRenderer(XkD3D12Renderer);

extern XKD3D12_API void 			xkD3D12ResizeRenderer(XkD3D12Renderer, const XkSize, const XkSize);
extern XKD3D12_API void 			xkD3D12ScissorRenderer(XkD3D12Renderer, const XkInt32, const XkInt32, const XkSize, const XkSize);

extern XKD3D12_API void 			xkD3D12Draw(XkD3D12Renderer, const XkSize);
extern XKD3D12_API void 			xkD3D12DrawIndexed(XkD3D12Renderer, const XkSize);

extern XKD3D12_API XkResult 	xkD3D12CreateBuffer(XkD3D12Buffer*, const XkBufferUsage, const XkSize, XkHandle, XkD3D12Renderer);
extern XKD3D12_API void 			xkD3D12DestroyBuffer(XkD3D12Buffer);

extern XKD3D12_API void 			xkD3D12MapBuffer(XkD3D12Buffer, const XkHandle);

extern XKD3D12_API void 			xkD3D12BindVertexBuffer(XkD3D12Buffer);
extern XKD3D12_API void 			xkD3D12BindIndexBuffer(XkD3D12Buffer);

extern XKD3D12_API XkResult 	xkD3D12CreateTexture2d(XkD3D12Texture2d*, XkHandle, const XkSize, const XkSize, XkD3D12Renderer);
extern XKD3D12_API void 			xkD3D12DestroyTexture2d(XkD3D12Texture2d);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

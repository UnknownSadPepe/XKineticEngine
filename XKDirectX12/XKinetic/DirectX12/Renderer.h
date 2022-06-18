#pragma once

#include "XKinetic/XKDirectX12.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/External.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkDX12Renderer* XkDX12Renderer;
typedef struct XkDX12Buffer* XkDX12Buffer;
typedef struct XkDX12Texture2D* XkDX12Texture2D;

XKDIRECTX12_API XkResult xkDX12CreateRenderer(XkDX12Renderer*, XkRendererConfig* const, XkWindow);
XKDIRECTX12_API void xkDX12DestroyRenderer(XkDX12Renderer);

XKDIRECTX12_API void xkDX12ClearColorRenderer(XkDX12Renderer, XkVec4);
XKDIRECTX12_API void xkDX12ClearDepthRenderer(XkDX12Renderer, XkFloat32);
XKDIRECTX12_API void xkDX12ClearStencilRenderer(XkDX12Renderer, XkUInt32);
XKDIRECTX12_API void xkDX12ClearRenderer(XkDX12Renderer);

XKDIRECTX12_API void xkDX12TopologyRenderer(XkDX12Renderer, XkTopology);
XKDIRECTX12_API void xkDX12CullModeRenderer(XkDX12Renderer, XkCullMode);

XKDIRECTX12_API void xkDX12BeginRenderer(XkDX12Renderer);
XKDIRECTX12_API void xkDX12EndRenderer(XkDX12Renderer);

XKDIRECTX12_API void xkDX12ResizeRenderer(XkDX12Renderer, XkSize, XkSize);
XKDIRECTX12_API void xkDX12ScissorRenderer(XkDX12Renderer, XkInt32, XkInt32, XkSize, XkSize);

XKDIRECTX12_API void xkDX12Draw(XkDX12Renderer, XkSize);
XKDIRECTX12_API void xkDX12DrawIndexed(XkDX12Renderer, XkSize);

XKDIRECTX12_API XkResult xkDX12CreateBuffer(XkDX12Buffer*, const XkBufferUsage, const XkSize, XkHandle, XkDX12Renderer);
XKDIRECTX12_API void xkDX12DestroyBuffer(XkDX12Buffer);

XKDIRECTX12_API void xkDX12MapBuffer(XkDX12Buffer, const XkHandle);

XKDIRECTX12_API void xkDX12BindVertexBuffer(XkDX12Buffer);
XKDIRECTX12_API void xkDX12BindIndexBuffer(XkDX12Buffer);

XKDIRECTX12_API XkResult xkDX12CreateTexture2D(XkDX12Texture2D*, XkHandle, const XkSize, const XkSize, XkDX12Renderer);
XKDIRECTX12_API void xkDX12DestroyTexture2D(XkDX12Texture2D);

#ifdef __cplusplus
}
#endif // __cplusplus

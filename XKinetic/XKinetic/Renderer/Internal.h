#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Module.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/External.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkResult(*XkInitializeRendererPfn)();
typedef void(*XkTerminateRendererPfn)();

typedef XkResult(*XkCreateRendererPfn)(XkHandle*, XkWindow, const XkRendererHint);
typedef void(*XkDestroyRendererPfn)(XkHandle);

typedef void(*XkClearColorRendererPfn)(XkHandle, const XkVec4);
typedef void(*XkClearDepthRendererPfn)(XkHandle, const XkFloat32);
typedef void(*XkClearStencilRendererPfn)(XkHandle, const XkUInt32);
typedef void(*XkClearRendererPfn)(XkHandle);

typedef void(*XkTopologyRendererPfn)(XkHandle, const XkTopology);
typedef void(*XkCullModeRendererPfn)(XkHandle, const XkCullMode);

typedef void(*XkBeginRendererPfn)(XkHandle);
typedef void(*XkEndRendererPfn)(XkHandle);

typedef void(*XkResizeRendererPfn)(XkHandle, const XkSize, const XkSize);
typedef void(*XkScissorRendererPfn)(XkHandle, const XkInt32, const XkInt32, const XkSize, const XkSize);

typedef void(*XkDrawPfn)(XkHandle, XkSize);
typedef void(*XkDrawIndexedPfn)(XkHandle, XkSize);

typedef XkResult(*XkCreateRendererBufferPfn)(XkHandle*, const XkSize, const XkHandle, const XkBufferUsage);
typedef void(*XkDestroyRendererBufferPfn)(XkHandle);

typedef void(*XkMapRendererBufferPfn)(XkHandle, const XkHandle);

typedef void(*XkBindRendererVertexBufferPfn)(XkHandle, XkHandle);
typedef void(*XkBindRendererIndexBufferPfn)(XkHandle, XkHandle);

typedef XkResult(*XkCreateRendererTexturePfn)(XkHandle*, const XkSize, const XkSize, const XkHandle, const XkTextureType);
typedef void(*XkDestroyRendererTexturePfn)(XkHandle);

typedef struct __XkRendererContext_T {
	XkBool8 initialized;

	struct {
		XkInitializeRendererPfn					initializeRenderer;
		XkTerminateRendererPfn					terminateRenderer;

		XkCreateRendererPfn							createRenderer;
		XkDestroyRendererPfn						destroyRenderer;

		XkClearColorRendererPfn					clearRendererColor;
		XkClearDepthRendererPfn					clearRendererDepth;
		XkClearStencilRendererPfn				clearRendererStencil;
		XkClearRendererPfn							clearRenderer;

		XkTopologyRendererPfn						topologyRenderer;
		XkCullModeRendererPfn						cullModeRenderer;

		XkBeginRendererPfn							beginRenderer;
		XkEndRendererPfn								endRenderer;

		XkResizeRendererPfn							resizeRenderer;
		XkScissorRendererPfn						scissorRenderer;

		XkDrawPfn draw;
		XkDrawIndexedPfn								drawIndexed;

		XkCreateRendererBufferPfn 			createBuffer;
		XkDestroyRendererBufferPfn 			destroyBuffer;

		XkMapRendererBufferPfn 					mapBuffer;

		XkBindRendererVertexBufferPfn 	bindVertexBuffer;
		XkBindRendererIndexBufferPfn 		bindIndexBuffer;
		
		XkCreateRendererTexturePfn 			createTexture;
		XkDestroyRendererTexturePfn 		destroyTexture;
	} callbacks;

	XkModule module;
} __XkRendererContext;

/* ########## EXTERN SECTION ########## */
extern __XkRendererContext _xkRendererContext;

#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#include "XKinetic/Math/Vec2.h"
#include "XKinetic/Math/Vec3.h"
#include "XKinetic/Math/Vec4.h"
#include "XKinetic/Math/Mat4.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkTopology_T {
	XK_TOPOLOGY_POINT_LIST			= 0,
	XK_TOPOLOGY_LINE_LIST				= 1,
	XK_TOPOLOGY_LINE_STRIP			= 2,
  XK_TOPOLOGY_TRIANGLE_LIST		= 3,
  XK_TOPOLOGY_TRIANGLE_STRIP	= 4
} XkTopology;

typedef enum XkCullMode_T {
	XK_CULL_MODE_FRONT					= 0,
	XK_CULL_MODE_BACK						= 1,
	XK_CULL_MODE_FRONT_BACK			= 2
} XkCullMode;

typedef enum XkBufferUsage_T {
	XK_BUFFER_USAGE_VERTEX			= 0,
	XK_BUFFER_USAGE_INDEX				= 1,
	XK_BUFFER_USAGE_UNIFORM			= 2
} XkBufferUsage;

typedef enum XkTextureType_T {
	XK_TEXTURE_TYPE_1D					= 0,
	XK_TEXTURE_TYPE_2D					= 1,
	XK_TEXTURE_TYPE_3D					= 2
} XkTextureType;

typedef enum XkRendererApi_T {
	XK_RENDERER_API_DEFAULT			= 0,
	XK_RENDERER_API_VULKAN			= 1,
	XK_RENDERER_API_D3D12				= 2
} XkRendererApi;

typedef enum XkRendererHint_T {
	XK_RENDERER_HINT_DEPTH_TEST_BIT			= 0x0001,
	XK_RENDERER_HINT_STENCIL_TEST_BIT		= 0x0002,
	XK_RENDERER_HINT_SCISSOR_TEST_BIT		= 0x0004,
	XK_RENDERER_HINT_BLENDING_BIT				= 0x0008
} XkRendererHint;

typedef struct XkVertex_T {
	XkVec3 position;
	XkVec3 normal;
	XkVec2 uv;
} XkVertex;

typedef XkUInt32 XkIndex;

typedef struct XkUniformBufferObject_T {
	XkMat4 model;
  XkMat4 view;
  XkMat4 projection;
} XkUniformBufferObject;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

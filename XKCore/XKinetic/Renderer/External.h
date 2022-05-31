#pragma once

#include "XKinetic/XKCore.h"
#include "XKinetic/Math/Vec2.h"
#include "XKinetic/Math/Vec3.h"
#include "XKinetic/Math/Vec4.h"
#include "XKinetic/Math/Mat4.h"

typedef enum {
	XK_TOPOLOGY_POINT,
	XK_TOPOLOGY_LINE,
	XK_TOPOLOGY_FILL,
} XkTopology;

typedef enum {
	XK_CULL_MODE_FRONT,
	XK_CULL_MODE_BACK,
	XK_CULL_MODE_FRONT_BACK
} XkCullMode;

typedef struct {
	XkBool32 blending;
	XkBool32 depthTest;
	XkBool32 stencilTest;
	XkBool32 scissorTest;
} XkRendererConfig;

typedef struct {
	XkVec3 position;
	XkVec3 normal;
	XkVec2 uv;
} XkVertex;

typedef struct {
	XkMat4 model;
  XkMat4 view;
  XkMat4 projection;
} XkUniformBufferObject;

typedef XkUInt32 XkIndex;

#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Math/Vec3.h"
#include "XKinetic/Systems/ModelSystem.h"
#include "XKinetic/Systems/MaterialSystem.h"

#define XK_TAG_COMPONENT_MAX_SIZE 64

typedef XkUInt64 XkComponentID;

typedef enum {
  XK_TAG_COMPONENT          = 0,
  XK_ID_COMPONENT           = 1,
  XK_TRANSFORM_COMPONENT    = 2,
  XK_MESH_COMPONENT         = 3,
  XK_CAMERA_COMPONENT       = 4
} XkComponentType;

typedef struct {
  XkChar tag[XK_TAG_COMPONENT_MAX_SIZE];
} XkTagComponent;

typedef struct {
  XkComponentID id;
} XkIDComponent;

typedef struct {
  XkVec3 position;
  XkVec3 rotation;
  XkVec3 scale;
} XkTransformComponent;

typedef struct {
  XkModelID model;
  XkMaterialID material;
} XkMeshComponent;

typedef enum {
	XX_CAMERA_PROJECTION_ORTHOGRAPHICS  = 0,
	XX_CAMERA_PROJECTION_PERSPECTIVE    = 1,
} xkCameraProjection;

typedef struct {
  XkVec3 background;
	xkCameraProjection projection;
	XkFloat32 fov;
	XkFloat32 zNear;
	XkFloat32 zFar;
} XkCameraComponent;

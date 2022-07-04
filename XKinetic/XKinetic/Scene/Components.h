#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Math/Vec3.h"
#include "XKinetic/Systems/MeshSystem.h"
#include "XKinetic/Systems/MaterialSystem.h"

/* ########## MACROS SECTION ########## */
#define XK_TAG_COMPONENT_MAX_SIZE 64

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkUInt64 XkComponentId;

typedef enum XkComponentType_T {
  XK_TAG_COMPONENT          = 0,
  XK_ID_COMPONENT           = 1,
  XK_TRANSFORM_COMPONENT    = 2,
  XK_MESH_COMPONENT         = 3,
  XK_CAMERA_COMPONENT       = 4
} XkComponentType;

typedef struct XkTagComponent_T {
  XkChar tag[XK_TAG_COMPONENT_MAX_SIZE];
} XkTagComponent;

typedef struct XkIdComponent_T {
  XkComponentId id;
} XkIdComponent;

typedef struct XkTransformComponent_T {
  XkVec3 position;
  XkVec3 rotation;
  XkVec3 scale;
} XkTransformComponent;

typedef struct XkMeshComponent_T {
  XkMeshId model;
  XkMaterialId material;
} XkMeshComponent;

typedef enum XkCameraProjection_T {
	XX_CAMERA_PROJECTION_ORTHOGRAPHICS  = 0,
	XX_CAMERA_PROJECTION_PERSPECTIVE    = 1,
} XkCameraProjection;

typedef struct XkCameraComponent_T {
  XkVec3 background;
	XkCameraProjection projection;
	XkFloat32 fov;
	XkFloat32 zNear;
	XkFloat32 zFar;
} XkCameraComponent;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Math/Vec3.h"

#define XK_TAG_COMPONENT_MAX_SIZE 64

typedef XkSize XkComponentID;

typedef enum {
  XK_TAG_COMPONENT          = 0,
  XK_ID_COMPONENT           = 1,
  XK_TRANSFORM_COMPONENT    = 2
} XkComponentType;

typedef struct {
  XkChar8 tag[XK_TAG_COMPONENT_MAX_SIZE];
} XkTagComponent;

typedef struct {
  XkSize id;
} XkIDComponent;

typedef struct {
  XkVec3 position;
  XkVec3 rotation;
  XkVec3 scale;
} XkTransformComponent;

#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

typedef struct {
  XkSize vertexCount;
  XkHandle vertices;
  XkSize indexCount;
  XkHandle indices;
} XkModelConfig;

typedef struct XkModel* XkModel;

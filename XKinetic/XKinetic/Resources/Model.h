#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

typedef struct {
  XkSize vertexCount;
  XkHandle vertices;
  XkSize indexCount;
  XkHandle indices;
} XkModelConfig;

struct XkModel {

};

typedef struct XkModel* XkModel;

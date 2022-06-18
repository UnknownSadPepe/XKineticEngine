#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
  XkSize vertexCount;
  XkHandle vertices;
  XkSize indexCount;
  XkHandle indices;
} XkModelConfig;

#ifdef __cplusplus
}
#endif // __cplusplus

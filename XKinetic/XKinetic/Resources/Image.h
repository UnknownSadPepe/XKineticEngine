#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
  XkSize width;
  XkSize height;
  XkHandle pixels;
} XkImageConfig;

#ifdef __cplusplus
}
#endif // __cplusplus

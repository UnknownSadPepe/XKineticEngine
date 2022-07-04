#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkModelConfig_T {
  XkSize vertexCount;
  XkHandle vertices;
  XkSize indexCount;
  XkHandle indices;
} XkModelConfig;

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

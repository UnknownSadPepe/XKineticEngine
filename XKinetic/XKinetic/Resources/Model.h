#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/* ########## MACROS SECTION ########## */
#define XK_MODEL_NAME_MAX_SIZE 32

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkModelConfig_T {
	XkChar		name[XK_MODEL_NAME_MAX_SIZE];
  XkSize		vertexCount;
  XkHandle	vertices;
  XkSize		indexCount;
  XkHandle	indices;
} XkModelConfig;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

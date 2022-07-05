#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/* ########## MACROS SECTION ########## */
#define XK_SHARED_NAME_MAX_SIZE 32

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkShaderConfig_T {
	XkChar		name[XK_SHARED_NAME_MAX_SIZE];
  XkSize		size;
  XkHandle	code;
} XkShaderConfig;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

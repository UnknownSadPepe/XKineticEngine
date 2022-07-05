#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/* ########## MACROS SECTION ########## */
#define XK_IMAGE_NAME_MAX_SIZE 32

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkImageConfig_T {
	XkChar		name[XK_IMAGE_NAME_MAX_SIZE];
  XkSize    width;
  XkSize    height;
  XkHandle  pixels;
} XkImageConfig;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

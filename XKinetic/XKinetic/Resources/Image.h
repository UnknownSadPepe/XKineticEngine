#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkImageConfig_T {
  XkSize    width;
  XkSize    height;
  XkHandle  pixels;
} XkImageConfig;

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

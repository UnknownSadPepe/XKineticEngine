#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/* ########## MACROS SECTION ########## */
#define XK_MATERIAL_NAME_MAX_SIZE 128

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkMaterialConfig_T {
	XkChar name[XK_MATERIAL_NAME_MAX_SIZE];
} XkMaterialConfig;

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

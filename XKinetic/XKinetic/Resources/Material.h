#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

#define XK_MATERIAL_NAME_MAX_SIZE 128

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	XkChar name[XK_MATERIAL_NAME_MAX_SIZE];
} XkMaterialConfig;

#ifdef __cplusplus
}
#endif // __cplusplus

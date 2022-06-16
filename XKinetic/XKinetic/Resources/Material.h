#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

#define XK_MATERIAL_NAME_MAX_SIZE 128

typedef struct {
	XkChar name[XK_MATERIAL_NAME_MAX_SIZE];
} XkMaterialConfig;

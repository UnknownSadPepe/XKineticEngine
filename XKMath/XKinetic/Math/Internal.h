#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Math/Math.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
static XK_INLINE void __xkForceFEval(const XkFloat32 x) {
	volatile XkFloat32 y;
	y = x;
}

static XK_INLINE void __xkForceDEval(const XkFloat64 x) {
	volatile XkFloat64 y;
	y = x;
}

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKOpenXR.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Renderer/External.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern XKOPENXR_API XkResult 		xkOpenXRInitializeContext(const XkRendererApi);
extern XKOPENXR_API void 				xkOpenXRTerminateContext();

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus


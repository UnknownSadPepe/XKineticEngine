#pragma once

#include "XKinetic/XKCore.h"
#include <openxr/openxr.h>
#include "XKinetic/Core/Minimal.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	XkBool initialized;

	XrInstance xrInstance;
} __XkXRContext;

extern __XkXRContext _xkXRContext;

XK_EXPORT XkString __xkXRGetErrorString(XrResult); 

XK_EXPORT XkResult __xkXRInitializeContext(void);
XK_EXPORT void __xkXRTerminateContext(void);

XK_EXPORT XkResult __xkXRCreateInstance(void);
XK_EXPORT void __xkXRDestroyInstance(void);

#ifdef __cplusplus
}
#endif // __cplusplus

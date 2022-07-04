#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Scene/Scene.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XK_API void xkLoadScene(XkString);
XK_API void xkUnloadScene(XkString);

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

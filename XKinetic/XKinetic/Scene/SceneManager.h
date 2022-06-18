#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Scene/Scene.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XK_API void xkLoadScene(XkString);
XK_API void xkUnloadScene(XkString);

#ifdef __cplusplus
}
#endif // __cplusplus

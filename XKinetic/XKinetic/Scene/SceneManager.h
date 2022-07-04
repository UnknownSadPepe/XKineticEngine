#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Scene/Scene.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XK_API void xkLoadScene(XkString);
extern XK_API void xkUnloadScene(XkString);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

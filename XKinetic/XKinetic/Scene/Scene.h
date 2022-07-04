#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkScene* XkScene;

XK_API XkResult xkCreateScene(XkScene*);
XK_API void xkDestroyScene(XkScene);
XK_API void xkBeginScene(XkScene);
XK_API void xkEndScene(XkScene);

/// note: for using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

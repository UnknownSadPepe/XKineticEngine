#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

typedef struct XkScene* XkScene;

XK_API XkResult xkCreateScene(XkScene*);
XK_API void xkDestroyScene(XkScene);
XK_API void xkBeginScene(XkScene);
XK_API void xkEndScene(XkScene);

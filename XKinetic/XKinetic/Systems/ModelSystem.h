#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Model.h"

typedef XkInt32 XkModelID;

typedef struct XkModelSystem* XkModelSystem;

XK_API XkResult xkCreateModelSystem(XkModelSystem*);
XK_API void xkDestroyModelSystem(XkModelSystem);
XK_API XkModelID xkCreateModel(XkModelSystem, XkModelConfig* const);
XK_API void xkDestroyModel(XkModelSystem, XkModelID);

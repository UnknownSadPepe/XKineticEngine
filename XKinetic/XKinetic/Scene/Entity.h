#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Scene/Components.h"

typedef XkUInt64 XkEntityID;

typedef struct {
  XkEntityID id;
} XkEntity;

XK_API XkResult xkCreateEntity(XkEntity*);
XK_API void xkDestroyEntity(XkEntity*);
XK_API XkComponentID xkAddEntityComponent(XkEntity*, XkComponentType);
XK_API void xkRemoveEntityComponent(XkEntity*, XkComponentID);
XK_API void xkEntityHasComponent(XkEntity*, XkComponentType);

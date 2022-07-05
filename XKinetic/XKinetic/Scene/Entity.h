#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Scene/Components.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkUInt64 XkEntityId;

typedef struct XkEntity_T {
  XkEntityId id;
} XkEntity;

extern XK_API XkResult				xkCreateEntity(XkEntity*);
extern XK_API void						xkDestroyEntity(XkEntity*);

extern XK_API XkComponentId		xkAddEntityComponent(XkEntity*, const XkComponentType);
extern XK_API void						xkRemoveEntityComponent(XkEntity*, const XkComponentId);
extern XK_API void						xkEntityHasComponent(XkEntity*, const XkComponentType);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

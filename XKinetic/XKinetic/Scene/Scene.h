#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkScene_T* XkScene;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkCreateScene(XkScene*);
extern XK_API void				xkDestroyScene(XkScene);
extern XK_API void				xkBeginScene(XkScene);
extern XK_API void				xkEndScene(XkScene);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

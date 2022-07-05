#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Image.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkInitializeImageLoader(XkString);
extern XK_API void				xkTerminateImageLoader();
extern XK_API XkResult		xkLoadImage(XkImageConfig* const, XkString);
extern XK_API void				xkUnloadImage(const XkImageConfig* const);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

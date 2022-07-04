#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Image.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkImageLoader_T* XkImageLoader;

/* ########## FUNCTIONS SECTION ########## */
extern XK_API XkResult		xkCreateImageLoader(XkImageLoader*, XkString);
extern XK_API void				xkDestroyImageLoader(XkImageLoader);
extern XK_API XkResult		xkLoadImage(XkImageLoader, XkImageConfig* const, XkString);
extern XK_API void				xkUnloadImage(XkImageLoader, const XkImageConfig* const);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

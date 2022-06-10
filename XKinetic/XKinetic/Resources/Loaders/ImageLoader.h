#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Resources/Image.h"

typedef struct XkImageLoader* XkImageLoader;

XK_API XkResult xkCreateImageLoader(XkImageLoader*, XkChar8*);
XK_API void xkDestroyImageLoader(XkImageLoader);
XK_API XkResult xkLoadImage(XkImageLoader, XkImageConfig* const, XkChar8*);
XK_API void xkUnloadImage(XkImageLoader, XkImageConfig* const);

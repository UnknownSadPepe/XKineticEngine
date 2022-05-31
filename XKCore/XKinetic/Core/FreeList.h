#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkFreeList* XkFreeList;

XKCORE_API XkResult __xkCreateFreeList(XkFreeList*, const XkSize, XkSize);
XKCORE_API void xkDestroyFreeList(XkFreeList);

#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkFreeList* XkFreeList;

XKCORE_API XkResult xkCreateFreeList(XkFreeList*, const XkSize);
XKCORE_API void xkDestroyFreeList(XkFreeList);

XKCORE_API void xkResizeFreeList(XkFreeList, const XkSize);
XKCORE_API void xkClearFreeList(XkFreeList);

XKCORE_API XkHandle xkFreeListAllocate(XkFreeList, const XkSize);
XKCORE_API void xkFreeListFree(XkFreeList, XkHandle);

XKCORE_API XkSize xkFreeListLength(XkFreeList);
XKCORE_API XkSize xkFreeListCapacity(XkFreeList);


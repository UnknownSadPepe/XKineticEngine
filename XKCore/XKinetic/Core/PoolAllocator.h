#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkPoolAllocator* XkPoolAllocator;

XKCORE_API XkResult xkCreatePoolAllocator(XkPoolAllocator*, const XkSize, const XkSize);
XKCORE_API void xkDestroyPoolAllocator(XkPoolAllocator);
XKCORE_API XkHandle xkAllocatePoolMemory(XkPoolAllocator, const XkSize);
XKCORE_API void xkFreePoolMemory(XkPoolAllocator, const XkHandle);

#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkDynamicAllocator* XkDynamicAllocator;

XKCORE_API XkResult xkCreateDynamicAllocator(XkDynamicAllocator*, const XkSize);
XKCORE_API void xkDestroyDynamicAllocator(XkDynamicAllocator);
XKCORE_API XkHandle xkAllocateDynamicMemory(XkDynamicAllocator, const XkSize);
XKCORE_API void xkFreeDynamicMemory(XkDynamicAllocator, const XkHandle);

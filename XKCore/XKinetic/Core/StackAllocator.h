#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkStackAllocator* XkStackAllocator;

XKCORE_API XkResult xkCreateStackAllocator(XkStackAllocator*, const XkSize);
XKCORE_API void xkDestroyStackAllocator(XkStackAllocator);
XKCORE_API XkHandle xkAllocateStackMemory(XkStackAllocator, const XkSize);
XKCORE_API void xkFreeStackMemory(XkStackAllocator, XkHandle);

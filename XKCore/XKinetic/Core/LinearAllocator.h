#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkLinearAllocator* XkLinearAllocator; 

XKCORE_API XkResult xkCreateLinearAllocator(XkLinearAllocator*, const XkSize);
XKCORE_API void xkDestroyLinearAllocator(XkLinearAllocator);

XKCORE_API void xkClearLinearAllocator(XkLinearAllocator);
XKCORE_API void xkResizeLinearAllocator(XkLinearAllocator, const XkSize);

XKCORE_API XkHandle xkAllocateLinearMemory(XkLinearAllocator, const XkSize);

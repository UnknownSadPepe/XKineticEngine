#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkStackAllocator* XkStackAllocator;

XKCORE_API XkResult xkCreateStackAllocator(XkStackAllocator*, const XkSize);
XKCORE_API void xkDestroyStackAllocator(XkStackAllocator);

XKCORE_API void xkClearStackAllocator(XkStackAllocator);
XKCORE_API void xkResizeStackAllocator(XkStackAllocator, const XkSize);

XKCORE_API XkHandle xkAllocateStackMemory(XkStackAllocator, const XkSize);
XKCORE_API void xkFreeStackMemory(XkStackAllocator, XkHandle);

#ifdef __cplusplus
}
#endif // __cplusplus

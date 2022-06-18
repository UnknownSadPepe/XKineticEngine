#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct XkDynamicAllocator* XkDynamicAllocator;

XKCORE_API XkResult xkCreateDynamicAllocator(XkDynamicAllocator*, const XkSize);
XKCORE_API void xkDestroyDynamicAllocator(XkDynamicAllocator);

XKCORE_API void xkClearDynamicAllocator(XkDynamicAllocator);
XKCORE_API void xkResizeDynamicAllocator(XkDynamicAllocator, const XkSize);

XKCORE_API XkHandle xkAllocateDynamicMemory(XkDynamicAllocator, const XkSize);
XKCORE_API void xkFreeDynamicMemory(XkDynamicAllocator, const XkHandle);

#ifdef __cplusplus
}
#endif // __cplusplus

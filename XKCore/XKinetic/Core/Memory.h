#pragma once

#include "XKinetic/XKCore.h"

typedef struct {
	XkHandle memory;
	XkSize size;
} XkMemoryHeader;

typedef struct XkLinearAllocator* XkLinearAllocator; 
typedef struct XkStackAllocator* XkStackAllocator; 
typedef struct XkDynamicAllocator* XkDynamicAllocator;
typedef struct XkPoolAllocator* XkPoolAllocator;

static const XkSize _xkAlign = 16;

XK_API_EXPORT XkResult xkMemoryInitialize(void);
XK_API_EXPORT void xkMemoryTerminate(void);

XKCORE_API XkHandle xkAllocateMemory(const XkSize);
XKCORE_API XkHandle xkReallocateMemory(const XkHandle, const XkSize);
XKCORE_API void xkFreeMemory(const XkHandle);

XKCORE_API XkHandle xkCopyMemory(XkHandle, const XkHandle, const XkSize);
XKCORE_API XkHandle xkMoveMemory(XkHandle, const XkHandle, const XkSize);
XKCORE_API XkHandle xkZeroMemory(XkHandle, const XkSize);

XKCORE_API XkResult xkCreateLinearAllocator(XkLinearAllocator*, const XkSize);
XKCORE_API void xkDestroyLinearAllocator(XkLinearAllocator);
XKCORE_API XkHandle xkAllocateLinearMemory(XkLinearAllocator, const XkSize);
XKCORE_API void xkFreeLinearMemory(XkLinearAllocator);

XKCORE_API XkResult xkCreateStackAllocator(XkStackAllocator*, const XkSize);
XKCORE_API void xkDestroyStackAllocator(XkStackAllocator);
XKCORE_API XkHandle xkAllocateStackMemory(XkStackAllocator, const XkSize);
XKCORE_API void xkFreeStackMemory(XkStackAllocator, XkHandle);

XKCORE_API XkResult xkCreateDynamicAllocator(XkDynamicAllocator*, const XkSize);
XKCORE_API void xkDestroyDynamicAllocator(XkDynamicAllocator);
XKCORE_API XkHandle xkAllocateDynamicMemory(XkDynamicAllocator, const XkSize);
XKCORE_API void xkFreeDynamicMemory(XkDynamicAllocator, const XkHandle);

XKCORE_API XkResult xkCreatePoolAllocator(XkPoolAllocator*, const XkSize, const XkSize);
XKCORE_API void xkDestroyPoolAllocator(XkPoolAllocator);
XKCORE_API XkHandle xkAllocatePoolMemory(XkPoolAllocator, const XkSize);
XKCORE_API void xkFreePoolMemory(XkPoolAllocator, const XkHandle);

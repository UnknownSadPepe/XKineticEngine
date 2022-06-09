#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkPoolAllocator* XkPoolAllocator;

XKCORE_API XkResult __xkCreatePoolAllocator(XkPoolAllocator*, const XkSize, const XkSize);
#define xkCreatePoolAllocator(allocator, totalChunkCount, chunkType) __xkCreatePoolAllocator(allocator, totalChunkCount, sizeof(chunkType))

XKCORE_API void xkClearPoolAllocator(XkPoolAllocator);
XKCORE_API void xkResizePoolAllocator(XkPoolAllocator, const XkSize);

XKCORE_API void xkDestroyPoolAllocator(XkPoolAllocator);
XKCORE_API XkHandle xkAllocatePoolMemory(XkPoolAllocator, const XkSize);
XKCORE_API void xkFreePoolMemory(XkPoolAllocator, const XkHandle);

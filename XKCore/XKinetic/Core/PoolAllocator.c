#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/FreeList.h"
#include "XKinetic/Core/PoolAllocator.h"

struct XkPoolAllocator {
	XkSize totalChunkCount;
	XkSize chunkSize;
	XkSize allocatedChunkCount;

	XkFreeList freelist;
};

static const XkSize XK_POOL_ALLOCATOR_ALIGN = 16;

#define XK_POOL_ALLOCATOR_REALLOCATE_COEFFICIENT 2

XkResult __xkCreatePoolAllocator(XkPoolAllocator* pAllocator, const XkSize totalChunkCount, const XkSize chunkSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkPoolAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkPoolAllocator allocator = *pAllocator;

	const XkSize alignChunkSize = (chunkSize + (XK_POOL_ALLOCATOR_ALIGN - 1)) & ~(XK_POOL_ALLOCATOR_ALIGN - 1);
	const XkSize alignTotalSize = ((totalChunkCount * alignChunkSize) + (alignChunkSize - 1)) & ~ (alignChunkSize - 1);

	allocator->totalChunkCount = totalChunkCount;
	allocator->chunkSize = alignChunkSize;
	allocator->allocatedChunkCount = 0;
	result = xkCreateFreeList(&allocator->freelist, alignTotalSize);
	if(result != XK_SUCCESS) goto _catch;	

_catch:
	return(result);
}

void xkDestroyPoolAllocator(XkPoolAllocator allocator) {
	xkDestroyFreeList(allocator->freelist);
	xkFreeMemory(allocator);
}

void xkClearPoolAllocator(XkPoolAllocator allocator) {
	allocator->allocatedChunkCount = 0;
	xkClearFreeList(allocator->freelist);
}

void xkResizePoolAllocator(XkPoolAllocator allocator, const XkSize newChunkCount) {
	const XkSize alignNewSize = ((newChunkCount * allocator->chunkSize) + (allocator->chunkSize - 1)) & ~(allocator->chunkSize - 1);

	allocator->totalChunkCount = newChunkCount;
	xkResizeFreeList(allocator->freelist, alignNewSize);
}

XkHandle xkAllocatePoolMemory(XkPoolAllocator allocator, const XkSize chunkCount) {
	if((allocator->allocatedChunkCount + chunkCount) > allocator->totalChunkCount) {
		xkResizePoolAllocator(allocator, allocator->totalChunkCount * XK_POOL_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	++allocator->allocatedChunkCount;
	return(xkFreeListAllocate(allocator->freelist, allocator->chunkSize * chunkCount));
}

void xkFreePoolMemory(XkPoolAllocator allocator, const XkHandle memory) {
	xkFreeListFree(allocator->freelist, memory);
}

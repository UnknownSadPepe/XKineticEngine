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

	// Allocate pool allocator.
	*pAllocator = xkAllocateMemory(sizeof(struct XkPoolAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template pool allocator.
	XkPoolAllocator allocator = *pAllocator;

	// Align chunk size with pool allocator alignment.
	const XkSize alignChunkSize = (chunkSize + (XK_POOL_ALLOCATOR_ALIGN - 1)) & ~(XK_POOL_ALLOCATOR_ALIGN - 1);

	// Initialize poll allocator total size.
	const XkSize totalSize = totalChunkCount * alignChunkSize;

	// Align total size with align chunk size.
	const XkSize alignTotalSize = (totalSize + (alignChunkSize - 1)) & ~ (alignChunkSize - 1);

	// Initialize pool allocator.
	allocator->totalChunkCount			= totalChunkCount;
	allocator->chunkSize						= alignChunkSize;
	allocator->allocatedChunkCount	= 0;

	// Create free list.
	result = xkCreateFreeList(&allocator->freelist, alignTotalSize);
	if(result != XK_SUCCESS) goto _catch;	

_catch:
	return(result);
}

void xkDestroyPoolAllocator(XkPoolAllocator allocator) {
	// Destroy free list.
	xkDestroyFreeList(allocator->freelist);

	// Free pool allocator.
	xkFreeMemory(allocator);
}

void xkClearPoolAllocator(XkPoolAllocator allocator) {
	// Null pool allocator allocated chunk count.
	allocator->allocatedChunkCount = 0;

	// Clear free list.
	xkClearFreeList(allocator->freelist);
}

void xkResizePoolAllocator(XkPoolAllocator allocator, const XkSize newChunkCount) {
	// Align new total size with pool allocator chunk size.
	const XkSize alignNewTotalSize = ((newChunkCount * allocator->chunkSize) + (allocator->chunkSize - 1)) & ~(allocator->chunkSize - 1);

	// Initialize pool allocator.
	allocator->totalChunkCount = newChunkCount;

	// Resize free list.
	xkResizeFreeList(allocator->freelist, alignNewTotalSize);
}

XkHandle xkAllocatePoolMemory(XkPoolAllocator allocator, const XkSize chunkCount) {
	// Check if there is not enough space in pool allocator.
	if((allocator->allocatedChunkCount + chunkCount) > allocator->totalChunkCount) {
		// Resize pool allocator.
		xkResizePoolAllocator(allocator, allocator->totalChunkCount * XK_POOL_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	// Increment pool allocator.
	++allocator->allocatedChunkCount;

	// Allocator free list memory.
	XkHandle newMemory = xkFreeListAllocate(allocator->freelist, allocator->chunkSize * chunkCount);

	return(newMemory);
}

void xkFreePoolMemory(XkPoolAllocator allocator, const XkHandle memory) {
	// Free free list memory.
	xkFreeListFree(allocator->freelist, memory);
}

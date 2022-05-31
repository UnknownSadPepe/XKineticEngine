#include "XKinetic/Core/Memory.h"

struct XkPoolAllocator {
	XkSize totalChunkCount;
	XkSize chunkSize;
	XkSize allocatedChunkCount;

	XkHandle memory;
};

XkResult xkCreatePoolAllocator(XkPoolAllocator* pAllocator, const XkSize totalChunkCount, const XkSize chunkSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkPoolAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkPoolAllocator allocator = *pAllocator;

	const XkSize alignChunkSize = (chunkSize + (_xkAlign - 1)) & ~ (_xkAlign - 1);
	const XkSize alignTotalSize = ((totalChunkCount * alignChunkSize) + (alignChunkSize - 1)) & ~ (alignChunkSize - 1);

	allocator->totalChunkCount = totalChunkCount;
	allocator->chunkSize = alignChunkSize;
	allocator->allocatedChunkCount = 0;
	allocator->memory = xkAllocateMemory(alignTotalSize);
	if(!allocator->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	

_catch:
	return(result);
}

void xkDestroyPoolAllocator(XkPoolAllocator allocator) {
	allocator->totalChunkCount = 0;
	allocator->chunkSize = 0;
	allocator->allocatedChunkCount = 0;
	xkFreeMemory(allocator->memory);
	allocator->memory = XK_NULL;
	xkFreeMemory(allocator);
}

XkHandle xkAllocatePoolMemory(XkPoolAllocator allocator, const XkSize chunkCount) {
	if((allocator->allocatedChunkCount + chunkCount) > allocator->totalChunkCount) {
		return(XK_NULL);
	}

	allocator->allocatedChunkCount += chunkCount;
 	XkHandle newMemory = allocator->memory + ((allocator->allocatedChunkCount + chunkCount) * allocator->chunkSize);
	return(newMemory);
}

void xkFreePoolMemory(XkPoolAllocator allocator, const XkHandle memory) {
	// TODO: implementation.

	allocator->allocatedChunkCount--;
	xkZeroMemory(memory, allocator->chunkSize);
}

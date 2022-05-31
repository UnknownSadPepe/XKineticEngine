#include "XKinetic/Core/Memory.h"

struct XkStackAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

XkResult xkCreateStackAllocator(XkStackAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkStackAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkStackAllocator allocator = *pAllocator;

	const XkSize alignTotalSize = (totalSize + (_xkAlign - 1)) & ~ (_xkAlign - 1);

	allocator->totalSize = alignTotalSize;
	allocator->allocated = 0;
	allocator->memory = xkAllocateMemory(alignTotalSize);
	if(!allocator->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	

_catch:
	return(result);
}

void xkDestroyStackAllocator(XkStackAllocator allocator) {
	allocator->totalSize = 0;
	allocator->allocated = 0;
	xkFreeMemory(allocator->memory);
	allocator->memory = XK_NULL;
	xkFreeMemory(allocator);
}

XkHandle xkAllocateStackMemory(XkStackAllocator allocator, const XkSize size) {
	const XkSize headerSize = (size + sizeof(XkMemoryHeader) + (_xkAlign - 1)) & ~ (_xkAlign - 1);

	if((allocator->allocated + headerSize) > allocator->totalSize) {
		return(XK_NULL);
	}

	allocator->allocated += headerSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + headerSize);
	return(newMemory);
}

void xkFreeStackMemory(XkStackAllocator allocator, const XkHandle memory) {
	XkMemoryHeader* pHeader = (XkMemoryHeader*)(((XkChar8*)memory) - sizeof(XkMemoryHeader));

	allocator->allocated -= pHeader->size;
	xkZeroMemory(pHeader->memory, pHeader->size);	
}

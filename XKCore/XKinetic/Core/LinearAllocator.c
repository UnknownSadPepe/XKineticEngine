#include "XKinetic/Core/Memory.h"

struct XkLinearAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

XkResult xkCreateLinearAllocator(XkLinearAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkLinearAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkLinearAllocator allocator = *pAllocator;

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

void xkDestroyLinearAllocator(XkLinearAllocator allocator) {
	allocator->totalSize = 0;
	allocator->allocated = 0;
	xkFreeMemory(allocator->memory);
	allocator->memory = XK_NULL;
	xkFreeMemory(allocator);
}

XkHandle xkAllocateLinearMemory(XkLinearAllocator allocator, const XkSize size) {
	const XkSize alignSize = (size + (_xkAlign - 1)) & ~ (_xkAlign - 1);

	if((allocator->allocated + alignSize) > allocator->totalSize) {
		return(XK_NULL);
	}

	allocator->allocated += alignSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + alignSize);
	return(newMemory);
}

void xkFreeLinearMemory(XkLinearAllocator allocator) {
	allocator->allocated = 0;
	xkZeroMemory(allocator->memory, allocator->totalSize);	
}

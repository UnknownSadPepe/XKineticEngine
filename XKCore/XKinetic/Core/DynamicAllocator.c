#include "XKinetic/Core/Memory.h"

struct XkDynamicAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

#define XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT 2

XkResult xkCreateDynamicAllocator(XkDynamicAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkDynamicAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDynamicAllocator allocator = *pAllocator;	

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

void xkDestroyDynamicAllocator(XkDynamicAllocator allocator) {
	allocator->totalSize = 0;
	allocator->allocated = 0;
	xkFreeMemory(allocator->memory);
	allocator->memory = XK_NULL;
	xkFreeMemory(allocator);
}

XkHandle xkAllocateDynamicMemory(XkDynamicAllocator allocator, const XkSize size) {
	const XkSize headerSize = (size + sizeof(XkMemoryHeader) + (_xkAlign - 1)) & ~ (_xkAlign - 1);

	if((allocator->allocated + headerSize) > allocator->totalSize) {
		allocator->totalSize *= XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT;
		allocator->memory = xkReallocateMemory(allocator->memory, allocator->totalSize);
		if(!allocator->memory) {
			return(XK_NULL);
		}
	}

	allocator->allocated += headerSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + headerSize);	

	XkMemoryHeader* pHeader = (XkMemoryHeader*)newMemory;
	pHeader->size = headerSize;
	pHeader->memory = newMemory;

	return(newMemory + sizeof(XkMemoryHeader));
}

void xkFreeDynamicMemory(XkDynamicAllocator allocator, const XkHandle memory) {
	XkMemoryHeader* pHeader = (XkMemoryHeader*)(((XkChar8*)memory) - sizeof(XkMemoryHeader));

	allocator->allocated = 0;
	xkZeroMemory(pHeader->memory, pHeader->size);
}

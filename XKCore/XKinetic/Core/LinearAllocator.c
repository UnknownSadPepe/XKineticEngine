#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/LinearAllocator.h"

struct XkLinearAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

#define XK_LINEAR_ALLOCATOR_ALIGN 16

XkResult xkCreateLinearAllocator(XkLinearAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkLinearAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkLinearAllocator allocator = *pAllocator;

	const XkSize alignTotalSize = (totalSize + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

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
	allocator->memory = XK_NULL_HANDLE;
	xkFreeMemory(allocator);
}

XkHandle xkAllocateLinearMemory(XkLinearAllocator allocator, const XkSize size) {
	const XkSize alignSize = (size + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	if((allocator->allocated + alignSize) > allocator->totalSize) {
		return(XK_NULL_HANDLE);
	}

	allocator->allocated += alignSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + alignSize);
	return(newMemory);
}

void xkFreeLinearMemory(XkLinearAllocator allocator) {
	allocator->allocated = 0;
	xkZeroMemory(allocator->memory, allocator->totalSize);	
}

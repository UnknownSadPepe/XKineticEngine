#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/LinearAllocator.h"

#include "XKinetic/Core/Log.h"

struct XkLinearAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

static const XkSize XK_LINEAR_ALLOCATOR_ALIGN = 16;

#define XK_LINEAR_ALLOCATOR_REALLOCATE_COEFFICIENT 2

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
	xkFreeMemory(allocator->memory);
	xkFreeMemory(allocator);
}

void xkClearLinearAllocator(XkLinearAllocator allocator) {
	allocator->allocated = 0;
	xkZeroMemory(allocator->memory, allocator->totalSize);	
}

void xkResizeLinearAllocator(XkLinearAllocator allocator, const XkSize newSize) {
	const XkSize alignNewSize = (newSize + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	allocator->totalSize = alignNewSize;
	allocator->memory = xkReallocateMemory(allocator->memory, alignNewSize);
}

XkHandle xkAllocateLinearMemory(XkLinearAllocator allocator, const XkSize size) {
	const XkSize alignSize = (size + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	if((allocator->allocated + alignSize) > allocator->totalSize) {
		xkResizeLinearAllocator(allocator, allocator->totalSize * XK_LINEAR_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	allocator->allocated += alignSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + alignSize);
	return(newMemory);
}


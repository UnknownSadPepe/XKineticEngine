#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/LinearAllocator.h"

#include "XKinetic/Core/Log.h"

struct XkLinearAllocator {
	XkSize size;
	XkSize totalSize;

	XkHandle memory;
};

static const XkSize XK_LINEAR_ALLOCATOR_ALIGN = 16;

#define XK_LINEAR_ALLOCATOR_REALLOCATE_COEFFICIENT 2

XkResult xkCreateLinearAllocator(XkLinearAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	// Allocate linear allocator.
	*pAllocator = xkAllocateMemory(sizeof(struct XkLinearAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template lineara allocator.
	XkLinearAllocator allocator = *pAllocator;

	// Align total size with linear allocator alignment.
	const XkSize alignTotalSize = (totalSize + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	// Initialize linear allocator.
	allocator->size = 0;
	allocator->totalSize = alignTotalSize;

	// Allocate linear allocator memory.
	allocator->memory = xkAllocateMemory(alignTotalSize);
	if(!allocator->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

_catch:
	return(result);
}

void xkDestroyLinearAllocator(XkLinearAllocator allocator) {
	// Free linear allocator memory.
	xkFreeMemory(allocator->memory);

	// Free linear allocator.
	xkFreeMemory(allocator);
}

void xkClearLinearAllocator(XkLinearAllocator allocator) {
	// Null linear allocator allocate size.
	allocator->size = 0;

	// Zero linear allocator memory.
	xkZeroMemory(allocator->memory, allocator->totalSize);	
}

void xkResizeLinearAllocator(XkLinearAllocator allocator, const XkSize newTotalSize) {
	// Align new total size with linear allocator stride.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	// Initialize linear allocator.
	allocator->totalSize = alignNewTotalSize;

	// Reallocate linear allocator memory.
	allocator->memory = xkReallocateMemory(allocator->memory, alignNewTotalSize);
}

XkHandle xkAllocateLinearMemory(XkLinearAllocator allocator, const XkSize size) {
	// Align allocate size with linear allocator stride.
	const XkSize alignSize = (size + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	// Check if there is not enough space in linear allocator.
	if((allocator->size + alignSize) > allocator->totalSize) {
		// Resize linear allocator.
		xkResizeLinearAllocator(allocator, allocator->totalSize * XK_LINEAR_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	// Increment linear allocator allocated size.
	allocator->size += alignSize;

	// Select new linear allocator allocated  memory.
 	XkHandle newMemory = (XkUInt8*)allocator->memory + (allocator->size + alignSize);

	return(newMemory);
}


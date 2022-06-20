#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/FreeList.h"
#include "XKinetic/Core/DynamicAllocator.h"

struct XkDynamicAllocator {
	XkFreeList freelist;
};

static const XkSize XK_DYNAMIC_ALLOCATOR_ALIGN = 16;

#define XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT 2

XkResult xkCreateDynamicAllocator(XkDynamicAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	// Allocate dynamic allocator.
	*pAllocator = xkAllocateMemory(sizeof(struct XkDynamicAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template dynammic allocator.
	XkDynamicAllocator allocator = *pAllocator;	

	// Align total size with dynamic allocator alignment.
	const XkSize alignTotalSize = (totalSize + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	// Create free list.
	result = xkCreateFreeList(&allocator->freelist, alignTotalSize);
	if(result != XK_SUCCESS) goto _catch;	

_catch:
	return(result);
}

void xkDestroyDynamicAllocator(XkDynamicAllocator allocator) {
	// Destroy free list.
	xkDestroyFreeList(allocator->freelist);

	// Free dynamic allocator.
	xkFreeMemory(allocator);
}

void xkClearDynamicAllocator(XkDynamicAllocator allocator) {
	// Clear free list.
	xkClearFreeList(allocator->freelist);
}

void xkResizeDynamicAllocator(XkDynamicAllocator allocator, const XkSize newTotalSize) {
	// Align new total size with dynamic allocator alignment.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	// Resize free list.
	xkResizeFreeList(allocator->freelist, alignNewTotalSize);
}

XkHandle xkAllocateDynamicMemory(XkDynamicAllocator allocator, const XkSize size) {
	// Allocate free list memory.
	XkHandle newMemory = xkFreeListAllocate(allocator->freelist, size);

	return(newMemory);
}

void xkFreeDynamicMemory(XkDynamicAllocator allocator, const XkHandle memory) {
	// Free free list memory.
	xkFreeListFree(allocator->freelist, memory);
}

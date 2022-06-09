#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/FreeList.h"
#include "XKinetic/Core/DynamicAllocator.h"

struct XkDynamicAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkFreeList freelist;
};

static const XkSize XK_DYNAMIC_ALLOCATOR_ALIGN = 16;

#define XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT 2

XkResult xkCreateDynamicAllocator(XkDynamicAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkDynamicAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDynamicAllocator allocator = *pAllocator;	

	const XkSize alignTotalSize = (totalSize + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	allocator->totalSize = alignTotalSize;
	allocator->allocated = 0;
	result = xkCreateFreeList(&allocator->freelist, alignTotalSize);
	if(result != XK_SUCCESS) goto _catch;	

_catch:
	return(result);
}

void xkDestroyDynamicAllocator(XkDynamicAllocator allocator) {
	xkDestroyFreeList(allocator->freelist);
	xkFreeMemory(allocator);
}

void xkClearDynamicAllocator(XkDynamicAllocator allocator) {
	allocator->allocated = 0;
	xkClearFreeList(allocator->freelist);
}

void xkResizeDynamicAllocator(XkDynamicAllocator allocator, const XkSize newSize) {
	const XkSize alignNewSize = (newSize + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	allocator->totalSize = alignNewSize;
	xkResizeFreeList(allocator->freelist, alignNewSize);
}

XkHandle xkAllocateDynamicMemory(XkDynamicAllocator allocator, const XkSize size) {
	if((allocator->allocated + size) > allocator->totalSize) {
		xkResizeDynamicAllocator(allocator, allocator->totalSize * XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	allocator->allocated += size;
	return(xkFreeListAllocate(allocator->freelist, size));
}

void xkFreeDynamicMemory(XkDynamicAllocator allocator, const XkHandle memory) {
	xkFreeListFree(allocator->freelist, memory);
}

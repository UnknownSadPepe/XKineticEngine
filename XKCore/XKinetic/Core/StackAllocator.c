#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/StackAllocator.h"

struct XkStackAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

typedef struct {
	XkSize size;
	XkHandle memory;
} XkStackMemoryHeader;

static const XkSize XK_STACK_ALLOCATOR_ALIGN = 16;

#define XK_STACK_ALLOCATOR_REALLOCATE_COEFFICIENT 2

XkResult xkCreateStackAllocator(XkStackAllocator* pAllocator, const XkSize totalSize) {
	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkStackAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkStackAllocator allocator = *pAllocator;

	const XkSize alignTotalSize = (totalSize + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

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
	xkFreeMemory(allocator->memory);
	xkFreeMemory(allocator);
}

void xkClearStackAllocator(XkStackAllocator allocator) {
	allocator->allocated = 0;
	xkZeroMemory(allocator->memory, allocator->totalSize);
}

void xkResizeStackAllocator(XkStackAllocator allocator, const XkSize newSize) {
	const XkSize alignNewSize = (newSize + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	allocator->totalSize = alignNewSize;
	allocator->memory = xkReallocateMemory(allocator->memory, alignNewSize);
}

XkHandle xkAllocateStackMemory(XkStackAllocator allocator, const XkSize size) {
	const XkSize headerSize = (size + sizeof(XkStackMemoryHeader) + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	if((allocator->allocated + headerSize) > allocator->totalSize) {
		xkResizeStackAllocator(allocator, allocator->totalSize * XK_STACK_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	allocator->allocated += headerSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + headerSize);
	return(newMemory);
}

void xkFreeStackMemory(XkStackAllocator allocator, const XkHandle memory) {
	XkStackMemoryHeader* pHeader = (XkStackMemoryHeader*)(((XkChar8*)memory) - sizeof(XkStackMemoryHeader));

	allocator->allocated -= pHeader->size;
	xkZeroMemory(pHeader->memory, pHeader->size);	
}

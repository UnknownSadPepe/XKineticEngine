#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/StackAllocator.h"

struct XkStackAllocator {
	XkSize size;
	XkSize totalSize;

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

	// Allocate stack allocator.
	*pAllocator = xkAllocateMemory(sizeof(struct XkStackAllocator));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template stack allocator.
	XkStackAllocator allocator = *pAllocator;

	// Align total size with stack allocator alignment.
	const XkSize alignTotalSize = (totalSize + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	// Initialize stack allocator.
	allocator->size = 0;
	allocator->totalSize = alignTotalSize;

	// Allocate stack allocator memory.
	allocator->memory = xkAllocateMemory(alignTotalSize);
	if(!allocator->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

_catch:
	return(result);
}

void xkDestroyStackAllocator(XkStackAllocator allocator) {
	// Free stack allocator memory.
	xkFreeMemory(allocator->memory);

	// Free stack allocator.
	xkFreeMemory(allocator);
}

void xkClearStackAllocator(XkStackAllocator allocator) {
	// Null stack allocator allocated size.
	allocator->size = 0;

	// Zero stack allocator array memory.
	xkZeroMemory(allocator->memory, allocator->totalSize);
}

void xkResizeStackAllocator(XkStackAllocator allocator, const XkSize newTotalSize) {
	// Align new total size with stack allocator alignment.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	// Initialize stack allocator.
	allocator->totalSize = alignNewTotalSize;

	// Reallocate stack allocator memory.
	allocator->memory = xkReallocateMemory(allocator->memory, alignNewTotalSize);
}

XkHandle xkAllocateStackMemory(XkStackAllocator allocator, const XkSize size) {
	// Align allocated size with stack allocator alignment.
	const XkSize alignSize = (size + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	// Initialize allocate size with header. 
	const XkSize headerSize = alignSize + sizeof(XkStackMemoryHeader);

	// Check if there is not enough space in stack allocator.
	if((allocator->size + headerSize) > allocator->totalSize) {
		// Resize stack allocator.
		xkResizeStackAllocator(allocator, allocator->totalSize * XK_STACK_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	// Initialize stack allocator header.
	XkStackMemoryHeader* pHeader = (XkStackMemoryHeader*)(((XkUInt8*)allocator->memory + allocator->size));

	// Select new stack allocator allocated memory.
	pHeader->memory = (XkUInt8*)pHeader + headerSize;
	pHeader->size = alignSize;

	// Increment stack allocator allocated size.
	allocator->size += headerSize;

	return(pHeader->memory);
}

void xkFreeStackMemory(XkStackAllocator allocator, const XkHandle memory) {
	// Initialize stack allocator header.
	XkStackMemoryHeader* pHeader = (XkStackMemoryHeader*)((XkUInt8*)memory - sizeof(XkStackMemoryHeader));

	// Initialize allocate size with header. 
	const XkSize headerSize = pHeader->size + sizeof(XkStackMemoryHeader);

	// Decrement stack allocator allocated size with header.
	allocator->size -= headerSize;

	// Zero memory with header.
	xkZeroMemory((XkHandle)pHeader, headerSize);
}

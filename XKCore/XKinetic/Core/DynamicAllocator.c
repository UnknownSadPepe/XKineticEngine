#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/DynamicAllocator.h"

struct XkDynamicAllocator {
	XkSize totalSize;
	XkSize allocated;

	XkHandle memory;
};

typedef struct {
	XkSize size;
	XkHandle memory;
} XkDynamicMemoryHeader;

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
	allocator->memory = XK_NULL_HANDLE;
	xkFreeMemory(allocator);
}

XkHandle xkAllocateDynamicMemory(XkDynamicAllocator allocator, const XkSize size) {
	const XkSize headerSize = (size + sizeof(XkDynamicMemoryHeader) + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	if((allocator->allocated + headerSize) > allocator->totalSize) {
		allocator->totalSize *= XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT;
		allocator->memory = xkReallocateMemory(allocator->memory, allocator->totalSize);
		if(!allocator->memory) {
			return(XK_NULL_HANDLE);
		}
	}

	allocator->allocated += headerSize;
 	XkHandle newMemory = allocator->memory + (allocator->allocated + headerSize);	

	XkDynamicMemoryHeader* pHeader = (XkDynamicMemoryHeader*)newMemory;
	pHeader->size = headerSize;
	pHeader->memory = newMemory;

	return(newMemory + sizeof(XkDynamicMemoryHeader));
}

void xkFreeDynamicMemory(XkDynamicAllocator allocator, const XkHandle memory) {
	XkDynamicMemoryHeader* pHeader = (XkDynamicMemoryHeader*)(((XkChar8*)memory) - sizeof(XkDynamicMemoryHeader));

	allocator->allocated = 0;
	xkZeroMemory(pHeader->memory, pHeader->size);
}

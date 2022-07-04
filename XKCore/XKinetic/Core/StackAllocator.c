/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/StackAllocator.h"

/* ########## MACROS SECTION ########## */
#define XK_STACK_ALLOCATOR_REALLOCATE_COEFFICIENT 2

/* ########## TYPES SECTION ########## */
struct XkStackAllocator_T {
	XkSize size;
	XkSize totalSize;

	XkHandle memory;
};

typedef struct XkStackMemoryHeader_T {
	XkSize size;
	XkHandle memory;
} XkStackMemoryHeader;

/* ########## GLOBAL VARIABLES SECTION ########## */
static const XkSize XK_STACK_ALLOCATOR_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateStackAllocator(XkStackAllocator* pAllocator, const XkSize totalSize) {
	xkAssert(pAllocator);
	xkAssert(totalSize > 0);

	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkStackAllocator_T));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkStackAllocator allocator = *pAllocator;

	// Align total size with stack allocator alignment for better performance and minimal fragmentation.
	const XkSize alignTotalSize = (totalSize + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	allocator->size 			= 0;
	allocator->totalSize 	= alignTotalSize;
	allocator->memory 		= xkAllocateMemory(alignTotalSize);
	if(!allocator->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _free;
	}

_catch:
	return(result);

_free:
	if(allocator) {
		xkFreeMemory(allocator);
	}

	goto _catch;
}

void xkDestroyStackAllocator(XkStackAllocator allocator) {
	xkAssert(allocator);

	xkFreeMemory(allocator->memory);

	xkFreeMemory(allocator);
}

void xkClearStackAllocator(XkStackAllocator allocator) {
	xkAssert(allocator);

	allocator->size = 0;

	xkZeroMemory(allocator->memory, allocator->totalSize);
}

void xkResizeStackAllocator(XkStackAllocator allocator, const XkSize newTotalSize) {
	xkAssert(allocator);
	xkAssert(newTotalSize > 0 && newTotalSize > allocator->totalSize);

	// Align new total size with stack allocator alignment for better performance and minimal fragmentation.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	allocator->totalSize 	= alignNewTotalSize;
	allocator->memory 		= xkReallocateMemory(allocator->memory, alignNewTotalSize);
}

XkHandle xkAllocateStackMemory(XkStackAllocator allocator, const XkSize size) {
	xkAssert(allocator);

	// Align allocated size with stack allocator alignment for better performance and minimal fragmentation.
	const XkSize alignSize = (size + (XK_STACK_ALLOCATOR_ALIGN - 1)) & ~(XK_STACK_ALLOCATOR_ALIGN - 1);

	const XkSize headerSize = alignSize + sizeof(XkStackMemoryHeader);

	if((allocator->size + headerSize) > allocator->totalSize) {
		xkResizeStackAllocator(allocator, allocator->totalSize * XK_STACK_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	XkStackMemoryHeader* pHeader = (XkStackMemoryHeader*)(((XkUInt8*)allocator->memory + allocator->size));

	pHeader->memory = (XkUInt8*)pHeader + headerSize;
	pHeader->size 	= alignSize;

	allocator->size += headerSize;

	return(pHeader->memory);
}

void xkFreeStackMemory(XkStackAllocator allocator, const XkHandle data) {
	xkAssert(allocator);
	xkAssert(data);

	XkStackMemoryHeader* pHeader = (XkStackMemoryHeader*)((XkUInt8*)data - sizeof(XkStackMemoryHeader));
 
	const XkSize headerSize = pHeader->size + sizeof(XkStackMemoryHeader);

	allocator->size -= headerSize;

	xkZeroMemory((XkHandle)pHeader, headerSize);
}

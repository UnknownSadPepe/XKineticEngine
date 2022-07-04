/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/LinearAllocator.h"

/* ########## MACROS SECTION ########## */
#define XK_LINEAR_ALLOCATOR_REALLOCATE_COEFFICIENT 2

/* ########## TYPES SECTION ########## */
struct XkLinearAllocator_T {
	XkSize size;
	XkSize totalSize;

	XkHandle memory;
};

/* ########## GLOBAL VARIABLES SECTION ########## */
static const XkSize XK_LINEAR_ALLOCATOR_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateLinearAllocator(XkLinearAllocator* pAllocator, const XkSize totalSize) {
  xkAssert(pAllocator);
  xkAssert(totalSize > 0);

	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkLinearAllocator_T));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkLinearAllocator allocator = *pAllocator;

	// Align total size with linear allocator alignment for better performance and minimal fragmentation.
	const XkSize alignTotalSize = (totalSize + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

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

void xkDestroyLinearAllocator(XkLinearAllocator allocator) {
  xkAssert(allocator);

	xkFreeMemory(allocator->memory);

	xkFreeMemory(allocator);
}

void xkClearLinearAllocator(XkLinearAllocator allocator) {
  xkAssert(allocator);

	allocator->size = 0;

	xkZeroMemory(allocator->memory, allocator->totalSize);	
}

void xkResizeLinearAllocator(XkLinearAllocator allocator, const XkSize newTotalSize) {
  xkAssert(allocator);

	// Align new total size with linear allocator stride for better performance and minimal fragmentation.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	allocator->totalSize 	= alignNewTotalSize;
	allocator->memory 		= xkReallocateMemory(allocator->memory, alignNewTotalSize);
}

XkHandle xkAllocateLinearMemory(XkLinearAllocator allocator, const XkSize size) {
  xkAssert(allocator);

	// Align allocate size with linear allocator stride for better performance and minimal fragmentation.
	const XkSize alignSize = (size + (XK_LINEAR_ALLOCATOR_ALIGN - 1)) & ~(XK_LINEAR_ALLOCATOR_ALIGN - 1);

	if((allocator->size + alignSize) > allocator->totalSize) {
		xkResizeLinearAllocator(allocator, allocator->totalSize * XK_LINEAR_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	allocator->size += alignSize;

 	XkHandle newMemory = (XkUInt8*)allocator->memory + (allocator->size + alignSize);

	return(newMemory);
}


/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/FreeList.h"
#include "XKinetic/Core/DynamicAllocator.h"

/* ########## MACROS SECTION ########## */
#define XK_DYNAMIC_ALLOCATOR_REALLOCATE_COEFFICIENT 2

/* ########## TYPES SECTION ########## */
struct XkDynamicAllocator_T {
	XkFreeList freelist;
};

/* ########## GLOBAL VARIABLES SECTION ########## */
static const XkSize XK_DYNAMIC_ALLOCATOR_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateDynamicAllocator(XkDynamicAllocator* pAllocator, const XkSize totalSize) {
	xkAssert(pAllocator);
	xkAssert(totalSize > 0);

	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkDynamicAllocator_T));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDynamicAllocator allocator = *pAllocator;	

	// Align total size with dynamic allocator alignment for better performance and minimal fragmentation.
	const XkSize alignTotalSize = (totalSize + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	result = xkCreateFreeList(&allocator->freelist, alignTotalSize);
	if(result != XK_SUCCESS) goto _free;

_catch:
	return(result);

_free:
	if(allocator) {
		xkFreeMemory(allocator);
	}

	goto _catch;
}

void xkDestroyDynamicAllocator(XkDynamicAllocator allocator) {
	xkAssert(allocator);

	xkDestroyFreeList(allocator->freelist);

	xkFreeMemory(allocator);
}

void xkClearDynamicAllocator(XkDynamicAllocator allocator) {
	xkAssert(allocator);

	xkClearFreeList(allocator->freelist);
}

void xkResizeDynamicAllocator(XkDynamicAllocator allocator, const XkSize newTotalSize) {
	xkAssert(allocator);
	xkAssert(newTotalSize > 0 && newTotalSize > allocator->totalSize)

	// Align new total size with dynamic allocator alignment for better performance and minimal fragmentation.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_DYNAMIC_ALLOCATOR_ALIGN - 1)) & ~(XK_DYNAMIC_ALLOCATOR_ALIGN - 1);

	xkResizeFreeList(allocator->freelist, alignNewTotalSize);
}

XkHandle xkAllocateDynamicMemory(XkDynamicAllocator allocator, const XkSize size) {
	xkAssert(allocator);

	XkHandle newMemory = xkFreeListAllocate(allocator->freelist, size);
	return(newMemory);
}

void xkFreeDynamicMemory(XkDynamicAllocator allocator, const XkHandle data) {
	xkAssert(allocator);
	xkAssert(data);

	xkFreeListFree(allocator->freelist, data);
}

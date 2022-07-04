/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/FreeList.h"
#include "XKinetic/Core/PoolAllocator.h"

/* ########## MACROS SECTION ########## */
#define XK_POOL_ALLOCATOR_REALLOCATE_COEFFICIENT 2

/* ########## TYPES SECTION ########## */
struct XkPoolAllocator_T {
	XkSize totalChunkCount;
	XkSize chunkSize;
	XkSize allocatedChunkCount;

	XkFreeList freelist;
};

/* ########## GLOBAL VARIABLES SECTION ########## */
static const XkSize XK_POOL_ALLOCATOR_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkCreatePoolAllocator(XkPoolAllocator* pAllocator, const XkSize totalChunkCount, const XkSize chunkSize) {
	xkAssert(pAllocator);
	xkAssert(totalChunkCount > 0);
	xkAssert(totalSize > 0);

	XkResult result = XK_SUCCESS;

	*pAllocator = xkAllocateMemory(sizeof(struct XkPoolAllocator_T));
	if(!(*pAllocator)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkPoolAllocator allocator = *pAllocator;

	// Align chunk size with pool allocator alignment for better performance and minimal fragmentation.
	const XkSize alignChunkSize = (chunkSize + (XK_POOL_ALLOCATOR_ALIGN - 1)) & ~(XK_POOL_ALLOCATOR_ALIGN - 1);

	const XkSize totalSize = totalChunkCount * alignChunkSize;

	// Align total size with align chunk size for better performance and minimal fragmentation.
	const XkSize alignTotalSize = (totalSize + (alignChunkSize - 1)) & ~ (alignChunkSize - 1);

	allocator->totalChunkCount			= totalChunkCount;
	allocator->chunkSize						= alignChunkSize;
	allocator->allocatedChunkCount	= 0;

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

void xkDestroyPoolAllocator(XkPoolAllocator allocator) {
	xkAssert(allocator);

	xkDestroyFreeList(allocator->freelist);

	xkFreeMemory(allocator);
}

void xkClearPoolAllocator(XkPoolAllocator allocator) {
	xkAssert(allocator);

	allocator->allocatedChunkCount = 0;

	xkClearFreeList(allocator->freelist);
}

void xkResizePoolAllocator(XkPoolAllocator allocator, const XkSize newChunkCount) {
	xkAssert(allocator);
	xkAssert(newChunkCount > 0 && newChunkCount > allocator->totalChunkCount);

	const XkSize alignNewTotalSize = ((newChunkCount * allocator->chunkSize) + (allocator->chunkSize - 1)) & ~(allocator->chunkSize - 1);

	allocator->totalChunkCount = newChunkCount;

	xkResizeFreeList(allocator->freelist, alignNewTotalSize);
}

XkHandle xkAllocatePoolMemory(XkPoolAllocator allocator, const XkSize chunkCount) {
	xkAssert(allocator);

	if((allocator->allocatedChunkCount + chunkCount) > allocator->totalChunkCount) {
		xkResizePoolAllocator(allocator, allocator->totalChunkCount * XK_POOL_ALLOCATOR_REALLOCATE_COEFFICIENT);
	}

	++allocator->allocatedChunkCount;
	XkHandle newMemory = xkFreeListAllocate(allocator->freelist, allocator->chunkSize * chunkCount);

	return(newMemory);
}

void xkFreePoolMemory(XkPoolAllocator allocator, const XkHandle data) {
	xkAssert(allocator);

	xkFreeListFree(allocator->freelist, data);
}

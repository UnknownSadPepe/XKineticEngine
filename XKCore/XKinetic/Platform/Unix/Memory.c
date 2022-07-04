/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

#define _GNU_SOURCE
#define __USE_GNU
#define __USE_MISC
#include <sys/mman.h>

/* ########## TYPES SECTION ########## */
typedef struct __XkMemoryHeader_T {
	XkHandle memory;
	XkSize size;
} __XkMemoryHeader;

/* ########## GLOBAL VARIABLE SECTION ########## */
static const XkSize XK_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkHandle xkAllocateMemory(const XkSize size) {
	xkAssert(size > 0);

	// Align memory allocate size for better performance and minimal fragmentation.
	const XkSize alignSize = (size + sizeof(__XkMemoryHeader) + (XK_ALIGN - 1)) & ~ (XK_ALIGN - 1);

	XkHandle memory = mmap(0, alignSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(!memory) {
		__xkErrorHandle("Unix: Failed to allocate memory");
		return(XK_NULL_HANDLE);
	}

	__XkMemoryHeader* pHeader = (__XkMemoryHeader*)memory;
	pHeader->size = alignSize;
	pHeader->memory = memory + sizeof(__XkMemoryHeader);

	return(pHeader->memory);
}

XkHandle xkReallocateMemory(const XkHandle memory, const XkSize size) {
	xkAssert(size > 0);

	if(!memory) {
		XkHandle newMemory = xkAllocateMemory(size);
		return(newMemory);
	}

	// Align memory reallocate size for better performance and minimal fragmentation.
	const XkSize alignSize = (size + sizeof(__XkMemoryHeader) + (XK_ALIGN - 1)) & ~ (XK_ALIGN - 1);

	__XkMemoryHeader* pHeader = (__XkMemoryHeader*)(((XkUInt8*)memory) - sizeof(__XkMemoryHeader));

	XkHandle newMemory = mremap(pHeader, pHeader->size, alignSize, 0, MREMAP_FIXED);
	if(!newMemory) {
		__xkErrorHandle("Unix: Failed to reallocate memory");
		return(XK_NULL_HANDLE);
	}

	pHeader->size = alignSize;
	pHeader->memory = newMemory + sizeof(__XkMemoryHeader);

	return(pHeader->memory);
}

void xkFreeMemory(const XkHandle memory) {
	xkAssert(memory);
	
	__XkMemoryHeader* pHeader = (__XkMemoryHeader*)(((XkUInt8*)memory) - sizeof(__XkMemoryHeader));

	munmap(memory, pHeader->size);
}

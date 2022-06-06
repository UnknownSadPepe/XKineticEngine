#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_UNIX)

#define _GNU_SOURCE
#define __USE_GNU
#include <sys/mman.h>

typedef struct {
	XkHandle memory;
	XkSize size;
} __XkMemoryHeader;

static const XkSize _xkAlign = 16;

XkResult xkMemoryInitialize(void) {
	XkResult result = XK_SUCCESS;

	/// NOTE: nothing to do here.

_catch:
	return(result);
}

void xkMemoryTerminate(void) {
	/// NOTE: nothing to do here.
}

XkHandle xkAllocateMemory(const XkSize size) {
	const XkSize alignSize = (size + sizeof(__XkMemoryHeader) + (_xkAlign - 1)) & ~ (_xkAlign - 1);

	XkHandle memory = mmap(0, alignSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if(!memory) {
		__xkErrorHandle("Failed to allocate memory");
		return(XK_NULL_HANDLE);
	}

	__XkMemoryHeader* pHeader = (__XkMemoryHeader*)memory;
	pHeader->size = alignSize;
	pHeader->memory = memory;

	return(memory + sizeof(__XkMemoryHeader));
}

XkHandle xkReallocateMemory(const XkHandle memory, const XkSize size) {
	const XkSize alignSize = (size + sizeof(__XkMemoryHeader) + (_xkAlign - 1)) & ~ (_xkAlign - 1);

	__XkMemoryHeader* pHeader = (__XkMemoryHeader*)(((XkUInt8*)memory) - sizeof(__XkMemoryHeader));

	XkHandle newMemory = mremap(pHeader->memory, pHeader->size, alignSize, 0, MREMAP_FIXED);
	if(!newMemory) {
		__xkErrorHandle("Failed to reallocate memory");
		return(XK_NULL_HANDLE);
	}

	pHeader->size = alignSize;
	pHeader->memory = newMemory;

	return(newMemory + sizeof(__XkMemoryHeader));
}

void xkFreeMemory(const XkHandle memory) {
	__XkMemoryHeader* pHeader = (__XkMemoryHeader*)(((XkUInt8*)memory) - sizeof(__XkMemoryHeader));

	munmap(pHeader->memory, pHeader->size);
}

#endif // XK_UNIX

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
static const XkSize XK_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkHandle xkAllocateMemory(const XkSize size) {
	xkAssert(size > 0);

	// Align memory allocate size for better performance and minimal fragmentation.
	const XkSize alignSize = (size + (XK_ALIGN - 1)) & ~(XK_ALIGN - 1);

	XkHandle memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, alignSize);
	if(!memory) {
		__xkErrorHandle("Win32: Failed to allocate memory");
		return(XK_NULL_HANDLE);
	}

	return(memory);
}

XkHandle xkReallocateMemory(const XkHandle memory, const XkSize size) {
	xkAssert(size > 0);

	if(!memory) {
		XkHandle newMemory = xkAllocateMemory(size);
		return(newMemory);
	}

	// Align memory reallocate size for better performance and minimal fragmentation.
	const XkSize alignSize = (size + (XK_ALIGN - 1)) & ~(XK_ALIGN - 1);

	XkHandle newMemory = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, memory, alignSize);
	if(!newMemory) {
		__xkErrorHandle("Win32: Failed to reallocate memory");
		return(XK_NULL_HANDLE);
	}

	return(newMemory);	
}

void xkFreeMemory(const XkHandle memory) {
	xkAssert(memory);

	HeapFree(GetProcessHeap(), 0, memory);
}

#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

static const XkSize XK_ALIGN = 16;

XkHandle xkAllocateMemory(const XkSize size) {
	// Align memory allocate size.
	const XkSize alignSize = (size + (XK_ALIGN - 1)) & ~(XK_ALIGN - 1);

	// Allocate Win32 heap memory.
	XkHandle memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, alignSize);
	if(!memory) {
		__xkErrorHandle("Win32: Failed to allocate memory");
		return(XK_NULL_HANDLE);
	}

	return(memory);
}

XkHandle xkReallocateMemory(const XkHandle memory, const XkSize size) {
	// Align memory reallocate size.
	const XkSize alignSize = (size + (XK_ALIGN - 1)) & ~(XK_ALIGN - 1);

	// Reallocate Win32 memory.
	XkHandle pNewMemory = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, memory, alignSize);
	if(!pNewMemory) {
		__xkErrorHandle("Win32: Failed to reallocate memory");
		return(XK_NULL_HANDLE);
	}

	return(pNewMemory);	
}

void xkFreeMemory(const XkHandle memory) {
	// Free Win32 heap memory.
	HeapFree(GetProcessHeap(), 0, memory);
}

#endif // XK_WIN32

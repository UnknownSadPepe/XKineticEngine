#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkHandle xkAllocateMemory(const XkSize size) {
	XkHandle memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	if(!memory) {
		__xkErrorHandle("Failed to allocate memory");
		return(XK_NULL_HANDLE);
	}
	return(memory);
}

XkHandle xkReallocateMemory(const XkHandle memory, const XkSize size) {
	XkHandle pNewMemory = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, memory, size);
	if(!pNewMemory) {
		__xkErrorHandle("Failed to reallocate memory");
		return(XK_NULL_HANDLE);
	}
	return(pNewMemory);	
}

void xkFreeMemory(const XkHandle memory) {
	HeapFree(GetProcessHeap(), 0, memory);
}

#endif // XK_WIN32

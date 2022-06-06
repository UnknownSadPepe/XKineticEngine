#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include "XKinetic/Platform/Win32/Internal.h"

XkResult __xkMemoryInitialize(void) {
	XkResult result = XK_SUCCESS;

	_xkPlatform.handle.heap = GetProcessHeap();
	if(!_xkPlatform.handle.heap) {
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void __xkMemoryTerminate(void) {
	/// NOTE: Nothing to do here.
}

XkHandle __xkAllocateMemory(const XkSize size) {
	XkHandle memory = HeapAlloc(_xkPlatform.handle.heap, HEAP_ZERO_MEMORY, size);
	if(!memory) {
		__xkErrorHandle("Failed to allocate memory");
		return(XK_NULL_HANDLE);
	}
	return(memory);
}

XkHandle __xkReallocateMemory(const XkHandle memory, const XkSize size) {
	XkHandle pNewMemory = HeapReAlloc(_xkPlatform.handle.heap, HEAP_ZERO_MEMORY, memory, size);
	if(!pNewMemory) {
		__xkErrorHandle("Failed to reallocate memory");
		return(XK_NULL_HANDLE);
	}
	return(pNewMemory);	
}

void __xkFreeMemory(const XkHandle memory) {
	HeapFree(_xkPlatform.handle.heap, 0, memory);
}

#endif // XK_WIN32

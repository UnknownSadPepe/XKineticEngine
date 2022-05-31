#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/Memory.h"

XkResult xkMemoryInitialize(void) {
	XkResult result = XK_SUCCESS;

	result = __xkMemoryInitialize();
	if(result != XK_SUCCESS) goto _catch;

_catch:
	return(result);
}

void xkMemoryTerminate(void) {
	__xkMemoryTerminate();
}

XkHandle xkAllocateMemory(const XkSize size) {
	XkHandle newMemory = __xkAllocateMemory(size);
	if(newMemory == XK_NULL) return XK_NULL;

	return(newMemory);
}

XkHandle xkReallocateMemory(const XkHandle memory, const XkSize size) {
	XkHandle newMemory = __xkReallocateMemory(memory, size);
	if(newMemory == XK_NULL) return XK_NULL;

	return(newMemory);
}

void xkFreeMemory(const XkHandle memory) {
	__xkFreeMemory(memory);
}

XkHandle xkCopyMemory(XkHandle dstMemory, const XkHandle srcMemory, const XkSize size) {
	const XkUInt8* alignSrcMemory = srcMemory;
	XkUInt8* alignDstMemory = dstMemory;

	XkSize len = size;
  while(--len) {
		*alignDstMemory++ = *alignSrcMemory++;
  }
  return(dstMemory);
}

XkHandle xkMoveMemory(XkHandle dstMemory, const XkHandle srcMemory, const XkSize size) {
	const XkUInt8* alignSrcMemory = srcMemory;
	XkUInt8* alignDstMemory = dstMemory;

  XkUInt8* tmpMemory  = xkAllocateMemory(size);
  if(tmpMemory == XK_NULL) return XK_NULL;

	for(XkSize i = 0; i < size; ++i) {
		*(tmpMemory + i) = *(alignSrcMemory + i);
	}

	for(XkSize i = 0 ; i < size; ++i) {
		*(alignDstMemory + i) = *(alignSrcMemory + i);
  }

  xkFreeMemory(tmpMemory);

  return(dstMemory);
}

XkHandle xkZeroMemory(XkHandle memory, const XkSize size) {
	XkUInt8* alignMemory = memory;

	XkSize len = size;
  while(--len) {
		*alignMemory++ = 0;
  }
  return(memory);
}

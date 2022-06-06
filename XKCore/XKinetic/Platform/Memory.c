#include "XKinetic/Platform/Memory.h"

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
  if(tmpMemory == XK_NULL_HANDLE) return XK_NULL_HANDLE;

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

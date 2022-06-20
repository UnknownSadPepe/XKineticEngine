#include "XKinetic/Platform/Memory.h"

XkHandle xkCopyMemory(XkHandle dstMemory, const XkHandle srcMemory, const XkSize size) {
	// Template align source memory.
	const XkUInt8* alignSrcMemory = srcMemory;

	// Template align destination memory.
	XkUInt8* alignDstMemory = dstMemory;

	// Template memory length.
	XkSize len = size;

  while(--len) {
		*alignDstMemory++ = *alignSrcMemory++;
  }
  return(dstMemory);
}

XkHandle xkMoveMemory(XkHandle dstMemory, const XkHandle srcMemory, const XkSize size) {
	// Template align source memory.
	const XkUInt8* alignSrcMemory = srcMemory;

	// Template align destination memory.
	XkUInt8* alignDstMemory = dstMemory;

	// Allocate template memory.
  XkUInt8* tmpMemory  = xkAllocateMemory(size);
	if(tmpMemory == XK_NULL_HANDLE) {
		return XK_NULL_HANDLE;
	}

	// Copy from source to template memory.
	for(XkSize i = 0; i < size; ++i) {
		*(tmpMemory + i) = *(alignSrcMemory + i);
	}

	// Copy from template to destination memory.
	for(XkSize i = 0 ; i < size; ++i) {
		*(alignDstMemory + i) = *(alignSrcMemory + i);
  }

	// Free template memory.
  xkFreeMemory(tmpMemory);

  return(dstMemory);
}

XkHandle xkZeroMemory(XkHandle memory, const XkSize size) {
	// Template align memory.
	XkUInt8* alignMemory = memory;

	// Template memory length.
	XkSize len = size;

  while(--len) {
		*alignMemory++ = 0;
  }

  return(memory);
}

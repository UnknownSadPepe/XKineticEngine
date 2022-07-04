/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Memory.h"

/* ########## FUNCTIONS SECTION ########## */
XkHandle xkCopyMemory(XkHandle dstMemory, const XkHandle srcMemory, const XkSize size) {
	const XkUInt8* alignSrcMemory = srcMemory;
	XkUInt8* alignDstMemory = dstMemory;

	XkSize length = size;

  while(--length) {
		*alignDstMemory++ = *alignSrcMemory++;
  }

  return(dstMemory);
}

XkHandle xkMoveMemory(XkHandle dstMemory, const XkHandle srcMemory, const XkSize size) {
	const XkUInt8* alignSrcMemory = srcMemory;
	XkUInt8* alignDstMemory = dstMemory;

  XkUInt8* tmpMemory  = xkAllocateMemory(size);
	if(tmpMemory == XK_NULL_HANDLE) {
		return XK_NULL_HANDLE;
	}

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

	XkSize length = size;

  while(--length) {
		*alignMemory++ = 0;
  }

  return(memory);
}

XkInt32 xkCompareMemory(const XkHandle memory1, const XkHandle memory2, const XkSize size) {
	XkUInt8* alignMemory1 = memory1;

	XkUInt8* alignMemory2 = memory2;

	XkSize length = size;

	while (--length && *alignMemory1 == *alignMemory2) {
		++alignMemory1;
		++alignMemory2;
	}

	XkInt32 difference = (*alignMemory1 - *alignMemory2);
	XkInt32 status = (difference == 0) ? 1 : (difference > 0) ? 0 : -1; 
	return(status);
}

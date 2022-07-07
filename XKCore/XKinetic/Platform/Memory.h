#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkHandle 	xkAllocateMemory(const XkSize);
extern XKCORE_API XkHandle 	xkReallocateMemory(const XkHandle, const XkSize);
extern XKCORE_API void 			xkFreeMemory(const XkHandle);

extern XKCORE_API void 			xkCopyMemory(XkHandle, const XkHandle, const XkSize);
extern XKCORE_API void 			xkMoveMemory(XkHandle, const XkHandle, const XkSize);
extern XKCORE_API void 			xkZeroMemory(XkHandle, const XkSize);

extern XKCORE_API XkInt32 	xkCompareMemory(const XkHandle, const XkHandle, const XkSize);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

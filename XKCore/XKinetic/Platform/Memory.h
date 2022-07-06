#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## MACROS SECTION ########## */
#define XK_MEMORY_CLEANUP XK_CLEANUP(xkFreeMemory)

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkHandle 	xkAllocateMemory(const XkSize);
extern XKCORE_API XkHandle 	xkReallocateMemory(const XkHandle, const XkSize);
extern XKCORE_API void 			xkFreeMemory(const XkHandle);

extern XKCORE_API XkHandle 	xkCopyMemory(XkHandle, const XkHandle, const XkSize);
extern XKCORE_API XkHandle 	xkMoveMemory(XkHandle, const XkHandle, const XkSize);
extern XKCORE_API XkHandle 	xkZeroMemory(XkHandle, const XkSize);

extern XKCORE_API XkInt32 	xkCompareMemory(const XkHandle, const XkHandle, const XkSize);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

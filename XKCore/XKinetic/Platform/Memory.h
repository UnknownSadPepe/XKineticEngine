#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

XKCORE_API XkHandle xkAllocateMemory(const XkSize);
XKCORE_API XkHandle xkReallocateMemory(const XkHandle, const XkSize);
XKCORE_API void xkFreeMemory(const XkHandle);

XKCORE_API XkHandle xkCopyMemory(XkHandle, const XkHandle, const XkSize);
XKCORE_API XkHandle xkMoveMemory(XkHandle, const XkHandle, const XkSize);
XKCORE_API XkHandle xkZeroMemory(XkHandle, const XkSize);

XKCORE_API XkBool xkCompareMemory(const XkHandle, const XkHandle, const XkSize);

#ifdef __cplusplus
}
#endif // __cplusplus

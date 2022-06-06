#pragma once

#include "XKinetic/XKCore.h"

XK_EXPORT XkHandle xkAllocateMemory(const XkSize);
XK_EXPORT XkHandle xkReallocateMemory(const XkHandle, const XkSize);
XK_EXPORT void xkFreeMemory(const XkHandle);

XK_EXPORT XkHandle xkCopyMemory(XkHandle, const XkHandle, const XkSize);
XK_EXPORT XkHandle xkMoveMemory(XkHandle, const XkHandle, const XkSize);
XK_EXPORT XkHandle xkZeroMemory(XkHandle, const XkSize);

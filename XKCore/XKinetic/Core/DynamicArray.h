#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkDynamicArray* XkDynamicArray;

#define XK_DYNAMIC_ARRAY_DEFAULT_CAPACITY 2

XKCORE_API XkResult __xkCreateDynamicArray(XkDynamicArray*, XkSize, XkSize);
#define xkCreateDynamicArray(array, type) __xkCreateDynamicArray(array, XK_DYNAMIC_ARRAY_DEFAULT_CAPACITY, sizeof(type))
#define xkCreateDynamicArrayCapacity(array, capacity, type) __xkCreateDynamicArray(array, capacity, sizeof(type))

XKCORE_API void xkDestroyDynamicArray(XkDynamicArray);

XKCORE_API void xkResizeDynamicArray(XkDynamicArray, const XkSize);
XKCORE_API void xkClearDynamicArray(XkDynamicArray);

XKCORE_API void __xkDynamicArrayPush(XkDynamicArray, const XkHandle);
#define xkPushDynamicArray(array, value)		\
{																						\
	typeof(value) tmp = value;								\
	__xkPushDynamicArray(array, &tmp);				\
}

XKCORE_API void xkDynamicArrayPop(XkDynamicArray);

XKCORE_API XkSize xkDynamicArrayLength(XkDynamicArray);
XKCORE_API XkSize xkDynamicArrayCapacity(XkDynamicArray);
XKCORE_API XkHandle xkDynamicArrayGet(XkDynamicArray, const XkSize);


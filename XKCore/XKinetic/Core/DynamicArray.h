#pragma once

#include "XKinetic/XKCore.h"

typedef struct XkDynamicArray* XkDynamicArray;

#define XK_DYNAMIC_ARRAY_DEFAULT_CAPACITY 2

XKCORE_API XkResult __xkCreateDynamicArray(XkDynamicArray*, XkSize, XkSize);
#define xkCreateDynamicArray(array, type) __xkCreateDynamicArray(array, XK_DYNAMIC_ARRAY_DEFAULT_CAPACITY, sizeof(type))
#define xkCreateDynamicArrayCapacity(array, capacity, type) __xkCreateDynamicArray(array, capacity, sizeof(type))

XKCORE_API void xkDestroyDynamicArray(XkDynamicArray);

XKCORE_API void xkClearDynamicArray(XkDynamicArray);
XKCORE_API void xkResizeDynamicArray(XkDynamicArray, const XkSize);

XKCORE_API void __xkDynamicArrayPush(XkDynamicArray, const XkHandle);
#define xkDynamicArrayPush(array, value)		\
{																						\
	typeof(value) tmp = value;								\
	__xkDynamicArrayPush(array, &tmp);				\
}

XKCORE_API void xkDynamicArrayPop(XkDynamicArray);


XKCORE_API void __xkDynamicArrayInsert(XkDynamicArray, const XkSize, XkHandle);
#define xkDynamicArrayInsert(array, index, value)	\
{																									\
	typeof(value) tmp = value;											\
	__xkDynamicArrayInsert(array, index, &tmp);			\
}

XKCORE_API void xkDynamicArrayErase(XkDynamicArray, const XkSize);

XKCORE_API XkSize xkDynamicArrayLength(XkDynamicArray);
XKCORE_API XkSize xkDynamicArrayCapacity(XkDynamicArray);

XKCORE_API XkHandle xkDynamicArrayGet(XkDynamicArray, const XkSize);
XKCORE_API void __xkDynamicArraySet(XkDynamicArray, const XkSize, XkHandle);
#define xkDynamicArraySet(array, value)			\
{																						\
	typeof(value) tmp = value;								\
	__xkDynamicArraySet(array, &tmp);					\
}


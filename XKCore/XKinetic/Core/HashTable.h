#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef XkInt64 XkKey;

typedef struct XkHashTable* XkHashTable;

#define XK_HASH_TABLE_DEFAULT_CAPACITY 2

XKCORE_API XkResult __xkCreateHashTable(XkHashTable*, const XkSize, const XkSize);
#define xkCreateHashTable(table, type) __xkCreateHashTable(table, XK_HASH_TABLE_DEFAULT_CAPACITY, sizeof(type))
#define xkCreateHashTableCapacity(table, capacity, type) __xkCreateHashTable(table, capacity, sizeof(type))

XKCORE_API void xkDestroyHashTable(XkHashTable);

XKCORE_API void xkResizeHashTable(XkHashTable, const XkSize);
XKCORE_API void xkClearHashTable(XkHashTable);

XKCORE_API void __xkHashTableInsert(XkHashTable, const XkKey, const XkHandle);
#define xkHashTableInsert(table, key, value)		  \
{																						      \
	typeof(value) tmp = value;								      \
	__xkHashTableInsert(table, key, &tmp);				  \
}

XKCORE_API void xkHashTableErase(XkHashTable, const XkKey);

XKCORE_API XkSize xkHashTableLength(XkHashTable);
XKCORE_API XkSize xkHashTableCapacity(XkHashTable);

XKCORE_API XkHandle xkHashTableGet(XkHashTable, const XkKey);
XKCORE_API void __xkHashTableSet(XkHashTable, const XkKey, XkHandle);
#define xkHashTableSet(table, key, value)					\
{																						      \
	typeof(value) tmp = value;								      \
	__xkHashTableSet(table, key, &tmp);							\
}

#ifdef __cplusplus
}
#endif // __cplusplus

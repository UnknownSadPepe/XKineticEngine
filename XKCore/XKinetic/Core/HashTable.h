#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/* ########## MACROS SECTION ########## */
#define XK_HASH_TABLE_DEFAULT_CAPACITY 2

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef XkString XkHashKey;

typedef struct XkHashTable_T* XkHashTable;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	__xkCreateHashTable(XkHashTable*, const XkSize, const XkSize);
extern XKCORE_API void 			xkDestroyHashTable(XkHashTable);

extern XKCORE_API void 			xkResizeHashTable(XkHashTable, const XkSize);
extern XKCORE_API void 			xkClearHashTable(XkHashTable);

extern XKCORE_API void 			__xkHashTableInsert(XkHashTable, const XkHashKey, const XkHandle);
extern XKCORE_API void 			xkHashTableErase(XkHashTable, const XkHashKey);

extern XKCORE_API XkSize 		xkHashTableLength(XkHashTable);
extern XKCORE_API XkSize 		xkHashTableCapacity(XkHashTable);

extern XKCORE_API XkHandle 	xkHashTableGet(XkHashTable, const XkHashKey);
extern XKCORE_API void 			__xkHashTableSet(XkHashTable, const XkHashKey, XkHandle);

/* ########## FUNCTIONS MACROS SECTION ########## */
#define xkCreateHashTable(table, type) __xkCreateHashTable(table, XK_HASH_TABLE_DEFAULT_CAPACITY, sizeof(type))
#define xkCreateHashTableCapacity(table, capacity, type) __xkCreateHashTable(table, capacity, sizeof(type))

#define xkHashTableInsert(table, key, value)		  \
{																						      \
	__auto_type tmp = value;												\
	__xkHashTableInsert(table, key, &tmp);				  \
}

#define xkHashTableSet(table, key, value)					\
{																						      \
	__auto_type tmp = value;												\
	__xkHashTableSet(table, key, &tmp);							\
}

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/HashTable.h"

/* ########## MACROS SECTION ########## */
#define XK_HASH_TABLE_REALLOCATE_COEFFICIENT 2

/* ########## TYPES SECTION ########## */
struct XkHashTable_T {
	XkSize length;
	XkSize capacity;
	XkSize stride;

	XkSize totalSize;
	
	XkHandle memory;
};

/* ########## FUNCTIONS SECTION ########## */
static XkSize __xkHashIndex(XkHashTable hashtable, const XkHashKey key) {
	xkAssert(hashtable);

	// SDBM hahs function.
  XkSize hash = 0;
	
  for(XkChar* us = (XkChar*)key; *us; ++us) {
		hash = *us + (hash << 6) + (hash << 16) - hash;
  }

	// Mod it against the size of the hashtable.
	hash %= hashtable->capacity;

  return(hash);
}

XkResult __xkCreateHashTable(XkHashTable* pHashTable, const XkSize capacity, const XkSize stride) {
	xkAssert(pHashTable);
	xkAssert(capacity > 0);
	xkAssert(stride > 0);	

  XkResult result = XK_SUCCESS;

	*pHashTable = xkAllocateMemory(sizeof(struct XkHashTable_T));
	if(!(*pHashTable)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkHashTable hashtable = *pHashTable;

	// Align stride with hash hashtable alignment for better performance and minimal fragmentation.
	const XkSize alignStride = (stride + (stride - 1)) & ~(stride - 1);

	const XkSize totalSize = capacity * alignStride;

  hashtable->length 		= 0;
	hashtable->capacity 	= capacity;
	hashtable->stride 		= stride;
	hashtable->totalSize 	= totalSize;
	hashtable->memory 		=	xkAllocateMemory(totalSize);
	if(!hashtable->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _free;
	}

_catch:
  return(result);

_free:
	if(hashtable) {
		xkFreeMemory(hashtable);
	}

	goto _catch;
}

void xkDestroyHashTable(XkHashTable hashtable) {
	xkAssert(hashtable);

	xkFreeMemory(hashtable->memory);

	xkFreeMemory(hashtable);
}

void xkResizeHashTable(XkHashTable hashtable, const XkSize newCapacity) {
	xkAssert(hashtable);
	xkAssert(newCapacity > 0 && newCapacity > array->capacity);

	const XkSize newTotalSize = newCapacity * hashtable->stride;
	
	hashtable->memory 		= xkReallocateMemory(hashtable->memory, newTotalSize);
	hashtable->capacity 	= newCapacity;
	hashtable->totalSize 	= newTotalSize;
}

void xkClearHashTable(XkHashTable hashtable) {
	xkAssert(hashtable);

	hashtable->length = 0;

	xkZeroMemory(hashtable->memory, hashtable->totalSize);	
}

void __xkHashTableInsert(XkHashTable hashtable, const XkHashKey key, const XkHandle data) {
	xkAssert(hashtable);
	xkAssert(data);

	if(hashtable->length >= hashtable->capacity) {
		xkResizeHashTable(hashtable, hashtable->capacity * XK_HASH_TABLE_REALLOCATE_COEFFICIENT);
	}

	XkSize index = __xkHashIndex(hashtable, key);

	xkCopyMemory((XkUInt8*)hashtable->memory + (hashtable->stride * (index)), data, hashtable->stride);

	++hashtable->length;
}

void xkHashTableErase(XkHashTable hashtable, XkHashKey key) {
	xkAssert(hashtable);

	XkSize index = __xkHashIndex(hashtable, key);

	xkZeroMemory((XkUInt8*)hashtable->memory + (hashtable->stride * (index)), hashtable->stride);

	--hashtable->length;
}

XkSize xkHashTableLength(XkHashTable hashtable) {
	xkAssert(hashtable);

	return(hashtable->length);
}

XkSize xkHashTableCapacity(XkHashTable hashtable) {
	xkAssert(hashtable);

	return(hashtable->capacity);
}

XkHandle xkHashTableGet(XkHashTable hashtable, const XkHashKey key) {
	xkAssert(hashtable);

	XkSize index = __xkHashIndex(hashtable, key);

	return((XkUInt8*)hashtable->memory + (hashtable->stride * (index)));
}

void __xkHashTableSet(XkHashTable hashtable, const XkHashKey key, XkHandle data) {
	xkAssert(hashtable);

	XkSize index = __xkHashIndex(hashtable, key);

	xkCopyMemory((XkUInt8*)hashtable->memory + (hashtable->stride * (index)), data, hashtable->stride);
}


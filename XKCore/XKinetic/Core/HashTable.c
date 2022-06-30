#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/HashTable.h"

#include "XKinetic/Core/Log.h"

struct XkHashTable {
	XkSize length;
	XkSize capacity;
	XkSize stride;

	XkSize totalSize;
	
	XkHandle memory;
};

#define XK_HASH_TABLE_REALLOCATE_COEFFICIENT 2

static XkSize __xkHashIndex(XkHashTable table, const XkKey key) {
	// SDBM hahs function.
  XkSize hash = 0;
	
  for(XkChar* us = (XkChar*)key; *us; ++us) {
		hash = *us + (hash << 6) + (hash << 16) - hash;
  }

	// Mod it against the size of the table.
	hash %= table->capacity;

	xkLogNotice("hash: %d", hash);

  return(hash);
}

XkResult __xkCreateHashTable(XkHashTable* pTable, const XkSize capacity, const XkSize stride) {
  XkResult result = XK_SUCCESS;

	// Allocate hash table.
	*pTable = xkAllocateMemory(sizeof(struct XkHashTable));
	if(!(*pTable)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template hash table.
	XkHashTable table = *pTable;

	// Align stride with hash table alignment.
	const XkSize alignStride = (stride + (stride - 1)) & ~(stride - 1);

	// Initialize hash table total size.
	const XkSize totalSize = capacity * alignStride;

	// Initialize hash table.
  table->length 		= 0;
	table->capacity 	= capacity;
	table->stride 		= stride;
	table->totalSize 	= totalSize;

	// Allocate hash table memory.
	table->memory =	xkAllocateMemory(totalSize);
	if(!table->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

_catch:
  return(result);
}

void xkDestroyHashTable(XkHashTable table) {
	// Free hash table memory.
	xkFreeMemory(table->memory);

	// Free hash table
	xkFreeMemory(table);
}

void xkResizeHashTable(XkHashTable table, const XkSize newCapacity) {
	// Initialize hash table new total size.
	const XkSize newTotalSize = newCapacity * table->stride;
	
	// Reallocate hash table memory.
	table->memory = xkReallocateMemory(table->memory, newTotalSize);

	// Initialize hash table
	table->capacity = newCapacity;
	table->totalSize = newTotalSize;
}

void xkClearHashTable(XkHashTable table) {
	// Null hash table allocated length.
	table->length = 0;

	// Zero hash table memory.
	xkZeroMemory(table->memory, table->totalSize);	
}

void __xkHashTableInsert(XkHashTable table, const XkKey key, const XkHandle data) {
	// Check if there is not enough space in hash table.
	if(table->length >= table->capacity) {
		// Resize hash table.
		xkResizeHashTable(table, table->capacity * XK_HASH_TABLE_REALLOCATE_COEFFICIENT);
	}

	// Get memory index by key.
	XkSize index = __xkHashIndex(table, key);

	// Copy data to indexed memory.
	xkCopyMemory((XkUInt8*)table->memory + (table->stride * (index)), data, table->stride);

	// Increment hash table allocated length.
	table->length++;
}

void xkHashTableErase(XkHashTable table, XkKey key) {
	// Get memory index by key.
	XkSize index = __xkHashIndex(table, key);

	// Copy data to indexed memory.
	xkZeroMemory((XkUInt8*)table->memory + (table->stride * (index)), table->stride);

	// Decrement hash table allocated length.
	table->length--;
}

XkSize xkHashTableLength(XkHashTable table) {
	return(table->length);
}

XkSize xkHashTableCapacity(XkHashTable table) {
	return(table->capacity);
}

XkHandle xkHashTableGet(XkHashTable table, const XkKey key) {
	// Get memory index by key.
	XkSize index = __xkHashIndex(table, key);

	return((XkUInt8*)table->memory + (table->stride * (index)));
}

void __xkHashTableSet(XkHashTable table, const XkKey key, XkHandle data) {
	// Get memory index by key.
	XkSize index = __xkHashIndex(table, key);

	// Copy data to indexed memory.
	xkCopyMemory((XkUInt8*)table->memory + (table->stride * (index)), data, table->stride);
}


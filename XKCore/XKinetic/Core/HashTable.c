#include "XKinetic/Core/Memory.h"
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

static XkSize __xkHashIndex(const XkKey key, const XkSize tableSize) {
  return(key % tableSize);
}

XkResult __xkCreateHashTable(XkHashTable* pTable, const XkSize capacity, const XkSize stride) {
  XkResult result = XK_SUCCESS;

	*pTable = xkAllocateMemory(sizeof(struct XkHashTable));
	if(!(*pTable)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkHashTable table = *pTable;

	const XkSize size = capacity * stride;
	const XkSize alignSize = (size + (stride - 1)) & ~(stride - 1);

  table->length = 0;
	table->capacity = capacity;
	table->stride = stride;
	table->totalSize = alignSize;
	table->memory = xkAllocateMemory(alignSize);
	if(!table->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

_catch:
  return(result);
}

void xkDestroyHashTable(XkHashTable table) {
	xkFreeMemory(table->memory);
	xkFreeMemory(table);
}

void xkResizeHashTable(XkHashTable table, const XkSize newCapacity) {
	const XkSize size = newCapacity * table->stride;
	const XkSize alignSize = (size + (table->stride - 1)) & ~ (table->stride - 1);

	table->memory = xkReallocateMemory(table->memory, alignSize);
	table->capacity = newCapacity;
	table->totalSize = alignSize;
}

void xkClearHashTable(XkHashTable table) {
	table->length = 0;
	xkZeroMemory(table->memory, table->totalSize);	
}

void __xkHashTableInsert(XkHashTable table, const XkKey key, const XkHandle data) {
  XkSize hashIndex = __xkHashIndex(key, table->capacity);

  // TODO: implementation.

	if(table->length >= table->capacity) {
		xkResizeHashTable(table, table->capacity * XK_HASH_TABLE_REALLOCATE_COEFFICIENT);
	}
	xkCopyMemory(table->memory + (table->stride * hashIndex), data, table->stride);
	table->length++;
}

void xkHashTableErase(XkHashTable table, XkKey key) {
  XkSize hashIndex = __xkHashIndex(key, table->capacity);
  // TODO: implementation.
	table->length--;
}

XkSize xkHashTableLength(XkHashTable table) {
	return(table->length);
}

XkSize xkHashTableCapacity(XkHashTable table) {
	return(table->capacity);
}

XkHandle xkHashTableGet(XkHashTable table, const XkKey key) {
  XkSize hashIndex = __xkHashIndex(key, table->capacity);
	return(&table->memory + (table->stride * (hashIndex + 1)));
}

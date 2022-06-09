#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/HashTable.h"

#include "XKinetic/Core/Log.h"

typedef struct {
	XkHandle data;
	XkKey key;
} XkNode;

struct XkHashTable {
	XkSize length;
	XkSize capacity;
	XkSize stride;
	XkSize totalSize;

	XkNode* nodes;
	
	XkHandle memory;
};

#define XK_HASH_TABLE_REALLOCATE_COEFFICIENT 2

static XkSize __xkHashIndex(XkHashTable table, const XkKey key) {
	XkSize hashIndex = key % table->capacity;

	while(table->nodes[hashIndex].data != XK_NULL_HANDLE && table->nodes[hashIndex].key != -1) {
    ++hashIndex;
    hashIndex %= table->capacity;
	}

	return(hashIndex);
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
	xkLogDebug("hash align size: %d", alignSize);

	const XkSize nodesSize = sizeof(XkNode) * capacity;
	xkLogDebug("hash nodes size: %d", nodesSize);

	XkHandle memory =	xkAllocateMemory(nodesSize + alignSize);
	if(!memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

  table->length = 0;
	table->capacity = capacity;
	table->stride = stride;
	table->totalSize = alignSize;
	table->nodes = memory + alignSize;
	table->memory = memory;
	if(!table->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}


_catch:
  return(result);
}

void xkDestroyHashTable(XkHashTable table) {
	xkFreeMemory(table->nodes);
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
	if(table->length >= table->capacity) {
		xkResizeHashTable(table, table->capacity * XK_HASH_TABLE_REALLOCATE_COEFFICIENT);
	}

	XkSize index = __xkHashIndex(table, key);

	xkCopyMemory(table->nodes[index].data, data, table->stride);

	table->length++;
}

void xkHashTableErase(XkHashTable table, XkKey key) {
	XkSize index = __xkHashIndex(table, key);

  table->nodes[index].key = -1; 
  table->nodes[index].data = XK_NULL_HANDLE; 

	table->length--;
}

XkSize xkHashTableLength(XkHashTable table) {
	return(table->length);
}

XkSize xkHashTableCapacity(XkHashTable table) {
	return(table->capacity);
}

XkHandle xkHashTableGet(XkHashTable table, const XkKey key) {
	XkSize index = __xkHashIndex(table, key);

	return(&table->nodes[index].data);
}

void __xkHashTableSet(XkHashTable table, const XkKey key, XkHandle data) {
  XkSize hashIndex = __xkHashIndex(table, key);

	xkCopyMemory(table->nodes[hashIndex].data, data, table->stride);
}


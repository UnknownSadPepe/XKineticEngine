#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/DynamicArray.h"

struct XkDynamicArray {
	XkSize length;
	XkSize capacity;

	XkSize stride;

	XkSize size;
	XkSize totalSize;

	XkHandle memory;
};

#define XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT 2

XkResult __xkCreateDynamicArray(XkDynamicArray* pArray, const XkSize capacity, const XkSize stride) {
	XkResult result = XK_SUCCESS;

	// Allocate dynamic array.
	*pArray = xkAllocateMemory(sizeof(struct XkDynamicArray));
	if(!(*pArray)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template dynamic array.
	XkDynamicArray array = *pArray;

	// Initialize dynamic array total size.
	const XkSize totalSize = capacity * stride;

	// Align total size with dynamic array stride.
	const XkSize alignTotalSize = (totalSize + (stride - 1)) & ~(stride - 1);

	// Initialize dynamic array.
	array->length			= 0;
	array->capacity		= capacity;
	array->stride			= stride;
	array->size				= 0;
	array->totalSize	= alignTotalSize;

	// Allocate dynamic array memory.
	array->memory			= xkAllocateMemory(alignTotalSize);
	if(!array->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

_catch:
	return(result);
}

void xkClearDynamicArray(XkDynamicArray array) {
	// Null dynamic array allocated length.
	array->length = 0;

	// Null dynamic array allocated size.
	array->size = 0;

	// Zero dynamic array memory.
	xkZeroMemory(array->memory, array->totalSize);	
}

void xkDestroyDynamicArray(XkDynamicArray array) {
	// Free dynamic array memory.
	xkFreeMemory(array->memory);

	// Free dynamic array.
	xkFreeMemory(array);
}

void xkResizeDynamicArray(XkDynamicArray array, XkSize newCapacity) {
	// Initialize dynamic array total size.
	const XkSize newTotalSize = newCapacity * array->stride;

	// Align new total size with dynamic array stride.
	const XkSize alignNewTotalSize = (newTotalSize + (array->stride - 1)) & ~ (array->stride - 1);

	// Initialize dynamic array.
	array->capacity = newCapacity;
	array->totalSize = alignNewTotalSize;

	// Reallocate dynamic array memory.
	array->memory = xkReallocateMemory(array->memory, alignNewTotalSize);
}

void __xkDynamicArrayPush(XkDynamicArray array, const XkHandle data) {
	// Check if there is not enough space in dynamic array.
	if(array->length >= array->capacity) {
		// Resize dynamic array.
		xkResizeDynamicArray(array, array->capacity * XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT);
	}

	// Copy data to last dynamic array memory.
	xkCopyMemory((XkUInt8*)array->memory + (array->stride * array->length), data, array->stride);

	// Increment dynamic array length.
	array->length++;

	// Increment dynamic array allocated size.
	array->size += array->stride;
}

void xkDynamicArrayPop(XkDynamicArray array) {
	// Zero last dynamic array memory.
	xkZeroMemory((XkUInt8*)array->memory + (array->stride * array->length), array->stride);

	// Decrement dynamic array length.
	array->length--;

	// Decrement dynamic array allocated size.
	array->size -= array->stride;
}

void __xkDynamicArrayInsert(XkDynamicArray array, const XkSize index, XkHandle data) {
	// Check if index outside dynamic array bounds.
	if(index >= array->length) {
		return;
	}

	// Check if there is not enough space in dynamic array.
	if (array->length >= array->capacity) {
		// resize dynamic array.
		xkResizeDynamicArray(array, array->capacity * XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT);
	}

	// Check if not the last element.
	if(index != array->length - 1) {

		// Copy the rest outward.
		xkCopyMemory((XkUInt8*)array->memory + ((index + 1) * array->stride), (XkUInt8*)array->memory + (index * array->stride), array->stride * (array->length - index));
	}

	// Increment dynamic array length.
	array->length++;

	// Increment dynamic array allocated size.
	array->size += array->stride;
}

void xkDynamicArrayErase(XkDynamicArray array, const XkSize index) {
	// Check if index outside dynamic array bounds.
	if (index >= array->length) {
		return;
	}

	// Check if not the last element.
	if(index != array->length - 1) {
		// Snip out the data and copy the rest inward.
		xkCopyMemory((XkUInt8*)array->memory + (index * array->stride), (XkUInt8*)array->memory + ((index + 1) * array->stride), array->stride * (array->length - index));
  }

	// Decrement dynamic array length.
	array->length--;

	// Decrement dynamic array allocated size.
	array->size -= array->stride;
}

XkSize xkDynamicArrayLength(XkDynamicArray array) {
	return(array->length);
}

XkSize xkDynamicArrayCapacity(XkDynamicArray array) {
	return(array->capacity);
}

XkHandle xkDynamicArrayGet(XkDynamicArray array, const XkSize index) {
	// Check if index outside dynamic array bounds.
	if (index >= array->length) {
		return(XK_NULL_HANDLE);
	}

	// Return indexed dynamic array memory.
	return(&array->memory + (array->stride * (index + 1)));
}

void __xkDynamicArraySet(XkDynamicArray array, const XkSize index, XkHandle data) {
	// Check if index outside dynamic array bounds.
	if (index >= array->length) {
		return;
	}

	// Set indexed dynamic array memory.
	xkCopyMemory((XkUInt8*)array->memory + (array->stride * (index + 1)), data, array->stride);
}


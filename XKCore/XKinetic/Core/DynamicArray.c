#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/DynamicArray.h"

struct XkDynamicArray {
	XkSize length;
	XkSize capacity;

	XkSize stride;

	XkSize totalSize;

	XkHandle memory;
};

#define XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT 2

XkResult __xkCreateDynamicArray(XkDynamicArray* pArray, const XkSize capacity, const XkSize stride) {
	XkResult result = XK_SUCCESS;

	*pArray = xkAllocateMemory(sizeof(struct XkDynamicArray));
	if(!(*pArray)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDynamicArray array = *pArray;

	const XkSize size = capacity * stride;
	const XkSize alignTotalSize = (size + (stride - 1)) & ~ (stride - 1);

	array->length = 0;
	array->capacity = capacity;
	array->stride = stride;
	array->totalSize = alignTotalSize;
	array->memory = xkAllocateMemory(alignTotalSize);
	if(!array->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

_catch:
	return(result);
}

void xkDestroyDynamicArray(XkDynamicArray array) {
	xkFreeMemory(array->memory);
	xkFreeMemory(array);
}

void xkClearDynamicArray(XkDynamicArray array) {
	array->length = 0;
	xkZeroMemory(array->memory, array->totalSize);	
}

void xkResizeDynamicArray(XkDynamicArray array, XkSize newCapacity) {
	const XkSize size = newCapacity * array->stride;
	const XkSize alignNewSize = (size + (array->stride - 1)) & ~ (array->stride - 1);

	array->capacity = newCapacity;
	array->totalSize = alignNewSize;
	array->memory = xkReallocateMemory(array->memory, alignNewSize);
}

void __xkDynamicArrayPush(XkDynamicArray array, const XkHandle data) {
	if(array->length >= array->capacity) {
		xkResizeDynamicArray(array, array->capacity * XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT);
	}

	xkCopyMemory(array->memory + (array->stride * array->length), data, array->stride);
	array->length++;
}

void xkDynamicArrayPop(XkDynamicArray array) {
	xkZeroMemory(array->memory + (array->stride * array->length), array->stride);

	array->length--;
}

void __xkDynamicArrayInsert(XkDynamicArray array, const XkSize index, XkHandle data) {
	// Check if not the last element.
	if(index != array->length - 1) {
		xkCopyMemory(array->memory + ((index + 1) * array->stride), array->memory + (index * array->stride), array->stride * (array->length - index));
  }

	xkCopyMemory(array->memory + (index * array->stride), data, array->stride);
	array->length++;
}

void xkDynamicArrayErase(XkDynamicArray array, const XkSize index) {
	// Check if not the last element.
	if(index != array->length - 1) {
		xkCopyMemory(array->memory + (index * array->stride), array->memory + ((index + 1) * array->stride), array->stride * (array->length - index));
  }
	array->length--;
}

XkSize xkDynamicArrayLength(XkDynamicArray array) {
	return(array->length);
}

XkSize xkDynamicArrayCapacity(XkDynamicArray array) {
	return(array->capacity);
}

XkHandle xkDynamicArrayGet(XkDynamicArray array, const XkSize index) {
	return(&array->memory + (array->stride * (index + 1)));
}

void __xkDynamicArraySet(XkDynamicArray array, const XkSize index, XkHandle data) {
	xkCopyMemory(array->memory + (array->stride * (index + 1)), data, array->stride);
}


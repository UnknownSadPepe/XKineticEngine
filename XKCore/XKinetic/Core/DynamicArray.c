/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/DynamicArray.h"

/* ########## MACROS SECTION ########## */
#define XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT 2

/* ########## TYPES SECTION ########## */
struct XkDynamicArray_T {
	XkSize length;
	XkSize capacity;

	XkSize stride;

	XkSize size;
	XkSize totalSize;

	XkHandle memory;
};

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkCreateDynamicArray(XkDynamicArray* pArray, const XkSize capacity, const XkSize stride) {
	xkAssert(pArray);
	xkAssert(capacity > 0);
	xkAssert(stride > 0);

	XkResult result = XK_SUCCESS;

	*pArray = xkAllocateMemory(sizeof(struct XkDynamicArray_T));
	if(!(*pArray)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDynamicArray array = *pArray;

	const XkSize totalSize = capacity * stride;

	// Align total size with dynamic array stride for better performance and minimal fragmentation.
	const XkSize alignTotalSize = (totalSize + (stride - 1)) & ~(stride - 1);

	array->length			= 0;
	array->capacity		= capacity;
	array->stride			= stride;
	array->size				= 0;
	array->totalSize	= alignTotalSize;
	array->memory			= xkAllocateMemory(alignTotalSize);
	if(!array->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _free;
	}

_catch:
	return(result);

_free:
	if(array) {
		xkFreeMemory(array);
	}

	goto _catch;
}

void xkClearDynamicArray(XkDynamicArray array) {
	xkAssert(array);

	array->length = 0;
	array->size = 0;

	xkZeroMemory(array->memory, array->totalSize);	
}

void xkDestroyDynamicArray(XkDynamicArray array) {
	xkAssert(array);

	xkFreeMemory(array->memory);

	xkFreeMemory(array);
}

void xkResizeDynamicArray(XkDynamicArray array, XkSize newCapacity) {
	xkAssert(array);
	xkAssert(newCapacity > 0 && newCapacity > array->capacity);

	const XkSize newTotalSize = newCapacity * array->stride;

	// Align new total size with dynamic array stride for better performance and minimal fragmentation.
	const XkSize alignNewTotalSize = (newTotalSize + (array->stride - 1)) & ~ (array->stride - 1);

	array->capacity 	= newCapacity;
	array->totalSize 	= alignNewTotalSize;
	array->memory 		= xkReallocateMemory(array->memory, alignNewTotalSize);
}

void __xkDynamicArrayPush(XkDynamicArray array, const XkHandle data) {
	xkAssert(array);
	xkAssert(data);

	if(array->length >= array->capacity) {
		xkResizeDynamicArray(array, array->capacity * XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT);
	}

	xkCopyMemory((XkUInt8*)array->memory + (array->stride * array->length), data, array->stride);

	++array->length;
	array->size += array->stride;
}

void xkDynamicArrayPop(XkDynamicArray array) {
	xkAssert(array);

	xkZeroMemory((XkUInt8*)array->memory + (array->stride * array->length), array->stride);

	--array->length;
	array->size -= array->stride;
}

void __xkDynamicArrayInsert(XkDynamicArray array, const XkSize index, XkHandle data) {
	xkAssert(array);
	xkAssert(index >= 0);
	xkAssert(data);

	if(index >= array->length) {
		return;
	}

	if (array->length >= array->capacity) {
		xkResizeDynamicArray(array, array->capacity * XK_DYNAMIC_ARRAY_REALLOCATE_COEFFICIENT);
	}

	if(index != array->length - 1) {
		xkCopyMemory((XkUInt8*)array->memory + ((index + 1) * array->stride), (XkUInt8*)array->memory + (index * array->stride), array->stride * (array->length - index));
	}

	++array->length;
	array->size += array->stride;
}

void xkDynamicArrayErase(XkDynamicArray array, const XkSize index) {
	xkAssert(array);
	xkAssert(index >= 0 && index < array->capacity - 1);

	if (index >= array->length) {
		return;
	}

	if(index != array->length - 1) {
		xkCopyMemory((XkUInt8*)array->memory + (index * array->stride), (XkUInt8*)array->memory + ((index + 1) * array->stride), array->stride * (array->length - index));
  }

	--array->length;
	array->size -= array->stride;
}

XkSize xkDynamicArrayLength(XkDynamicArray array) {
	xkAssert(array);

	return(array->length);
}

XkSize xkDynamicArrayCapacity(XkDynamicArray array) {
	xkAssert(array);

	return(array->capacity);
}

XkHandle xkDynamicArrayGet(XkDynamicArray array, const XkSize index) {
	xkAssert(array);
	xkAssert(index >= 0 && index < array->capacity - 1);

	if (index >= array->length) {
		return(XK_NULL_HANDLE);
	}

	return(&array->memory + (array->stride * (index + 1)));
}

void __xkDynamicArraySet(XkDynamicArray array, const XkSize index, XkHandle data) {
	xkAssert(array);
	xkAssert(index >= 0 && index < array->capacity - 1);
	xkAssert(data);

	if (index >= array->length) {
		return;
	}

	xkCopyMemory((XkUInt8*)array->memory + (array->stride * (index + 1)), data, array->stride);
}


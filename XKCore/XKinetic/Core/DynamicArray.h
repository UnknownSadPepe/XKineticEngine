#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/* ########## MACROS SECTION ########## */
#define XK_DYNAMIC_ARRAY_DEFAULT_CAPACITY 2

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkDynamicArray_T* XkDynamicArray;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	__xkCreateDynamicArray(XkDynamicArray*, XkSize, XkSize);
extern XKCORE_API void 			xkDestroyDynamicArray(XkDynamicArray);

extern XKCORE_API void 			xkClearDynamicArray(XkDynamicArray);
extern XKCORE_API void 			xkResizeDynamicArray(XkDynamicArray, const XkSize);

extern XKCORE_API void 			__xkDynamicArrayPush(XkDynamicArray, const XkHandle);
extern XKCORE_API 					void xkDynamicArrayPop(XkDynamicArray);

extern XKCORE_API void 			__xkDynamicArrayInsert(XkDynamicArray, const XkSize, XkHandle);
extern XKCORE_API void 			xkDynamicArrayErase(XkDynamicArray, const XkSize);

extern XKCORE_API XkSize 		xkDynamicArrayLength(XkDynamicArray);
extern XKCORE_API XkSize 		xkDynamicArrayCapacity(XkDynamicArray);

extern XKCORE_API XkHandle 	xkDynamicArrayGet(XkDynamicArray, const XkSize);
extern XKCORE_API void 			__xkDynamicArraySet(XkDynamicArray, const XkSize, XkHandle);

/* ########## FUNCTIONS MACROS SECTION ########## */
#define 										xkCreateDynamicArray(array, type) __xkCreateDynamicArray(array, XK_DYNAMIC_ARRAY_DEFAULT_CAPACITY, sizeof(type))
#define 										xkCreateDynamicArrayCapacity(array, capacity, type) __xkCreateDynamicArray(array, capacity, sizeof(type))

#define xkDynamicArrayPush(array, value)		\
{																						\
	__auto_type tmp = value;									\
	__xkDynamicArrayPush(array, &tmp);				\
}

#define xkDynamicArrayInsert(array, index, value)	\
{																									\
	__auto_type tmp = value;												\
	__xkDynamicArrayInsert(array, index, &tmp);			\
}

#define xkDynamicArraySet(array, value)			\
{																						\
	__auto_type tmp = value;									\
	__xkDynamicArraySet(array, &tmp);					\
}

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

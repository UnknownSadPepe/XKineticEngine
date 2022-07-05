#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkStackAllocator_T* XkStackAllocator;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	xkCreateStackAllocator(XkStackAllocator*, const XkSize);
extern XKCORE_API void 			xkDestroyStackAllocator(XkStackAllocator);

extern XKCORE_API void 			xkClearStackAllocator(XkStackAllocator);
extern XKCORE_API void 			xkResizeStackAllocator(XkStackAllocator, const XkSize);

extern XKCORE_API XkHandle 	xkAllocateStackMemory(XkStackAllocator, const XkSize);
extern XKCORE_API void 			xkFreeStackMemory(XkStackAllocator, XkHandle);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

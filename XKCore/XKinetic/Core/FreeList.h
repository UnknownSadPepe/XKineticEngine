#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkFreeList_T* XkFreeList;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	xkCreateFreeList(XkFreeList*, const XkSize);
extern XKCORE_API void 			xkDestroyFreeList(XkFreeList);

extern XKCORE_API void 			xkResizeFreeList(XkFreeList, const XkSize);
extern XKCORE_API void 			xkClearFreeList(XkFreeList);

extern XKCORE_API XkHandle 	xkFreeListAllocate(XkFreeList, const XkSize);
extern XKCORE_API void 			xkFreeListFree(XkFreeList, XkHandle);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

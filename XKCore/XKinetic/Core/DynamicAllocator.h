#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkDynamicAllocator_T* XkDynamicAllocator;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	xkCreateDynamicAllocator(XkDynamicAllocator*, const XkSize);
extern XKCORE_API void 			xkDestroyDynamicAllocator(XkDynamicAllocator);

extern XKCORE_API void 			xkClearDynamicAllocator(XkDynamicAllocator);
extern XKCORE_API void 			xkResizeDynamicAllocator(XkDynamicAllocator, const XkSize);

extern XKCORE_API XkHandle 	xkAllocateDynamicMemory(XkDynamicAllocator, const XkSize);
extern XKCORE_API void 			xkFreeDynamicMemory(XkDynamicAllocator, const XkHandle);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

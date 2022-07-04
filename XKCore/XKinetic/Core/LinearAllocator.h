#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkLinearAllocator_T* XkLinearAllocator; 

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	xkCreateLinearAllocator(XkLinearAllocator*, const XkSize);
extern XKCORE_API void 			xkDestroyLinearAllocator(XkLinearAllocator);

extern XKCORE_API void 			xkClearLinearAllocator(XkLinearAllocator);
extern XKCORE_API void 			xkResizeLinearAllocator(XkLinearAllocator, const XkSize);

extern XKCORE_API XkHandle 	xkAllocateLinearMemory(XkLinearAllocator, const XkSize);

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

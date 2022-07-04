#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkPoolAllocator_T* XkPoolAllocator;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 	__xkCreatePoolAllocator(XkPoolAllocator*, const XkSize, const XkSize);

extern XKCORE_API void 			xkClearPoolAllocator(XkPoolAllocator);
extern XKCORE_API void 			xkResizePoolAllocator(XkPoolAllocator, const XkSize);

extern XKCORE_API void 			xkDestroyPoolAllocator(XkPoolAllocator);
extern XKCORE_API XkHandle 	xkAllocatePoolMemory(XkPoolAllocator, const XkSize);
extern XKCORE_API void 			xkFreePoolMemory(XkPoolAllocator, const XkHandle);

/* ########## FUNCTIONS MACROS SECTION ########## */
#define 										xkCreatePoolAllocator(allocator, totalChunkCount, chunkType) __xkCreatePoolAllocator(allocator, totalChunkCount, sizeof(chunkType))

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

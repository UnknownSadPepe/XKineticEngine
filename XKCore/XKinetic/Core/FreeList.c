/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/FreeList.h"

/* ########## TYPES SECTION ########## */
typedef struct XkFreeListNode_T XkFreeListNode;

struct XkFreeListNode_T {
	XkSize size;
  XkSize offset;
  XkFreeListNode* next;
};

struct XkFreeList_T {
	XkSize totalSize;

  XkFreeListNode* head;

	XkHandle memory;
};

/* ########## GLOBAL VARIABLES SECTION ########## */
static const XkSize XK_FREE_LIST_ALIGN = 16;

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateFreeList(XkFreeList* pFreeList, const XkSize totalSize) {
  xkAssert(pFreeList);
  xkAssert(totalSize > 0);

  XkResult result = XK_SUCCESS;

	*pFreeList = xkAllocateMemory(sizeof(struct XkFreeList_T));
	if(!(*pFreeList)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkFreeList freelist = *pFreeList;

	// Align total size with free list alignment for better performance and minimal segmentation.
	const XkSize alignTotalSize = (totalSize + (XK_FREE_LIST_ALIGN - 1)) & ~(XK_FREE_LIST_ALIGN - 1);

  freelist->totalSize   = alignTotalSize;
  freelist->memory      = xkAllocateMemory(alignTotalSize);
  if(!freelist->memory) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _free;
  }

  freelist->head          = (XkFreeListNode*)freelist->memory;
  freelist->head->size    = freelist->totalSize;
  freelist->head->offset  = sizeof(XkFreeListNode);
  freelist->head->next    = XK_NULL_HANDLE;

_catch:
  return(result);

_free:
  if(freelist) {
    xkFreeMemory(freelist);
  }

  goto _catch;
}

void xkDestroyFreeList(XkFreeList freelist) {
  xkAssert(freelist);

	xkFreeMemory(freelist->memory);

	xkFreeMemory(freelist);
}

void xkClearFreeList(XkFreeList freelist) {
  xkAssert(freelist);

  xkZeroMemory(freelist->memory, freelist->totalSize); 
}

void xkResizeFreeList(XkFreeList freelist, const XkSize newTotalSize) {
  xkAssert(freelist);

  // Align new total size with free list alignment for better performance and minimal segmentation.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_FREE_LIST_ALIGN - 1)) & ~(XK_FREE_LIST_ALIGN - 1);

  freelist->totalSize   = alignNewTotalSize;
	freelist->memory      = xkReallocateMemory(freelist->memory, alignNewTotalSize);	
}

XkHandle xkFreeListAllocate(XkFreeList freelist, const XkSize size) {
  xkAssert(freelist);

  XkHandle newMemory = XK_NULL_HANDLE;

  XkFreeListNode* node = freelist->head;
  XkFreeListNode* previous = XK_NULL_HANDLE;

  while(node) {
    if(node->size == size) {
      if(previous) {
        previous->next = node;
      } else {
        // This node is the head of the list.
        freelist->head = node->next;
      }

      newMemory = ((XkUInt8*)freelist->memory + node->offset);
      goto _catch;
    } else if(node->size > size) {
      // Create new node.
      XkFreeListNode* newNode = (XkFreeListNode*)((XkUInt8*)freelist->memory + (node->offset + size));
      newNode->size = node->size - size;
      newNode->offset = node->offset + size;
      newNode->next = XK_NULL_HANDLE;

      node->size = size;
      node->next = newNode;

      newMemory = ((XkUInt8*)freelist->memory + newNode->offset);
      goto _catch;
    }

    previous = node;
    node = node->next;
  }

_catch:
	return(newMemory);
}

void xkFreeListFree(XkFreeList freelist, XkHandle data) {
  xkAssert(freelist);
  xkAssert(data);

  /// TODO: Implementation.
}

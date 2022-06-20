#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/FreeList.h"

#include "XKinetic/Core/Log.h"

typedef struct XkFreeListNode XkFreeListNode;

struct XkFreeListNode {
	XkSize size;
  XkSize offset;
  XkFreeListNode* next;
};

struct XkFreeList {
	XkSize totalSize;

  XkFreeListNode* head;

	XkHandle memory;
};

static const XkSize XK_FREE_LIST_ALIGN = 16;

XkResult xkCreateFreeList(XkFreeList* pFreeList, const XkSize totalSize) {
  XkResult result = XK_SUCCESS;

  // Allocate free list.
	*pFreeList = xkAllocateMemory(sizeof(struct XkFreeList));
	if(!(*pFreeList)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

  // Template free list.
	XkFreeList freelist = *pFreeList;

	// Align total size with free list alignment.
	const XkSize alignTotalSize = (totalSize + (XK_FREE_LIST_ALIGN - 1)) & ~(XK_FREE_LIST_ALIGN - 1);

  // Initialize free list.
  freelist->totalSize   = alignTotalSize;

  // Allocate free list memory.
  freelist->memory      = xkAllocateMemory(alignTotalSize);
  if(!freelist->memory) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  // Initialize free list head like first memory.
  freelist->head        = (XkFreeListNode*)freelist->memory;

  // Initialize free list head.
  freelist->head->size    = freelist->totalSize;
  freelist->head->offset  = sizeof(XkFreeListNode);
  freelist->head->next    = XK_NULL_HANDLE;

_catch:
  return(result);
}

void xkDestroyFreeList(XkFreeList freelist) {
  // Free free list memory.
	xkFreeMemory(freelist->memory);

  // Free free list.
	xkFreeMemory(freelist);
}

void xkClearFreeList(XkFreeList freelist) {
  // Zero free list memory.
  xkZeroMemory(freelist->memory, freelist->totalSize); 
}

void xkResizeFreeList(XkFreeList freelist, const XkSize newTotalSize) {
	// Align new total size with free list alignment.
	const XkSize alignNewTotalSize = (newTotalSize + (XK_FREE_LIST_ALIGN - 1)) & ~(XK_FREE_LIST_ALIGN - 1);

  // Initialize free list.
  freelist->totalSize = alignNewTotalSize;

  // Reallocate free list memory.
	freelist->memory = xkReallocateMemory(freelist->memory, alignNewTotalSize);	
}

XkHandle xkFreeListAllocate(XkFreeList freelist, const XkSize size) {
  XkHandle newMemory = XK_NULL_HANDLE;

  XkFreeListNode* node = freelist->head;
  XkFreeListNode* previous = XK_NULL_HANDLE;

  while(node) {
    // Check if node has equal size.
    if(node->size == size) {
      if(previous) {
        // Set next node of previous node to this node. (;
        previous->next = node;
      } else {
        // This node is the head of the list.
        freelist->head = node->next;
      }

      // Set new allocated memory.
      newMemory = ((XkUInt8*)freelist->memory + node->offset);
      goto _catch;
    } else if(node->size > size) /*Check if node has greater size*/ {
      // Create new node.
      XkFreeListNode* newNode = (XkFreeListNode*)((XkUInt8*)freelist->memory + (node->offset + size));
      newNode->size = node->size - size;
      newNode->offset = node->offset + size;
      newNode->next = XK_NULL_HANDLE;

      node->size = size;
      node->next = newNode;

      // Set new allocated memory.
      newMemory = ((XkUInt8*)freelist->memory + newNode->offset);
      goto _catch;
    }

    // Set previous node.
    previous = node;

    // Set next node.
    node = node->next;
  }

_catch:
	return(newMemory);
}

void xkFreeListFree(XkFreeList freelist, XkHandle memory) {

}

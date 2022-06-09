#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/FreeList.h"

#include "XKinetic/Core/Log.h"

typedef struct XkNode XkNode;

struct XkNode {
	XkSize size;
	XkNode* next;
};

struct XkFreeList {
	XkSize totalSize;
	XkSize maxNodes;

  XkNode* nodes;
	XkNode* head;

	XkHandle memory;
};

static const XkSize XK_FREE_LIST_ALIGN = 16;

XkResult xkCreateFreeList(XkFreeList* pFreeList, const XkSize totalSize) {
  XkResult result = XK_SUCCESS;

	*pFreeList = xkAllocateMemory(sizeof(struct XkFreeList));
	if(!(*pFreeList)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkFreeList freelist = *pFreeList;

	const XkSize alignSize = (totalSize + (XK_FREE_LIST_ALIGN - 1)) & ~ (XK_FREE_LIST_ALIGN - 1);
	const XkSize maxNodes = (alignSize / (sizeof(XkHandle) + sizeof(XkNode)));
	const XkSize size = sizeof(XkNode) * maxNodes;

	xkLogDebug("freelist size: %ld", size);

	freelist->totalSize = size;
	freelist->maxNodes = maxNodes;
	freelist->memory = xkAllocateMemory(size);
	if(!freelist->memory) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}
	freelist->nodes = (XkNode*)freelist->memory;
	freelist->head = &freelist->nodes[0];

  freelist->head->size = totalSize;
  freelist->head->next = XK_NULL_HANDLE;

	for(XkSize i = 0; i < maxNodes; i++) {
		freelist->nodes[i].size = 0;
		freelist->nodes[i].next = XK_NULL_HANDLE;
	}

_catch:
  return(result);
}

void xkDestroyFreeList(XkFreeList freelist) {
	xkFreeMemory(freelist->memory);
	xkFreeMemory(freelist);
}

void xkResizeFreeList(XkFreeList freelist, const XkSize newSize) {
	freelist->memory = xkReallocateMemory(freelist->memory, newSize);	
	freelist->totalSize = newSize;
}

void xkClearFreeList(XkFreeList freelist) {
	for(XkSize i = 0; i < freelist->maxNodes; i++) {
		freelist->nodes[i].size = 0;
		freelist->nodes[i].next = XK_NULL_HANDLE;
	}

  freelist->head->size = freelist->totalSize;
  freelist->head->next = XK_NULL_HANDLE;
}

XkHandle xkFreeListAllocate(XkFreeList freelist, const XkSize size) {
  /// TODO: implementation.
	/*XkNode* node = freelist->head;
  XkNode* previous = XK_NULL_HANDLE;
  while(node) {
    if(node->size == size) {
			// Exact match. Just return the node.
      *out_offset = node->offset;
      freelist_node* node_to_return = 0;
      if(previous) {
				previous->next = node->next;
        node_to_return = node;
      } else {
        // This node is the head of the list. Reassign the head
        // and return the previous head node.
        node_to_return = state->head;
        state->head = node->next;
      }
			node_to_return->size = 0;
			node_to_return->next = XK_NULL_HANDLE;
      return true;
    } else if(node->size > size) {
      // Node is larger. Deduct the memory from it and move the offset
      // by that amount.
      *out_offset = node->offset;
      node->size -= size;
      node->offset += size;
      return true;
    }

    previous = node;
    node = node->next;
  }*/

	return(XK_NULL_HANDLE);
}

void xkFreeListFree(XkFreeList freelist, XkHandle memory) {
  /// TODO: implementation.
}

XkSize xkFreeListLength(XkFreeList freelist) {
  /// TODO: implementation.
	return(0);
}

XkSize xkFreeListCapacity(XkFreeList freelist) {
  /// TODO: implementation.
	return(0);
}


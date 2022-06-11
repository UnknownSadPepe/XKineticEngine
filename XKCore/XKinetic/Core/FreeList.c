#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/FreeList.h"

#include "XKinetic/Core/Log.h"

typedef struct XkNode XkNode;

struct XkNode {
	XkSize size;
	XkSize offset;
	XkNode* next;
};

struct XkFreeList {
	XkSize totalSize;
	XkSize maxNodes;

	XkSize length;

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
	const XkSize maxNodes = (alignSize / sizeof(XkNode));
	const XkSize size = sizeof(XkNode) * maxNodes;

	xkLogDebug("freelist size: %ld", size);

	freelist->totalSize = size;
	freelist->maxNodes = maxNodes;
	freelist->length = 0;
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
		freelist->nodes[i].offset = 0;
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
		freelist->nodes[i].offset = 0;
		freelist->nodes[i].next = XK_NULL_HANDLE;
	}

  freelist->head->size = freelist->totalSize;
  freelist->head->next = XK_NULL_HANDLE;
}

XkHandle xkFreeListAllocate(XkFreeList freelist, const XkSize size) {
	XkNode* node = freelist->head;
  XkNode* previous = XK_NULL_HANDLE;
	XkNode* node_to_return = node;
  while(node) {
    if(node->size == size) {
      if(previous) {
				previous->next = node->next;
        node_to_return = node;
      } else {
        node_to_return = freelist->head;
        freelist->head = node->next;
      }
			node_to_return->size = 0;
			node_to_return->next = XK_NULL_HANDLE;
			freelist->length++;
      return(node_to_return);
    } else if(node->size > size) {
      node->size -= size;
      node->offset += size;
			freelist->length++;
      return(node_to_return);
    }

    previous = node;
    node = node->next;
  }

	return(node_to_return);
}

void xkFreeListFree(XkFreeList freelist, XkHandle memory) {
 	XkNode* node = freelist->head;
  XkNode* previous = XK_NULL_HANDLE;

  /*while(node) {
    if(node->offset == ) {
      // Can just be appended to this node.
                node->size += size;

                // Check if this then connects the range between this and the next
                // node, and if so, combine them and return the second node..
                if (node->next && node->next->offset == node->offset + node->size) {
                    node->size += node->next->size;
                    freelist_node* next = node->next;
                    node->next = node->next->next;
                    return_node(list, next);
                }
                return true;
            } else if (node->offset > offset) {
                // Iterated beyond the space to be freed. Need a new node.
                freelist_node* new_node = get_node(list);
                new_node->offset = offset;
                new_node->size = size;

                // If there is a previous node, the new node should be inserted between this and it.
                if (previous) {
                    previous->next = new_node;
                    new_node->next = node;
                } else {
                    // Otherwise, the new node becomes the head.
                    new_node->next = node;
                    state->head = new_node;
                }

                // Double-check next node to see if it can be joined.
                if (new_node->next && new_node->offset + new_node->size == new_node->next->offset) {
                    new_node->size += new_node->next->size;
                    freelist_node* rubbish = new_node->next;
                    new_node->next = rubbish->next;
                    return_node(list, rubbish);
                }

                // Double-check previous node to see if the new_node can be joined to it.
                if (previous && previous->offset + previous->size == new_node->offset) {
                    previous->size += new_node->size;
                    freelist_node* rubbish = new_node;
                    previous->next = rubbish->next;
                    return_node(list, rubbish);
                }

                return true;
            }

            previous = node;
            node = node->next;
        }
    }
*/

	freelist->length--;
}

XkSize xkFreeListLength(XkFreeList freelist) {
	return(freelist->length);
}

XkSize xkFreeListCapacity(XkFreeList freelist) {
	return(freelist->maxNodes);
}


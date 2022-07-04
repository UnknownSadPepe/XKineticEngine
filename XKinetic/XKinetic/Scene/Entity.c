/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Scene/Entity.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateEntity(XkEntity* pEntity) {
	xkAssert(pEntity);

  XkResult result = XK_SUCCESS;

	pEntity = xkAllocateMemory(sizeof(struct XkEntity_T));
	if(!pEntity) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

  /// TODO: Implementation.
  
_catch:
  return(result);

_free:
	if(pEntity) {
		xkFreeMemory(pEntity);
	}

	goto _catch;
}

void xkDestroyEntity(XkEntity* pEntity) {
	xkAssert(pEntity);
  /// TODO: Implementation.
	xkFreeMemory(pEntity);
}

XkComponentId xkAddEntityComponent(XkEntity* pEntity, const XkComponentType componentType) {
	xkAssert(pEntity);
  /// TODO: Implementation.
  return(0);
}

void xkRemoveEntityComponent(XkEntity* pEntity, const XkComponentId componentId) {
	xkAssert(pEntity);
  /// TODO: Implementation.
}

void xkEntityHasComponent(XkEntity* pEntity, const XkComponentType componentType) {
	xkAssert(pEntity);
  /// TODO: Implementation.
}

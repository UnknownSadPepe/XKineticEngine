/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

XkResult xkInitializeJoystick() {
	XkResult result = XK_SUCCESS;

	/// TODO: Implementation.

_catch:
	return(result);	
}

void xkTerminateJoystick() {
	/// TODO: Implementation.
}

XkResult xkCreateJoystick(XkJoystick* pJoystick, const XkJoystickId id) {
	xkAssert(pJoystick);
	xkAssert(id >= XK_JOYSTICK_1);

	XkResult result = XK_SUCCESS;

	*pJoystick = xkAllocateMemory(sizeof(struct XkJoystick_T));
	if(!(*pJoystick)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkJoystick joystick = *pJoystick;

	joystick->id = id;

	/// TODO: Implementation.

_catch:
	return(result);

_free:
	if(joystick) {
		xkFreeMemory(joystick);
	}

	goto _catch;
}

void xkDestroyJoystick(XkJoystick joystick) {
	xkAssert(pJoystick);
	/// TODO: Implementation.
	
	xkFreeMemory(joystick);
}

XkString xkJoystickMappingName(XkJoystick joystick) {
	xkAssert(pJoystick);
	return("Linux");
}

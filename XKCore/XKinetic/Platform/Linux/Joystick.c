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

XkResult xkJoystickPresent(XkJoystick j) {
	xkAssert(j >= XK_JOYSTICK_1 && j < XK_JOYSTICK_16);

	XkResult result = XK_SUCCESS;

	/// TODO: Implementation.

_catch:
	return(result);
}

XkString xkJoystickMappingName(XkJoystick j) {
	xkAssert(j >= XK_JOYSTICK_1 && j < XK_JOYSTICK_16);
	return("Linux");
}

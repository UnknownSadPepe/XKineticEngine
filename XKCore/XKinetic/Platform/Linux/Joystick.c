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

XkResult xkJoystickPresent(XkJoystickId jid) {
	xkAssert(jid >= XK_JOYSTICK_1 && jid < XK_JOYSTICK_16);

	XkResult result = XK_SUCCESS;

	/// TODO: Implementation.

_catch:
	return(result);
}

XkString xkJoystickMappingName(XkJoystickId jid) {
	xkAssert(jid >= XK_JOYSTICK_1 && jid < XK_JOYSTICK_16);
	
	return("Linux");
}

void xkPollJoystickEvents() {
	/// TODO: Implementation.
}

void xkWaitJoystickEvents() {
	/// TODO: Implementation.
}

void xkWaitTimeoutJoystickEvents(const XkFloat64 timeout) {
	/// TODO: Implementation.
}

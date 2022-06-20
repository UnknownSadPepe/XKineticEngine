#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_WIN32)

XkResult xkInitializeJoysticks(void) {
	XkResult result = XK_SUCCESS;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkTerminateJoysticks(void) {
	/// TODO: implementation.
}

XkResult xkCreateJoystick(XkJoystick* pJoystick, const XkJoystickID id) {
	XkResult result = XK_SUCCESS;

	// Allocate joystick.
	*pJoystick = xkAllocateMemory(sizeof(struct XkJoystick));
	if (!(*pJoystick)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	// Template joystick.
	XkJoystick joystick = *pJoystick;

	// Initialize joystick.
	joystick->id = id;

	/// TODO: implementation.

	// Call joystick connect event.
	__xkInputJoystickEvent(joystick, XK_JOYSTICK_CONNECTED);

_catch:
	return(result);
}

void xkDestroyJoystick(XkJoystick joystick) {
	/// TODO: implementation.

	// Call joystick disconnect event.
	__xkInputJoystickEvent(joystick, XK_JOYSTICK_DISCONNECTED);

	// Free joystick.
	xkFreeMemory(joystick);
}

XkString xkJoystickMappingName(XkJoystick joystick) {
	return("Windows");
}

void xkPollJoystickEvents(void) {
	/// TODO: implementation.
}

#endif // XK_WIN32

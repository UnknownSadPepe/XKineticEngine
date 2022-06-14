#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_LINUX)

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

	*pJoystick = xkAllocateMemory(sizeof(struct XkJoystick));
	if(!(*pJoystick)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkJoystick joystick = *pJoystick;

	joystick->id = id;

	/// TODO: implementation.

	__xkInputJoystickEvent(joystick, XK_JOYSTICK_CONNECTED);

_catch:
	return(result);
}

void xkDestroyJoystick(XkJoystick joystick) {
	/// TODO: implementation.
	__xkInputJoystickEvent(joystick, XK_JOYSTICK_DISCONNECTED);
	xkFreeMemory(joystick);
}

XkString xkJoystickMappingName(XkJoystick joystick) {
	return("Linux");
}

#endif // XK_LINUX

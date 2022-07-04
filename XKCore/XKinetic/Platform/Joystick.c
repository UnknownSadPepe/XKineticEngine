/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"

/* ########## FUNCTIONS SECTION ########## */
void __xkInputJoystickEvent(XkJoystick joystick, const XkJoystickEvent event) {
	if(joystick->callbacks.event) {
		joystick->callbacks.event(joystick, event);
	}
}

void __xkInputJoystickAxis(XkJoystick joystick, const XkJoystickAxis axis, const XkFloat32 value) {
	if(joystick->callbacks.axis) {
		joystick->callbacks.axis(joystick, axis, value);
	}
}

void __xkInputJoystickButton(XkJoystick joystick, const XkJoystickButton button, const XkAction action) {
	if(joystick->callbacks.button) {
		joystick->callbacks.button(joystick, button, action);
	}
}

void __xkInputJoystickHat(XkJoystick joystick, const XkJoystickHat hat, const XkAction action) {
	if(joystick->callbacks.hat) {
		joystick->callbacks.hat(joystick, hat, action);
	}
}

void xkSetJoystickEventCallback(XkJoystick joystick, const XkJoystickEventPfn pfnCallback) {
	joystick->callbacks.event = pfnCallback;	
}

void xkSetJoystickAxisCallback(XkJoystick joystick, const XkJoystickAxisPfn pfnCallback) {
	joystick->callbacks.axis = pfnCallback;	
}

void xkSetJoystickButtonCallback(XkJoystick joystick, const XkJoystickButtonPfn pfnCallback) {
	joystick->callbacks.button = pfnCallback;	
}

void xkSetJoystickHatCallback(XkJoystick joystick, const XkJoystickHatPfn pfnCallback) {
	joystick->callbacks.hat = pfnCallback;	
}

XkBool xkJoystickGamepad(XkJoystick joystick) {
	return(XK_FALSE);
}

XkString xkJoystickName(XkJoystick joystick) {
	return(XK_NULL_HANDLE);
}

XkJoystickId xkJoystickID(XkJoystick joystick) {
	return(-1);
}

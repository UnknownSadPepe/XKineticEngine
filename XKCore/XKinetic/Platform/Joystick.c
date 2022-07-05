/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"

/* ########## FUNCTIONS SECTION ########## */
void __xkInputJoystickEvent(XkJoystick j, const XkJoystickEvent event) {
	if(_xkPlatform.joysticks[j].callbacks.event) {
		_xkPlatform.joysticks[j].callbacks.event(j, event);
	}
}

void __xkInputJoystickAxis(XkJoystick j, const XkJoystickAxis axis, const XkFloat32 value) {
	if(_xkPlatform.joysticks[j].callbacks.axis) {
		_xkPlatform.joysticks[j].callbacks.axis(j, axis, value);
	}
}

void __xkInputJoystickButton(XkJoystick j, const XkJoystickButton button, const XkAction action) {
	if(_xkPlatform.joysticks[j].callbacks.button) {
		_xkPlatform.joysticks[j].callbacks.button(j, button, action);
	}
}

void __xkInputJoystickHat(XkJoystick j, const XkJoystickHat hat, const XkAction action) {
	if(_xkPlatform.joysticks[j].callbacks.hat) {
		_xkPlatform.joysticks[j].callbacks.hat(j, hat, action);
	}
}

void xkSetJoystickEventCallback(XkJoystick j, const XkJoystickEventPfn pfnCallback) {
	_xkPlatform.joysticks[j].callbacks.event = pfnCallback;	
}

void xkSetJoystickAxisCallback(XkJoystick j, const XkJoystickAxisPfn pfnCallback) {
	_xkPlatform.joysticks[j].callbacks.axis = pfnCallback;	
}

void xkSetJoystickButtonCallback(XkJoystick j, const XkJoystickButtonPfn pfnCallback) {
	_xkPlatform.joysticks[j].callbacks.button = pfnCallback;	
}

void xkSetJoystickHatCallback(XkJoystick j, const XkJoystickHatPfn pfnCallback) {
	_xkPlatform.joysticks[j].callbacks.hat = pfnCallback;	
}

XkBool xkJoystickGamepad(XkJoystick j) {
	return(XK_FALSE);
}

XkString xkJoystickName(XkJoystick j) {
	return(XK_NULL_HANDLE);
}


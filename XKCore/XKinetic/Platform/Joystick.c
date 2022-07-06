/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
void __xkInputJoystickEvent(XkJoystickId jid, const XkJoystickEvent event) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);

	if(_xkPlatform.joysticks[jid].callbacks.event) {
		_xkPlatform.joysticks[jid].callbacks.event(jid, event);
	}
}

void __xkInputJoystickAxis(XkJoystickId jid, const XkGamepadAxis axis, const XkFloat32 value) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);

	if(_xkPlatform.joysticks[jid].callbacks.axis) {
		_xkPlatform.joysticks[jid].callbacks.axis(jid, axis, value);
	}
}

void __xkInputJoystickButton(XkJoystickId jid, const XkGamepadButton button, const XkAction action) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);

	if(_xkPlatform.joysticks[jid].callbacks.button) {
		_xkPlatform.joysticks[jid].callbacks.button(jid, button, action);
	}
}

void __xkInputJoystickHat(XkJoystickId jid, const XkGamepadHat hat, const XkAction action) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);

	if(_xkPlatform.joysticks[jid].callbacks.hat) {
		_xkPlatform.joysticks[jid].callbacks.hat(jid, hat, action);
	}
}

void xkSetJoystickEventCallback(XkJoystickId jid, const XkJoystickEventPfn pfnCallback) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);
	xkAssert(pfnCallback);

	_xkPlatform.joysticks[jid].callbacks.event = pfnCallback;	
}

void xkSetJoystickAxisCallback(XkJoystickId jid, const XkGamepadAxisPfn pfnCallback) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);
	xkAssert(pfnCallback);

	_xkPlatform.joysticks[jid].callbacks.axis = pfnCallback;	
}

void xkSetJoystickButtonCallback(XkJoystickId jid, const XkGamepadButtonPfn pfnCallback) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);
	xkAssert(pfnCallback);

	_xkPlatform.joysticks[jid].callbacks.button = pfnCallback;	
}

void xkSetJoystickHatCallback(XkJoystickId jid, const XkGamepadHatPfn pfnCallback) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);
	xkAssert(pfnCallback);

	_xkPlatform.joysticks[jid].callbacks.hat = pfnCallback;	
}

XkBool8 xkJoystickGamepad(XkJoystickId jid) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);

	return(XK_FALSE);
}

XkString xkJoystickName(XkJoystickId jid) {
	xkAssert(jid > XK_JOYSTICK_1 && jid <= XK_JOYSTICK_16);
	
	return(XK_NULL_HANDLE);
}


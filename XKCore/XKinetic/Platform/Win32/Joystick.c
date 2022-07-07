/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeJoystick() {
	XkResult result = XK_SUCCESS;

	if(_xkPlatform.windows.dinput.initialized) {
		return;
	}

	HRESULT hResult = DirectInput8Create(_xkPlatform.windows.winapi.instance, DIRECTINPUT_VERSION, &IID_IDirectInput8W, (void**)&_xkPlatform.windows.dinput.dInput, NULL);
	if(FAILED(hResult))  {
		result = XK_ERROR_UNKNOWN;
		__xkErrorHandler("DirectInput: Failed to create interface");
		goto _catch;
	}

	_xkPlatform.windows.dinput.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateJoystick() {
	if(!_xkPlatform.windows.dinput.initialized) {
		return;
	}

	if(_xkPlatform.windows.dinput.dInput) {
		IDirectInput8_Release(_xkPlatform.windows.dinput.dInput);

		_xkPlatform.windows.dinput.dInput = NULL;
	}

	_xkPlatform.windows.dinput.initialized = XK_FALSE;
}

XkResult xkJoystickPresent(XkJoystickId jid) {
	xkAssert(jid >= XK_JOYSTICK_1 && jid < XK_JOYSTICK_16);

	XkResult result = XK_SUCCESS;

	/// TODO: Implementation.

_catch:
	return(result);
}

XkString xkJoystickMappingName(XkJoystick j) {
	xkAssert(jid >= XK_JOYSTICK_1 && jid < XK_JOYSTICK_16);

	return("Windows");
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

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeJoystick() {
	XkResult result = XK_SUCCESS;

	if(_xkPlatform.dinput.initialized) {
		return;
	}

	HRESULT hResult = DirectInput8Create(_xkPlatform.win32.instance, DIRECTINPUT_VERSION, &IID_IDirectInput8W, (void**)&_xkPlatform.win32.dinput, NULL);
	if(FAILED(hResult))  {
		result = XK_ERROR_UNKNOWN;
		_glfwInputError("DirectInput: Failed to create interface");
		goto _catch;
	}

	_xkPlatform.dinput.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateJoystick() {
	if(!_xkPlatform.dinput.initialized) {
		return;
	}

	if(_xkPlatform.win32.dinput) {
		IDirectInput8_Release(_xkPlatform.win32.dinput);

		_xkPlatform.win32.dinput = NULL;
	}

	_xkPlatform.dinput.initialized = XK_FALSE;
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
	return("Windows");
}

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

XkResult xkCreateJoystick(XkJoystick* pJoystick, const XkJoystickId id) {
	xkAssert(pJoystick);

	XkResult result = XK_SUCCESS;

	*pJoystick = xkAllocateMemory(sizeof(struct XkJoystick_T));
	if (!(*pJoystick)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkJoystick joystick = *pJoystick;

	joystick->id = id;

_catch:
	return(result);

_free:
	if(joystick) {
		xkFreeMemory(joystick);
	}

	goto _catch;
}

void xkDestroyJoystick(XkJoystick joystick) {
	xkAssert(joystick);

	xkFreeMemory(joystick);
}

XkString xkJoystickMappingName(XkJoystick joystick) {
	xkAssert(joystick);

	return("Windows");
}

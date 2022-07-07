/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_TYPE_AXIS 		0
#define XK_TYPE_SLIDER 	1
#define XK_TYPE_BUTTON 	2
#define XK_TYPE_POV 		3

#define XK_POLL_PRESENCE	0
#define XK_POLL_AXES			1
#define XK_POLL_BUTTONS		2
#define XK_POLL_ALL				(XK_POLL_AXES | XK_POLL_BUTTONS)

typedef struct __xkDInputObject_T {
	IDirectInputDevice8W*				diDevice;
	__XkDInputJoystickObject* 	objects;
	XkSize											objectCount;
	XkSize											axisCount;
	XkSize											sliderCount;
	XkSize											buttonCount;
	XkSize											povCount;
} __xkDInputObject;

static DIOBJECTDATAFORMAT _xkDInputObjectDataFormats[] = {
	{&GUID_XAxis,DIJOFS_X,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_YAxis,DIJOFS_Y,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_ZAxis,DIJOFS_Z,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_RxAxis,DIJOFS_RX,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_RyAxis,DIJOFS_RY,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_RzAxis,DIJOFS_RZ,DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_Slider,DIJOFS_SLIDER(0),DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_Slider,DIJOFS_SLIDER(1),DIDFT_AXIS | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,DIDOI_ASPECTPOSITION},
	{&GUID_POV,DIJOFS_POV(0),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{&GUID_POV,DIJOFS_POV(1),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{&GUID_POV,DIJOFS_POV(2),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{&GUID_POV,DIJOFS_POV(3),DIDFT_POV | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(0),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(1),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(2),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(3),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(4),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(5),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(6),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(7),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(8),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(9),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(10),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(11),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(12),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(13),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(14),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(15),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(16),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(17),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(18),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(19),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(20),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(21),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(22),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(23),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(24),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(25),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(26),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(27),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(28),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(29),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(30),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
	{NULL,DIJOFS_BUTTON(31),DIDFT_BUTTON | DIDFT_OPTIONAL | DIDFT_ANYINSTANCE,0},
};


static const DIDATAFORMAT _xkDInputDataFormat = {
	sizeof(DIDATAFORMAT),
	sizeof(DIOBJECTDATAFORMAT),
	DIDFT_ABSAXIS,
	sizeof(DIJOYSTATE),
	sizeof(_xkDInputObjectDataFormats) / sizeof(DIOBJECTDATAFORMAT),
	_xkDInputObjectDataFormats
};

static void			__xkDInputDetectJoystickConnection();
static void			__xkXInputDetectJoystickConnection();
static void 		__xkWin32DetectJoystickConnection();
static void 		__xkWin32DetectJoystickDisconnection();

static XkBool8 	__xkDInputPollJoystick(XkJoystick* const, const XkInt32);
static XkBool8 	__xkXInputPollJoystick(XkJoystick* const, const XkInt32);
static XkBool8	__xkWin32PollJoystick(XkJoystick* const, const XkInt32);

static void 		__xkWin32CloseJoystick(XkJoystick* const);

static BOOL			__xkDInputDeviceCallback(const DIDEVICEINSTANCE*, void*);
static BOOL			__xkDInputDeviceObjectCallback(const DIDEVICEOBJECTINSTANCEW*, void*);

static XkInt32	__xkDInputCompareJoystickObjects(const void*, const void*);

static XkBool8	__xkXInputSupport(const GUID*);

/* ########## FUNCTIONS SECTION ########## */
XkResult xkInitializeJoystick() {
	XkResult result = XK_SUCCESS;

	if(_xkPlatform.windows.dinput.initialized || _xkPlatform.windows.xinput.initialized) {
		goto _catch;
	}

	HRESULT hResult = DirectInput8Create(_xkPlatform.windows.winapi.instance, DIRECTINPUT_VERSION, &IID_IDirectInput8W, (void**)&_xkPlatform.windows.dinput.dInput, NULL);
	if(FAILED(hResult))  {
		result = XK_ERROR_UNKNOWN;
		__xkErrorHandler("DirectInput: Failed to create interface");
		goto _catch;
	}

	_xkPlatform.windows.dinput.initialized = XK_TRUE;

	__xkWin32DetectJoystickConnection();

	_xkPlatform.windows.xinput.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateJoystick() {
	if(!_xkPlatform.windows.dinput.initialized && !_xkPlatform.windows.xinput.initialized) {
		return;
	}

	for(XkJoystickId jid = XK_JOYSTICK_ID_1; jid <= XK_JOYSTICK_ID_16; jid++) {
		__xkWin32CloseJoystick(&_xkPlatform.joysticks[jid]);
	}

	if(_xkPlatform.windows.dinput.dInput) {
		IDirectInput8_Release(_xkPlatform.windows.dinput.dInput);

		_xkPlatform.windows.dinput.dInput = NULL;
	}

	_xkPlatform.windows.dinput.initialized = XK_FALSE;

	_xkPlatform.windows.xinput.initialized = XK_FALSE;
}

XkResult xkJoystickPresent(XkJoystickId jid) {
	xkAssert(jid >= XK_JOYSTICK_ID_1 && jid < XK_JOYSTICK_ID_16);

	XkResult result = XK_SUCCESS;

	/// TODO: Implementation.

_catch:
	return(result);
}

void xkJoystickVibrarion(XkJoystickId jid, const XkFloat32 right, const XkFloat32 left) {
	xkAssert(jid >= XK_JOYSTICK_ID_1 && jid < XK_JOYSTICK_ID_16);
	xkAssert(right >= 0 && left >= 0);

	/// TODO: Implementation.		
}

XkString xkJoystickMappingName(XkJoystick jid) {
	xkAssert(jid >= XK_JOYSTICK_ID_1 && jid < XK_JOYSTICK_ID_16);

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

static void __xkDInputDetectJoystickConnection() {
	HRESULT hResult = IDirectInput8_EnumDevices(_xkPlatform.windows.dinput.dInput,
																							DI8DEVCLASS_GAMECTRL, 
																							__xkDInputDeviceCallback, 
																							NULL, 
																							DIEDFL_ALLDEVICES);
	if(FAILED(hResult)) {
		__xkErrorHandle("DirectInput: Failed to enumerate devices");
		goto _catch;
	}

_catch:
	return;
}

static void __xkXInputDetectJoystickConnection() {
	for(DWORD index = 0; index < XUSER_MAX_COUNT; index++) {
		XkJoystickId jid = 0;
		for(jid = XK_JOYSTICK_ID_1; jid <= XK_JOYSTICK_ID_16; jid++) {
			if(_xkPlatform.joysticks[jid].connected 
					&& _xkPlatform.joysticks[jid].windows.dinput.diDevice == NULL 
					&& _xkPlatform.joysticks[jid].windows.index == index) {
				break;
			}
		}

		if(jid <= XK_JOYSTICK_ID_16) {
			continue;
		}

		XINPUT_CAPABILITIES xInputCapabilities = {0};
		if(XInputGetCapabilities(index, 0, &xInputCapabilities) != ERROR_SUCCESS) {
			continue;
		}

		// Generate a joystick GUID.
		char guid[33];
		xkStringFormat(guid, "78696e707574%02x000000000000000000", xInputCapabilities.SubType & 0xFF);

		/// TODO: Allocate joystick.
		XkJoystick* pJoystick = XK_NULL_HANDLE;
		if(!pJoystick) {
			continue;
		}

		pJoystick->windows.index = index;
	
		__xkInputJoystickEvent(pJoystick->id, XK_JOYSTICK_CONNECTED);
	}
}

static void __xkWin32DetectJoystickConnection() {
	__xkXInputDetectJoystickConnection();
	__xkDInputDetectJoystickConnection();
}

static void __xkWin32DetectJoystickDisconnection() {
	for(XkJoystickId jid = XK_JOYSTICK_ID_1; jid <= XK_JOYSTICK_ID_16; jid++) {
		XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];
		if(pJoystick->connected) {
			__xkWin32PollJoystick(pJoystick, XK_POLL_PRESENCE);
		}
	}
}

static XkBool8 __xkDInputPollJoystick(XkJoystick* const pJoystick, const XkInt32 mode) {
	xkAssert(pJoystick);

	XkBool8 result = XK_TRUE;

	IDirectInputDevice8_Poll(pJoystick->windows.dinput.diDevice);

	DIJOYSTATE diState = {0};
	HRESULT hResult = IDirectInputDevice8_GetDeviceState(pJoystick->windows.dinput.diDevice, sizeof(DIJOYSTATE), &diState);
	if(hResult == DIERR_NOTACQUIRED || hResult == DIERR_INPUTLOST) {
		IDirectInputDevice8_Acquire(pJoystick->windows.dinput.diDevice);
		IDirectInputDevice8_Poll(pJoystick->windows.dinput.diDevice);
		hResult = IDirectInputDevice8_GetDeviceState(pJoystick->windows.dinput.diDevice, sizeof(DIJOYSTATE), &diState);
		if(FAILED(hResult)) {
			__xkWin32CloseJoystick(pJoystick);
			result = XK_FALSE;
			goto _catch;
		}
	}

	if(mode == XK_POLL_PRESENCE) {
		result = XK_TRUE;
		goto _catch;
	}

	XkGamepadAxis axis = 0; 
	XkGamepadButton button = 0;
	XkGamepadHat hat = 0;
	for(XkSize i = 0; i < pJoystick->windows.dinput.objectCount; i++) {
		const void* data = &diState + pJoystick->windows.dinput.objects[i].offset;

		switch(pJoystick->windows.dinput.objects[i].type) {
			case XK_TYPE_AXIS:
			case XK_TYPE_SLIDER: {
				// BOO!
				const XkFloat32 value = (*((LONG*) data) = 0.5f) / 32767.5f;
				__xkInputGamepadAxis(pJoystick->id, axis, value);
				++axis;
				break;
			}

			case XK_TYPE_BUTTON: {
				// BOO!
				const XkAction action = (*((BYTE*) data) & 0x80) != 0;
				__xkInputGamepadButton(pJoystick->id, button, action);
				++button;
				break;
			}

			case XK_TYPE_POV: {
				const int states[] = {
					XK_GAMEPAD_HAT_UP,
					XK_GAMEPAD_HAT_RIGHT_UP,
					XK_GAMEPAD_HAT_RIGHT,
					XK_GAMEPAD_HAT_RIGHT_DOWN,
					XK_GAMEPAD_HAT_DOWN,
					XK_GAMEPAD_HAT_LEFT_DOWN,
					XK_GAMEPAD_HAT_LEFT,
					XK_GAMEPAD_HAT_LEFT_UP,
					XK_GAMEPAD_HAT_CENTERED
				};

				// BOO!
				XkInt32 statei = LOWORD(*(DWORD*) data) / (45 * DI_DEGREES);
				if(statei < 0 ||  statei > 8) {
					statei = 8;
				}
				__xkInputGamepadHat(pJoystick->id, hat, states[statei]);
				++hat;
				break;
			}
		}
	}

_catch:
	return(result);
}

static XkBool8 __xkXInputPollJoystick(XkJoystick* const pJoystick, const XkInt32 mode) {
	xkAssert(pJoystick);

	XkBool8 result = XK_TRUE;

	XINPUT_STATE xInputState = {0};
	DWORD dResult = XInputGetState(pJoystick->windows.index, &xInputState);
	if(dResult != ERROR_SUCCESS) {
		if(dResult == ERROR_DEVICE_NOT_CONNECTED) {
			__xkWin32CloseJoystick(pJoystick);
		}

		result = XK_FALSE;
		goto _catch;
	}

	if(mode == XK_POLL_PRESENCE) {
		result = XK_TRUE;
		goto _catch;
	}

	__xkInputGamepadAxis(pJoystick->id, XK_GAMEPAD_AXIS_LEFT_X, (xInputState.Gamepad.sThumbLX + 0.5f) / 32767.5f);
	__xkInputGamepadAxis(pJoystick->id, XK_GAMEPAD_AXIS_LEFT_Y, -(xInputState.Gamepad.sThumbLY + 0.5f) / 32767.5f);
	__xkInputGamepadAxis(pJoystick->id, XK_GAMEPAD_AXIS_RIGHT_X, (xInputState.Gamepad.sThumbRX + 0.5f) / 32767.5f);
	__xkInputGamepadAxis(pJoystick->id, XK_GAMEPAD_AXIS_RIGHT_X, -(xInputState.Gamepad.sThumbRY + 0.5f) / 32767.5f);
	__xkInputGamepadAxis(pJoystick->id, XK_GAMEPAD_AXIS_LEFT_TRIGGER, xInputState.Gamepad.bLeftTrigger / 127.5f - 1.0f);
	__xkInputGamepadAxis(pJoystick->id, XK_GAMEPAD_AXIS_RIGHT_TRIGGER, xInputState.Gamepad.bRightTrigger / 127.5f - 1.0f);

	const WORD buttons[] = {
		XINPUT_GAMEPAD_A,
		XINPUT_GAMEPAD_B,
		XINPUT_GAMEPAD_X,
		XINPUT_GAMEPAD_Y,
		XINPUT_GAMEPAD_LEFT_SHOULDER,
		XINPUT_GAMEPAD_RIGHT_SHOULDER,
		XINPUT_GAMEPAD_BACK,
		XINPUT_GAMEPAD_START,
		XINPUT_GAMEPAD_LEFT_THUMB,
		XINPUT_GAMEPAD_RIGHT_THUMB,					
	};

	for(XkGamepadButton button = XK_GAMEPAD_BUTTON_A; button < XK_GAMEPAD_BUTTON_RIGHT_THUMB; button++) {
		const XkAction action = (xInputState.Gamepad.wButtons & buttons[button]) ? XK_ACTION_PRESS : XK_ACTION_RELEASE;
		__xkInputGamepadButton(pJoystick->id, button, action);
	}

	XkGamepadHat hat = 0;
	if(xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) {
		hat |= XK_GAMEPAD_HAT_UP;
	}
	if(xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
		hat |= XK_GAMEPAD_HAT_DOWN;
	}
	if(xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
		hat |= XK_GAMEPAD_HAT_RIGHT;
	}
	if(xInputState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
		hat |= XK_GAMEPAD_HAT_LEFT;
	}

	/// TODO: Action implementation.
	__xkInputGamepadHat(pJoystick->id, hat, XK_ACTION_PRESS);

_catch:
	return(result);
}

static XkBool8	__xkWin32PollJoystick(XkJoystick* const pJoystick, const XkInt32 mode) {
	xkAssert(pJoystick);

	XkBool8 result = XK_TRUE;

	if(pJoystick->windows.dinput.diDevice) {
		result = __xkDInputPollJoystick(pJoystick, mode);
	} else {
		result = __xkXInputPollJoystick(pJoystick, mode);
	}

_catch:
	return(result);
}

static void __xkWin32CloseJoystick(XkJoystick* const pJoystick) {
	xkAssert(pJoystick);

	__xkInputJoystickEvent(pJoystick->id, XK_JOYSTICK_DISCONNECTED);

	if(pJoystick->windows.dinput.diDevice) {
		IDirectInputDevice8_Unacquire(pJoystick->windows.dinput.diDevice);
		IDirectInputDevice8_Release(pJoystick->windows.dinput.diDevice);
	}

	/// TODO: Free joystick.
}

static BOOL __xkDInputDeviceCallback(const DIDEVICEINSTANCE* diDeviceInstance, void* data) {
	BOOL result = DIENUM_CONTINUE;

	for(XkJoystickId jid = XK_JOYSTICK_ID_1; jid <= XK_JOYSTICK_ID_16; jid++) {
		XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];
		if(pJoystick->connected) {
			if(xkCompareMemory(&pJoystick->windows.guid, &diDeviceInstance, sizeof(GUID)) == 1) {
				result = DIENUM_CONTINUE;
				goto _catch;
			}
		}
	}

	if(__xkXInputSupport(&diDeviceInstance->guidProduct)) {
		result = DIENUM_CONTINUE;
		goto _catch;
	}

	IDirectInputDevice8* diDevice = NULL;
	HRESULT hResult = IDirectInput8_CreateDevice(_xkPlatform.windows.dinput.dInput,
																							&diDeviceInstance->guidInstance,
																							&diDevice,
																							NULL);
	if(FAILED(hResult)) {
		__xkErrorHandle("DirectInput: Failed to create device");
		result = DIENUM_CONTINUE;
		goto _catch;
	}

	hResult = IDirectInputDevice8_SetDataFormat(diDevice, &_xkDInputDataFormat);
	if(FAILED(hResult)) {
		__xkErrorHandle("DirectInput: Failed to set device data format");
		result = DIENUM_CONTINUE;
		goto _release;		
	}

	DIDEVCAPS diDevCaps = {0};
	diDevCaps.dwSize 		= sizeof(DIDEVCAPS);

	hResult = IDirectInputDevice8_GetCapabilities(diDevice, &diDevCaps);
	if(FAILED(hResult)) {
		__xkErrorHandle("DirectInput: Failed to get device capabilities");
		result = DIENUM_CONTINUE;
		goto _release;		
	}

	DIPROPDWORD diProp 				= {0};
	diProp.diph.dwSize 				= sizeof(diProp);
	diProp.diph.dwHeaderSize	= sizeof(DIPROPHEADER);	
	diProp.diph.dwHow					= DIPH_DEVICE;
	diProp.dwData							= DIPROPAXISMODE_ABS;

	hResult = IDirectInputDevice8_SetProperty(diDevice, DIPROP_AXISMODE, &diProp.diph);
	if(FAILED(hResult)) {
		__xkErrorHandle("DirectInput: Failed to set device axis mode");
		result = DIENUM_CONTINUE;
		goto _release;		
	}

	__xkDInputObject object = {0};
	object.diDevice = diDevice;
	object.objects = xkAllocateMemory((diDevCaps.dwAxes + diDevCaps.dwButtons + diDevCaps.dwPOVs) * sizeof(__XkDInputJoystickObject));
	if(!object.objects) {
		__xkErrorHandle("DirectInput: Failed to allocate device objects");
		result = DIENUM_CONTINUE;
		goto _release;			
	}
	hResult = IDirectInputDevice8_EnumObjects(diDevice, 
																						__xkDInputDeviceObjectCallback, 
																						&object,
																						DIDFT_AXIS | DIDFT_BUTTON | DIDFT_POV);
	if(FAILED(hResult)) {
		__xkErrorHandle("DirectInput: Failed to enumerate device objects");
		result = DIENUM_CONTINUE;
		goto _free;		
	}

	qsort(object.objects, object.objectCount, sizeof(__XkDInputJoystickObject), __xkDInputCompareJoystickObjects);

	XkChar guid[32];
	if(xkCompareMemory(&diDeviceInstance->guidProduct.Data4[2], "PIDVID", 6) == 1) {
		xkStringFormat(guid, "03000000%02x%02x0000%02x%02x000000000000",
                	(XkUInt8)diDeviceInstance->guidProduct.Data1,
                	(XkUInt8)(diDeviceInstance->guidProduct.Data1 >> 8),
                	(XkUInt8)(diDeviceInstance->guidProduct.Data1 >> 16),
                	(XkUInt8)(diDeviceInstance->guidProduct.Data1 >> 24));
	} else {
		CHAR name[255];
		if(!WideCharToMultiByte(CP_UTF8, 0, diDeviceInstance->tszInstanceName, -1, name, sizeof(name), NULL, NULL)) {
			__xkErrorHandle("DirectInput: Failed to convert device name to UTF-8");
			result = DIENUM_STOP;
			goto _free;				
		}

		xkStringFormat(guid, "05000000%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x00",
                	name[0], name[1], name[2], name[3],
                	name[4], name[5], name[6], name[7],
                	name[8], name[9], name[10]);
	}

	/// TODO: Allocate joystick.
	XkJoystick* pJoystick = XK_NULL_HANDLE;
	if(!pJoystick) {
		result = DIENUM_STOP;
		goto _free;		
	}

	pJoystick->windows.dinput.diDevice 		= diDevice;
	pJoystick->windows.dinput.objects 		= object.objects;
	pJoystick->windows.dinput.objectCount = object.objectCount;
	pJoystick->windows.guid								= diDeviceInstance->guidInstance;

	__xkInputJoystickEvent(pJoystick->id, XK_JOYSTICK_CONNECTED);

_catch:
	return(result);

_release:
	if(diDevice) {
		IDirectInputDevice8_Release(diDevice);
	}

	goto _catch;

_free:
	if(object.objects) {
		xkFreeMemory(object.objects);
	}

	goto _release;
}

static BOOL __xkDInputDeviceObjectCallback(const DIDEVICEOBJECTINSTANCEW* diDeviceObjectInstance, void* data) {

}

static XkInt32	__xkDInputCompareJoystickObjects(const void* first, const void* second) {
	xkAssert(first);
	xkAssert(second);

	const __XkDInputJoystickObject* fo = first;
	const __XkDInputJoystickObject* so = second;

	if(fo->type != so->type) {
		return(fo->type - so->type);
	}

	return(fo->offset - so->offset);
}

static XkBool8	__xkXInputSupport(const GUID* guid) {
	xkAssert(guid);

	XkBool8 result = XK_FALSE;

	UINT count = 0;
	if(GetRawInputDeviceList(NULL, &count, sizeof(RAWINPUTDEVICELIST))) {
		result = XK_FALSE;
		goto _catch;
	}

	RAWINPUTDEVICELIST* pRawDeviceList = NULL;
	pRawDeviceList = xkAllocateMemory(count * sizeof(RAWINPUTDEVICELIST));
	if(GetRawInputDeviceList(NULL, &count, sizeof(RAWINPUTDEVICELIST))) {
		result = XK_FALSE;
		goto _catch;
	}	

	for(UINT i = 0; i < count; i++) {
		if(pRawDeviceList[i].dwType != RIM_TYPEHID) {
			continue;
		}

		RID_DEVICE_INFO ridDeviceInfo = {0};
		ridDeviceInfo.cbSize 					= sizeof(RID_DEVICE_INFO);

		UINT size = sizeof(RID_DEVICE_INFO);
		if(GetRawInputDeviceInfoA(pRawDeviceList[i].hDevice, RIDI_DEVICEINFO, &ridDeviceInfo, &size) == -1) {
			continue;
		}

		if(MAKELONG(ridDeviceInfo.hid.dwVendorId, ridDeviceInfo.hid.dwProductId) != guid->Data1) {
			continue;
		}

		XkChar name[255];
		size = sizeof(name);
		if(GetRawInputDeviceInfoA(pRawDeviceList[i].hDevice, RIDI_DEVICENAME, name, &size) == -1) {
			break;
		}

		name[sizeof(name) - 1] = '\0';

		if(XK_TRUE) {
			result = XK_TRUE;
			break;
		}
	}

_catch:
	if(pRawDeviceList) {
		xkFreeMemory(pRawDeviceList);
	}

	return(result);
}

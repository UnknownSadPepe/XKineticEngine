/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Joystick.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/String.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkJoystick* __xkAllocateJoystick(XkString name, XkString guid, const XkSize axisCount, const XkSize buttonCount, const XkSize hatCount) {
	xkAssert(name);
	xkAssert(guid);
	xkAssert(axisCount > 0);
	xkAssert(buttonCount > 0);
	xkAssert(hatCount > 0);

	XkJoystick* pJoystick = XK_NULL_HANDLE;

	XkJoystickId jid = 0;
	for(jid = XK_JOYSTICK_ID_1; jid <= XK_JOYSTICK_ID_16; jid++) {
		if(!_xkPlatform.joysticks[jid].allocated) {
			break;
		}
	}

	if (jid > XK_JOYSTICK_ID_16) {
		pJoystick = XK_NULL_HANDLE;
		goto _catch;
	}

	pJoystick = &_xkPlatform.joysticks[jid];
	pJoystick->allocated		= XK_TRUE;
	pJoystick->id						= jid;
	pJoystick->axis					= xkAllocateMemory(axisCount * sizeof(XkFloat32));
	pJoystick->axisCount		= axisCount;
	pJoystick->buttons			= xkAllocateMemory((axisCount + hatCount * 4) * sizeof(XkUInt8));
	pJoystick->buttonCount	= buttonCount;
	pJoystick->hats					= xkAllocateMemory(axisCount * sizeof(XkUInt8));
	pJoystick->hatCount			= hatCount;

	xkNCopyString(pJoystick->name, name, sizeof(pJoystick->name) - 1);
	xkNCopyString(pJoystick->guid, guid, sizeof(pJoystick->guid) - 1);

_catch:
	return(pJoystick);
}

void __xkFreeJoystick(XkJoystick* pJoystick) {
	xkAssert(pJoystick);

	xkFreeMemory(pJoystick->axis);
	xkFreeMemory(pJoystick->buttons);
	xkFreeMemory(pJoystick->hats);
	pJoystick->id					= XK_JOYSTICK_ID_NONE;
	pJoystick->allocated	= XK_FALSE;
}

void __xkInputJoystickEvent(XkJoystickId jid, const XkInt32 event) {
	xkAssert(jid > XK_JOYSTICK_ID_1 && jid <= XK_JOYSTICK_ID_16);

	XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];

	if(event == XK_JOYSTICK_CONNECTED) {
		pJoystick->connected = XK_TRUE;
	} else if(event == XK_JOYSTICK_DISCONNECTED) {
		pJoystick->connected = XK_FALSE;
	}

	if(_xkPlatform.joystickCallbacks.event) {
		_xkPlatform.joystickCallbacks.event(jid, event);
	}
}

void __xkInputGamepadAxis(XkJoystickId jid, const XkInt32 axis, const XkFloat32 value) {
	xkAssert(jid > XK_JOYSTICK_ID_1 && jid <= XK_JOYSTICK_ID_16);

	XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];

	pJoystick->axis[axis] = value;

	if(_xkPlatform.joystickCallbacks.axis) {
		_xkPlatform.joystickCallbacks.axis(jid, axis, pJoystick->axis[axis]);
	}
}

void __xkInputGamepadButton(XkJoystickId jid, const XkInt32 button, const XkChar value) {
	xkAssert(jid > XK_JOYSTICK_ID_1 && jid <= XK_JOYSTICK_ID_16);

	XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];

	pJoystick->buttons[button] = value;

	if(_xkPlatform.joystickCallbacks.button) {
		_xkPlatform.joystickCallbacks.button(jid, button, value);
	}
}

void __xkInputGamepadHat(XkJoystickId jid, const XkInt32 hat, const XkChar value) {
	xkAssert(jid > XK_JOYSTICK_ID_1 && jid <= XK_JOYSTICK_ID_16);

	XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];

	int base = pJoystick->buttonCount + hat * 4;

	pJoystick->buttons[base + 0] = (value & 0x01) ? XK_ACTION_PRESS : XK_ACTION_RELEASE;
	pJoystick->buttons[base + 1] = (value & 0x02) ? XK_ACTION_PRESS : XK_ACTION_RELEASE;
	pJoystick->buttons[base + 2] = (value & 0x04) ? XK_ACTION_PRESS : XK_ACTION_RELEASE;
	pJoystick->buttons[base + 3] = (value & 0x08) ? XK_ACTION_PRESS : XK_ACTION_RELEASE;

	if(_xkPlatform.joystickCallbacks.hat) {
		_xkPlatform.joystickCallbacks.hat(jid, hat, value);
	}
}

void xkSetJoystickEventCallback(const XkJoystickEventPfn pfnCallback) {
	xkAssert(pfnCallback);

	_xkPlatform.joystickCallbacks.event = pfnCallback;	
}

void xkSetGamepadAxisCallback(const XkGamepadAxisPfn pfnCallback) {
	xkAssert(pfnCallback);

	_xkPlatform.joystickCallbacks.axis = pfnCallback;	
}

void xkSetGamepadButtonCallback(const XkGamepadButtonPfn pfnCallback) {
	xkAssert(pfnCallback);

	_xkPlatform.joystickCallbacks.button = pfnCallback;	
}

void xkSetGamepadHatCallback(const XkGamepadHatPfn pfnCallback) {
	xkAssert(pfnCallback);

	_xkPlatform.joystickCallbacks.hat = pfnCallback;	
}

XkJoystickType xkJoystickGetType(XkJoystickId jid) {
	xkAssert(jid > XK_JOYSTICK_ID_1 && jid <= XK_JOYSTICK_ID_16);

	XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];

	return(XK_JOYSTICK_TYPE_GAMEPAD);
}

XkString xkJoystickGetName(XkJoystickId jid) {
	xkAssert(jid > XK_JOYSTICK_ID_1 && jid <= XK_JOYSTICK_ID_16);
	
	XkJoystick* pJoystick = &_xkPlatform.joysticks[jid];

	return(pJoystick->name);
}


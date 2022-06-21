#pragma once

#include "XKinetic/XKCore.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef enum {
	XK_JOYSTICK_1  = 0,
	XK_JOYSTICK_2  = 1,
	XK_JOYSTICK_3  = 2,
	XK_JOYSTICK_4  = 3,
	XK_JOYSTICK_5  = 4,
	XK_JOYSTICK_6  = 5,
	XK_JOYSTICK_7  = 6,
	XK_JOYSTICK_8  = 7,
	XK_JOYSTICK_9  = 8,
	XK_JOYSTICK_10 = 9,
	XK_JOYSTICK_11 = 10,
	XK_JOYSTICK_12 = 11,
	XK_JOYSTICK_13 = 12,
	XK_JOYSTICK_14 = 13,
	XK_JOYSTICK_15 = 14,
	XK_JOYSTICK_16 = 15
} XkJoystickID;

typedef enum {
	XK_GAMEPAD_RELEASE 	= 0,
	XK_GAMEPAD_PRESS 		= 1
} XkJoystickAction;

typedef enum {
	XK_JOYSTICK_DISCONNECTED 	= 0,
	XK_JOYSTICK_CONNECTED 		= 1,
} XkJoystickEvent;

typedef enum {
	XK_GAMEPAD_AXIS_LEFT_X        = 0,
	XK_GAMEPAD_AXIS_LEFT_Y        = 1,
	XK_GAMEPAD_AXIS_RIGHT_X       = 2,
	XK_GAMEPAD_AXIS_RIGHT_Y       = 3,
	XK_GAMEPAD_AXIS_LEFT_TRIGGER  = 4,
	XK_GAMEPAD_AXIS_RIGHT_TRIGGER = 5
} XkJoystickAxis;

typedef enum {
	XK_GAMEPAD_BUTTON_A               = 0,
	XK_GAMEPAD_BUTTON_B               = 1,
	XK_GAMEPAD_BUTTON_X               = 2,
	XK_GAMEPAD_BUTTON_Y               = 3,
	XK_GAMEPAD_BUTTON_LEFT_BUMPER     = 4,
	XK_GAMEPAD_BUTTON_RIGHT_BUMPER    = 5,
	XK_GAMEPAD_BUTTON_BACK            = 6,
	XK_GAMEPAD_BUTTON_START           = 7,
	XK_GAMEPAD_BUTTON_GUIDE           = 8,
	XK_GAMEPAD_BUTTON_LEFT_THUMB      = 9,
	XK_GAMEPAD_BUTTON_RIGHT_THUMB     = 10,
	XK_GAMEPAD_BUTTON_DPAD_UP         = 11,
	XK_GAMEPAD_BUTTON_DPAD_RIGHT      = 12,
	XK_GAMEPAD_BUTTON_DPAD_DOWN       = 13,
	XK_GAMEPAD_BUTTON_DPAD_LEFT       = 14,

	XK_GAMEPAD_BUTTON_CROSS       		= XK_GAMEPAD_BUTTON_A,
	XK_GAMEPAD_BUTTON_CIRCLE      		= XK_GAMEPAD_BUTTON_B,
	XK_GAMEPAD_BUTTON_SQUARE      		= XK_GAMEPAD_BUTTON_X,
	XK_GAMEPAD_BUTTON_TRIANGLE    		= XK_GAMEPAD_BUTTON_Y
} XkJoystickButton;

typedef enum {
	XK_GAMEPAD_HAT_CENTERED           = 0,
	XK_GAMEPAD_HAT_UP                 = 1,
	XK_GAMEPAD_HAT_RIGHT              = 2,
	XK_GAMEPAD_HAT_DOWN               = 4,
	XK_GAMEPAD_HAT_LEFT               = 8,
	XK_GAMEPAD_HAT_RIGHT_UP           = (XK_GAMEPAD_HAT_RIGHT | XK_GAMEPAD_HAT_UP),
	XK_GAMEPAD_HAT_RIGHT_DOWN         = (XK_GAMEPAD_HAT_RIGHT | XK_GAMEPAD_HAT_DOWN),
	XK_GAMEPAD_HAT_LEFT_UP            = (XK_GAMEPAD_HAT_LEFT  | XK_GAMEPAD_HAT_UP),
	XK_GAMEPAD_HAT_LEFT_DOWN          = (XK_GAMEPAD_HAT_LEFT  | XK_GAMEPAD_HAT_DOWN)
} XkJoystickHat;

typedef struct XkJoystick* XkJoystick;

typedef void(*XkJoystickEventPfn)(XkJoystick, const XkJoystickEvent);
typedef void(*XkJoystickAxisPfn)(XkJoystick, const XkJoystickAxis, const XkFloat32);
typedef void(*XkJoystickButtonPfn)(XkJoystick, const XkJoystickButton, const XkJoystickAction);
typedef void(*XkJoystickHatPfn)(XkJoystick, const XkJoystickHat, const XkJoystickAction);

XKCORE_API XkResult xkInitializeJoysticks(void);
XKCORE_API void xkTerminateJoysticks(void);

XKCORE_API XkResult xkCreateJoystick(XkJoystick*, const XkJoystickID);
XKCORE_API void xkDestroyJoystick(XkJoystick);

XKCORE_API XkBool xkJoystickGamepad(XkJoystick);
XKCORE_API XkString xkJoystickName(XkJoystick);
XKCORE_API XkString xkJoystickMappingName(XkJoystick);
XKCORE_API XkString xkJoystickName(XkJoystick);
XKCORE_API XkJoystickID xkJoystickID(XkJoystick);

XKCORE_API void xkSetJoystickEventCallback(XkJoystick, const XkJoystickEventPfn);
XKCORE_API void xkSetJoystickAxisCallback(XkJoystick, const XkJoystickAxisPfn);
XKCORE_API void xkSetJoystickButtonCallback(XkJoystick, const XkJoystickButtonPfn);
XKCORE_API void xkSetJoystickHatCallback(XkJoystick, const XkJoystickHatPfn);

XKCORE_API void xkPollJoystickEvents(XkJoystick);

XK_EXPORT void __xkInputJoystickEvent(XkJoystick, const XkJoystickEvent);
XK_EXPORT void __xkInputJoystickAxis(XkJoystick, const XkJoystickAxis, const XkFloat32);
XK_EXPORT void __xkInputJoystickButton(XkJoystick, const XkJoystickButton, const XkJoystickAction);
XK_EXPORT void __xkInputJoystickHat(XkJoystick, const XkJoystickHat, const XkJoystickAction);

#ifdef __cplusplus
}
#endif // __cplusplus

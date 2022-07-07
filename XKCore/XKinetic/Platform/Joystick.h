#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"
#include "XKinetic/Core/Event.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkJoystickId_T {
	XK_JOYSTICK_ID_1  = 0,
	XK_JOYSTICK_ID_2  = 1,
	XK_JOYSTICK_ID_3  = 2,
	XK_JOYSTICK_ID_4  = 3,
	XK_JOYSTICK_ID_5  = 4,
	XK_JOYSTICK_ID_6  = 5,
	XK_JOYSTICK_ID_7  = 6,
	XK_JOYSTICK_ID_8  = 7,
	XK_JOYSTICK_ID_9  = 8,
	XK_JOYSTICK_ID_10 = 9,
	XK_JOYSTICK_ID_11 = 10,
	XK_JOYSTICK_ID_12 = 11,
	XK_JOYSTICK_ID_13 = 12,
	XK_JOYSTICK_ID_14 = 13,
	XK_JOYSTICK_ID_15 = 14,
	XK_JOYSTICK_ID_16 = 15
} XkJoystickId;

typedef enum XkJoystickType_T {
	XK_JOYSTICK_TYPE_GAMEPAD 				= 0,
	XK_JOYSTICK_TYPE_WHEEL					= 1,
	XK_JOYSTICK_TYPE_ARCADE_STICK 	= 2,
	XK_JOYSTICK_TYPE_FLIGHT_STICK 	= 3
} XkJoystickType;

typedef void(*XkJoystickEventPfn)(XkJoystickId, const XkJoystickEvent);

typedef void(*XkGamepadAxisPfn)(XkJoystickId, const XkGamepadAxis, const XkFloat32);
typedef void(*XkGamepadButtonPfn)(XkJoystickId, const XkGamepadButton, const XkAction);
typedef void(*XkGamepadHatPfn)(XkJoystickId, const XkGamepadHat, const XkAction);

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 					xkInitializeJoystick();
extern XKCORE_API void 							xkTerminateJoystick();

extern XKCORE_API XkResult 					xkJoystickPresent(XkJoystickId);

extern XKCORE_API XkJoystickType 		xkJoystickGetType(XkJoystickId);
extern XKCORE_API XkString 					xkJoystickName(XkJoystickId);
extern XKCORE_API XkString 					xkJoystickMappingName(XkJoystickId);

extern XKCORE_API void 							xkSetJoystickEventCallback(XkJoystickId, const XkJoystickEventPfn);

extern XKCORE_API void							xkGamepadVibrarion(XkJoystickId, const XkFloat32, const XkFloat32);

extern XKCORE_API void 							xkSetGamepadAxisCallback(XkJoystickId, const XkGamepadAxisPfn);
extern XKCORE_API void 							xkSetGamepadButtonCallback(XkJoystickId, const XkGamepadButtonPfn);
extern XKCORE_API void 							xkSetGamepadHatCallback(XkJoystickId, const XkGamepadHatPfn);

extern XKCORE_API void							xkWaitJoystickEvents();
extern XKCORE_API void							xkPollJoystickEvents();
extern XKCORE_API void							xkWaitTimeoutJoystickEvents(const XkFloat64);

/* ##### HELPER FUNCTIONS SECTION ##### */
extern XK_EXPORT void 							__xkInputJoystickEvent(XkJoystickId, const XkJoystickEvent);

extern XK_EXPORT void 							__xkInputGamepadAxis(XkJoystickId, const XkGamepadAxis, const XkFloat32);
extern XK_EXPORT void 							__xkInputGamepadButton(XkJoystickId, const XkGamepadButton, const XkAction);
extern XK_EXPORT void 							__xkInputGamepadHat(XkJoystickId, const XkGamepadHat, const XkAction);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

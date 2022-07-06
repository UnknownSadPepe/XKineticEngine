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
} XkJoystickId;

typedef void(*XkJoystickEventPfn)(XkJoystickId, const XkJoystickEvent);
typedef void(*XkGamepadAxisPfn)(XkJoystickId, const XkGamepadAxis, const XkFloat32);
typedef void(*XkGamepadButtonPfn)(XkJoystickId, const XkGamepadButton, const XkAction);
typedef void(*XkGamepadHatPfn)(XkJoystickId, const XkGamepadHat, const XkAction);

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API XkResult 		xkInitializeJoystick();
extern XKCORE_API void 				xkTerminateJoystick();

extern XKCORE_API XkResult 		xkJoystickPresent(XkJoystickId);

extern XKCORE_API XkBool8 		xkJoystickGamepad(XkJoystickId);
extern XKCORE_API XkString 		xkJoystickName(XkJoystickId);
extern XKCORE_API XkString 		xkJoystickMappingName(XkJoystickId);
extern XKCORE_API XkString 		xkJoystickName(XkJoystickId);

extern XKCORE_API void 				xkSetJoystickEventCallback(XkJoystickId, const XkJoystickEventPfn);
extern XKCORE_API void 				xkSetJoystickAxisCallback(XkJoystickId, const XkGamepadAxisPfn);
extern XKCORE_API void 				xkSetJoystickButtonCallback(XkJoystickId, const XkGamepadButtonPfn);
extern XKCORE_API void 				xkSetJoystickHatCallback(XkJoystickId, const XkGamepadHatPfn);

extern XKCORE_API void				xkPollJoystickEvents();
extern XKCORE_API void				xkWaitJoystickEvents();
extern XKCORE_API void				xkWaitTimeoutJoystickEvents(const XkFloat64);

/* ##### HELPER FUNCTIONS SECTION ##### */
extern XK_EXPORT void 				__xkInputJoystickEvent(XkJoystickId, const XkJoystickEvent);
extern XK_EXPORT void 				__xkInputJoystickAxis(XkJoystickId, const XkGamepadAxis, const XkFloat32);
extern XK_EXPORT void 				__xkInputJoystickButton(XkJoystickId, const XkGamepadButton, const XkAction);
extern XK_EXPORT void 				__xkInputJoystickHat(XkJoystickId, const XkGamepadHat, const XkAction);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

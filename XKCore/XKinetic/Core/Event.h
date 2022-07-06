#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkKey_T {
	XK_KEY_UNKNOWN =					-1,
	XK_KEY_SPACE =            32,
	XK_KEY_APOSTROPHE =       39,
	XK_KEY_COMMA =            44,
	XK_KEY_MINUS =            45,
	XK_KEY_PERIOD =           46,
	XK_KEY_SLASH =            47,
	XK_KEY_0 =                48,
	XK_KEY_1 =                49,
	XK_KEY_2 =                50,
	XK_KEY_3 =                51,
	XK_KEY_4 =                52,
	XK_KEY_5 =                53,
	XK_KEY_6 =                54,
	XK_KEY_7 =                55,
	XK_KEY_8 =                56,
	XK_KEY_9 =                57,
	XK_KEY_SEMICOLON =        59,
	XK_KEY_EQUAL =            61,
	XK_KEY_A =                65,
	XK_KEY_B =                66,
	XK_KEY_C =                67,
	XK_KEY_D =                68,
	XK_KEY_E =                69,
	XK_KEY_F =                70,
	XK_KEY_G =                71,
	XK_KEY_H =                72,
	XK_KEY_I =                73,
	XK_KEY_J =                74,
	XK_KEY_K =                75,
	XK_KEY_L =                76,
	XK_KEY_M =                77,
	XK_KEY_N =                78,
	XK_KEY_O =                79,
	XK_KEY_P =                80,
	XK_KEY_Q =                81,
	XK_KEY_R =                82,
	XK_KEY_S =                83,
	XK_KEY_T =                84,
	XK_KEY_U =                85,
	XK_KEY_V =                86,
	XK_KEY_W =                87,
	XK_KEY_X =                88,
	XK_KEY_Y =                89,
	XK_KEY_Z =                90,
	XK_KEY_LEFT_BRACKET =     91,
	XK_KEY_BACKSLASH =        92,
	XK_KEY_RIGHT_BRACKET =    93,
	XK_KEY_GRAVE_ACCENT =     96,
	XK_KEY_WORLD_1 =          161,
	XK_KEY_WORLD_2 =          162,
	XK_KEY_ESCAPE =						256,
	XK_KEY_ENTER =						257,
	XK_KEY_TAB =							258,
	XK_KEY_BACKSPACE =				259,
	XK_KEY_INSERT =						260,
	XK_KEY_DELETE =						261,
	XK_KEY_RIGHT =						262,
	XK_KEY_LEFT =							263,
	XK_KEY_DOWN =							264,
	XK_KEY_UP =								265,
	XK_KEY_PAGE_UP =					266,
	XK_KEY_PAGE_DOWN =				267,
	XK_KEY_HOME =							268,
	XK_KEY_END =							269,
	XK_KEY_CAPS_LOCK =				280,
	XK_KEY_SCROLL_LOCK =			281,
	XK_KEY_NUM_LOCK =					282,
	XK_KEY_PRINT_SCREEN =			283,
	XK_KEY_PAUSE =						284,
	XK_KEY_F1 =								290,
	XK_KEY_F2 =								291,
	XK_KEY_F3 =								292,
	XK_KEY_F4 =								293,
	XK_KEY_F5 =								294,
	XK_KEY_F6 =								295,
	XK_KEY_F7 =								296,
	XK_KEY_F8 =								297,
	XK_KEY_F9 =								298,
	XK_KEY_F10 =							299,
	XK_KEY_F11 =							300,
	XK_KEY_F12 =							301,
	XK_KEY_F13 =							302,
	XK_KEY_F14 =							303,
	XK_KEY_F15 =							304,
	XK_KEY_F16 =							305,
	XK_KEY_F17 =							306,
	XK_KEY_F18 =							307,
	XK_KEY_F19 =							308,
	XK_KEY_F20 =							309,
	XK_KEY_F21 =							310,
	XK_KEY_F22 =							311,
	XK_KEY_F23 =							312,
	XK_KEY_F24 =							313,
	XK_KEY_F25 =							314,
	XK_KEY_KP_0 =							320,
	XK_KEY_KP_1 =							321,
	XK_KEY_KP_2 =							322,
	XK_KEY_KP_3 =							323,
	XK_KEY_KP_4 =							324,
	XK_KEY_KP_5 =							325,
	XK_KEY_KP_6 =							326,
	XK_KEY_KP_7 =							327,
	XK_KEY_KP_8 =							328,
	XK_KEY_KP_9 =							329,
	XK_KEY_KP_DECIMAL =				330,
	XK_KEY_KP_DIVIDE =				331,
	XK_KEY_KP_MULTIPLY =			332,
	XK_KEY_KP_SUBTRACT =			333,
	XK_KEY_KP_ADD =						334,
	XK_KEY_KP_ENTER =					335,
	XK_KEY_KP_EQUAL =					336,
	XK_KEY_LEFT_SHIFT =				340,
	XK_KEY_LEFT_CONTROL =			341,
	XK_KEY_LEFT_ALT =					342,
	XK_KEY_LEFT_SUPER =				343,
	XK_KEY_RIGHT_SHIFT =			344,
	XK_KEY_RIGHT_CONTROL =		345,
	XK_KEY_RIGHT_ALT =				346,
	XK_KEY_RIGHT_SUPER =			347,
	XK_KEY_MENU =							348
} XkKey;

typedef enum XkAction_T {
	XK_ACTION_RELEASE 	= 0,
	XK_ACTION_PRESS 		= 1,
	XK_ACTION_REPEAT 		= 2
} XkAction;

typedef enum XkMod_T {
	XK_MOD_SHIFT_BIT 			= 0x0001,
	XK_MOD_CONTROL_BIT 		= 0x0002,
	XK_MOD_ALT_BIT 				= 0x0004,
	XK_MOD_SUPER_BIT 			= 0x0008,
	XK_MOD_CAPS_LOCK_BIT 	= 0x0010,
	XK_MOD_NUM_LOCK_BIT 	= 0x0020
} XkMod;

typedef enum XkButton_T {
	XK_BUTTON_LEFT  	= 0,
	XK_BUTTON_RIGHT 	= 1,
	XK_BUTTON_MIDDLE 	= 2,
	XK_BUTTON_1 			= 3,
	XK_BUTTON_2 			= 4,
	XK_BUTTON_3 			= 5,
	XK_BUTTON_4 			= 6,
	XK_BUTTON_5 			= 7,
	XK_BUTTON_6 			= 7,	
} XkButton;

typedef enum XkCursorMode_T {
	XK_CURSOR_NORMAL 		= 0,
	XK_CURSOR_HIDDEN 		= 1,
	XK_CURSOR_DISABLED 	= 2
} XkCursorMode;

typedef enum XkJoystickEvent_T {
	XK_JOYSTICK_DISCONNECTED 	= 0,
	XK_JOYSTICK_CONNECTED 		= 1,
} XkJoystickEvent;

typedef enum XkGamepadAxis_T {
	XK_GAMEPAD_AXIS_LEFT_X        = 0,
	XK_GAMEPAD_AXIS_LEFT_Y        = 1,
	XK_GAMEPAD_AXIS_RIGHT_X       = 2,
	XK_GAMEPAD_AXIS_RIGHT_Y       = 3,
	XK_GAMEPAD_AXIS_LEFT_TRIGGER  = 4,
	XK_GAMEPAD_AXIS_RIGHT_TRIGGER = 5
} XkGamepadAxis;

typedef enum XkGamepadButton_T {
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
} XkGamepadButton;

typedef enum XkGamepadHat_T {
	XK_GAMEPAD_HAT_CENTERED           = 0,
	XK_GAMEPAD_HAT_UP                 = 1,
	XK_GAMEPAD_HAT_RIGHT              = 2,
	XK_GAMEPAD_HAT_DOWN               = 4,
	XK_GAMEPAD_HAT_LEFT               = 8,
	XK_GAMEPAD_HAT_RIGHT_UP           = (XK_GAMEPAD_HAT_RIGHT | XK_GAMEPAD_HAT_UP),
	XK_GAMEPAD_HAT_RIGHT_DOWN         = (XK_GAMEPAD_HAT_RIGHT | XK_GAMEPAD_HAT_DOWN),
	XK_GAMEPAD_HAT_LEFT_UP            = (XK_GAMEPAD_HAT_LEFT  | XK_GAMEPAD_HAT_UP),
	XK_GAMEPAD_HAT_LEFT_DOWN          = (XK_GAMEPAD_HAT_LEFT  | XK_GAMEPAD_HAT_DOWN)
} XkGamepadHat;

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

#include "XKinetic/XKCore.h"

typedef enum {
	XK_CONSOLE_STDOUT = 1,
	XK_CONSOLE_STDERR = 2
} XkConsoleHandle;

typedef enum {
 XK_COLOR_RESET,

 XK_COLOR_FBLACK_BIT,
 XK_COLOR_FRED_BIT,
 XK_COLOR_FGREEN_BIT,
 XK_COLOR_FYELLOW_BIT,
 XK_COLOR_FBLUE_BIT,
 XK_COLOR_FPURPLE_BIT,
 XK_COLOR_FCYAN_BIT,
 XK_COLOR_FWHITE_BIT,

 XK_COLOR_FUBLACK_BIT,
 XK_COLOR_FURED_BIT,
 XK_COLOR_FUGREEN_BIT,
 XK_COLOR_FUYELLOW_BIT,
 XK_COLOR_FUBLUE_BIT,
 XK_COLOR_FUPURPLE_BIT,
 XK_COLOR_FUCYAN_BIT,
 XK_COLOR_FUWHITE_BIT,

 XK_COLOR_FBBLACK_BIT,
 XK_COLOR_FBRED_BIT,
 XK_COLOR_FBGREEN_BIT,
 XK_COLOR_FBYELLOW_BIT,
 XK_COLOR_FBBLUE_BIT,
 XK_COLOR_FBPURPLE_BIT,
 XK_COLOR_FBCYAN_BIT,
 XK_COLOR_FBWHITE_BIT,

 XK_COLOR_BBLACK_BIT,
 XK_COLOR_BRED_BIT,
 XK_COLOR_BGREEN_BIT,
 XK_COLOR_BYELLOW_BIT,
 XK_COLOR_BBLUE_BIT,
 XK_COLOR_BPURPLE_BIT,
 XK_COLOR_BCYAN_BIT,
 XK_COLOR_BWHITE_BIT
} XkConsoleColor;

typedef enum {
	XK_FILE_FLAG_RO_BIT = 1,
	XK_FILE_FLAG_WO_BIT = 2,
	XK_FILE_FLAG_RW_BIT = 4,
	XK_FILE_FLAG_AP_BIT = 8,
	XK_FILE_FLAG_CR_BIT = 16
} XkFileFlag;

typedef enum {
	XK_FILE_SEEK_SET = 0,
	XK_FILE_SEEK_CUR = 1,
	XK_FILE_SEEK_END = 2
}	XkFileSeek;

typedef struct XkFile* XkFile;

typedef XkInt32(*XkThreadRoutinePfn)(XkHandle);

typedef struct XkThread* XkThread;
typedef struct XkMutex* XkMutex;

typedef enum {
	XK_WINDOW_DECORATED_BIT = 1,
	XK_WINDOW_RESIZABLE_BIT = 2,
	XK_WINDOW_FLOATING_BIT = 4,
} XkWindowHint;

typedef enum {
	XK_WINDOW_SHOW_DEFAULT = 0,
	XK_WINDOW_SHOW_MAXIMIZED = 1,
	XK_WINDOW_SHOW_MINIMIZED = 2,
	XK_WINDOW_SHOW_FULLSCREEN = 3,
	XK_WINDOW_HIDE = 4
} XkWindowShow;

typedef enum {
	XK_WINDOW_KEY_UNKNOWN =						-1,
	XK_WINDOW_KEY_SPACE =             32,
	XK_WINDOW_KEY_APOSTROPHE =        39,
	XK_WINDOW_KEY_COMMA =             44,
	XK_WINDOW_KEY_MINUS =             45,
	XK_WINDOW_KEY_PERIOD =            46,
	XK_WINDOW_KEY_SLASH =             47,
	XK_WINDOW_KEY_0 =                 48,
	XK_WINDOW_KEY_1 =                 49,
	XK_WINDOW_KEY_2 =                 50,
	XK_WINDOW_KEY_3 =                 51,
	XK_WINDOW_KEY_4 =                 52,
	XK_WINDOW_KEY_5 =                 53,
	XK_WINDOW_KEY_6 =                 54,
	XK_WINDOW_KEY_7 =                 55,
	XK_WINDOW_KEY_8 =                 56,
	XK_WINDOW_KEY_9 =                 57,
	XK_WINDOW_KEY_SEMICOLON =         59,
	XK_WINDOW_KEY_EQUAL =             61,
	XK_WINDOW_KEY_A =                 65,
	XK_WINDOW_KEY_B =                 66,
	XK_WINDOW_KEY_C =                 67,
	XK_WINDOW_KEY_D =                 68,
	XK_WINDOW_KEY_E =                 69,
	XK_WINDOW_KEY_F =                 70,
	XK_WINDOW_KEY_G =                 71,
	XK_WINDOW_KEY_H =                 72,
	XK_WINDOW_KEY_I =                 73,
	XK_WINDOW_KEY_J =                 74,
	XK_WINDOW_KEY_K =                 75,
	XK_WINDOW_KEY_L =                 76,
	XK_WINDOW_KEY_M =                 77,
	XK_WINDOW_KEY_N =                 78,
	XK_WINDOW_KEY_O =                 79,
	XK_WINDOW_KEY_P =                 80,
	XK_WINDOW_KEY_Q =                 81,
	XK_WINDOW_KEY_R =                 82,
	XK_WINDOW_KEY_S =                 83,
	XK_WINDOW_KEY_T =                 84,
	XK_WINDOW_KEY_U =                 85,
	XK_WINDOW_KEY_V =                 86,
	XK_WINDOW_KEY_W =                 87,
	XK_WINDOW_KEY_X =                 88,
	XK_WINDOW_KEY_Y =                 89,
	XK_WINDOW_KEY_Z =                 90,
	XK_WINDOW_KEY_LEFT_BRACKET =      91,
	XK_WINDOW_KEY_BACKSLASH =         92,
	XK_WINDOW_KEY_RIGHT_BRACKET =     93,
	XK_WINDOW_KEY_GRAVE_ACCENT =      96,
	XK_WINDOW_KEY_WORLD_1 =           161,
	XK_WINDOW_KEY_WORLD_2 =           162,
	XK_WINDOW_KEY_ESCAPE =						256,
	XK_WINDOW_KEY_ENTER =							257,
	XK_WINDOW_KEY_TAB =								258,
	XK_WINDOW_KEY_BACKSPACE =					259,
	XK_WINDOW_KEY_INSERT =						260,
	XK_WINDOW_KEY_DELETE =						261,
	XK_WINDOW_KEY_RIGHT =							262,
	XK_WINDOW_KEY_LEFT =							263,
	XK_WINDOW_KEY_DOWN =							264,
	XK_WINDOW_KEY_UP =								265,
	XK_WINDOW_KEY_PAGE_UP =						266,
	XK_WINDOW_KEY_PAGE_DOWN =					267,
	XK_WINDOW_KEY_HOME =							268,
	XK_WINDOW_KEY_END =								269,
	XK_WINDOW_KEY_CAPS_LOCK =					280,
	XK_WINDOW_KEY_SCROLL_LOCK =				281,
	XK_WINDOW_KEY_NUM_LOCK =					282,
	XK_WINDOW_KEY_PRINT_SCREEN =			283,
	XK_WINDOW_KEY_PAUSE =							284,
	XK_WINDOW_KEY_F1 =								290,
	XK_WINDOW_KEY_F2 =								291,
	XK_WINDOW_KEY_F3 =								292,
	XK_WINDOW_KEY_F4 =								293,
	XK_WINDOW_KEY_F5 =								294,
	XK_WINDOW_KEY_F6 =								295,
	XK_WINDOW_KEY_F7 =								296,
	XK_WINDOW_KEY_F8 =								297,
	XK_WINDOW_KEY_F9 =								298,
	XK_WINDOW_KEY_F10 =								299,
	XK_WINDOW_KEY_F11 =								300,
	XK_WINDOW_KEY_F12 =								301,
	XK_WINDOW_KEY_F13 =								302,
	XK_WINDOW_KEY_F14 =								303,
	XK_WINDOW_KEY_F15 =								304,
	XK_WINDOW_KEY_F16 =								305,
	XK_WINDOW_KEY_F17 =								306,
	XK_WINDOW_KEY_F18 =								307,
	XK_WINDOW_KEY_F19 =								308,
	XK_WINDOW_KEY_F20 =								309,
	XK_WINDOW_KEY_F21 =								310,
	XK_WINDOW_KEY_F22 =								311,
	XK_WINDOW_KEY_F23 =								312,
	XK_WINDOW_KEY_F24 =								313,
	XK_WINDOW_KEY_F25 =								314,
	XK_WINDOW_KEY_KP_0 =							320,
	XK_WINDOW_KEY_KP_1 =							321,
	XK_WINDOW_KEY_KP_2 =							322,
	XK_WINDOW_KEY_KP_3 =							323,
	XK_WINDOW_KEY_KP_4 =							324,
	XK_WINDOW_KEY_KP_5 =							325,
	XK_WINDOW_KEY_KP_6 =							326,
	XK_WINDOW_KEY_KP_7 =							327,
	XK_WINDOW_KEY_KP_8 =							328,
	XK_WINDOW_KEY_KP_9 =							329,
	XK_WINDOW_KEY_KP_DECIMAL =				330,
	XK_WINDOW_KEY_KP_DIVIDE =					331,
	XK_WINDOW_KEY_KP_MULTIPLY =				332,
	XK_WINDOW_KEY_KP_SUBTRACT =				333,
	XK_WINDOW_KEY_KP_ADD =						334,
	XK_WINDOW_KEY_KP_ENTER =					335,
	XK_WINDOW_KEY_KP_EQUAL =					336,
	XK_WINDOW_KEY_LEFT_SHIFT =				340,
	XK_WINDOW_KEY_LEFT_CONTROL =			341,
	XK_WINDOW_KEY_LEFT_ALT =					342,
	XK_WINDOW_KEY_LEFT_SUPER =				343,
	XK_WINDOW_KEY_RIGHT_SHIFT =				344,
	XK_WINDOW_KEY_RIGHT_CONTROL =			345,
	XK_WINDOW_KEY_RIGHT_ALT =					346,
	XK_WINDOW_KEY_RIGHT_SUPER =				347,
	XK_WINDOW_KEY_MENU =							348
} XkWindowKey;

typedef enum {
	XK_RELEASE = 0,
	XK_PRESS = 1,
	XK_REPEAT = 2
} XkWindowAction;

typedef enum {
	XK_WINDOW_MOD_SHIFT = 0x0001,
	XK_WINDOW_MOD_CONTROL = 0x0002,
	XK_WINDOW_MOD_ALT = 0x0004,
	XK_WINDOW_MOD_SUPER = 0x0008,
	XK_WINDOW_MOD_CAPS_LOCK = 0x0010,
	XK_WINDOW_MOD_NUM_LOCK = 0x0020
} XkWindowMod;

typedef enum {
	XK_WINDOW_BUTTON_1 = 0,
	XK_WINDOW_BUTTON_2 = 1,
	XK_WINDOW_BUTTON_3 = 2,
	XK_WINDOW_BUTTON_4 = 3,
	XK_WINDOW_BUTTON_5 = 4,
	XK_WINDOW_BUTTON_6 = 5,
	XK_WINDOW_BUTTON_7 = 6,
	XK_WINDOW_BUTTON_8 = 7,
	XK_WINDOW_BUTTON_LEFT  = XK_WINDOW_BUTTON_1,
	XK_WINDOW_BUTTON_RIGHT = XK_WINDOW_BUTTON_2,
	XK_WINDOW_BUTTON_MIDDLE = XK_WINDOW_BUTTON_3
} XkWindowButton;

typedef struct XkWindow* XkWindow;

typedef void(*XkWindowShowPfn)(XkWindow, const XkWindowShow);
typedef void(*XkWindowKeyPfn)(XkWindow, const XkWindowKey, const XkWindowAction, const XkWindowMod);
typedef void(*XkWindowButtonPfn)(XkWindow, const XkWindowButton, const XkWindowAction, const XkWindowMod);
typedef void(*XkWindowCursorPfn)(XkWindow, const XkFloat64, const XkFloat64);
typedef void(*XkWindowCursorEnterPfn)(XkWindow, const XkBool32);
typedef void(*XkWindowScrollPfn)(XkWindow, const XkFloat64, const XkFloat64);
typedef void(*XkWindowClosePfn)(XkWindow);
typedef void(*XkWindowPositionPfn)(XkWindow, const XkInt32, const XkInt32);
typedef void(*XkWindowSizePfn)(XkWindow, const XkSize, const XkSize);
typedef void(*XkWindowFocusPfn)(XkWindow, const XkBool32);

typedef struct XkWindowIcon {
	XkSize width;
	XkSize height;
	XkUInt8* pixels;
} XkWindowIcon;

typedef XkHandle XkModule;
typedef void(*XkProcPfn)(void);


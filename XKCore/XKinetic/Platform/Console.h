#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef enum XkConsoleHandle_T {
	XK_CONSOLE_STDOUT = 1,
	XK_CONSOLE_STDERR = 2
} XkConsoleHandle;

typedef enum XkConsoleColor_T {
 XK_COLOR_FBLACK    = 1,
 XK_COLOR_FRED      = 2,
 XK_COLOR_FGREEN    = 3,
 XK_COLOR_FYELLOW   = 4,
 XK_COLOR_FBLUE     = 5,
 XK_COLOR_FPURPLE   = 6,
 XK_COLOR_FCYAN     = 7,
 XK_COLOR_FWHITE    = 8,

 XK_COLOR_FUBLACK   = 9,
 XK_COLOR_FURED     = 10,
 XK_COLOR_FUGREEN   = 11,
 XK_COLOR_FUYELLOW  = 12,
 XK_COLOR_FUBLUE    = 13,
 XK_COLOR_FUPURPLE  = 14,
 XK_COLOR_FUCYAN    = 15,
 XK_COLOR_FUWHITE   = 16,

 XK_COLOR_FBBLACK   = 17,
 XK_COLOR_FBRED     = 18,
 XK_COLOR_FBGREEN   = 19,
 XK_COLOR_FBYELLOW  = 20,
 XK_COLOR_FBBLUE    = 21,
 XK_COLOR_FBPURPLE  = 22,
 XK_COLOR_FBCYAN    = 23,
 XK_COLOR_FBWHITE   = 24,

 XK_COLOR_BBLACK    = 25,
 XK_COLOR_BRED      = 26,
 XK_COLOR_BGREEN    = 27,
 XK_COLOR_BYELLOW   = 28,
 XK_COLOR_BBLUE     = 29,
 XK_COLOR_BPURPLE   = 30,
 XK_COLOR_BCYAN     = 31,
 XK_COLOR_BWHITE    = 32
} XkConsoleColor;

/* ########## FUNCTIONS SECTION ########## */
extern XKCORE_API void   xkWriteConsole(const XkConsoleHandle, const XkString, const XkSize);
extern XKCORE_API void   xkWriteConsoleColored(const XkConsoleHandle, const XkConsoleColor, const XkString, const XkSize);
extern XKCORE_API void   xkReadConsole(XkString, const XkSize);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Unix/Internal.h"
#include "XKinetic/Platform/Posix/Internal.h"
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct __XkCocoaWindow_T {
	/// TODO: Implementation.
} __XkCocoaWindow;

typedef struct __XkCocoaJoystick_T {
	/// TODO: Implementation.
} __XkCocoaJoystick;

typedef struct __XkCocoaPlatform_T {
	/// TODO: Implementation.
} __XkCocoaPlatform;

/* ########## TYPES MACROS SECTION ########## */
#define XK_PLATFORM_WINDOW 		__XkCocoaWindow 		cocoa
#define XK_PLATFORM_JOYSTICK 	__XkCocoaJoystick 	cocoa
#define XK_PLATFORM 					__XkCocoaPlatform 	cocoa

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

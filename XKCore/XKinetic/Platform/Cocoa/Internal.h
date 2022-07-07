#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Unix/Internal.h"
#include "XKinetic/Platform/Posix/Internal.h"
#include "XKinetic/XKCore.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct __XkAppleWindow_T {
	struct {
		/// TODO: Implementation.
	} cocoa;
	/// TODO: Implementation.
} __XkAppleWindow;

typedef struct __XkAppleJoystick_T {
	struct {
		/// TODO: Implementation.
	} cocoa;
	/// TODO: Implementation.
} __XkAppleJoystick;

typedef struct __XkApplePlatform_T {
	struct {
		/// TODO: Implementation.
	} cocoa;
	/// TODO: Implementation.
} __XkApplePlatform;

/* ########## TYPES MACROS SECTION ########## */
#define XK_PLATFORM_WINDOW 		__XkAppleWindow 		apple
#define XK_PLATFORM_JOYSTICK 	__XkAppleJoystick 	apple
#define XK_PLATFORM 					__XkApplePlatform 	apple

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

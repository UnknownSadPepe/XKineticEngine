#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKinetic.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Renderer/Renderer.h"

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct XkApplication_T {
	XkString name;
	struct {
		XkSize major;
		XkSize minor;	
		XkSize patch;	
	}	version;

	XkWindow window;
	XkRenderer renderer;

	XkBool exit;
}	XkApplication;

/* ########## EXTERN SECTION ########## */
extern XkApplication _xkApplication;

/* ########## FUNCTIONS SECTION ########## */
extern XkResult 	xkInitializeApplication(const XkSize, const XkString*);
extern void 			xkTerminateApplication();
extern void 			xkUpdateApplication();

/// NOTE: For using in cpp programs. 
#ifdef __cplusplus
}
#endif // __cplusplus

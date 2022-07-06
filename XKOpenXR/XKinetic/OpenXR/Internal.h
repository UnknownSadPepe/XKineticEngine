#pragma once

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/XKOpenXR.h"

#if defined(__XKOPENXR_VULKAN__)
	#define XKOPENXR_VULKAN
	#define XR_USE_GRAPHICS_API_VULKAN
	#include <vulkan/vulkan.h>
#endif // __XK_XRVULKAN__

#if defined(__XKOPENXR_DIRECTX12__)
	#define XKOPENXR_DIRECTX12
	#define XR_USE_GRAPHICS_API_D3D12
	#include <d3d12.h>
#endif // __XK_XRDIRECTX12__

#include "XKinetic/XKCore.h"
#if defined(XK_LINUX)
	#define XR_USE_PLATFORM_WAYLAND
#elif defined(XK_WINDOWS)
	#include <windows.h>
	#define XR_USE_PLATFORM_WIN32
#endif // XK_LINUX || XK_WINDOWS
#include <openxr/openxr.h>
#include <openxr/openxr_platform.h>

#include "XKinetic/Core/Minimal.h"
	
/* ########## MACROS SECTION ########## */
#define XKOPENXR_LEFT_SIDE 	0
#define XKOPENXR_RIGHT_SIDE 1

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct __XkXRContext_T {
	XkBool8 																	initialized;

	XrInstance 															xrInstance;
#if defined(XKOPENXR_DEBUG)
	XrDebugUtilsMessengerEXT								xrDebugMessenger;
#endif // XKOPENXR_DEBUG
	XrSystemId															xrSystemId;

	XrPath																	xrSubactionPaths[2];
	uint32_t 																subactionPathCount;

	XrActionSet 														xrActionSet;
	XrAction 																xrPlaceAction;
	XrAction 																xrPoseAction;
	XrAction 																xrVibrateAction;
	XrAction 																xrExitAction;
	XrInteractionProfileSuggestedBinding 		xrProfileBindings;

	XrSession																xrSession;

	XrSpace																	xrReferenceSpace;

	XrEnvironmentBlendMode 									xrEnvironmentBlendMode;
} __XkXRContext;

/* ########## EXTERN SECTION ########## */
extern const char* 										_xkOpenXRInstanceExtensions[];
extern const uint32_t 								_xkOpenXRInstanceExtensionCount;

extern const char* 										_xkOpenXRInstanceLayers[];
extern const uint32_t 								_xkOpenXRInstanceLayerCount;

extern const XrEnvironmentBlendMode 	_xkOpenXREnvironmentBlendMode;

extern __XkXRContext 									_xkOpenXRContext;

/* ########## FUNCTIONS SECTION ########## */
extern XK_EXPORT XkString 		__xkOpenXRGetResultString(XrResult); 

extern XK_EXPORT XkResult 		__xkOpenXRInitializeContext();
extern XK_EXPORT void 				__xkOpenXRTerminateContext();

extern XK_EXPORT XkResult 		__xkOpenXRCreateInstance();
extern XK_EXPORT void 				__xkOpenXRDestroyInstance();

#if defined(XKOPENXR_DEBUG)
extern XK_EXPORT XkResult			__xkOpenXRCreateDebugMessenger();
extern XK_EXPORT void					__xkOpenXRDestroyDebugMessenger();
#endif // XKOPENXR_DEBUG

extern XK_EXPORT XkResult 		__xkOpenXRCreateActionSet(XrActionSet*, XkString, XkString);
extern XK_EXPORT void 				__xkOpenXRDestroyActionSet(XrActionSet);

extern XK_EXPORT XkResult 		__xkOpenXRCreateAction(XrAction*, XkString, XkString, const XrActionType, const uint32_t, XrPath*, XrActionSet);
extern XK_EXPORT void 				__xkOpenXRDestroyAction(XrAction);

extern XK_EXPORT XkResult 		__xkOpenXRProfileBindings(const uint32_t, XrActionSuggestedBinding*, XrPath);

extern XK_EXPORT XkResult 		__xkOpenXRInitializeSystem();

extern XK_EXPORT XkResult 		__xkOpenXRCreateSession();
extern XK_EXPORT void 				__xkOpenXRDestroySession();

extern XK_EXPORT XkResult 		__xkOpenXRCreateReferenceSpace();
extern XK_EXPORT void 				__xkOpenXRDestroyReferenceSpace();

extern XK_EXPORT XkResult 		__xkOpenXRCreateActionSpace(XrSpace*);
extern XK_EXPORT void 				__xkOpenXRDestroyActionSpace(XrSpace);

extern XK_EXPORT XkResult 		__xkOpenXRCreateSwapChain();
extern XK_EXPORT void 				__xkOpenXRDestroySwapChain();

/* ########## HELPER FUNCTIONS SECTION ########## */
#ifdef XKVULKAN_DEBUG
extern XK_EXPORT void 				__xkOpenXRPopulateDebugMessengerCreateInfo(XrDebugUtilsMessengerCreateInfoEXT*);
#endif // XKVULKAN_DEBUG

extern XK_EXPORT XrPath 			__xkOpenXRGetPath(XkString);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus

#pragma once

#include "XKinetic/XKOpenXR.h"
#if defined(__XK_XRVULKAN__)
	#define XK_XRVULKAN
	#define XR_USE_GRAPHICS_API_VULKAN
	#include <vulkan/vulkan.h>
#elif defined(__XK_XRDIRECTX12__)
	#define XK_XRDIRECTX12
	#define XR_USE_GRAPHICS_API_D3D12
	#include <d3d12.h>
#endif // __XK_XRVULKAN__ || __XK_XRDIRECTX12__

#include "XKinetic/XKCore.h"
#if defined(XK_LINUX)
	#define XR_USE_PLATFORM_WAYLAND
	#include <openxr/openxr.h>
	#include <openxr/openxr_platform.h>
#elif defined(XK_WIN32)
	#include <windows.h>
	#define XR_USE_PLATFORM_WIN32
	#include <openxr/openxr.h>
	#include <openxr/openxr_platform.h>
#endif // XK_LINUX || XK_WIN32
#include "XKinetic/Core/Minimal.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define XKXR_LEFT_SIDE 0
#define XKXR_RIGHT_SIDE 1

extern const char* _xkXRInstanceExtensions[];
extern const uint32_t _xkXRInstanceExtensionCount;
extern const char* _xkXRInstanceLayers[];
extern const uint32_t _xkXRInstanceLayerCount;
extern const XrEnvironmentBlendMode _xkXREnvironmentBlendMode;

typedef struct {
	XkBool 																	initialized;

	XrInstance 															xrInstance;

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

extern __XkXRContext _xkXRContext;

XK_EXPORT XkString __xkXRGetErrorString(XrResult); 

XK_EXPORT XkResult __xkXRInitializeContext(void);
XK_EXPORT void __xkXRTerminateContext(void);

XK_EXPORT XkResult __xkXRCreateInstance(void);
XK_EXPORT void __xkXRDestroyInstance(void);

XK_EXPORT XkResult __xkXRCreateActionSet(XrActionSet*, XkString, XkString);
XK_EXPORT void __xkXRDestroyActionSet(XrActionSet);

XK_EXPORT XkResult __xkXRCreateAction(XrAction*, XkString, XkString, const XrActionType, const uint32_t, XrPath*, XrActionSet);
XK_EXPORT void __xkXRDestroyAction(XrAction);

XK_EXPORT XrPath __xkXrGetPath(XkString);

XK_EXPORT XkResult __xkXRProfileBindings(const uint32_t, XrActionSuggestedBinding*, XrPath);

XK_EXPORT XkResult __xkXRInitializeSystem(void);

XK_EXPORT XkResult __xkXRCreateSession(void);
XK_EXPORT void __xkXRDestroySession(void);

XK_EXPORT XkResult __xkXRCreateReferenceSpace(void);
XK_EXPORT void __xkXRDestroyReferenceSpace(void);

XK_EXPORT XkResult __xkXRCreateActionSpace(XrSpace*);
XK_EXPORT void __xkXRDestroyActionSpace(XrSpace);

XK_EXPORT XkResult __xkXRCreateSwapChain(void);
XK_EXPORT void __xkXRDestroySwapChain(void);

#ifdef __cplusplus
}
#endif // __cplusplus

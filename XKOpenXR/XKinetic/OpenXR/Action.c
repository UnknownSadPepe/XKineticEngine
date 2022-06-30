#include "XKinetic/OpenXR/Internal.h"

XrPath __xkXrGetPath(XkString path) {
	XrPath xrPath = XR_NULL_HANDLE;
	// Get OpenXR path.
	XrResult xrResult = xrStringToPath(_xkXRContext.xrInstance, path, &xrPath);
	if(xrResult != XR_SUCCESS) {
    xkLogError("Failed to get OpenXR path: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
	}

_catch:
	return(xrPath);
}

XkResult __xkXRCreateAction(XrAction* pXrAction, XkString name, XkString localizedName, const XrActionType xrActionType, const uint32_t countSubactionPath, XrPath* subactionPaths, XrActionSet xrActionSet) {
	XkResult result = XK_SUCCESS;

	// Initialize OpenXR action info.
	XrActionCreateInfo xrActionCreateInfo 	= {0};
	xrActionCreateInfo.type 								= XR_TYPE_ACTION_CREATE_INFO;
	xrActionCreateInfo.next 								= XR_NULL_HANDLE;
	xkCopyString(xrActionCreateInfo.actionName, name);
	xrActionCreateInfo.actionType						= xrActionType;
	xrActionCreateInfo.countSubactionPaths	= countSubactionPath;
	xrActionCreateInfo.subactionPaths 			= subactionPaths;
	xkCopyString(xrActionCreateInfo.localizedActionName, localizedName);

	// Create OpenXR action.
	XrResult xrResult = xrCreateAction(xrActionSet, &xrActionCreateInfo, pXrAction);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR action: %s", __xkXRGetErrorString(xrResult));
    goto _catch;		
	}

_catch:
	return(result);
}

void __xkXRDestroyAction(XrAction xrAction) {
	if(xrAction) {
		xrDestroyAction(xrAction);
	}
}
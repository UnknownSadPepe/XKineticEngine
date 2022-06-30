#include "XKinetic/OpenXR/Internal.h"

XkResult __xkXRCreateActionSet(XrActionSet* pXrActionSet, XkString name, XkString localizedName) {
	XkResult result = XK_SUCCESS;

	// Initialize OpenXR action set info.
	XrActionSetCreateInfo xrActionSetCreateInfo = { 0 };
	xrActionSetCreateInfo.type = XR_TYPE_ACTION_SET_CREATE_INFO;
	xrActionSetCreateInfo.next = XR_NULL_HANDLE;
	xkCopyString(xrActionSetCreateInfo.actionSetName, name);
	xkCopyString(xrActionSetCreateInfo.localizedActionSetName, localizedName);

	// Create OpenXR action set.
	XrResult xrResult = xrCreateActionSet(_xkXRContext.xrInstance, &xrActionSetCreateInfo, pXrActionSet);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR action set: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
	}
	
_catch:
	return(result);
}

void __xkXRDestroyActionSet(XrActionSet xrActionSet) {
	if(xrActionSet) {
		xrDestroyActionSet(xrActionSet);
	}
}
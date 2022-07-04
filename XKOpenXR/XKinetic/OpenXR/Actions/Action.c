/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XrPath __xkOpenXRGetPath(XkString path) {
	XrPath xrPath = XR_NULL_HANDLE;

	XrResult xrResult = xrStringToPath(_xkOpenXRContext.xrInstance, path, &xrPath);
	if(xrResult != XR_SUCCESS) {
    xkLogError("OpenXR: Failed to get path: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
	}

_catch:
	return(xrPath);
}

XkResult __xkOpenXRCreateAction(XrAction* pXrAction, XkString name, XkString localizedName, const XrActionType xrActionType, const uint32_t countSubactionPath, XrPath* xrSubactionPaths, XrActionSet xrActionSet) {
	xkAssert(pXrAction);
	xkAssert(xrSubactionPaths);
	xkAssert(countSubactionPath > 0);
	xkAssert(xrActionSet);

	XkResult result = XK_SUCCESS;

	XrActionCreateInfo xrActionCreateInfo 	= {};
	xrActionCreateInfo.type 								= XR_TYPE_ACTION_CREATE_INFO;
	xrActionCreateInfo.next 								= XR_NULL_HANDLE;
	xkCopyString(xrActionCreateInfo.actionName, name);
	xrActionCreateInfo.actionType						= xrActionType;
	xrActionCreateInfo.countSubactionPaths	= countSubactionPath;
	xrActionCreateInfo.subactionPaths 			= subactionPaths;
	xkCopyString(xrActionCreateInfo.localizedActionName, localizedName);

	XrResult xrResult = xrCreateAction(xrActionSet, &xrActionCreateInfo, pXrAction);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create action: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;		
	}

_catch:
	return(result);
}

void __xkOpenXRDestroyAction(XrAction xrAction) {
	xkAssert(xrAction);

	xrDestroyAction(xrAction);
}
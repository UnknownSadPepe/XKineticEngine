/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkOpenXRCreateActionSet(XrActionSet* pXrActionSet, XkString name, XkString localizedName) {
	xkAssert(pXrActionSet);

	XkResult result = XK_SUCCESS;

	XrActionSetCreateInfo xrActionSetCreateInfo = {0};
	xrActionSetCreateInfo.type = XR_TYPE_ACTION_SET_CREATE_INFO;
	xrActionSetCreateInfo.next = XR_NULL_HANDLE;
	xkCopyString(xrActionSetCreateInfo.actionSetName, name);
	xkCopyString(xrActionSetCreateInfo.localizedActionSetName, localizedName);

	XrResult xrResult = xrCreateActionSet(_xkOpenXRContext.xrInstance, &xrActionSetCreateInfo, pXrActionSet);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create action set: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
	}
	
_catch:
	return(result);
}

void __xkOpenXRDestroyActionSet(XrActionSet xrActionSet) {
	xkAssert(xrActionSet);

	xrDestroyActionSet(xrActionSet);
}

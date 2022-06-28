#include "XKinetic/OpenXR/Internal.h"

XkResult __xkXRCreateInstance(void) {
	XkResult result = XK_SUCCESS;

	// Initialize OpenXR application info.
	XrApplicationInfo xrApplicationInfo 		= {0};
	//xrApplicationInfo.engineName 						= "XKineticEngine";
	xrApplicationInfo.engineVersion 				= XR_MAKE_VERSION(0, 0, 1);
	xrApplicationInfo.apiVersion 						= XR_CURRENT_API_VERSION;

	// Initialize OpenXR instance info.
	XrInstanceCreateInfo xrInstanceCreateInfo 	= {0};
	xrInstanceCreateInfo.type 									= XR_TYPE_INSTANCE_CREATE_INFO;
	xrInstanceCreateInfo.next 									= XR_NULL_HANDLE;
	xrInstanceCreateInfo.createFlags						= 0;
	xrInstanceCreateInfo.applicationInfo 				= xrApplicationInfo;

/*
	// Create OpenXR instance.
	XrResult xrResult = xrCreateInstance(&xrInstanceCreateInfo, &_xkXRContext.xrInstance);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR instance: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
	}
*/
_catch:
	return(result);
}

void __xkXRDestroyInstance(void) {
/*
	// Destroy OpenXR instance.
	if(_xkXRContext.xrInstance) {
		xrDestroyInstance(_xkXRContext.xrInstance);

		_xkXRContext.xrInstance = XR_NULL_HANDLE;
	}
*/
}

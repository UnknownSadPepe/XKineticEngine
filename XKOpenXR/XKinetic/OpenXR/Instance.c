#include "XKinetic/OpenXR/Internal.h"

const char* _xkXRInstanceExtensions[] = {
	// XR_KHR_COMPOSITION_LAYER_DEPTH_EXTENSION_NAME,
	// XR_MSFT_UNBOUNDED_REFERENCE_SPACE_EXTENSION_NAME,
	// XR_MSFT_SPATIAL_ANCHOR_EXTENSION_NAME,
	// XR_MSFT_HAND_INTERACTION_EXTENSION_NAME,
	// XR_EXT_HP_MIXED_REALITY_CONTROLLER_EXTENSION_NAME,

#if defined(XK_XRVULKAN)
	XR_KHR_VULKAN_ENABLE_EXTENSION_NAME
#elif defined(XK_XRDIRECTX12)
	XR_KHR_D3D12_ENABLE_EXTENSION_NAME
#endif // XK_XRVULKAN

#ifdef XKOPENXR_DEBUG
	XR_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif // XKOPENXR_DEBUG
};

#ifdef XKOPENXR_DEBUG
const uint32_t _xkXRInstanceExtensionCount = 3;
#else
const uint32_t _xkXRInstanceExtensionCount = 2;
#endif // XKOPENXR_DEBUG

#ifdef XKOPENXR_DEBUG
const char* _xkXRInstanceLayers[] = {
	"XR_LAYER_KHRONOS_validation"
};

const uint32_t _xkXRInstanceLayerCount = 1;
#else
const char* _xkXRInstanceLayers[] = { 0 };

const uint32_t _xkXRInstanceLayerCount = 0;
#endif // XKOPENXR_DEBUG

static XkBool __xkXRCheckInstanceExtensionsSupport(void);
static XkBool __xkXRCheckInstanceLayersSupport(void);

XkResult __xkXRCreateInstance(void) {
	XkResult result = XK_SUCCESS;

	// Check OpenXR instance extensions support.
	if (!__xkXRCheckInstanceExtensionsSupport()) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR instance extensions doesn't support");
		goto _catch;
	}

	// Check OpenXR instance layers support.
	if (!__xkXRCheckInstanceLayersSupport()) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR instance layers doesn't support");
		goto _catch;
	}

	// Initialize OpenXR application info.
	XrApplicationInfo xrApplicationInfo 		= {0};
	xkCopyString(xrApplicationInfo.engineName, "XKineticEngine");
	xrApplicationInfo.engineVersion 				= XR_MAKE_VERSION(0, 0, 1);
	xrApplicationInfo.apiVersion 						= XR_VERSION_1_0;

	// Initialize OpenXR instance info.
	XrInstanceCreateInfo xrInstanceCreateInfo 	= {0};
	xrInstanceCreateInfo.type 									= XR_TYPE_INSTANCE_CREATE_INFO;
	xrInstanceCreateInfo.next 									= XR_NULL_HANDLE;
	xrInstanceCreateInfo.createFlags						= 0;
	xrInstanceCreateInfo.applicationInfo 				= xrApplicationInfo;
	xrInstanceCreateInfo.enabledApiLayerCount		= 0;
	xrInstanceCreateInfo.enabledApiLayerNames		= XK_NULL_HANDLE;
	xrInstanceCreateInfo.enabledExtensionCount	= 0;
	xrInstanceCreateInfo.enabledExtensionNames	= XK_NULL_HANDLE;

	// Create OpenXR instance.
	XrResult xrResult = xrCreateInstance(&xrInstanceCreateInfo, &_xkXRContext.xrInstance);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create OpenXR instance: %s", __xkXRGetErrorString(xrResult));
    goto _catch;
	}

_catch:
	return(result);
}

void __xkXRDestroyInstance(void) {
	// Destroy OpenXR instance.
	if(_xkXRContext.xrInstance) {
		xrDestroyInstance(_xkXRContext.xrInstance);

		_xkXRContext.xrInstance = XR_NULL_HANDLE;
	}
}

static XkBool __xkXRCheckInstanceExtensionsSupport(void) {
	XkBool result = XK_TRUE;

	// Get OpenXR instance exntension properties.
	uint32_t availableExtensionPropertiesCount = 0;
	xrEnumerateInstanceExtensionProperties(XR_NULL_HANDLE, 0, &availableExtensionPropertiesCount, XR_NULL_HANDLE);
	if(availableExtensionPropertiesCount == 0) {
		xkLogError("Failed to enumerate OpenXR instance extension properties");
		result = XK_FALSE;
		goto _catch;
	}

	XrExtensionProperties* xrAvailableExtensionProperties = XK_NULL_HANDLE;
	xrAvailableExtensionProperties = xkAllocateMemory(sizeof(XrExtensionProperties) * availableExtensionPropertiesCount);
	if(!xrAvailableExtensionProperties) {
		xkLogError("Failed to enumerate OpenXR instance extension properties");
		result = XK_FALSE;
		goto _catch;
	}

	// Get OpenXR instance extension properties.
	xrEnumerateInstanceExtensionProperties(XR_NULL_HANDLE, 0, &availableExtensionPropertiesCount, xrAvailableExtensionProperties);

	// Template available OpenXR extension.
	const char* availableExtension = XK_NULL_HANDLE;

	// Template required OpenXR extension.
	const char* requiredExtension = XK_NULL_HANDLE;

	// Helper boolean value.
	XkBool availableExtensionFind = XK_FALSE;

	for(uint32_t i = 0; i < _xkXRInstanceExtensionCount; i++) {
		requiredExtension = _xkXRInstanceExtensions[i];
		availableExtensionFind = XK_FALSE;

		for(uint32_t j = 0; j < availableExtensionPropertiesCount; j++) {
			availableExtension = xrAvailableExtensionProperties[j].extensionName;

			// Check OpenXR extension.
			if(xkCompareString((XkString)requiredExtension, (XkString)availableExtension)) {
				availableExtensionFind = XK_TRUE;
				break;
			}
		}

		// If doesn't find available OpenXR extension.
		if(!availableExtensionFind) {
			result = XK_FALSE;
			goto _catch;
		}
	}

_catch:
	if(xrAvailableExtensionProperties) {
		xkFreeMemory(xrAvailableExtensionProperties);
	}

	return(result);
}

static XkBool __xkXRCheckInstanceLayersSupport(void) {
	XkBool result = XK_TRUE;

	// Get OpenXR instance layer properties count.
	uint32_t availableLayerPropertiesCount = 0;
	xrEnumerateApiLayerProperties(0, &availableLayerPropertiesCount, XR_NULL_HANDLE);
	if(availableLayerPropertiesCount == 0) {
		xkLogError("Failed to enumerate Vulkan instance layer properties");
		result = XK_FALSE;
		goto _catch;
	}

	XrApiLayerProperties* xrAvailableLayerProperties = XK_NULL_HANDLE;
	xrAvailableLayerProperties = xkAllocateMemory(sizeof(XrApiLayerProperties) * availableLayerPropertiesCount);
	if(!xrAvailableLayerProperties) {
		xkLogError("Failed to enumerate OpenXR instance layer properties");
		result = XK_FALSE;
		goto _catch;
	}

	// Get OpenXR instance layer properties.
	xrEnumerateApiLayerProperties(availableLayerPropertiesCount, XR_NULL_HANDLE, xrAvailableLayerProperties);

	// Template available OpenXR layer.
	const char* availableLayer = XK_NULL_HANDLE;

	// Template required OpenXR layer.
	const char* requiredLayer = XK_NULL_HANDLE;

	// Helper boolean value.
	XkBool availableLayerFind = XK_FALSE;

	for(uint32_t i = 0; i < _xkXRInstanceLayerCount; i++) {
		requiredLayer = _xkXRInstanceLayers[i];
		availableLayerFind = XK_FALSE;

		for(uint32_t j = 0; j < availableLayerPropertiesCount; j++) {
			availableLayer = xrAvailableLayerProperties[j].layerName;

			// Check OpenXR layer.
			if(xkCompareString((XkString)requiredLayer, (XkString)availableLayer)) {
				availableLayerFind = XK_TRUE;
				break;
			}
		}

		// If doesn't find available Vulkan layer.
		if(!availableLayerFind) {
			result = XK_FALSE;
			goto _catch;
		}
	}

_catch:
	if (xrAvailableLayerProperties) {
		xkFreeMemory(xrAvailableLayerProperties);
	}

	return(result);
}

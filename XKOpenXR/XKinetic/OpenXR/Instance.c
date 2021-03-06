/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
#ifdef XKOPENXR_DEBUG
const char* _xkOpenXRInstanceLayers[] = {
	"XR_APILAYER_LUNARG_core_validation"
};

const uint32_t _xkOpenXRInstanceLayerCount = 1;
#else
const char* _xkOpenXRInstanceLayers[] = {0};

const uint32_t _xkOpenXRInstanceLayerCount = 0;
#endif // XKOPENXR_DEBUG

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
static XkBool8			__xkOpenXRCheckInstanceExtensionsSupport();
static XkBool8			__xkOpenXRCheckInstanceLayersSupport();

static char** __xkOpenXRGetInstanceExtensions(uint32_t* const);

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkOpenXRCreateInstance(const XkRendererApi api) {
	XkResult result = XK_SUCCESS;

	if (!__xkOpenXRCheckInstanceExtensionsSupport()) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR: Instance extensions doesn't support");
		goto _catch;
	}

	if (!__xkOpenXRCheckInstanceLayersSupport()) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR: Instance layers doesn't support");
		goto _catch;
	}

#ifdef XKOPENXR_DEBUG
  XrDebugUtilsMessengerCreateInfoEXT xrDebugUtilsMessengerCreateInfo;
  __xkOpenXRPopulateDebugMessengerCreateInfo(&xrDebugUtilsMessengerCreateInfo);
#endif // XKOPENXR_DEBUG

	XrApplicationInfo xrApplicationInfo 		= {0};
	xkCopyString(xrApplicationInfo.engineName, "XKineticEngine");
	xrApplicationInfo.engineVersion 				= XR_MAKE_VERSION(0, 0, 1);
	xrApplicationInfo.apiVersion 						= XR_VERSION_1_0;

	uint32_t extensionCount = 0;
	char** extensions = __xkOpenXRGetInstanceExtensions(&extensionCount);
	if(extensionCount <= 0) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("OpenXR: Failed to get instance extensions");
		goto _catch;
	}

	XrInstanceCreateInfo xrInstanceCreateInfo 	= {0};
	xrInstanceCreateInfo.type 									= XR_TYPE_INSTANCE_CREATE_INFO;
#ifdef XKOPENXR_DEBUG
  xrInstanceCreateInfo.next                   = (XrDebugUtilsMessengerCreateInfoEXT*)&xrDebugUtilsMessengerCreateInfo;
#else
  xrInstanceCreateInfo.next                   = XR_NULL_HANDLE;
#endif // XKOPENXR_DEBUG
	xrInstanceCreateInfo.createFlags						= 0;
	xrInstanceCreateInfo.applicationInfo 				= xrApplicationInfo;
	xrInstanceCreateInfo.enabledApiLayerCount		= _xkOpenXRInstanceLayerCount;
	xrInstanceCreateInfo.enabledApiLayerNames		= _xkOpenXRInstanceLayers;
	xrInstanceCreateInfo.enabledExtensionCount	= _xkOpenXRInstanceExtensionCount;
	xrInstanceCreateInfo.enabledExtensionNames	= _xkOpenXRInstanceExtensions;

	XrResult xrResult = xrCreateInstance(&xrInstanceCreateInfo, &_xkOpenXRContext.xrInstance);
	if(xrResult != XR_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("OpenXR: Failed to create instance: %s", __xkOpenXRGetResultString(xrResult));
    goto _catch;
	}

_catch:
	if(extensions) {
		for(XkSize i = 0; i < extensionCount; i++) {
			xkFreeMemory(extensions[i]);
		}
		xkFreeMemory(extensions);
	}

	return(result);
}

void __xkOpenXRDestroyInstance() {
	if(_xkOpenXRContext.xrInstance) {
		xrDestroyInstance(_xkOpenXRContext.xrInstance);

		_xkOpenXRContext.xrInstance = XR_NULL_HANDLE;
	}
}

static XkBool8 __xkOpenXRCheckInstanceExtensionsSupport() {
	XkBool8 result = XK_TRUE;

	uint32_t availableExtensionPropertiesCount = 0;
	xrEnumerateInstanceExtensionProperties(XR_NULL_HANDLE, 0, &availableExtensionPropertiesCount, XR_NULL_HANDLE);
	if(availableExtensionPropertiesCount == 0) {
		xkLogError("OpenXR: Failed to enumerate instance extension properties");
		result = XK_FALSE;
		goto _catch;
	}

	XrExtensionProperties* xrAvailableExtensionProperties = XK_NULL_HANDLE;
	xrAvailableExtensionProperties = xkAllocateMemory(sizeof(XrExtensionProperties) * availableExtensionPropertiesCount);
	if(!xrAvailableExtensionProperties) {
		xkLogError("OpenXR: Failed to allocate instance extension properties");
		result = XK_FALSE;
		goto _catch;
	}

	xrEnumerateInstanceExtensionProperties(XR_NULL_HANDLE, 0, &availableExtensionPropertiesCount, xrAvailableExtensionProperties);

	const char* availableExtension = XK_NULL_HANDLE;

	const char* requiredExtension = XK_NULL_HANDLE;

	XkBool8 availableExtensionFind = XK_FALSE;

	for(uint32_t i = 0; i < _xkOpenXRInstanceExtensionCount; i++) {
		requiredExtension = _xkOpenXRInstanceExtensions[i];
		availableExtensionFind = XK_FALSE;

		for(uint32_t j = 0; j < availableExtensionPropertiesCount; j++) {
			availableExtension = xrAvailableExtensionProperties[j].extensionName;

			if(xkCompareString((XkString)requiredExtension, (XkString)availableExtension)) {
				availableExtensionFind = XK_TRUE;
				break;
			}
		}

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

static XkBool8 __xkOpenXRCheckInstanceLayersSupport() {
	XkBool8 result = XK_TRUE;

	uint32_t availableLayerPropertiesCount = 0;
	xrEnumerateApiLayerProperties(0, &availableLayerPropertiesCount, XR_NULL_HANDLE);
	if(availableLayerPropertiesCount == 0) {
		xkLogError("OpenXR: Failed to enumerate instance layer properties");
		result = XK_FALSE;
		goto _catch;
	}

	XrApiLayerProperties* xrAvailableLayerProperties = XK_NULL_HANDLE;
	xrAvailableLayerProperties = xkAllocateMemory(sizeof(XrApiLayerProperties) * availableLayerPropertiesCount);
	if(!xrAvailableLayerProperties) {
		xkLogError("OpenXR: Failed to allocate instance layer properties");
		result = XK_FALSE;
		goto _catch;
	}

	xrEnumerateApiLayerProperties(availableLayerPropertiesCount, XR_NULL_HANDLE, xrAvailableLayerProperties);

	const char* availableLayer = XK_NULL_HANDLE;

	const char* requiredLayer = XK_NULL_HANDLE;

	XkBool8 availableLayerFind = XK_FALSE;

	for(uint32_t i = 0; i < _xkOpenXRInstanceLayerCount; i++) {
		requiredLayer = _xkOpenXRInstanceLayers[i];
		availableLayerFind = XK_FALSE;

		for(uint32_t j = 0; j < availableLayerPropertiesCount; j++) {
			availableLayer = xrAvailableLayerProperties[j].layerName;

			if(xkCompareString((XkString)requiredLayer, (XkString)availableLayer)) {
				availableLayerFind = XK_TRUE;
				break;
			}
		}

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

const char* _xkOpenXRInstanceExtensions[] = {
#if defined(XKOPENXR_VULKAN)
	XR_KHR_VULKAN_ENABLE_EXTENSION_NAME
#elif defined(XKOPENXR_DIRECTX12)
	XR_KHR_D3D12_ENABLE_EXTENSION_NAME
#endif // XKOPENXR_VULKAN || XKOPENXR_DIRECTX12

#ifdef XKOPENXR_DEBUG
	XR_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif // XKOPENXR_DEBUG
};

#ifdef XKOPENXR_DEBUG
const uint32_t _xkOpenXRInstanceExtensionCount = 2;
#else
const uint32_t _xkOpenXRInstanceExtensionCount = 1;
#endif // XKOPENXR_DEBUG

static char** __xkOpenXRGetInstanceExtensions(uint32_t* const pCount) {
	char** extensions = XK_NULL_HANDLE;
	uint32_t count = 0;

	if(_xkOpenXRContext.api == XK_RENDERER_API_VULKAN) {
		++count;
	} else if(_xkOpenXRContext.api == XK_RENDERER_API_D3D12) {
		++count;
	}

#ifdef XKOPENXR_DEBUG
	++count;
#endif // XKOPENXR_DEBUG

	extensions = xkAllocateMemory(sizeof(char*) * count);
	if(!extensions) {
		extensions = XK_NULL_HANDLE;
		xkLogError("OpenXR: Failed to allocate instance extensions");
		goto _catch;
	}

#if defined(XK_LINUX) || defined(XK_WINDOWS)
	if(_xkOpenXRContext.api == XK_RENDERER_API_VULKAN) {
		extensions[0] = xkAllocateMemory(sizeof(XR_KHR_VULKAN_ENABLE_EXTENSION_NAME));
		if(!extensions[0]) {
			extensions[0] = XK_NULL_HANDLE;
			xkLogError("OpenXR: Failed to allocate instance Vulkan extension");
			goto _free;
		}
		xkCopyString(extensions[0], XR_KHR_VULKAN_ENABLE_EXTENSION_NAME);
	}
#endif // XK_LINUX || XK_WINDOWS

#if defined(XK_WINDOWS)
	if(_xkOpenXRContext.api == XK_RENDERER_API_D3D12) {
		extensions[0] = xkAllocateMemory(sizeof(XR_KHR_D3D12_ENABLE_EXTENSION_NAME));
		if(!extensions[0]) {
			extensions[0] = XK_NULL_HANDLE;
			xkLogError("OpenXR: Failed to allocate instance DirectX12 extension");
			goto _free;
		}
		xkCopyString(extensions[0], XR_KHR_D3D12_ENABLE_EXTENSION_NAME);
	}
#endif // XK_WINDOWS

#ifdef XKOPENXR_DEBUG
		extensions[1] = xkAllocateMemory(sizeof(XR_EXT_DEBUG_UTILS_EXTENSION_NAME));
		if(!extensions[1]) {
			extensions[1] = XK_NULL_HANDLE;
			xkLogError("OpenXR: Failed to allocate instance debug utils extension");
			goto _free;
		}
		xkCopyString(extensions[1], XR_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif // XKOPENXR_DEBUG

	*pCount = count;

_catch:
	return(extensions);

_free:
	if(extensions) {
		for(uint32_t i = 0; i < count; i++) {
			if(extensions[i]) {
				xkFreeMemory(extensions[i]);
			}
		}
		xkFreeMemory(extensions);
	}
}

#include "XKinetic/OpenXR/Internal.h"

XkResult __xkXRProfileBindings(const uint32_t countBinding, XrActionSuggestedBinding* xrBindings, XrPath interactionProfile) {
  XkResult result = XK_SUCCESS;

  // Initialize OpenXR interaction profile suggested binding.
  XrInteractionProfileSuggestedBinding xrProfileBindings  = {0};
  xrProfileBindings.type                                  = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING;
  xrProfileBindings.next                                  = XR_NULL_HANDLE;
  xrProfileBindings.interactionProfile                    = interactionProfile;;
  xrProfileBindings.suggestedBindings                     = xrBindings;
  xrProfileBindings.countSuggestedBindings                = xrBindings;

  // Suggest OpenXR interaction profile bindings.
  XrResult xrResult = xrSuggestInteractionProfileBindings(_xkXRContext.xrInstance, &_xkXRContext.xrProfileBindings);
  if(result != XK_SUCCESS) {
    xkLogError("Failed to suggest OpenXR interaction profile bindings: %s", __xkXRGetErrorString(xrResult));
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

_catch:
  return(result);
}
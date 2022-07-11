/* ########## INCLUDE SECTION ########## */
#include "XKinetic/OpenXR/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkOpenXRProfileBindings(const uint32_t bindingCount, XrActionSuggestedBinding* xrBindings, XrPath xrInteractionProfile) {
  xkAssert(xrBindings);
  xkAssert(countBinding > 0);
  xkAssert(xrInteractionProfile);

  XkResult result = XK_SUCCESS;

  XrInteractionProfileSuggestedBinding xrProfileBindings  = {0};
  xrProfileBindings.type                                  = XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING;
  xrProfileBindings.next                                  = XR_NULL_HANDLE;
  xrProfileBindings.interactionProfile                    = xrInteractionProfile;;
  xrProfileBindings.suggestedBindings                     = xrBindings;
  xrProfileBindings.countSuggestedBindings                = bindingCount;

  XrResult xrResult = xrSuggestInteractionProfileBindings(_xkOpenXRContext.xrInstance, &xrProfileBindings);
  if(result != XK_SUCCESS) {
    xkLogError("OpenXR: Failed to suggest interaction profile bindings: %s", __xkOpenXRGetResultString(xrResult));
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

_catch:
  return(result);
}

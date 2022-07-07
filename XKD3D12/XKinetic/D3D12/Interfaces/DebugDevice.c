/* ########## INCLUDE SECTION ########## */
#include "XKinetic/D3D12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
#ifdef XKDIRECTX12_DEBUG
XkResult __xkD3D12QueryDebugDeviceInterface(void) {
  XkResult result = XK_SUCCESS;
  
  HRESULT hResult = ID3D12DebugDevice2_QueryInterface(_xkD3D12Context.d3d12Device8, &IID_ID3D12DebugDevice2, &_xkD3D12Context.d3d12DebugDevice2);
  if (FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to query debug device interface: %s", __xkD3D12GetResultString(hResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkD3D12ReportLiveDeviceObjects(void) {
  ID3D12DebugDevice2_ReportLiveDeviceObjects(_xkD3D12Context.d3d12DebugDevice2, D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
}
#endif // XKDIRECTX12_DEBUG

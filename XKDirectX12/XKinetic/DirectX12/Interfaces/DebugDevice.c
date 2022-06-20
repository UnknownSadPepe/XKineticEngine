#include "XKinetic/DirectX12/Internal.h"

#ifdef XKDIRECTX12_DEBUG
XkResult __xkDX12QueryDebugDeviceInterface(void) {
  XkResult result = XK_SUCCESS;
  
  HRESULT hResult = ID3D12DebugDevice2_QueryInterface(_xkDX12Context.d3d12Device8, &IID_ID3D12DebugDevice2, &_xkDX12Context.d3d12DebugDevice2);
  if (FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to query debug device interface");
    goto _catch;
  }

_catch:
  return(result);
}

void __xkDX12ReportLiveDeviceObjects(void) {
  ID3D12DebugDevice2_ReportLiveDeviceObjects(_xkDX12Context.d3d12DebugDevice2, D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
}
#endif // XKDIRECTX12_DEBUG

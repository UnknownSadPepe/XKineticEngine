#include "XKinetic/DirectX12/Internal.h"

XkResult __xkDX12CreateDevice(void) {
  XkResult result = XK_SUCCESS;

  // Create DirectX12 device.
  HRESULT hResult = D3D12CreateDevice(_xkDX12Context.dxgiAdapter4, _xkDX12Context.d3dDeviceMaximumFeatureLevel, &IID_ID3D12Device8, &_xkDX12Context.d3d12Device8);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to create device");
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  // Set DirectX12 device name.
  ID3D12Object_SetName(_xkDX12Context.d3d12Device8, L"D3D12 Device");
#endif // XKDIRECTX12_DEBUG

_catch:
  return(result);  
}

void __xkDX12DestroyDevice(void) {
  // Destroy DirectX12 device.
  if(_xkDX12Context.d3d12Device8) {
    ID3D12Device8_Release(_xkDX12Context.d3d12Device8);
    _xkDX12Context.d3d12Device8 = NULL;
  }
}

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12CreateDevice(void) {
  XkResult result = XK_SUCCESS;

  HRESULT hResult = D3D12CreateDevice((IUnknown*)_xkD3D12Context.dxgiAdapter4, _xkD3D12Context.d3dDeviceMaximumFeatureLevel, &IID_ID3D12Device8, &_xkD3D12Context.d3d12Device8);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to create device: %s", __xkD3D12ResultString(hResult));
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  ID3D12Object_SetName(_xkD3D12Context.d3d12Device8, L"D3D12 Device");
#endif // XKDIRECTX12_DEBUG

_catch:
  return(result);  
}

void __xkD3D12DestroyDevice(void) {
  if(_xkD3D12Context.d3d12Device8) {
    ID3D12Device8_Release(_xkD3D12Context.d3d12Device8);
    
    _xkD3D12Context.d3d12Device8 = NULL;
  }
}

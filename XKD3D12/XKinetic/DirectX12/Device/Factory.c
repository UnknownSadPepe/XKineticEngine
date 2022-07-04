/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkDXGICreateFactory(void) {
  XkResult result = XK_SUCCESS;

  UINT factoryFlags = 0;
#ifdef XKDIRECTX12_DEBUG
  factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif // XKDIRECTX12_DEBUG

  HRESULT hResult = CreateDXGIFactory2(factoryFlags, &IID_IDXGIFactory7, &_xkD3D12Context.dxgiFactory7);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to create factory2: %s", __xkD3D12ResultString(hResult));
    goto _catch;
  }

_catch: 
  return(result);
}

void __xkDXGIDestroyFactory(void) {
  if(_xkD3D12Context.dxgiFactory7) {
    IDXGIFactory7_Release(_xkD3D12Context.dxgiFactory7);
    _xkD3D12Context.dxgiFactory7 = NULL;
  }
}
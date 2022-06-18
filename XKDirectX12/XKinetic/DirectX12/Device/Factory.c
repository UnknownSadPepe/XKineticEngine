#include "XKinetic/DirectX12/Internal.h"

XkResult __xkDXGICreateFactory(void) {
  XkResult result = XK_SUCCESS;

  // Choose DXGI factory flags.
  UINT factoryFlags = 0;
#ifdef XKDIRECTX12_DEBUG
  factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif // XKDIRECTX12_DEBUG

  // Create DXGI factory
  HRESULT hResult = CreateDXGIFactory2(factoryFlags, &IID_IDXGIFactory7, &_xkDX12Context.dxgiFactory7);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to create factory2");
    goto _catch;
  }

_catch: 
  return(result);
}

void __xkDXGIDestroyFactory(void) {
  // Destroy DXGI factory, if valid.
  if(_xkDX12Context.dxgiFactory7) {
    IDXGIFactory7_Release(_xkDX12Context.dxgiFactory7);
    _xkDX12Context.dxgiFactory7 = NULL;
  }
}
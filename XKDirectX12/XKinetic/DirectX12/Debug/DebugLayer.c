#include "XKinetic/DirectX12/Internal.h"

#ifdef XKDIRECTX12_DEBUG

XkResult __xkDX12CreateDebugLayer(void) {
  XkResult result = XK_SUCCESS;

  // Get DirectX12 debug layer.
  HRESULT hResult = D3D12GetDebugInterface(&IID_ID3D12Debug3, &_xkDX12Context.d3d12Debug3);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to get debug interface");
    goto _catch;    
  }

  // Enable DirectX12 debug layer.
  ID3D12Debug3_EnableDebugLayer(_xkDX12Context.d3d12Debug3);

_catch:
  return(result);
}

#endif // XKDIRECTX12_DEBUG

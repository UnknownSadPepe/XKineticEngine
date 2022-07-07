/* ########## INCLUDE SECTION ########## */
#include "XKinetic/D3D12/Internal.h"

#ifdef XKDIRECTX12_DEBUG

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12CreateDebugLayer(void) {
  XkResult result = XK_SUCCESS;

  HRESULT hResult = D3D12GetDebugInterface(&IID_ID3D12Debug3, &_xkD3D12Context.d3d12Debug3);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to get debug interface: %s", __xkD3D12GetResultString(hResult));
    goto _catch;    
  }

  ID3D12Debug3_EnableDebugLayer(_xkD3D12Context.d3d12Debug3);

_catch:
  return(result);
}

#endif // XKDIRECTX12_DEBUG

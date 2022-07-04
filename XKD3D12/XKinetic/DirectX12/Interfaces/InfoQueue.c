/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12QueryInfoQueueInterface(void) {
  XkResult result = XK_SUCCESS;

  HRESULT hResult = ID3D12Device8_QueryInterface(_xkD3D12Context.d3d12Device8, &IID_ID3D12InfoQueue, &_xkD3D12Context.d3d12InfoQueue);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to query info queue interface: %s", __xkD3D12ResultString(hResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkD3D12EnableInfoQueue(void) {
  ID3D12InfoQueue_SetBreakOnSeverity(_xkD3D12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkD3D12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkD3D12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_WARNING, TRUE);
}

void __xkD3D12DisableInfoQueue(void) {
  ID3D12InfoQueue_SetBreakOnSeverity(_xkD3D12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_CORRUPTION, FALSE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkD3D12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_ERROR, FALSE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkD3D12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_WARNING, FALSE);
}

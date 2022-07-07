/* ########## INCLUDE SECTION ########## */
#include "XKinetic/D3D12/Internal.h"
#include "XKinetic/D3D12/Renderer.h"

/* ########## GLOBAL VARIABLES SECTION ########## */
__XkD3D12Context _xkD3D12Context;

/* ########## FUNCTIONS SECTION ########## */
XkString   __xkD3D12GetResultString(HRESULT hResult) {
  /// TODO: Implementation
  switch(hResult) {
    case ERROR_SUCCESS:             return("D3D12 Success");
    default:                        return("unknown D3D12 error");
  }
}

XkResult xkD3D12InitializeContext() {
  XkResult result = XK_SUCCESS;

  if(_xkD3D12Context.initialized) {
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  // Always enable the debug layer before doing anything DirectX12 related.
  result = __xkD3D12CreateDebugLayer();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }
#endif // XKDIRECTX12_DEBUG

  result = __xkDXGICreateFactory();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkD3D12PickAdapter();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }
  
  result = __xkD3D12CreateDevice();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  result = __xkD3D12QueryInfoQueueInterface();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  __xkD3D12EnableInfoQueue();
#endif // XKDIRECTX12_DEBUG

  /// TODO: Implementation.

  _xkD3D12Context.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkD3D12TerminateContext() {
  if(!_xkD3D12Context.initialized) {
    return;
  }

  __xkDXGIDestroyFactory();

#ifdef XKDIRECTX12_DEBUG
  __xkD3D12DisableInfoQueue();

  __xkD3D12QueryDebugDeviceInterface();
#endif // XKDIRECTX12_DEBUG

  __xkD3D12DestroyDevice();

#ifdef XKDIRECTX12_DEBUG
  __xkD3D12ReportLiveDeviceObjects();
#endif // XKDIRECTX12_DEBUG

  /// TODO: Implementation.

  _xkD3D12Context.initialized = XK_FALSE;
}

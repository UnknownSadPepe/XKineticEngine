#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Platform/Window.h"

__XkDX12Context _xkDX12Context;

XkResult __xkDX12InitializeContext(void) {
  XkResult result = XK_SUCCESS;

#ifdef XKDIRECTX12_DEBUG
  result = __xkDX12CreateDebugLayer();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create DirectX12 debug layer");
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }
#endif // XKDIRECTX12_DEBUG

  // Create DXGI context factory.
  result = __xkDXGICreateFactory();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create DXGI factory");
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  // Pick best DXGI context adapter.
  result = __xkDX12PickAdapter();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to choose DXGI adapter");
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }
  
  // Create DirectX12 context device.
  result = __xkDX12CreateDevice();
  if(result != XK_SUCCESS) {
    xkLogError("Failed to create DirectX12 device");
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  // Query DirectX12 info queue.
  __xkDX12QueryInfoQueueInterface();

  // Enable DirectX12 info queue. 
  __xkDX12EnableInfoQueue();
#endif // XKDIRECTX12_DEBUG

  /// TODO: implementation.

_catch:
  return(result);
}

void __xkDX12TerminateContext(void) {
  // Destroy DXGI context factory.
  __xkDXGIDestroyFactory();

#ifdef XKDIRECTX12_DEBUG
  // Disable DirectX12 info queue.
  __xkDX12DisableInfoQueue();

  // Query DirectX12 debug device.
  __xkDX12QueryDebugDeviceInterface();
#endif // XKDIRECTX12_DEBUG

  // Destroy DirectX12 context device.
  __xkDX12DestroyDevice();

#ifdef XKDIRECTX12_DEBUG
  // Report DirectX12 live objects.
  __xkDX12ReportLiveDeviceObjects();
#endif // XKDIRECTX12_DEBUG

  /// TODO: implementation.
}

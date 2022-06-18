#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Platform/Window.h"

__XkDX12Context _xkDX12Context;

static const D3D_FEATURE_LEVEL _xkD3DMinimumDeviceFeatureLevel = {D3D_FEATURE_LEVEL_12_0};

static const UINT _xkD3DDeviceFeatureLevelCount = 2;
static const D3D_FEATURE_LEVEL _xkD3DDeviceFeatureLevels[] = {D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_12_1};

static D3D_FEATURE_LEVEL __xkDXGIAdapter4GetMaximumFeatureLevel(IDXGIAdapter4*);
static IDXGIAdapter4* __xkDXGIChooseAdapter4(void);

XkResult __xkDX12InitializeContext(void) {
  XkResult result = XK_SUCCESS;

#ifdef XKDIRECTX12_DEBUG
  D3D12GetDebugInterface(&IID_ID3D12Debug3, &_xkDX12Context.d3d12Debug3);
  //_xkDX12Context.d3d12Debug->EnableDebugLayer();
  ID3D12Debug3_EnableDebugLayer(_xkDX12Context.d3d12Debug3);
#endif // XKDIRECTX12_DEBUG

  // Choose DXGI factory flags.
  UINT factoryFlags = 0;
#ifdef XKDIRECTX12_DEBUG
  factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif // XKDIRECTX12_DEBUG

  HRESULT hResult = CreateDXGIFactory2(factoryFlags, &IID_IDXGIFactory7, &_xkDX12Context.dxgiFactory7);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to create factory2");
    goto _catch;
  }

  // Attach DXGI adapter.
  _xkDX12Context.dxgiAdapter4 = __xkDXGIChooseAdapter4();
  if(!_xkDX12Context.dxgiAdapter4) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to choose adapter");
    goto _catch;
  }

  const D3D_FEATURE_LEVEL d3dDeviceMaximumFeatureLevel = __xkDXGIAdapter4GetMaximumFeatureLevel(_xkDX12Context.dxgiAdapter4);
  hResult = D3D12CreateDevice(_xkDX12Context.dxgiAdapter4, d3dDeviceMaximumFeatureLevel, &IID_ID3D12Device8, &_xkDX12Context.d3d12Device8);
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to create device");
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  ID3D12Object_SetName(_xkDX12Context.d3d12Device8, L"D3D12 Device");
#endif // XKDIRECTX12_DEBUG


#ifdef XKDIRECTX12_DEBUG
  ID3D12Device8_QueryInterface(_xkDX12Context.d3d12Device8, &IID_ID3D12InfoQueue, &_xkDX12Context.d3d12InfoQueue);

  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_WARNING, TRUE);
#endif // XKDIRECTX12_DEBUG

  /// TODO: implementation.

_catch:
  return(result);
}

void __xkDX12TerminateContext(void) {
  if(_xkDX12Context.dxgiAdapter4) {
    IDXGIAdapter4_Release(_xkDX12Context.dxgiAdapter4);
    _xkDX12Context.dxgiAdapter4 = NULL;
  }

  if(_xkDX12Context.dxgiFactory7) {
    IDXGIFactory7_Release(_xkDX12Context.dxgiFactory7);
    _xkDX12Context.dxgiFactory7 = NULL;
  }

#ifdef XKDIRECTX12_DEBUG
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_CORRUPTION, FALSE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_ERROR, FALSE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_WARNING, FALSE);

  ID3D12DebugDevice2* d3d12DebugDevice2;
  ID3D12DebugDevice2_QueryInterface(_xkDX12Context.d3d12Device8, &IID_ID3D12DebugDevice2, &d3d12DebugDevice2);

  if (_xkDX12Context.d3d12Device8) {
    ID3D12Device8_Release(_xkDX12Context.d3d12Device8);
    //_xkDX12Context.d3d12Device->Release();
    _xkDX12Context.d3d12Device8 = NULL;
  }

  ID3D12DebugDevice2_ReportLiveDeviceObjects(d3d12DebugDevice2, D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
#endif // XKDIRECTX12_DEBUG

  if(_xkDX12Context.d3d12Device8) {
    ID3D12Device8_Release(_xkDX12Context.d3d12Device8);
    _xkDX12Context.d3d12Device8 = NULL;
  }

  /// TODO: implementation.
}

static D3D_FEATURE_LEVEL __xkDXGIAdapter4GetMaximumFeatureLevel(IDXGIAdapter4* dxgiAdapter4) {
  D3D12_FEATURE_DATA_FEATURE_LEVELS d3d12FeatureLevelInfo = {0};
  d3d12FeatureLevelInfo.NumFeatureLevels           = _xkD3DDeviceFeatureLevelCount;
  d3d12FeatureLevelInfo.pFeatureLevelsRequested    = _xkD3DDeviceFeatureLevels;

  ID3D12Device* d3d12Device;
  HRESULT hResult = D3D12CreateDevice(dxgiAdapter4, _xkD3DMinimumDeviceFeatureLevel, &IID_ID3D12Device, &d3d12Device);
  if(FAILED(hResult)) {
    return((D3D_FEATURE_LEVEL)0);
  }

  ID3D12Device_CheckFeatureSupport(d3d12Device, D3D12_FEATURE_FEATURE_LEVELS, &d3d12FeatureLevelInfo, sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS));

  return(d3d12FeatureLevelInfo.MaxSupportedFeatureLevel);
}

static IDXGIAdapter4* __xkDXGIChooseAdapter4(void) {
  IDXGIAdapter4* dxgiAdapter4 = NULL;

  // Choose best DXGI adapter by performance.
  for(UINT i = 0; IDXGIFactory7_EnumAdapterByGpuPreference(_xkDX12Context.dxgiFactory7, i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, &IID_IDXGIAdapter4, &dxgiAdapter4) != DXGI_ERROR_NOT_FOUND; i++) {
    HRESULT hResult = D3D12CreateDevice(dxgiAdapter4, _xkD3DMinimumDeviceFeatureLevel, &IID_ID3D12Device, NULL);
    if(SUCCEEDED(hResult)) {
      const D3D_FEATURE_LEVEL d3dDeviceMaximumFeatureLevel = __xkDXGIAdapter4GetMaximumFeatureLevel(dxgiAdapter4);
      if (d3dDeviceMaximumFeatureLevel > _xkD3DMinimumDeviceFeatureLevel) {
        break;
      }
    } else if(FAILED(hResult)) {
      IDXGIAdapter4_Release(dxgiAdapter4);
      dxgiAdapter4 = NULL;
    }
  }

  return(dxgiAdapter4);
}
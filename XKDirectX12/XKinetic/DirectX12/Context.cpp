#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Platform/Window.h"

__XkDX12Context _xkDX12Context;

static const D3D_FEATURE_LEVEL _xkD3DMinimumDeviceFeatureLevel = {D3D_FEATURE_LEVEL_12_0};

static const UINT _xkD3DDeviceFeatureLevelCount = 2;
static const D3D_FEATURE_LEVEL _xkD3DDeviceFeatureLevels[] = {D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_12_1};

static D3D_FEATURE_LEVEL __xkDXGIAdapterGetMaximumFeatureLevel(IDXGIAdapter4*);
static IDXGIAdapter4* __xkDXGIChooseAdapter(void);

XkResult __xkDX12InitializeContext(void) {
  XkResult result = XK_SUCCESS;

#ifdef XKDIRECTX12_DEBUG
  D3D12GetDebugInterface(IID_PPV_ARGS(&_xkDX12Context.dx12Debug));
  _xkDX12Context.dx12Debug->EnableDebugLayer();
#endif // XKDIRECTX12_DEBUG

  // Choose DXGI factory flags.
  UINT factoryFlags = 0;
#ifdef XKDIRECTX12_DEBUG
  factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif // XKDIRECTX12_DEBUG

  HRESULT hResult = CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&_xkDX12Context.dxgiFactory));
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to create factory2");
    goto _catch;
  }

  // Attach DXGI adapter.
  _xkDX12Context.dxgiAdapter = __xkDXGIChooseAdapter();
  if(!_xkDX12Context.dxgiAdapter) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to choose adapter");
    goto _catch;
  }

  const D3D_FEATURE_LEVEL d3dDeviceMaximumFeatureLevel = __xkDXGIAdapterGetMaximumFeatureLevel(_xkDX12Context.dxgiAdapter);
  hResult = D3D12CreateDevice(_xkDX12Context.dxgiAdapter, d3dDeviceMaximumFeatureLevel, IID_PPV_ARGS(&_xkDX12Context.dx12Device));
  if(FAILED(hResult)) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DirectX12: Failed to create device");
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  _xkDX12Context.dx12Device->SetName(L"D3D12 Device");
#endif // XKDIRECTX12_DEBUG


#ifdef XKDIRECTX12_DEBUG
  _xkDX12Context.dx12Device->QueryInterface(IID_PPV_ARGS(&_xkDX12Context.dx12InfoQueue));

  _xkDX12Context.dx12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
  _xkDX12Context.dx12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
  _xkDX12Context.dx12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, TRUE);
#endif // XKDIRECTX12_DEBUG

  /// TODO: implementation.

_catch:
  return(result);
}

void __xkDX12TerminateContext(void) {
  if(_xkDX12Context.dxgiAdapter) {
    _xkDX12Context.dxgiAdapter->Release();
    _xkDX12Context.dxgiAdapter = NULL;
  }

  if(_xkDX12Context.dxgiFactory) {
    _xkDX12Context.dxgiFactory->Release();
    _xkDX12Context.dxgiFactory = NULL;
  }

#ifdef XKDIRECTX12_DEBUG
  _xkDX12Context.dx12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, FALSE);
  _xkDX12Context.dx12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, FALSE);
  _xkDX12Context.dx12InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, FALSE);

  ID3D12DebugDevice2* dx12DebugDevice;
  _xkDX12Context.dx12Device->QueryInterface(IID_PPV_ARGS(&dx12DebugDevice));
  // The reason because i release DirectX12 device object here, because i don't want any life object to next point.
  if (_xkDX12Context.dx12Device) {
    _xkDX12Context.dx12Device->Release();
    _xkDX12Context.dx12Device = NULL;
  }

  dx12DebugDevice->ReportLiveDeviceObjects(D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
#endif // XKDIRECTX12_DEBUG

  if(_xkDX12Context.dx12Device) {
    _xkDX12Context.dx12Device->Release();
    _xkDX12Context.dx12Device = NULL;
  }

  /// TODO: implementation.
}

static D3D_FEATURE_LEVEL __xkDXGIAdapterGetMaximumFeatureLevel(IDXGIAdapter4* dxgiAdapter) {
  D3D12_FEATURE_DATA_FEATURE_LEVELS dx12FeatureLevelInfo = {};
  dx12FeatureLevelInfo.NumFeatureLevels           = _xkD3DDeviceFeatureLevelCount;
  dx12FeatureLevelInfo.pFeatureLevelsRequested    = _xkD3DDeviceFeatureLevels;

  ID3D12Device* dx12Device;
  HRESULT hResult = D3D12CreateDevice(dxgiAdapter, _xkD3DMinimumDeviceFeatureLevel, IID_PPV_ARGS(&dx12Device));
  if(FAILED(hResult)) {
    return((D3D_FEATURE_LEVEL)0);
  }

  dx12Device->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &dx12FeatureLevelInfo, sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS));

  return(dx12FeatureLevelInfo.MaxSupportedFeatureLevel);
}

static IDXGIAdapter4* __xkDXGIChooseAdapter(void) {
  IDXGIAdapter4* dxgiAdapter = NULL;

  // Choose best DXGI adapter by performance.
  for(UINT i = 0; _xkDX12Context.dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&dxgiAdapter)) != DXGI_ERROR_NOT_FOUND; i++) {
    HRESULT hResult = D3D12CreateDevice(dxgiAdapter, _xkD3DMinimumDeviceFeatureLevel, __uuidof(ID3D12Device), NULL);
    if(SUCCEEDED(hResult)) {
      const D3D_FEATURE_LEVEL d3dDeviceMaximumFeatureLevel = __xkDXGIAdapterGetMaximumFeatureLevel(dxgiAdapter);
      if (d3dDeviceMaximumFeatureLevel > _xkD3DMinimumDeviceFeatureLevel) {
        break;
      }
    } else if (FAILED(hResult)) {
      dxgiAdapter->Release();
      dxgiAdapter = NULL;
    }
  }

  return(dxgiAdapter);
}
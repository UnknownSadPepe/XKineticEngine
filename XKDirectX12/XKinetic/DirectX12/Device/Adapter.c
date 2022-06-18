#include "XKinetic/DirectX12/Internal.h"

const D3D_FEATURE_LEVEL _xkD3DMinimumDeviceFeatureLevel = {D3D_FEATURE_LEVEL_12_0};
const UINT _xkD3DDeviceFeatureLevelCount = 2;
const D3D_FEATURE_LEVEL _xkD3DDeviceFeatureLevels[] = {D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_12_1};

static D3D_FEATURE_LEVEL __xkDXGIAdapter4GetMaximumFeatureLevel(IDXGIAdapter4*);
static IDXGIAdapter4* __xkDXGIChooseAdapter4(void);

XkResult __xkDX12PickAdapter(void) {
  XkResult result = XK_SUCCESS;

  // Choose DXGI adapter.
  _xkDX12Context.dxgiAdapter4 = __xkDXGIChooseAdapter4();
  if(!_xkDX12Context.dxgiAdapter4) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to choose adapter");
    goto _catch;
  }

  // Get DXGI adapter maximum features.
  _xkDX12Context.d3dDeviceMaximumFeatureLevel = __xkDXGIAdapter4GetMaximumFeatureLevel(_xkDX12Context.dxgiAdapter4);

_catch:
  return(result);
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
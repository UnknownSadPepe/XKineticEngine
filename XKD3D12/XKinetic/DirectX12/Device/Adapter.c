/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Core/Assert.h"

const D3D_FEATURE_LEVEL   _xkD3DMinimumDeviceFeatureLevel = {D3D_FEATURE_LEVEL_12_0};
const UINT                _xkD3DDeviceFeatureLevelCount = 2;
const D3D_FEATURE_LEVEL   _xkD3DDeviceFeatureLevels[] = {D3D_FEATURE_LEVEL_12_0, D3D_FEATURE_LEVEL_12_1};

/* ########## FUNCTIONS DECLARATION SECTION ########## */
static D3D_FEATURE_LEVEL  __xkDXGIAdapter4GetMaximumFeatureLevel(IDXGIAdapter4*);
static IDXGIAdapter4*     __xkDXGIChooseAdapter4(void);

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12PickAdapter(void) {
  XkResult result = XK_SUCCESS;

  _xkD3D12Context.dxgiAdapter4 = __xkDXGIChooseAdapter4();
  if(!_xkD3D12Context.dxgiAdapter4) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("DXGI: Failed to choose adapter");
    goto _catch;
  }

  _xkD3D12Context.d3dDeviceMaximumFeatureLevel = __xkDXGIAdapter4GetMaximumFeatureLevel(_xkD3D12Context.dxgiAdapter4);
  if(_xkD3D12Context.d3dDeviceMaximumFeatureLevel == 0) {
    result = XK_ERROR_UNKNOWN;   
    xkLogError("DXGI: Failed to get maximum feature level");
    goto _catch;
  }

_catch:
  return(result);
}

static D3D_FEATURE_LEVEL __xkDXGIAdapter4GetMaximumFeatureLevel(IDXGIAdapter4* dxgiAdapter4) {
  xkAssert(dxgiAdapter4);

  D3D_FEATURE_LEVEL d3dFeatureLevel = (D3D_FEATURE_LEVEL)0;

  D3D12_FEATURE_DATA_FEATURE_LEVELS d3d12FeatureLevelInfo   = {};
  d3d12FeatureLevelInfo.NumFeatureLevels                    = _xkD3DDeviceFeatureLevelCount;
  d3d12FeatureLevelInfo.pFeatureLevelsRequested             = _xkD3DDeviceFeatureLevels;

  ID3D12Device* d3d12Device;
  HRESULT hResult = D3D12CreateDevice((IUnknown*)dxgiAdapter4, _xkD3DMinimumDeviceFeatureLevel, &IID_ID3D12Device, &d3d12Device);
  if(FAILED(hResult)) {
    return(d3dFeatureLevel);
  }

  ID3D12Device_CheckFeatureSupport(d3d12Device, D3D12_FEATURE_FEATURE_LEVELS, &d3d12FeatureLevelInfo, sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS));

  d3dFeatureLevel = d3d12FeatureLevelInfo.MaxSupportedFeatureLevel

  return(d3dFeatureLevel);
}

static IDXGIAdapter4* __xkDXGIChooseAdapter4(void) {
  IDXGIAdapter4* dxgiAdapter4 = NULL;

  for(UINT i = 0; IDXGIFactory7_EnumAdapterByGpuPreference(_xkD3D12Context.dxgiFactory7, i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, &IID_IDXGIAdapter4, &dxgiAdapter4) != DXGI_ERROR_NOT_FOUND; i++) {
    HRESULT hResult = D3D12CreateDevice((IUnknown*)dxgiAdapter4, _xkD3DMinimumDeviceFeatureLevel, &IID_ID3D12Device, NULL);
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

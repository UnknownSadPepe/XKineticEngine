#include "XKinetic/DirectX12/Internal.h"

#ifdef XKDIRECTX12_DEBUG
void __xkDX12QueryDebugDeviceInterface(void) {
  ID3D12DebugDevice2_QueryInterface(_xkDX12Context.d3d12Device8, &IID_ID3D12DebugDevice2, &_xkDX12Context.d3d12DebugDevice2);
}

void __xkDX12ReportLiveDeviceObjects(void) {
  ID3D12DebugDevice2_ReportLiveDeviceObjects(_xkDX12Context.d3d12DebugDevice2, D3D12_RLDO_SUMMARY | D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
}
#endif // XKDIRECTX12_DEBUG

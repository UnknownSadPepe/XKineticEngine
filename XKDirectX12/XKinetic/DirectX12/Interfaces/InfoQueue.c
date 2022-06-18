#include "XKinetic/DirectX12/Internal.h"

void __xkDX12QueryInfoQueueInterface(void) {
  ID3D12Device8_QueryInterface(_xkDX12Context.d3d12Device8, &IID_ID3D12InfoQueue, &_xkDX12Context.d3d12InfoQueue);
}

void __xkDX12EnableInfoQueue(void) {
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_CORRUPTION, TRUE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_ERROR, TRUE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_WARNING, TRUE);
}

void __xkDX12DisableInfoQueue(void) {
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_CORRUPTION, FALSE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_ERROR, FALSE);
  ID3D12InfoQueue_SetBreakOnSeverity(_xkDX12Context.d3d12InfoQueue, D3D12_MESSAGE_SEVERITY_WARNING, FALSE);
}

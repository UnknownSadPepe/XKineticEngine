#include "XKinetic/DirectX12/Internal.h"

XkResult __xkDX12CreateFence(ID3D12Fence** ppD3D12Fence) {
	XkResult result = XK_SUCCESS;

	// Create DirectX12 fence.
	HRESULT hResult = ID3D12Device_CreateFence(_xkDX12Context.d3d12Device8, 0, D3D12_FENCE_FLAG_NONE, &IID_ID3D12Fence1, ppD3D12Fence);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create fence");
		goto _catch;
	}

	// Template DirectX12 fence.
	ID3D12Fence* d3d12Fence = *ppD3D12Fence;

#ifdef XKDIRECTX12_DEBUG
	// Set DirectX12 fence name.
	ID3D12Fence_SetName(d3d12Fence, L"DirectX12 Fence");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkDX12DestroyFence(ID3D12Fence* pD3D12Fence) {
	// Release DirectX12 fence.
	ID3D12Fence_Release(pD3D12Fence);
}

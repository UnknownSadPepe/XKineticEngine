#include "XKinetic/DirectX12/Internal.h"

XkResult __xkDX12CreateCommandAllocator(ID3D12CommandAllocator** ppD3D12CommandAllocator, const D3D12_COMMAND_LIST_TYPE d3d12Type) {
	XkResult result = XK_SUCCESS;

	// Create DirectX12 command allocator.
	HRESULT hResult = ID3D12Device_CreateCommandAllocator(_xkDX12Context.d3d12Device8, d3d12Type, &IID_ID3D12CommandAllocator, ppD3D12CommandAllocator);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create command allocator");
		goto _catch;
	}

	// Template DirectX12 command allocator.
	ID3D12CommandAllocator* d3d12CommandAllocator = *ppD3D12CommandAllocator;

#ifdef XKDIRECTX12_DEBUG
	// Set DirectX12 command allocator name.
	ID3D12CommandQueue_SetName(d3d12CommandAllocator,
		d3d12Type == D3D12_COMMAND_LIST_TYPE_DIRECT ? L"DirectX12 Graphics Command Allocator" :
		d3d12Type == D3D12_COMMAND_LIST_TYPE_COMPUTE ? L"DirectX12 Compute Commans Allocator" :
		L"DirectX12 Command Allocator");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkDX12DestroyCommandAllocator(ID3D12CommandAllocator* pD3D12CommandAllocator) {
	// Release DirectX12 command allocator.
	ID3D12CommandAllocator_Release(pD3D12CommandAllocator);
}

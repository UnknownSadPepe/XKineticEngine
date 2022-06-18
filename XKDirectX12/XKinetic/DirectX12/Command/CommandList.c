#include "XKinetic/DirectX12/Internal.h"

XkResult __xkDX12CreateCommandList(ID3D12GraphicsCommandList6** ppD3D12CommandList, ID3D12CommandAllocator* pD3D12CommandAllocator, const D3D12_COMMAND_LIST_TYPE d3d12Type) {
	XkResult result = XK_SUCCESS;

	// Create DirectX12 command list.
	HRESULT hResult = ID3D12Device8_CreateCommandList(_xkDX12Context.d3d12Device8, 0, d3d12Type, pD3D12CommandAllocator, NULL, &IID_ID3D12CommandList, ppD3D12CommandList);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create command list");
		goto _catch;
	}

	// Template DirectX12 command list.
	ID3D12GraphicsCommandList6* d3d12CommandList = *ppD3D12CommandList;

	// Reset DirectX12 command list, to start recording commands.
	ID3D12GraphicsCommandList_Close(d3d12CommandList);

#ifdef XKDIRECTX12_DEBUG
	// Set DirectX12 command list name.
	ID3D12CommandList_SetName(d3d12CommandList,
		d3d12Type == D3D12_COMMAND_LIST_TYPE_DIRECT ? L"DirectX12 Graphics Command List" :
		d3d12Type == D3D12_COMMAND_LIST_TYPE_COMPUTE ? L"DirectX12 Compute Commans List" :
		L"DirectX12 Command List");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkDX12DestroyCommandList(ID3D12GraphicsCommandList6* pD3D12CommandList) {
	// Release DirectX12 command list.
	ID3D12CommandList_Release(pD3D12CommandList);
}

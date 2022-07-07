/* ########## INCLUDE SECTION ########## */
#include "XKinetic/D3D12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12CreateCommandAllocator(ID3D12CommandAllocator** ppD3D12CommandAllocator, const D3D12_COMMAND_LIST_TYPE d3d12Type) {
	xkAssert(ppD3D12CommandAllocator);

	XkResult result = XK_SUCCESS;

	HRESULT hResult = ID3D12Device_CreateCommandAllocator(_xkD3D12Context.d3d12Device8, d3d12Type, &IID_ID3D12CommandAllocator, ppD3D12CommandAllocator);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create command allocator: %s", __xkD3D12GetResultString(hResult));
		goto _catch;
	}

	ID3D12CommandAllocator* d3d12CommandAllocator = *ppD3D12CommandAllocator;

#ifdef XKDIRECTX12_DEBUG
	ID3D12CommandQueue_SetName(d3d12CommandAllocator,
		d3d12Type == D3D12_COMMAND_LIST_TYPE_DIRECT ? L"DirectX12 Graphics Command Allocator" :
		d3d12Type == D3D12_COMMAND_LIST_TYPE_COMPUTE ? L"DirectX12 Compute Commans Allocator" :
		L"DirectX12 Command Allocator");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkD3D12DestroyCommandAllocator(ID3D12CommandAllocator* pD3D12CommandAllocator) {
	xkAssert(pD3D12CommandAllocator);

	ID3D12CommandAllocator_Release(pD3D12CommandAllocator);
}

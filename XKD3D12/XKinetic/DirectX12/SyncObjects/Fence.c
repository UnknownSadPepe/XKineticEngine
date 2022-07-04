/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12CreateFence(ID3D12Fence** ppD3D12Fence) {
	xkAssert(ppD3D12Fence);

	XkResult result = XK_SUCCESS;

	HRESULT hResult = ID3D12Device_CreateFence(_xkD3D12Context.d3d12Device8, 0, D3D12_FENCE_FLAG_NONE, &IID_ID3D12Fence1, ppD3D12Fence);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create fence: %s", __xkD3D12ResultString(hResult));
		goto _catch;
	}

	ID3D12Fence* d3d12Fence = *ppD3D12Fence;

#ifdef XKDIRECTX12_DEBUG
	ID3D12Fence_SetName(d3d12Fence, L"DirectX12 Fence");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkD3D12DestroyFence(ID3D12Fence* pD3D12Fence) {
	xkAssert(pD3D12Fence);

	ID3D12Fence_Release(pD3D12Fence);
}

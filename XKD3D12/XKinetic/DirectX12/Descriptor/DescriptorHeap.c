/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12CreateDescriptorHeap(ID3D12DescriptorHeap** ppD3D12DescriptorHeap, const D3D12_DESCRIPTOR_HEAP_TYPE d3d12Type, const UINT descriptorCount) {
	xkAssert(ppD3D12DescriptorHeap);
	xkAssert(descriptorCount > 0);

	XkResult result = XK_SUCCESS;

	D3D12_DESCRIPTOR_HEAP_DESC d3d12DescriptorHeapInfo	= {};
	d3d12DescriptorHeapInfo.Type												= d3d12Type;
	d3d12DescriptorHeapInfo.NumDescriptors							= descriptorCount;
	d3d12DescriptorHeapInfo.Flags												= D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	d3d12DescriptorHeapInfo.NodeMask										= 0;

	HRESULT hResult = ID3D12Device8_CreateDescriptorHeap(_xkD3D12Context.d3d12Device8, &d3d12DescriptorHeapInfo, &IID_ID3D12DescriptorHeap, ppD3D12DescriptorHeap);
	if(FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create descriptor heap: %s", __xkD3D12ResultString(hResult));
		goto _catch;
	}

	ID3D12DescriptorHeap* d3d12DescriptorHeap = *ppD3D12DescriptorHeap;

#ifdef XKDIRECTX12_DEBUG
	ID3D12DescriptorHeap_SetName(d3d12DescriptorHeap, L"DirectX12 Descriptor Heap");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkD3D12DestroyDescriptorHeap(ID3D12DescriptorHeap* pD3D12DescriptorHeap) {
	xkAssert(pD3D12DescriptorHeap);
	
	ID3D12DescriptorHeap_Release(pD3D12DescriptorHeap);
}

/* ########## INCLUDE SECTION ########## */
#include "XKinetic/D3D12/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkD3D12CreateCommandQueue(ID3D12CommandQueue** ppD3D12CommandQueue, const D3D12_COMMAND_LIST_TYPE d3d12Type) {
	xkAssert(ppD3D12CommandQueue);

	XkResult result = XK_SUCCESS;

	D3D12_COMMAND_QUEUE_DESC d3d12CommandQueueInfo	={0};
	d3d12CommandQueueInfo.Flags											= D3D12_COMMAND_QUEUE_FLAG_NONE;
	d3d12CommandQueueInfo.NodeMask									= 0;
	d3d12CommandQueueInfo.Priority									= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
	d3d12CommandQueueInfo.Type											= d3d12Type;

	HRESULT hResult = ID3D12Device_CreateCommandQueue(_xkD3D12Context.d3d12Device8, &d3d12CommandQueueInfo, &IID_ID3D12CommandQueue, ppD3D12CommandQueue);
	if(FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create command queue: %s", __xkD3D12GetResultString(hResult));
		goto _catch;
	}

	ID3D12CommandQueue* d3d12CommandQueue = *ppD3D12CommandQueue;

#ifdef XKDIRECTX12_DEBUG
	ID3D12CommandQueue_SetName(d3d12CommandQueue, 
		d3d12Type == D3D12_COMMAND_LIST_TYPE_DIRECT ? L"DirectX12 Graphics Command Queue" : 
		d3d12Type == D3D12_COMMAND_LIST_TYPE_COMPUTE ? L"DirectX12 Compute Commans Queue" :
		L"DirectX12 Command Queue");
#endif // XKDIRECTX12_DEBUG

_catch:
	return(result);
}

void __xkD3D12DestroyCommandQueue(ID3D12CommandQueue* pD3D12CommandQueue) {
	xkAssert(pD3D12CommandQueue);

	ID3D12CommandQueue_Release(pD3D12CommandQueue);
}

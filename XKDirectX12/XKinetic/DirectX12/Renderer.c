#include "XKinetic/Renderer/External.h"
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/DirectX12/Renderer.h"

struct XkDX12Renderer {
	XkRendererConfig config;

	ID3D12CommandQueue*						d3d12CommandQueue;
	ID3D12CommandAllocator*				d3d12CommandAllocators[XKDIRECTX12_FRAME_COUNT];
	ID3D12Fence1*									d3d12Fence;
	ID3D12GraphicsCommandList6*		d3d12GraphicsCommandList6;

	UINT frameIndex;

	UINT fenceValue;
	HANDLE hFenceEvent;
  /// TODO: implementation.
};

struct XkDX12Buffer {
	ID3D12Resource* dx12Resource;
  /// TODO: implementation.
};

struct XkDX12Texture2D {
	ID3D12Resource* dx12Resource;
  /// TODO: implementation.
};

XkResult xkDX12CreateRenderer(XkDX12Renderer* pRenderer, XkRendererConfig* const pConfig, XkWindow window) {
	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkDX12Renderer));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12Renderer renderer = *pRenderer;

	renderer->config = *pConfig;

	// Initialize DirectX12 context.
	result = __xkDX12InitializeContext();
	if (result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		xkLogError("Failed to initialize DirectX12 Context");
		goto _catch;
	}

	// Create DirectX12 command queue.
	result = __xkDX12CreateCommandQueue(&renderer->d3d12CommandQueue, D3D12_COMMAND_LIST_TYPE_DIRECT);
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		xkLogError("Failed to create DirectX12 command queue");
		goto _catch;
	}

	// Create DirectX12 command allocators.
	for(XkSize i = 0; i < XKDIRECTX12_FRAME_COUNT; i++) {
		result = __xkDX12CreateCommandAllocator(&renderer->d3d12CommandAllocators[i], D3D12_COMMAND_LIST_TYPE_DIRECT);
		if(result != XK_SUCCESS) {
			result = XK_ERROR_CREATE_FAILED;
			xkLogError("Failed to create DirectX12 command allocator");
			goto _catch;
		}
	}

	// Create DirectX12 command list.
	result = __xkDX12CreateCommandList(&renderer->d3d12GraphicsCommandList6, renderer->d3d12CommandAllocators[0], D3D12_COMMAND_LIST_TYPE_DIRECT);
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		xkLogError("Failed to create DirectX12 command list");
		goto _catch;
	}

	// Create DirectX12 fence.
	result = __xkDX12CreateFence(&renderer->d3d12Fence);
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		xkLogError("Failed to create DirectX12 fence");
		goto _catch;
	}

	// Create fence event.
	renderer->hFenceEvent = CreateEventEx(NULL, NULL, 0, EVENT_ALL_ACCESS);
	if (!renderer->hFenceEvent) {
		result = XK_ERROR_CREATE_FAILED;
		xkLogError("Failed to create DirectX12 fence event");
		goto _catch;
	}

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyRenderer(XkDX12Renderer renderer) {
	// Destroy fence event.
	CloseHandle(renderer->hFenceEvent);

	// Destroy DirectX12 fence.
	__xkDX12DestroyFence(renderer->d3d12Fence);

	// Destroy DirectX12 command list
	__xkDX12DestroyCommandList(renderer->d3d12GraphicsCommandList6);

	// Destroy DirectX12 command allocators.
	for(XkSize i = 0; i < XKDIRECTX12_FRAME_COUNT; i++) {
		__xkDX12DestroyCommandAllocator(renderer->d3d12CommandAllocators[i]);
	}

	// Destroy DirectX12 command queue.
	__xkDX12DestroyCommandQueue(renderer->d3d12CommandQueue);

	/// TODO: implementation.
	xkFreeMemory(renderer);

	// Terminate DirectX12 context.
	__xkDX12TerminateContext();
}

void xkDX12ClearColorRenderer(XkDX12Renderer renderer, XkVec4 color) {
	/// TODO: implementation.
}

void xkDX12ClearDepthRenderer(XkDX12Renderer renderer, XkFloat32 depth) {
	/// TODO: implementation.
}

void xkDX12ClearStencilRenderer(XkDX12Renderer renderer, XkUInt32 stencil) {
	/// TODO: implementation.
}

void xkDX12ClearRenderer(XkDX12Renderer renderer) {
	/// TODO: implementation.
}

void xkDX12TopologyRenderer(XkDX12Renderer renderer, XkTopology topology) {
	/// TODO: implementation.
}

void xkDX12CullModeRenderer(XkDX12Renderer renderer, XkCullMode cullMode) {
	/// TODO: implementation.
}

void xkDX12BeginRenderer(XkDX12Renderer renderer) {
	// DirectX12 GPU has not finished executing the command list.
	if (ID3D12Fence1_GetCompletedValue(renderer->d3d12Fence) < renderer->fenceValue) {
		// Set DirectX12 fence event.
		ID3D12Fence1_SetEventOnCompletion(renderer->d3d12Fence, renderer->fenceValue, renderer->hFenceEvent);

		// Wait for DirectX12 fence event.
		WaitForSingleObject(renderer->hFenceEvent, INFINITE);
	}

	/// Template DirectX12 current command allocator.
	ID3D12CommandAllocator* d3d12CommandAllocator = renderer->d3d12CommandAllocators[renderer->frameIndex];

	// Reset DirectX12 current command allocator.
	ID3D12CommandAllocator_Reset(d3d12CommandAllocator);

	// Reset DirectX12 command list.
	ID3D12GraphicsCommandList_Reset(renderer->d3d12GraphicsCommandList6, d3d12CommandAllocator, NULL);
}

void xkDX12EndRenderer(XkDX12Renderer renderer) {
	// Reset DirectX12 command list, to start recording commands at next frame.
	ID3D12GraphicsCommandList_Close(renderer->d3d12GraphicsCommandList6);

	// Execute DirectX12 command lists.
	ID3D12CommandList d3d12CommandLists[] = {renderer->d3d12GraphicsCommandList6};
	ID3D12CommandQueue_ExecuteCommandLists(renderer->d3d12CommandQueue, 1, &d3d12CommandLists[0]);

	UINT* pFenceValue = &renderer->fenceValue;
	*pFenceValue++;

	ID3D12CommandQueue_Signal(renderer->d3d12CommandQueue, renderer->d3d12Fence, pFenceValue);

	// Register frame index.
	renderer->frameIndex = (renderer->frameIndex + 1) % XKDIRECTX12_FRAME_COUNT;
}

void xkDX12ResizeRenderer(XkDX12Renderer renderer, XkSize width, XkSize height) {
	/// TODO: implementation.
}

void xkDX12ScissorRenderer(XkDX12Renderer renderer, XkInt32 x, XkInt32 y, XkSize width, XkSize height) {
	/// TODO: implementation.
}

void xkDX12Draw(XkDX12Renderer renderer, XkSize vertexCount) {
	/// TODO: implementation.
}

void xkDX12DrawIndexed(XkDX12Renderer renderer, XkSize indexCount) {
	/// TODO: implementation.
}

XkResult xkDX12CreateBuffer(XkDX12Buffer* pBuffer, const XkBufferUsage usage, const XkSize size, XkHandle data, XkDX12Renderer renderer) {
	XkResult result = XK_SUCCESS;

	*pBuffer = (XkDX12Buffer)xkAllocateMemory(sizeof(struct XkDX12Buffer));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12Buffer buffer = *pBuffer;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyBuffer(XkDX12Buffer buffer) {
	/// TODO: implementation.
}

void xkDX12MapBuffer(XkDX12Buffer buffer, const XkHandle data) {
	/// TODO: implementation.
}

void xkDX12BindVertexBuffer(XkDX12Buffer buffer) {
	/// TODO: implementation.
}

void xkDX12BindIndexBuffer(XkDX12Buffer buffer) {
	/// TODO: implementation.
}

XkResult xkDX12CreateTexture2D(XkDX12Texture2D* pTexture, XkHandle data, const XkSize width, const XkSize height, XkDX12Renderer renderer) {
	XkResult result = XK_SUCCESS;

	*pTexture = (XkDX12Texture2D)xkAllocateMemory(sizeof(struct XkDX12Texture2D));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkDX12Texture2D texture = *pTexture;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkDX12DestroyTexture2D(XkDX12Texture2D texture) {
	/// TODO: implementation.
	xkFreeMemory(texture);
}

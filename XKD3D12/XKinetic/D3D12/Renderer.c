/* ########## INCLUDE SECTION ########## */
#include "XKinetic/D3D12/Internal.h"
#include "XKinetic/Renderer/External.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/D3D12/Renderer.h"

/* ########## TYPES SECTION ########## */
struct XkD3D12Renderer_T {
	XkRendererHint								hint;

	IDXGISwapChain4*							dxgiSwapChain;
	ID3D12Resource*								d3d12BackBffers[XKDIRECTX12_FRAME_COUNT];

	ID3D12DescriptorHeap*					d3d12DesriptorHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE		d3d12CpuDesriptorHandle;
	D3D12_GPU_DESCRIPTOR_HANDLE		d3d12GpuDesriptorHandle;

	ID3D12CommandQueue*						d3d12CommandQueue;
	ID3D12CommandAllocator*				d3d12CommandAllocators[XKDIRECTX12_FRAME_COUNT];
	ID3D12Fence*									d3d12Fence;
	ID3D12GraphicsCommandList6*		d3d12CommandList6;

	FLOAT													clearColorValues[4];
	D3D12_VIEWPORT								d3d12Viewport;
	D3D12_RECT										d3d12Scissor;

	UINT frameIndex;

	UINT64 fenceValue;
	UINT64 frameFenceValues[XKDIRECTX12_FRAME_COUNT];
	HANDLE hFenceEvent;
};

struct XkD3D12Buffer_T {
	ID3D12Resource* 	d3d12Resource;
};

struct XkD3D12Texture_T {
	ID3D12Resource* 	d3d12Resource;
};

/* ########## GLOBAL VARIABLES SECTION ########## */
__XkD3D12Context _xkD3D12Context;

/* ########## FUNCTIONS SECTION ########## */
XkString  __xkD3D12GetResultString(HRESULT hResult) {
  /// TODO: Implementation
  switch(hResult) {
    case ERROR_SUCCESS:             return("D3D12 Success");
    default:                        return("unknown D3D12 error");
  }
}

XkResult xkD3D12InitializeRenderer() {
  XkResult result = XK_SUCCESS;

  if(_xkD3D12Context.initialized) {
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  // Always enable the debug layer before doing anything DirectX12 related.
  result = __xkD3D12CreateDebugLayer();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }
#endif // XKDIRECTX12_DEBUG

  result = __xkDXGICreateFactory();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  result = __xkD3D12PickAdapter();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }
  
  result = __xkD3D12CreateDevice();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

#ifdef XKDIRECTX12_DEBUG
  result = __xkD3D12QueryInfoQueueInterface();
  if(result != XK_SUCCESS) {
    result = XK_ERROR_INITIALIZE_FAILED;
    goto _catch;
  }

  __xkD3D12EnableInfoQueue();
#endif // XKDIRECTX12_DEBUG

  /// TODO: Implementation.

  _xkD3D12Context.initialized = XK_TRUE;

_catch:
  return(result);
}

void xkD3D12TerminateRenderer() {
  if(!_xkD3D12Context.initialized) {
    return;
  }

  __xkDXGIDestroyFactory();

#ifdef XKDIRECTX12_DEBUG
  __xkD3D12DisableInfoQueue();

  __xkD3D12QueryDebugDeviceInterface();
#endif // XKDIRECTX12_DEBUG

  __xkD3D12DestroyDevice();

#ifdef XKDIRECTX12_DEBUG
  __xkD3D12ReportLiveDeviceObjects();
#endif // XKDIRECTX12_DEBUG

  /// TODO: Implementation.

  _xkD3D12Context.initialized = XK_FALSE;
}


XkResult xkD3D12CreateRenderer(XkD3D12Renderer* pRenderer, XkWindow window, const XkRendererHint hint) {
	xkAssert(pRenderer);
	xkAssert(window);

	XkResult result = XK_SUCCESS;

	*pRenderer = xkAllocateMemory(sizeof(struct XkD3D12Renderer_T));
	if(!pRenderer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkD3D12Renderer renderer = *pRenderer;

	renderer->hint										= hint;

	result = __xkD3D12CreateCommandQueue(&renderer->d3d12CommandQueue, D3D12_COMMAND_LIST_TYPE_DIRECT);
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		goto _catch;
	}

	for(XkSize i = 0; i < XKDIRECTX12_FRAME_COUNT; i++) {
		result = __xkD3D12CreateCommandAllocator(&renderer->d3d12CommandAllocators[i], D3D12_COMMAND_LIST_TYPE_DIRECT);
		if(result != XK_SUCCESS) {
			result = XK_ERROR_CREATE_FAILED;
			goto _catch;
		}
	}

	result = __xkD3D12CreateCommandList(&renderer->d3d12CommandList6, renderer->d3d12CommandAllocators[0], D3D12_COMMAND_LIST_TYPE_DIRECT);
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		goto _catch;
	}

	result = __xkD3D12CreateFence(&renderer->d3d12Fence);
	if(result != XK_SUCCESS) {
		result = XK_ERROR_CREATE_FAILED;
		goto _catch;
	}

	renderer->hFenceEvent = CreateEventEx(NULL, NULL, 0, EVENT_ALL_ACCESS);
	if (!renderer->hFenceEvent) {
		result = XK_ERROR_CREATE_FAILED;
		goto _catch;
	}

	/// TODO: Implementation.

_catch:
	return(result);

_free:
	if(renderer) {
		xkFreeMemory(renderer);
	}

	goto _catch;
}

void xkD3D12DestroyRenderer(XkD3D12Renderer renderer) {
	xkAssert(renderer);

	CloseHandle(renderer->hFenceEvent);

	__xkD3D12DestroyFence(renderer->d3d12Fence);

	__xkD3D12DestroyCommandList(renderer->d3d12CommandList6);

	for(XkSize i = 0; i < XKDIRECTX12_FRAME_COUNT; i++) {
		__xkD3D12DestroyCommandAllocator(renderer->d3d12CommandAllocators[i]);
	}

	__xkD3D12DestroyCommandQueue(renderer->d3d12CommandQueue);

	/// TODO: Implementation.

	xkFreeMemory(renderer);
}

void xkD3D12ClearColorRenderer(XkD3D12Renderer renderer, const XkVec4 color) {
	xkAssert(renderer);

	renderer->clearColorValues[0] = color.r;
	renderer->clearColorValues[1] = color.g;
	renderer->clearColorValues[2] = color.b;
	renderer->clearColorValues[3] = color.a;
}

void xkD3D12ClearDepthRenderer(XkD3D12Renderer renderer, const XkFloat32 depth) {
	xkAssert(renderer);
	xkAssert(depth > 0.0f);
	/// TODO: Implementation.
}

void xkD3D12ClearStencilRenderer(XkD3D12Renderer renderer, const XkUInt32 stencil) {
	xkAssert(renderer);
	xkAssert(stencil > 0);
	/// TODO: Implementation.
}

void xkD3D12ClearRenderer(XkD3D12Renderer renderer) {
	xkAssert(renderer);
	/// TODO: Implementation.
}

void xkD3D12TopologyRenderer(XkD3D12Renderer renderer, const XkTopology topology) {
	xkAssert(renderer);
	/// TODO: Implementation.
}

void xkD3D12CullModeRenderer(XkD3D12Renderer renderer, const XkCullMode cullMode) {
	xkAssert(renderer);
	/// TODO: Implementation.
}

void xkD3D12BeginRenderer(XkD3D12Renderer renderer) {
	xkAssert(renderer);

	if(ID3D12Fence1_GetCompletedValue(renderer->d3d12Fence) < renderer->fenceValue) {
		ID3D12Fence1_SetEventOnCompletion(renderer->d3d12Fence, renderer->fenceValue, renderer->hFenceEvent);

		WaitForSingleObject(renderer->hFenceEvent, INFINITE);
	}

	ID3D12CommandAllocator* d3d12CommandAllocator = renderer->d3d12CommandAllocators[renderer->frameIndex];

	ID3D12CommandAllocator_Reset(d3d12CommandAllocator);

	ID3D12GraphicsCommandList_Reset(renderer->d3d12CommandList6, d3d12CommandAllocator, NULL);
}

void xkD3D12EndRenderer(XkD3D12Renderer renderer) {
	xkAssert(renderer);

	ID3D12GraphicsCommandList_Close(renderer->d3d12CommandList6);

	//ID3D12CommandList d3d12CommandLists[] = {renderer->d3d12CommandList6};
	//ID3D12CommandQueue_ExecuteCommandLists(renderer->d3d12CommandQueue, 1, &d3d12CommandLists[0]);

	renderer->fenceValue++;

	ID3D12CommandQueue_Signal(renderer->d3d12CommandQueue, renderer->d3d12Fence, renderer->fenceValue);

	renderer->frameIndex = (renderer->frameIndex + 1) % XKDIRECTX12_FRAME_COUNT;
}

void xkD3D12ResizeRenderer(XkD3D12Renderer renderer, const XkSize width, const XkSize height) {
	xkAssert(renderer);
	xkAssert(width > 0);
	xkAssert(height > 0);

	renderer->d3d12Viewport.TopLeftX	= 0.0f;
	renderer->d3d12Viewport.TopLeftY	= 0.0f;
	renderer->d3d12Viewport.Width			= (FLOAT)width;
	renderer->d3d12Viewport.Height		= (FLOAT)height;
	renderer->d3d12Viewport.MinDepth	= 0.0f;
	renderer->d3d12Viewport.MaxDepth	= 1.0f;
}

void xkD3D12ScissorRenderer(XkD3D12Renderer renderer, const XkInt32 x, const XkInt32 y, const XkSize width, const XkSize height) {
	xkAssert(renderer);
	xkAssert(width > 0);
	xkAssert(height > 0);

	renderer->d3d12Scissor.left				= x;
	renderer->d3d12Scissor.top				= y;
	renderer->d3d12Scissor.right			= width;
	renderer->d3d12Scissor.bottom			= height;
}

void xkD3D12Draw(XkD3D12Renderer renderer, const XkSize vertexCount) {
	xkAssert(renderer);
	xkAssert(vertexCount > 0);

	/// TODO: Draw DirectX12.
	//ID3D12GraphicsCommandList6_DrawInstanced(renderer->d3d12CommandList6, vertexCount, 1, 0, 0);
}

void xkD3D12DrawIndexed(XkD3D12Renderer renderer, const XkSize indexCount) {
	xkAssert(renderer);
	xkAssert(indexCount > 0);

	/// TODO: Draw indexed DirectX12.
	//ID3D12GraphicsCommandList6_DrawIndexedInstanced(renderer->d3d12CommandList6, indexCount, 1, 0, 0, 0);
}

XkResult xkD3D12CreateBuffer(XkD3D12Buffer* pBuffer, const XkSize size, const XkHandle data, const XkBufferUsage usage) {
	xkAssert(pBuffer);
	xkAssert(size > 0);
	xkAssert(renderer);

	XkResult result = XK_SUCCESS;

	*pBuffer = xkAllocateMemory(sizeof(struct XkD3D12Buffer_T));
	if(!pBuffer) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkD3D12Buffer buffer = *pBuffer;

	/// TODO: Implementation.

_catch:
	return(result);

_free:
	if(buffer) {
		xkFreeMemory(buffer);
	}

	goto _catch;
}

void xkD3D12DestroyBuffer(XkD3D12Buffer buffer) {
	xkAssert(buffer);
	
	/// TODO: Implementation.
	xkFreeMemory(buffer);
}

void xkD3D12MapBuffer(XkD3D12Buffer buffer, const XkHandle data) {
	xkAssert(buffer);
	xkAssert(data);
	/// TODO: Implementation.
}

void xkD3D12BindVertexBuffer(XkD3D12Buffer buffer, XkD3D12Renderer renderer) {
	xkAssert(buffer);
	xkAssert(renderer);
	/// TODO: Implementation.
}

void xkD3D12BindIndexBuffer(XkD3D12Buffer buffer, XkD3D12Renderer renderer) {
	xkAssert(buffer);
	xkAssert(renderer);
	/// TODO: Implementation.
}

XkResult xkD3D12CreateTexture(XkD3D12Texture* pTexture, const XkSize width, const XkSize height, const XkHandle data, const XkTextureType type) {
	xkAssert(pTexture);
	xkAssert(width > 0);
	xkAssert(height > 0);
	xkAssert(data);

	XkResult result = XK_SUCCESS;

	*pTexture = xkAllocateMemory(sizeof(struct XkD3D12Texture_T));
	if(!pTexture) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkD3D12Texture texture = *pTexture;

	/// TODO: Implementation.

_catch:
	return(result);

_free:
	if(texture) {
		xkFreeMemory(texture);
	}

	goto _catch;
}

void xkD3D12DestroyTexture(XkD3D12Texture texture) {
	xkAssert(texture);

	/// TODO: Implementation.
	xkFreeMemory(texture);
}

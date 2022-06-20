#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Platform/Internal.h"

static XkBool __xkDX12CheckTearingSupport(void);

XkResult __xkDXGICreateSwapChain(IDXGISwapChain4** ppDXGISwapChain4, ID3D12CommandQueue* pD3D12CommandQueue, const UINT bufferCount, XkWindow window) {
	XkResult result = XK_SUCCESS;

	// Get window size.
	UINT width = 0;
	UINT height = 0;
	xkGetWindowSize(window, (XkSize* const)&width, (XkSize* const)&height);

	// Get window handle.
	HWND hWnd = __xkWin32GetHWND(window);

	// Template DXGI swapchain1.
	IDXGISwapChain1* dxgiSwapChain1 = NULL;

	// Initialize DirectX12 swap chain info.
	DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainInfo = {0};
	dxgiSwapChainInfo.Width									= width;
	dxgiSwapChainInfo.Height								= height;
	dxgiSwapChainInfo.Format								= DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiSwapChainInfo.Stereo								= FALSE;
	dxgiSwapChainInfo.SampleDesc.Count			= 1;
	dxgiSwapChainInfo.SampleDesc.Quality		= 0;
	dxgiSwapChainInfo.BufferUsage						= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	dxgiSwapChainInfo.BufferCount						= bufferCount;
	dxgiSwapChainInfo.Scaling								= DXGI_SCALING_STRETCH;
	dxgiSwapChainInfo.SwapEffect						= DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiSwapChainInfo.AlphaMode							= DXGI_ALPHA_MODE_UNSPECIFIED;
	dxgiSwapChainInfo.Flags									= __xkDX12CheckTearingSupport() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

	// Create DirectX12 swap chain.
	HRESULT hResult = IDXGIFactory7_CreateSwapChainForHwnd(_xkDX12Context.dxgiFactory7, (IUnknown*)pD3D12CommandQueue, hWnd, &dxgiSwapChainInfo, NULL, NULL, &dxgiSwapChain1);
	if(FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create swap chain");
		goto _catch;
	}

	// Diable the Alt+Enter fullscreen toggle feature. Switching to fullscreen will be handled manually.
	hResult = IDXGIFactory7_MakeWindowAssociation(_xkDX12Context.dxgiFactory7, hWnd, DXGI_MWA_NO_ALT_ENTER);
	if(FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to make window association");
		goto _catch;
	}

	// Query DXGI swapchain4 interface.
	hResult = IDXGISwapChain1_QueryInterface(dxgiSwapChain1 , &IID_IDXGISwapChain4, ppDXGISwapChain4);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to query swapchain4 interface");
		goto _catch;
	}

_catch:
	return(result);
}

void __xkDXGIDestroySwapChain(IDXGISwapChain4* pDXGISwapChain) {
	IDXGISwapChain_Release(pDXGISwapChain);
}

static XkBool __xkDX12CheckTearingSupport(void) {
	IDXGIFactory5* dxgiFactory5 = NULL;

	BOOL allowTearing = FALSE;

	// Create DXGI factory.
	if(SUCCEEDED(CreateDXGIFactory1(&IID_IDXGIFactory5, &dxgiFactory5))) {
		// Check DXGI factory allow tearing.
		if(FAILED(IDXGIFactory5_CheckFeatureSupport(dxgiFactory5, DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(BOOL)))) {
			allowTearing = FALSE;
		}

		// Release DXGI factory.
		IDXGIFactory7_Release(dxgiFactory5);
	}

	return(allowTearing == TRUE);
}

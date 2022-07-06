/* ########## INCLUDE SECTION ########## */
#include "XKinetic/DirectX12/Internal.h"
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Core/Assert.h"

static XkBool8 __xkD3D12CheckTearingSupport(void);

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkDXGICreateSwapChain(IDXGISwapChain4** ppDXGISwapChain4, ID3D12CommandQueue* pD3D12CommandQueue, const UINT bufferCount, XkWindow window) {
	xkAssert(ppDXGISwapChain4);
	xkAssert(pD3D12CommandQueue);
	xkAssert(bufferCount > 0);
	xkAssert(window);

	XkResult result = XK_SUCCESS;

	UINT width = 0;
	UINT height = 0;
	xkGetWindowSize(window, (XkSize* const)&width, (XkSize* const)&height);

	HWND hWnd = __xkWin32GetHWND(window);

	IDXGISwapChain1* dxgiSwapChain1 = NULL;

	DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainInfo = {};
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
	dxgiSwapChainInfo.Flags									= __xkD3D12CheckTearingSupport() ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

	HRESULT hResult = IDXGIFactory7_CreateSwapChainForHwnd(_xkD3D12Context.dxgiFactory7, (IUnknown*)pD3D12CommandQueue, hWnd, &dxgiSwapChainInfo, NULL, NULL, &dxgiSwapChain1);
	if(FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to create swap chain: %s", __xkD3D12ResultString(hResult));
		goto _catch;
	}

	// Diable the Alt+Enter fullscreen toggle feature. Switching to fullscreen will be handled manually.
	hResult = IDXGIFactory7_MakeWindowAssociation(_xkD3D12Context.dxgiFactory7, hWnd, DXGI_MWA_NO_ALT_ENTER);
	if(FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to make window association: %s", __xkD3D12ResultString(hResult));
		goto _catch;
	}

	hResult = IDXGISwapChain1_QueryInterface(dxgiSwapChain1 , &IID_IDXGISwapChain4, ppDXGISwapChain4);
	if (FAILED(hResult)) {
		result = XK_ERROR_UNKNOWN;
		xkLogError("DirectX12: Failed to query swapchain4 interface: %s", __xkD3D12ResultString(hResult));
		goto _catch;
	}

_catch:
	return(result);
}

void __xkDXGIDestroySwapChain(IDXGISwapChain4* pDXGISwapChain) {
	xkAssert(pDXGISwapChain);

	IDXGISwapChain_Release(pDXGISwapChain);
}

static XkBool8 __xkD3D12CheckTearingSupport(void) {
	IDXGIFactory5* dxgiFactory5 = NULL;

	BOOL allowTearing = FALSE;

	if(SUCCEEDED(CreateDXGIFactory1(&IID_IDXGIFactory5, &dxgiFactory5))) {
		if(FAILED(IDXGIFactory5_CheckFeatureSupport(dxgiFactory5, DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(BOOL)))) {
			allowTearing = FALSE;
		}

		IDXGIFactory7_Release(dxgiFactory5);
	}

	return(allowTearing == TRUE);
}

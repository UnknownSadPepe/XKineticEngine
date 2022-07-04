#pragma once

/* ########## INCLUDE SECTION ########## */
#define INITGUID
#define CINTERFACE
#define COBJMACROS
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3dcompiler.h>
#include "XKinetic/XKDirectX12.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"

/* ########## MACROS SECTION ########## */
#define XKDIRECTX12_FRAME_COUNT 2

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* ########## TYPES SECTION ########## */
typedef struct __XkD3D12Context_T {
	IDXGIFactory7*							dxgiFactory7;
	IDXGIAdapter4*							dxgiAdapter4;
 	D3D_FEATURE_LEVEL						d3dDeviceMaximumFeatureLevel;

#ifdef XKDIRECTX12_DEBUG
	ID3D12Debug3*								d3d12Debug3;
	ID3D12DebugDevice2*					d3d12DebugDevice2;
#endif // XKDIRECTX12_DEBUG
	ID3D12InfoQueue*						d3d12InfoQueue;
	ID3D12Device8*							d3d12Device8;
} __XkD3D12Context;

/* ########## EXTERN SECTION ########## */
extern const D3D_FEATURE_LEVEL 	_xkD3DMinimumDeviceFeatureLevel;

extern const UINT 							_xkD3DDeviceFeatureLevelCount;
extern const D3D_FEATURE_LEVEL 	_xkD3DDeviceFeatureLevels[];

extern __XkD3D12Context 				_xkD3D12Context;

/* ########## FUNCTIONS SECTION ########## */
extern XK_EXPORT XkString 	__xkD3D12GetResultString(HRESULT); 

#ifdef XKDIRECTX12_DEBUG
extern XK_EXPORT XkResult 	__xkD3D12CreateDebugLayer();
#endif // XKDIRECTX12_DEBUG

extern XK_EXPORT XkResult 	__xkDXGICreateFactory();
extern XK_EXPORT void 			__xkDXGIDestroyFactory();

extern XK_EXPORT XkResult 	__xkD3D12PickAdapter();

extern XK_EXPORT XkResult 	__xkD3D12CreateDevice();
extern XK_EXPORT void 			__xkD3D12DestroyDevice();

extern XK_EXPORT XkResult 	__xkD3D12QueryInfoQueueInterface();
extern XK_EXPORT void 			__xkD3D12EnableInfoQueue();
extern XK_EXPORT void 			__xkD3D12DisableInfoQueue();

#ifdef XKDIRECTX12_DEBUG
extern XK_EXPORT XkResult 	__xkD3D12QueryDebugDeviceInterface();
extern XK_EXPORT void 			__xkD3D12ReportLiveDeviceObjects();
#endif // XKDIRECTX12_DEBUG

extern XK_EXPORT XkResult 	__xkD3D12CreateCommandAllocator(ID3D12CommandAllocator**, const D3D12_COMMAND_LIST_TYPE);
extern XK_EXPORT void 			__xkD3D12DestroyCommandAllocator(ID3D12CommandAllocator*);

extern XK_EXPORT XkResult 	__xkD3D12CreateCommandQueue(ID3D12CommandQueue**, const D3D12_COMMAND_LIST_TYPE);
extern XK_EXPORT void 			__xkD3D12DestroyCommandQueue(ID3D12CommandQueue*);

extern XK_EXPORT XkResult 	__xkD3D12CreateCommandList(ID3D12GraphicsCommandList6**, ID3D12CommandAllocator*, const D3D12_COMMAND_LIST_TYPE);
extern XK_EXPORT void 			__xkD3D12DestroyCommandList(ID3D12GraphicsCommandList6*);

extern XK_EXPORT XkResult 	__xkD3D12CreateFence(ID3D12Fence**);
extern XK_EXPORT void 			__xkD3D12DestroyFence(ID3D12Fence*);

extern XK_EXPORT XkResult 	__xkD3D12CreateDescriptorHeap(ID3D12DescriptorHeap**, const D3D12_DESCRIPTOR_HEAP_TYPE, const UINT);
extern XK_EXPORT void 			__xkD3D12DestroyDescriptorHeap(ID3D12DescriptorHeap*);

extern XK_EXPORT XkResult 	__xkDXGICreateSwapChain(IDXGISwapChain4**, ID3D12CommandQueue*, const UINT, XkWindow);
extern XK_EXPORT void 			__xkDXGIDestroySwapChain(IDXGISwapChain4*);

/// NOTE: For using in cpp programs.
#ifdef __cplusplus
}
#endif // __cplusplus
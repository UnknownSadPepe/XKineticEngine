#pragma once

#define INITGUID
#define CINTERFACE
#define COBJMACROS
#include <windows.h>
#include <dxgi1_6.h>
#include <d3d12.h>
#include "XKinetic/XKDirectX12.h"
#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/Window.h"

#define XKDIRECTX12_FRAME_COUNT 2

extern const D3D_FEATURE_LEVEL _xkD3DMinimumDeviceFeatureLevel;

extern const UINT _xkD3DDeviceFeatureLevelCount;
extern const D3D_FEATURE_LEVEL _xkD3DDeviceFeatureLevels[];

typedef struct {
	IDXGIFactory7*							dxgiFactory7;
	IDXGIAdapter4*							dxgiAdapter4;
 	D3D_FEATURE_LEVEL						d3dDeviceMaximumFeatureLevel;

#ifdef XKDIRECTX12_DEBUG
	ID3D12Debug3*								d3d12Debug3;
	ID3D12DebugDevice2*					d3d12DebugDevice2;
#endif // XKDIRECTX12_DEBUG
	ID3D12InfoQueue*						d3d12InfoQueue;
	ID3D12Device8*							d3d12Device8;
} __XkDX12Context;

extern __XkDX12Context _xkDX12Context;

XK_IMPORT XkResult __xkDX12InitializeContext(void);
XK_IMPORT void __xkDX12TerminateContext(void);

#ifdef XKDIRECTX12_DEBUG
XK_IMPORT XkResult __xkDX12CreateDebugLayer(void);
#endif // XKDIRECTX12_DEBUG

XK_IMPORT XkResult __xkDXGICreateFactory(void);
XK_IMPORT void __xkDXGIDestroyFactory(void);

XK_IMPORT XkResult __xkDX12PickAdapter(void);

XK_IMPORT XkResult __xkDX12CreateDevice(void);
XK_IMPORT void __xkDX12DestroyDevice(void);

XK_IMPORT void __xkDX12QueryInfoQueueInterface(void);
XK_IMPORT void __xkDX12EnableInfoQueue(void);
XK_IMPORT void __xkDX12DisableInfoQueue(void);

#ifdef XKDIRECTX12_DEBUG
XK_IMPORT void __xkDX12QueryDebugDeviceInterface(void);
XK_IMPORT void __xkDX12ReportLiveDeviceObjects(void);
#endif // XKDIRECTX12_DEBUG

XK_IMPORT XkResult __xkDX12CreateCommandAllocator(ID3D12CommandAllocator**, const D3D12_COMMAND_LIST_TYPE);
XK_IMPORT void __xkDX12DestroyCommandAllocator(ID3D12CommandAllocator*);

XK_IMPORT XkResult __xkDX12CreateCommandQueue(ID3D12CommandQueue**, const D3D12_COMMAND_LIST_TYPE);
XK_IMPORT void __xkDX12DestroyCommandQueue(ID3D12CommandQueue*);

XK_IMPORT XkResult __xkDX12CreateCommandList(ID3D12GraphicsCommandList6**, ID3D12CommandAllocator*, const D3D12_COMMAND_LIST_TYPE);
XK_IMPORT void __xkDX12DestroyCommandList(ID3D12GraphicsCommandList6*);

XK_IMPORT XkResult __xkDX12CreateFence(ID3D12Fence1**);
XK_IMPORT void __xkDX12DestroyFence(ID3D12Fence1*);

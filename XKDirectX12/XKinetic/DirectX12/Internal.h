#pragma once

#include <dxgi1_6.h>
#include <d3d12.h>
extern "C" {
	#include "XKinetic/XKDirectX12.h"
	#include "XKinetic/Core/Minimal.h"
	#include "XKinetic/Platform/Window.h"
}

typedef struct {
	IDXGIFactory7* dxgiFactory;
	IDXGIAdapter4* dxgiAdapter;
	ID3D12Debug3* dx12Debug;
	ID3D12InfoQueue* dx12InfoQueue;
	ID3D12Device8* dx12Device;
} __XkDX12Context;

extern __XkDX12Context _xkDX12Context;

XK_IMPORT XkResult __xkDX12InitializeContext(void);
XK_IMPORT void __xkDX12TerminateContext(void);

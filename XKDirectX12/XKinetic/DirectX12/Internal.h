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

typedef struct {
	IDXGIFactory7* dxgiFactory7;
	IDXGIAdapter4* dxgiAdapter4;
	ID3D12Debug3* d3d12Debug3;
	ID3D12InfoQueue* d3d12InfoQueue;
	ID3D12Device8* d3d12Device8;
} __XkDX12Context;

extern __XkDX12Context _xkDX12Context;

XK_IMPORT XkResult __xkDX12InitializeContext(void);
XK_IMPORT void __xkDX12TerminateContext(void);

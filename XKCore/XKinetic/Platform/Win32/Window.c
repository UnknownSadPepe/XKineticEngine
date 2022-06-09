#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <windows.h>
#include <windowsx.h>
#include "XKinetic/Platform/Win32/Internal.h"

#ifndef WM_MOUSEHWHEEL
 #define WM_MOUSEHWHEEL 0x020E
#endif

static const char XK_WIN32_WINDOW_CLASS_NAME[]  = "XKinetic Win32 Window Class";

static DWORD __xkWin32GetWindowStyle(const XkWindow);
static DWORD __xkWin32GetWindowExStyle(const XkWindow);
static HICON __xkWin32CreateIcon(const XkWindowIcon*, int, int, XkBool32);
static XkWindowIcon* __xkWin32ChooseImage(const XkWindowIcon*, XkSize, XkInt32, XkInt32);
static LRESULT CALLBACK __xkWin32WindowProc(HWND, UINT, WPARAM, LPARAM);
static XkWindowMod __xkWin32GetKeyMod(void);

XkResult xkWindowInitialize(void) {
	XkResult result = XK_SUCCESS;

	_xkPlatform.handle.instance = GetModuleHandle(NULL);
	
	// Initialize Win32 window class.
	WNDCLASSEX wc			= {0};
	wc.cbSize					= sizeof(WNDCLASSEX);
  wc.style					= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc		= __xkWin32WindowProc;
  wc.cbClsExtra			= 0;
  wc.cbWndExtra			= 0;
  wc.hInstance			= _xkPlatform.handle.instance;
	wc.hIcon					= LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor				= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszClassName	= XK_WIN32_WINDOW_CLASS_NAME;
	wc.hCursor				= NULL;
	wc.lpszMenuName		= NULL;

	// Load user-provided icon.
	wc.hIcon = LoadImage(_xkPlatform.handle.instance, "XK_WIN32_ICON", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
  if(!wc.hIcon) {
		// No user-provided icon found, load default icon.
    wc.hIcon = LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
  }

	// Register Win32 window class.
	if(!RegisterClassEx(&wc)) {
		__xkErrorHandle("Failed to register class");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void xkWindowTerminate(void) {
	// Unregister Win32 window class.
	UnregisterClass(XK_WIN32_WINDOW_CLASS_NAME, _xkPlatform.handle.instance); 
}

XkResult xkCreateWindow(XkWindow* pWindow, const XkChar8* title, const XkSize width, const XkSize height, const XkWindowHint hint) {
	XkResult result = XK_SUCCESS;

	*pWindow = xkAllocateMemory(sizeof(struct XkWindow));
	if(!(*pWindow)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;	
	}
	
	XkWindow window = *pWindow;

	if(hint & XK_WINDOW_DECORATED_BIT) window->decorated = XK_TRUE;
	if(hint & XK_WINDOW_RESIZABLE_BIT) window->resizable = XK_TRUE;
	if(hint & XK_WINDOW_FLOATING_BIT) window->floating = XK_TRUE;

  DWORD style = __xkWin32GetWindowStyle(window);
  DWORD exStyle = __xkWin32GetWindowExStyle(window);

	// Create Win32 window.
	window->handle.handle = CreateWindowA(XK_WIN32_WINDOW_CLASS_NAME, title, style, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, _xkPlatform.handle.instance, NULL);
  if(!window->handle.handle) {
		__xkErrorHandle("Failed to create window");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	SetPropA(window->handle.handle, "XKinetic", window);

_catch:
	return(result);
}

void xkDestroyWindow(XkWindow window) {
	DestroyWindow(window->handle.handle);

	if(window->handle.bigIcon) {
  	DestroyIcon(window->handle.bigIcon);
	}

  if(window->handle.smallIcon) {
    DestroyIcon(window->handle.smallIcon);
	}

	xkFreeMemory(window);
}

void xkShowWindow(XkWindow window, const XkWindowShow show) {
	int cmdShow = 0;

	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT: cmdShow = SW_SHOWDEFAULT; break;
		case XK_WINDOW_SHOW_MAXIMIZED: cmdShow = SW_SHOWMAXIMIZED; break;
		case XK_WINDOW_SHOW_MINIMIZED: cmdShow = SW_SHOWMINIMIZED; break;
		case XK_WINDOW_SHOW_FULLSCREEN: /* TODO: implementation */ break;
		case XK_WINDOW_HIDE: cmdShow = SW_HIDE; break;
	}

	ShowWindow(window->handle.handle, cmdShow);
}

void xkFocusWindow(XkWindow window) {
	SetFocus(window->handle.handle);
}

void xkSetWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	RECT rect = { 0, 0, width, height };

  AdjustWindowRectEx(&rect, __xkWin32GetWindowStyle(window), FALSE, __xkWin32GetWindowExStyle(window));

	SetWindowPos(window->handle.handle, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
}

void xkGetWindowSize(XkWindow window, XkSize* const pWidth, XkSize* const pHeight) {
  RECT area;
  GetClientRect(window->handle.handle, &area);

  if(pWidth)
  	*pWidth = area.right;
  if(pHeight)
  	*pHeight = area.bottom;
}

void xkSetWindowSizeLimits(XkWindow window, const XkSize minWidth, const XkSize minHeight, const XkSize maxWidth, const XkSize maxHeight) {
	RECT area;
	GetWindowRect(window->handle.handle, &area);
  MoveWindow(window->handle.handle, area.left, area.top, area.right - area.left, area.bottom - area.top, TRUE);
}

void xkSetWindowPosition(XkWindow window, const XkInt32 xPos, const XkInt32 yPos) {
	SetWindowPos(window->handle.handle, NULL, xPos , yPos, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

void xkGetWindowPosition(XkWindow window, XkInt32* const pXPos, XkInt32* const pYPos) {
	POINT pos = { 0, 0 };
  ClientToScreen(window->handle.handle, &pos);

  if(pXPos)
  	*pXPos = pos.x;
  if(pYPos)
  	*pYPos = pos.y;
}

void xkSetWindowTitle(XkWindow window, const XkChar8* title) {
	SetWindowTextA(window->handle.handle, title);
}

void xkSetWindowIcon(XkWindow window, const XkSize count, const XkWindowIcon* pIcon) {
	HICON bigIcon = NULL, smallIcon = NULL;

   if(count) {
  	const XkWindowIcon* bigImage = __xkWin32ChooseImage(pIcon, count, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON));
    const XkWindowIcon* smallImage = __xkWin32ChooseImage(pIcon, count, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON));

    bigIcon = __xkWin32CreateIcon(bigImage, 0, 0, XK_TRUE);
    smallIcon = __xkWin32CreateIcon(smallImage, 0, 0, XK_TRUE);
 	} else {
    bigIcon = (HICON)GetClassLongPtrW(window->handle.handle, GCLP_HICON);
  	smallIcon = (HICON)GetClassLongPtrW(window->handle.handle, GCLP_HICONSM);
  }

  SendMessageW(window->handle.handle, WM_SETICON, ICON_BIG, (LPARAM) bigIcon);
  SendMessageW(window->handle.handle, WM_SETICON, ICON_SMALL, (LPARAM) smallIcon);

  if(window->handle.bigIcon)
  	DestroyIcon(window->handle.bigIcon);

  if(window->handle.smallIcon)
    DestroyIcon(window->handle.smallIcon);

  if(count) {
  	window->handle.bigIcon = bigIcon;
    window->handle.smallIcon = smallIcon;
  }
}

void xkPollWindowEvents(void) {
	MSG msg;

	while(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
  	TranslateMessage(&msg);
  	DispatchMessageW(&msg);
	}
}

void xkWaitWindowEvents(void) {
	WaitMessage();

	xkPollWindowEvents();
}

static DWORD __xkWin32GetWindowStyle(const XkWindow window) {
	DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	style |= WS_POPUP;
	style |= WS_MINIMIZEBOX | WS_SYSMENU;

	if(window->decorated) {
		style |= WS_CAPTION;
	}

	if(window->resizable) {
		style |= WS_MAXIMIZEBOX | WS_THICKFRAME;
	}

	return(style);
}

static DWORD __xkWin32GetWindowExStyle(const XkWindow window) {
	DWORD style = WS_EX_APPWINDOW;

  return(style);
}

static XkWindowIcon* __xkWin32ChooseImage(const XkWindowIcon* pIcons, const XkSize count, const XkInt32 width, const XkInt32 height) {
  int leastDiff = INT_MAX;
  const XkWindowIcon* pSelect = NULL;

  for(XkSize i = 0;  i < count;  i++) {
  	const int currDiff = (pIcons[i].width * pIcons[i].height - width * height);
    if(currDiff < leastDiff) {
      pSelect = pIcons + i;
      leastDiff = currDiff;
    }
  }

  return(pSelect);
}

static HICON __xkWin32CreateIcon(const XkWindowIcon* pIcon, const XkInt32 xHot, const XkInt32 yHot, const XkBool32 icon) {
	XkUInt8* pTarget = NULL;
	XkUInt8* pSource = pIcon->pixels;

	/*BITMAPV5HEADER bi = {
		.bV5Size = sizeof(bi),
  	.bV5Width = pIcon->width,
  	.bV5Height = -pIcon->height,
  	.bV5Planes = 1,
  	.bV5BitCount = 32,
  	.bV5Compression = BI_BITFIELDS,
  	.bV5RedMask = 0x00ff0000,
  	.bV5GreenMask = 0x0000ff00,
  	.bV5BlueMask = 0x000000ff,
  	.bV5AlphaMask = 0xff000000
	};	

	HDC dc = GetDC(NULL);
	HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*) &bi, DIB_RGB_COLORS, (void**) &pSource, NULL, (DWORD)0);
  ReleaseDC(NULL, dc);

  if(!color) {
  	return(NULL);
  }

  HBITMAP mask = CreateBitmap(pIcon->width, pIcon->height, 1, 1, NULL);
  if(!mask) {
  	DeleteObject(color);
  	return(NULL);
  }

  for(XkSize i = 0;  i < pIcon->width * pIcon->height;  i++) {
  	pTarget[0] = pSource[2];
  	pTarget[1] = pSource[1];
  	pTarget[2] = pSource[0];
  	pTarget[3] = pSource[3];
  	pTarget += 4;
  	pSource += 4;
  }

	ICONINFO ii = {
    .fIcon    = icon,
    .xHotspot = xHot,
    .yHotspot = yHot,
    .hbmMask  = mask,
    .hbmColor = color
	};

  HICON handle = CreateIconIndirect(&ii);

  DeleteObject(color);
  DeleteObject(mask);

  if(!handle) {
  	return(NULL);  	
  }

  return(handle);*/
   	return(NULL);  	
}

static LRESULT CALLBACK __xkWin32WindowProc(HWND hwindow, UINT message, WPARAM wParam, LPARAM lParam) {
	XkWindow window = GetPropA(hwindow, "XKinetic");
	if(!window) {
		return DefWindowProcW(hwindow, message, wParam, lParam);
	}

	switch(message) {
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP: {
      XkWindowAction action = (HIWORD(lParam) & KF_UP) ? XK_RELEASE : XK_PRESS;
      XkWindowMod mod = __xkWin32GetKeyMod();

			int scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));
			// Alt+PrtSc has a different scancode than just PrtSc.
      if(scancode == 0x54)
        scancode = 0x137;

      // Ctrl+Pause has a different scancode than just Pause.
      if(scancode == 0x146)
        scancode = 0x45;

			int key = _xkPlatform.keycodes[scancode];
			__xkInputWindowKey(window, key, action, mod);
			return(0);
		}

		case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP: {
			XkWindowButton button;
			XkWindowAction action;

      if(message == WM_LBUTTONDOWN || message == WM_LBUTTONUP)
        button = XK_WINDOW_BUTTON_LEFT;
      else if(message == WM_RBUTTONDOWN || message == WM_RBUTTONUP)
        button = XK_WINDOW_BUTTON_RIGHT;
			else if(message == WM_MBUTTONDOWN || message == WM_MBUTTONUP)
        button = XK_WINDOW_BUTTON_MIDDLE;
      else if(GET_XBUTTON_WPARAM(wParam) == XBUTTON1)
        button = XK_WINDOW_BUTTON_4;
      else
        button = XK_WINDOW_BUTTON_5;

      if(message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_XBUTTONDOWN) {
				action = XK_PRESS;
      } else {
        action = XK_RELEASE;
			}

			XkWindowMod mod = __xkWin32GetKeyMod();

			__xkInputWindowButton(window, button, action, mod);
		}

		case WM_MOUSEMOVE: {
			const int x = GET_X_LPARAM(lParam);
      const int y = GET_Y_LPARAM(lParam);
			__xkInputWindowCursor(window, x, y);
			if(!window->handle.cursorTracked) {
				__xkInputWindowCursorEnter(window, XK_TRUE);	
				window->handle.cursorTracked = XK_TRUE;
			}
			return(0);
		}

    case WM_MOUSELEAVE: {
      __xkInputWindowCursorEnter(window, XK_FALSE);
			window->handle.cursorTracked = XK_FALSE;
      return 0;
    }

    case WM_MOUSEWHEEL: {
      __xkInputWindowScroll(window, 0.0, (SHORT)HIWORD(wParam) / (double)WHEEL_DELTA);
			return(0);
		}

    case WM_MOUSEHWHEEL: {
      __xkInputWindowScroll(window, -((SHORT)HIWORD(wParam) / (double)WHEEL_DELTA), 0.0);
			return(0);
		}

		case WM_CLOSE: {
			__xkInputWindowClose(window);
			return(0);
		}

		case WM_MOVE: {
			__xkInputWindowPosition(window, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return(0);
		}

		case WM_SIZE: {
			const int width = LOWORD(lParam);
      const int height = HIWORD(lParam);
      const XkBool32 minimized = wParam == SIZE_MINIMIZED;
      const XkBool32 maximized = wParam == SIZE_MAXIMIZED || (window->maximized && wParam != SIZE_RESTORED);

			if(window->minimized != minimized) {
        __xkInputWindowShow(window, XK_WINDOW_SHOW_MINIMIZED);
			}

			if(window->maximized != maximized) {
        __xkInputWindowShow(window, XK_WINDOW_SHOW_MAXIMIZED);
			}

      if(width != window->width || height != window->height) {
				window->width = width;
        window->height = height;

        __xkInputWindowSize(window, width, height);
      }


      window->minimized = minimized;
      window->maximized = maximized;

			return(0);
		}

		case WM_SETFOCUS: {
			__xkInputWindowFocus(window, XK_TRUE);
			return(0);
		}

		case WM_KILLFOCUS: {
			__xkInputWindowFocus(window, XK_FALSE);
			return(0);
		}
	}

  return DefWindowProcW(window, message, wParam, lParam);
}

static XkWindowMod __xkWin32GetKeyMod(void) {
  XkWindowMod mod;

  if(GetKeyState(VK_SHIFT) & 0x8000) mod |= XK_WINDOW_MOD_SHIFT;
  if(GetKeyState(VK_CONTROL) & 0x8000) mod |= XK_WINDOW_MOD_CONTROL;
  if(GetKeyState(VK_MENU) & 0x8000) mod |= XK_WINDOW_MOD_ALT;
  if((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) mod |= XK_WINDOW_MOD_SUPER;
  if(GetKeyState(VK_CAPITAL) & 1) mod |= XK_WINDOW_MOD_CAPS_LOCK;
	if(GetKeyState(VK_NUMLOCK) & 1) mod |= XK_WINDOW_MOD_NUM_LOCK;

  return mod;
}

#endif // XK_WIN32

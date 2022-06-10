#include "XKinetic/Platform/Internal.h"

#if defined(XK_WIN32)

#include <limits.h>
#include <windows.h>
#include <windowsx.h>
#include "XKinetic/Platform/Win32/Internal.h"

#ifndef WM_MOUSEHWHEEL
 #define WM_MOUSEHWHEEL 0x020E
#endif

#ifndef GET_XBUTTON_WPARAM
	#define GET_XBUTTON_WPARAM(w) (HIWORD(w))
#endif // GET_XBUTTON_WPARAM

static const char XK_WIN32_WINDOW_CLASS_NAME[]  = "XKinetic Win32 Window Class";

static DWORD __xkWin32GetWindowStyle(const XkWindow);
static DWORD __xkWin32GetWindowExStyle(const XkWindow);
static void __xkWin32GetFullWindowSize(DWORD, DWORD, int, int, int*, int*);
static HICON __xkWin32CreateIcon(const XkWindowIcon*, int, int, XkBool32);
static XkWindowIcon* __xkWin32ChooseImage(const XkWindowIcon*, XkSize, XkInt32, XkInt32);
static LRESULT CALLBACK __xkWin32WindowProc(HWND, UINT, WPARAM, LPARAM);
static XkWindowMod __xkWin32GetKeyMod(void);

static void __xkWin32InitializeKeycodes();

XkResult xkWindowInitialize(void) {
	XkResult result = XK_SUCCESS;

  // Get Win32 instance handle.
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

	// Register Win32 window class.
	if(!RegisterClassEx(&wc)) {
		__xkErrorHandle("Win32: Failed to register class");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

  // Initialize Win32 keycodes.
	__xkWin32InitializeKeycodes();

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
  if(hint & XK_WINDOW_FULLSCREEN_BIT) window->fullscreen = XK_TRUE;

  window->minWidth  = 0;
  window->minHeight = 0;
  window->maxWidth  = 0;
  window->maxHeight = 0;

  DWORD style = __xkWin32GetWindowStyle(window);
  DWORD exStyle = __xkWin32GetWindowExStyle(window);

  int xpos = 0;
  int ypos = 0;
  int fullWidth = width;
  int fullHeight = height;

	// Create Win32 window.
	window->handle.handle = CreateWindowA(XK_WIN32_WINDOW_CLASS_NAME, title, style, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, _xkPlatform.handle.instance, NULL);
  if(!window->handle.handle) {
		__xkErrorHandle("Win32: Failed to create window");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

  // Set Win32 property for get it int WindowProc.
	SetPropA(window->handle.handle, "XKinetic", window);

_catch:
	return(result);
}

void xkDestroyWindow(XkWindow window) {
  // Remove Win32 property.
  RemovePropA(window->handle.handle, "XKinetic");

  // Destroy Win32 window.
	DestroyWindow(window->handle.handle);

	xkFreeMemory(window);
}

void xkShowWindow(XkWindow window, const XkWindowShow show) {
	int cmdShow = 0;

	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT: ShowWindow(window->handle.handle, SW_SHOWDEFAULT); break;
		case XK_WINDOW_SHOW_MAXIMIZED: ShowWindow(window->handle.handle, SW_SHOWMAXIMIZED); break;
		case XK_WINDOW_SHOW_MINIMIZED: ShowWindow(window->handle.handle, SW_SHOWMINIMIZED); break;
		case XK_WINDOW_SHOW_FULLSCREEN: {
      SetWindowPos(window->handle.handle, HWND_TOPMOST , 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_SHOWWINDOW);
      break;
    }
		case XK_WINDOW_HIDE: ShowWindow(window->handle.handle, SW_HIDE); break;
	}
}

void xkFocusWindow(XkWindow window) {
  BringWindowToTop(window->handle.handle);
  SetForegroundWindow(window->handle.handle);
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
  MoveWindow(window->handle.handle, area.left, area.top, area.right - area.left, area.bottom - area.top, FALSE);

  window->minWidth  = minWidth;
  window->minHeight = minHeight;
  window->maxWidth  = maxWidth;
  window->maxHeight = maxHeight;
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

    bigIcon = __xkWin32CreateIcon(bigImage, 0, 0, TRUE);
    smallIcon = __xkWin32CreateIcon(smallImage, 0, 0, TRUE);
 	} else {
    bigIcon = (HICON)GetClassLongPtrW(window->handle.handle, GCLP_HICON);
  	smallIcon = (HICON)GetClassLongPtrW(window->handle.handle, GCLP_HICONSM);
  }

  SendMessageW(window->handle.handle, WM_SETICON, ICON_BIG, (LPARAM) bigIcon);
  SendMessageW(window->handle.handle, WM_SETICON, ICON_SMALL, (LPARAM) smallIcon);
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

  if(window->fullscreen) {
    style |= WS_POPUP;
  } else {
	  style |= WS_SYSMENU;

    if(window->decorated) {
		  style |= WS_CAPTION;

      if(window->resizable) {
		    style |= WS_MAXIMIZEBOX | WS_THICKFRAME | WS_MINIMIZEBOX;
	    }
	  } else {
      style |= WS_POPUP;   
    }
  }

	return(style);
}

static DWORD __xkWin32GetWindowExStyle(const XkWindow window) {
	DWORD style = WS_EX_APPWINDOW;

  if(window->fullscreen || window->floating)
    style |= WS_EX_TOPMOST;

  return(style);
}

static XkWindowIcon* __xkWin32ChooseImage(const XkWindowIcon* pIcons, const XkSize count, const XkInt32 width, const XkInt32 height) {
  int leastDiff = INT_MAX;
  XkWindowIcon* pSelect = NULL;

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

  BITMAPV5HEADER bi;
  ZeroMemory(&bi, sizeof(bi));
	bi = (BITMAPV5HEADER){
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
	HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*) &bi, DIB_RGB_COLORS, (void**) &pTarget, NULL, (DWORD)0);
  ReleaseDC(NULL, dc);

  if(!color) {
    __xkErrorHandle("Win32: Failed to create RGBA bitmap");
  	return(NULL);
  }

  HBITMAP mask = CreateBitmap(pIcon->width, pIcon->height, 1, 1, NULL);
  if(!mask) {
    __xkErrorHandle("Win32: Failed to create mask bitmap");
  	DeleteObject(color);
  	return(NULL);
  }

  for(int i = 0;  i < pIcon->width * pIcon->height;  i++) {
  	pTarget[0] = pSource[2];
  	pTarget[1] = pSource[1];
  	pTarget[2] = pSource[0];
  	pTarget[3] = pSource[3];
  	pTarget += 4;
  	pSource += 4;
  }

  ICONINFO ii;
  ZeroMemory(&ii, sizeof(ii));
	ii = (ICONINFO){
    .fIcon    = icon,
    .xHotspot = xHot,
    .yHotspot = yHot,
    .hbmMask  = mask,
    .hbmColor = color
	};

  HICON handle = CreateIconIndirect(&ii);

  if(!handle) {
    if(icon) {
      __xkErrorHandle("Win32: Failed to create icon");
    } else {
      __xkErrorHandle("Win32: Failed to create cursor");
    }
  }

  DeleteObject(color);
  DeleteObject(mask);

  return(handle); 	
}

static void __xkWin32GetFullWindowSize(DWORD style, DWORD exStyle, int contentWidth, int contentHeight, int* fullWidth, int* fullHeight) {
  RECT rect = {0, 0, contentWidth, contentHeight};

  AdjustWindowRectEx(&rect, style, FALSE, exStyle);

  *fullWidth = rect.right - rect.left;
  *fullHeight = rect.bottom - rect.top;
}

static LRESULT CALLBACK __xkWin32WindowProc(HWND hwindow, UINT message, WPARAM wParam, LPARAM lParam) {
	XkWindow window = GetPropA(hwindow, "XKinetic");
	if(!window) {
		return DefWindowProcA(hwindow, message, wParam, lParam);
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

			if(wParam == VK_CONTROL) {
				if(HIWORD(lParam) & KF_EXTENDED) {
          key = XK_KEY_RIGHT_CONTROL;
        } else {
 					MSG next;
          const DWORD time = GetMessageTime();

          if(PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE)) {
          	if(next.message == WM_KEYDOWN || next.message == WM_SYSKEYDOWN || next.message == WM_KEYUP || next.message == WM_SYSKEYUP) {
              if (next.wParam == VK_MENU && (HIWORD(next.lParam) & KF_EXTENDED) && next.time == time) {
                break;
              }
            }
          }

          key = XK_KEY_LEFT_CONTROL;
				}
			} else if(wParam == VK_PROCESSKEY) {
				break;
			}

			if(action == XK_RELEASE && wParam == VK_SHIFT) {
				__xkInputWindowKey(window, XK_KEY_LEFT_SHIFT, action, mod);
				__xkInputWindowKey(window, XK_KEY_RIGHT_SHIFT, action, mod);
			} else if(wParam == VK_SNAPSHOT) {
				__xkInputWindowKey(window, key, XK_PRESS, mod);
				__xkInputWindowKey(window, key, XK_RELEASE, mod);
			} else {
				__xkInputWindowKey(window, key, action, mod);
			}

			break;
		}

		case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_XBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_XBUTTONUP: {
      XkWindowMod mod = __xkWin32GetKeyMod();

			XkWindowButton button;
			XkWindowAction action;

      if(message == WM_LBUTTONDOWN || message == WM_LBUTTONUP) {
        button = XK_BUTTON_LEFT;
      } else if(message == WM_RBUTTONDOWN || message == WM_RBUTTONUP) {
        button = XK_BUTTON_RIGHT;
			} else if(message == WM_MBUTTONDOWN || message == WM_MBUTTONUP) {
        button = XK_BUTTON_MIDDLE;
      } else if(GET_XBUTTON_WPARAM(wParam) == XBUTTON1) {
        button = XK_BUTTON_4;
      } else {
        button = XK_BUTTON_5;
      }

      if(message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_XBUTTONDOWN) {
				action = XK_PRESS;
      } else {
        action = XK_RELEASE;
			}

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

    case WM_GETMINMAXINFO: {
      int xoff, yoff;
      MINMAXINFO* mmi = (MINMAXINFO*)lParam;

      if(window->fullscreen)
        break;

      __xkWin32GetFullWindowSize(__xkWin32GetWindowStyle(window), __xkWin32GetWindowExStyle(window), 0, 0, &xoff, &yoff);

      if(window->minWidth != 0 && window->minHeight != 0) {
        mmi->ptMinTrackSize.x = window->minWidth + xoff;
        mmi->ptMinTrackSize.y = window->minHeight + yoff;
      }

      if(window->maxWidth != 0 && window->maxHeight != 0) {
        mmi->ptMaxTrackSize.x = window->maxWidth + xoff;
        mmi->ptMaxTrackSize.y = window->maxHeight + yoff;
      }

      if(!window->decorated) {
        MONITORINFO mi;
        const HMONITOR mh = MonitorFromWindow(window->handle.handle, MONITOR_DEFAULTTONEAREST);

        ZeroMemory(&mi, sizeof(mi));
        mi.cbSize = sizeof(mi);
        GetMonitorInfoW(mh, &mi);

        mmi->ptMaxPosition.x = mi.rcWork.left - mi.rcMonitor.left;
        mmi->ptMaxPosition.y = mi.rcWork.top - mi.rcMonitor.top;
        mmi->ptMaxSize.x = mi.rcWork.right - mi.rcWork.left;
        mmi->ptMaxSize.y = mi.rcWork.bottom - mi.rcWork.top;
      }

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

  return DefWindowProc(hwindow, message, wParam, lParam);
}

static XkWindowMod __xkWin32GetKeyMod(void) {
  XkWindowMod mod = 0;

  if(GetKeyState(VK_SHIFT) & 0x8000) 
    mod |= XK_MOD_SHIFT_BIT;

  if(GetKeyState(VK_CONTROL) & 0x8000) 
    mod |= XK_MOD_CONTROL_BIT;

  if(GetKeyState(VK_MENU) & 0x8000) 
    mod |= XK_MOD_ALT_BIT;

  if((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & 0x8000) 
    mod |= XK_MOD_SUPER_BIT;

  if(GetKeyState(VK_CAPITAL) & 1) 
    mod |= XK_MOD_CAPS_LOCK_BIT;

	if(GetKeyState(VK_NUMLOCK) & 1)
    mod |= XK_MOD_NUM_LOCK_BIT;

  return mod;
}

static void __xkWin32InitializeKeycodes(void) {
  int scancode;

  xkZeroMemory(_xkPlatform.keycodes, sizeof(_xkPlatform.keycodes));

  _xkPlatform.keycodes[0x00B] = XK_KEY_0;
  _xkPlatform.keycodes[0x002] = XK_KEY_1;
  _xkPlatform.keycodes[0x003] = XK_KEY_2;
  _xkPlatform.keycodes[0x004] = XK_KEY_3;
  _xkPlatform.keycodes[0x005] = XK_KEY_4;
  _xkPlatform.keycodes[0x006] = XK_KEY_5;
  _xkPlatform.keycodes[0x007] = XK_KEY_6;
  _xkPlatform.keycodes[0x008] = XK_KEY_7;
  _xkPlatform.keycodes[0x009] = XK_KEY_8;
  _xkPlatform.keycodes[0x00A] = XK_KEY_9;
  _xkPlatform.keycodes[0x01E] = XK_KEY_A;
  _xkPlatform.keycodes[0x030] = XK_KEY_B;
  _xkPlatform.keycodes[0x02E] = XK_KEY_C;
  _xkPlatform.keycodes[0x020] = XK_KEY_D;
  _xkPlatform.keycodes[0x012] = XK_KEY_E;
  _xkPlatform.keycodes[0x021] = XK_KEY_F;
  _xkPlatform.keycodes[0x022] = XK_KEY_G;
  _xkPlatform.keycodes[0x023] = XK_KEY_H;
  _xkPlatform.keycodes[0x017] = XK_KEY_I;
  _xkPlatform.keycodes[0x024] = XK_KEY_J;
  _xkPlatform.keycodes[0x025] = XK_KEY_K;
  _xkPlatform.keycodes[0x026] = XK_KEY_L;
  _xkPlatform.keycodes[0x032] = XK_KEY_M;
  _xkPlatform.keycodes[0x031] = XK_KEY_N;
  _xkPlatform.keycodes[0x018] = XK_KEY_O;
  _xkPlatform.keycodes[0x019] = XK_KEY_P;
  _xkPlatform.keycodes[0x010] = XK_KEY_Q;
  _xkPlatform.keycodes[0x013] = XK_KEY_R;
  _xkPlatform.keycodes[0x01F] = XK_KEY_S;
  _xkPlatform.keycodes[0x014] = XK_KEY_T;
  _xkPlatform.keycodes[0x016] = XK_KEY_U;
  _xkPlatform.keycodes[0x02F] = XK_KEY_V;
  _xkPlatform.keycodes[0x011] = XK_KEY_W;
  _xkPlatform.keycodes[0x02D] = XK_KEY_X;
  _xkPlatform.keycodes[0x015] = XK_KEY_Y;
  _xkPlatform.keycodes[0x02C] = XK_KEY_Z;

  _xkPlatform.keycodes[0x028] = XK_KEY_APOSTROPHE;
  _xkPlatform.keycodes[0x02B] = XK_KEY_BACKSLASH;
  _xkPlatform.keycodes[0x033] = XK_KEY_COMMA;
  _xkPlatform.keycodes[0x00D] = XK_KEY_EQUAL;
  _xkPlatform.keycodes[0x029] = XK_KEY_GRAVE_ACCENT;
  _xkPlatform.keycodes[0x01A] = XK_KEY_LEFT_BRACKET;
  _xkPlatform.keycodes[0x00C] = XK_KEY_MINUS;
  _xkPlatform.keycodes[0x034] = XK_KEY_PERIOD;
  _xkPlatform.keycodes[0x01B] = XK_KEY_RIGHT_BRACKET;
  _xkPlatform.keycodes[0x027] = XK_KEY_SEMICOLON;
  _xkPlatform.keycodes[0x035] = XK_KEY_SLASH;
  _xkPlatform.keycodes[0x056] = XK_KEY_WORLD_2;

  _xkPlatform.keycodes[0x00E] = XK_KEY_BACKSPACE;
  _xkPlatform.keycodes[0x153] = XK_KEY_DELETE;
  _xkPlatform.keycodes[0x14F] = XK_KEY_END;
  _xkPlatform.keycodes[0x01C] = XK_KEY_ENTER;
  _xkPlatform.keycodes[0x001] = XK_KEY_ESCAPE;
  _xkPlatform.keycodes[0x147] = XK_KEY_HOME;
  _xkPlatform.keycodes[0x152] = XK_KEY_INSERT;
  _xkPlatform.keycodes[0x15D] = XK_KEY_MENU;
  _xkPlatform.keycodes[0x151] = XK_KEY_PAGE_DOWN;
  _xkPlatform.keycodes[0x149] = XK_KEY_PAGE_UP;
  _xkPlatform.keycodes[0x045] = XK_KEY_PAUSE;
  _xkPlatform.keycodes[0x039] = XK_KEY_SPACE;
  _xkPlatform.keycodes[0x00F] = XK_KEY_TAB;
  _xkPlatform.keycodes[0x03A] = XK_KEY_CAPS_LOCK;
  _xkPlatform.keycodes[0x145] = XK_KEY_NUM_LOCK;
  _xkPlatform.keycodes[0x046] = XK_KEY_SCROLL_LOCK;
  _xkPlatform.keycodes[0x03B] = XK_KEY_F1;
  _xkPlatform.keycodes[0x03C] = XK_KEY_F2;
  _xkPlatform.keycodes[0x03D] = XK_KEY_F3;
  _xkPlatform.keycodes[0x03E] = XK_KEY_F4;
  _xkPlatform.keycodes[0x03F] = XK_KEY_F5;
  _xkPlatform.keycodes[0x040] = XK_KEY_F6;
  _xkPlatform.keycodes[0x041] = XK_KEY_F7;
  _xkPlatform.keycodes[0x042] = XK_KEY_F8;
  _xkPlatform.keycodes[0x043] = XK_KEY_F9;
  _xkPlatform.keycodes[0x044] = XK_KEY_F10;
  _xkPlatform.keycodes[0x057] = XK_KEY_F11;
  _xkPlatform.keycodes[0x058] = XK_KEY_F12;
  _xkPlatform.keycodes[0x064] = XK_KEY_F13;
  _xkPlatform.keycodes[0x065] = XK_KEY_F14;
  _xkPlatform.keycodes[0x066] = XK_KEY_F15;
  _xkPlatform.keycodes[0x067] = XK_KEY_F16;
  _xkPlatform.keycodes[0x068] = XK_KEY_F17;
  _xkPlatform.keycodes[0x069] = XK_KEY_F18;
  _xkPlatform.keycodes[0x06A] = XK_KEY_F19;
  _xkPlatform.keycodes[0x06B] = XK_KEY_F20;
  _xkPlatform.keycodes[0x06C] = XK_KEY_F21;
  _xkPlatform.keycodes[0x06D] = XK_KEY_F22;
  _xkPlatform.keycodes[0x06E] = XK_KEY_F23;
  _xkPlatform.keycodes[0x076] = XK_KEY_F24;
  _xkPlatform.keycodes[0x038] = XK_KEY_LEFT_ALT;
  _xkPlatform.keycodes[0x01D] = XK_KEY_LEFT_CONTROL;
  _xkPlatform.keycodes[0x02A] = XK_KEY_LEFT_SHIFT;
  _xkPlatform.keycodes[0x15B] = XK_KEY_LEFT_SUPER;
  _xkPlatform.keycodes[0x137] = XK_KEY_PRINT_SCREEN;
  _xkPlatform.keycodes[0x138] = XK_KEY_RIGHT_ALT;
  _xkPlatform.keycodes[0x11D] = XK_KEY_RIGHT_CONTROL;
  _xkPlatform.keycodes[0x036] = XK_KEY_RIGHT_SHIFT;
  _xkPlatform.keycodes[0x15C] = XK_KEY_RIGHT_SUPER;
  _xkPlatform.keycodes[0x150] = XK_KEY_DOWN;
  _xkPlatform.keycodes[0x14B] = XK_KEY_LEFT;
  _xkPlatform.keycodes[0x14D] = XK_KEY_RIGHT;
  _xkPlatform.keycodes[0x148] = XK_KEY_UP;

  _xkPlatform.keycodes[0x052] = XK_KEY_KP_0;
  _xkPlatform.keycodes[0x04F] = XK_KEY_KP_1;
  _xkPlatform.keycodes[0x050] = XK_KEY_KP_2;
  _xkPlatform.keycodes[0x051] = XK_KEY_KP_3;
  _xkPlatform.keycodes[0x04B] = XK_KEY_KP_4;
  _xkPlatform.keycodes[0x04C] = XK_KEY_KP_5;
  _xkPlatform.keycodes[0x04D] = XK_KEY_KP_6;
  _xkPlatform.keycodes[0x047] = XK_KEY_KP_7;
  _xkPlatform.keycodes[0x048] = XK_KEY_KP_8;
  _xkPlatform.keycodes[0x049] = XK_KEY_KP_9;
  _xkPlatform.keycodes[0x04E] = XK_KEY_KP_ADD;
  _xkPlatform.keycodes[0x053] = XK_KEY_KP_DECIMAL;
  _xkPlatform.keycodes[0x135] = XK_KEY_KP_DIVIDE;
  _xkPlatform.keycodes[0x11C] = XK_KEY_KP_ENTER;
  _xkPlatform.keycodes[0x059] = XK_KEY_KP_EQUAL;
  _xkPlatform.keycodes[0x037] = XK_KEY_KP_MULTIPLY;
  _xkPlatform.keycodes[0x04A] = XK_KEY_KP_SUBTRACT;
}

#endif // XK_WIN32

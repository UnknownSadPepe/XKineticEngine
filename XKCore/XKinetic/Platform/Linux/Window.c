#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_LINUX)

#define _GNU_SOURCE
#define _POSIX_SOURCE 200809L
#define _XOPEN_SOURCE
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/timerfd.h>
#include <stdlib.h>
#include <limits.h>
#include "XKinetic/Core/String.h"
#include <xkbcommon/xkbcommon.h>
#include <poll.h>

#include "wayland-client-protocol.h"
#include "wayland-xdg-shell-client-protocol.h"
#include "wayland-xdg-decoration-client-protocol.h"
#include "wayland-viewporter-client-protocol.h"
#include "wayland-relative-pointer-unstable-v1-client-protocol.h"
#include "wayland-pointer-constraints-unstable-v1-client-protocol.h"
#include "wayland-idle-inhibit-unstable-v1-client-protocol.h"

#include "wayland-client-protocol-code.h"
#include "wayland-xdg-shell-client-protocol-code.h"
#include "wayland-xdg-decoration-client-protocol-code.h"
#include "wayland-viewporter-client-protocol-code.h"
#include "wayland-relative-pointer-unstable-v1-client-protocol-code.h"
#include "wayland-pointer-constraints-unstable-v1-client-protocol-code.h"
#include "wayland-idle-inhibit-unstable-v1-client-protocol-code.h"

static XkBool __xkXdgCreateSurface(XkWindow);
static void __xkXdgSetDecorations(XkWindow);
static void __xkZwpSetIdleInhibitor(XkWindow, XkBool);

static void __xkWlCreateKeycodes(void);

static void __xkXdgWmBasePing(void* data, struct xdg_wm_base* xdgBase, uint32_t serial) {
	xdg_wm_base_pong(xdgBase, serial);
}

static const struct xdg_wm_base_listener _xkXdgWmBaseListener = {
  __xkXdgWmBasePing,
};

static void __xkXdgSurfaceHandleConfigure(void* data, struct xdg_surface* xdgSurface, uint32_t serial) {
  xdg_surface_ack_configure(xdgSurface, serial);
}

static const struct xdg_surface_listener _xkXdgSurfaceListener = {
  __xkXdgSurfaceHandleConfigure
};

static void __xkXdgToplevelHandleConfigure(void* data, struct xdg_toplevel* xdgToplevel, int32_t width, int32_t height, struct wl_array* wlStates) {
	XkWindow window = (XkWindow)data;

  XkBool maximized = XK_FALSE;
  XkBool fullscreen = XK_FALSE;
  XkBool activated = XK_FALSE;

	uint32_t* state;
	wl_array_for_each(state, wlStates) {
		switch(*state) {
			case XDG_TOPLEVEL_STATE_MAXIMIZED: maximized = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_FULLSCREEN: fullscreen = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_RESIZING: break;
      case XDG_TOPLEVEL_STATE_ACTIVATED: activated = XK_TRUE; break;
    }
  }

	if(width != 0 && height != 0) {
		__xkInputWindowSize(window, (XkSize)width, (XkSize)height);
		xkSetWindowSize(window, (XkSize)width, (XkSize)height);
	}

	if(window->fullscreen) {
		if(!activated || !fullscreen)	{
			xkShowWindow(window, XK_WINDOW_SHOW_MINIMIZED);
			window->fullscreen = XK_FALSE;
		}
	}

  if(fullscreen && activated) {
		window->fullscreen = XK_TRUE;
  }
}

static void __xkXdgToplevelHandleClose(void* data, struct xdg_toplevel* xdgToplevel) {
	XkWindow window = (XkWindow)data;
	__xkInputWindowClose(window);
}

static const struct xdg_toplevel_listener _xkXdgToplevelListener = {
  __xkXdgToplevelHandleConfigure,
  __xkXdgToplevelHandleClose
};

static void __xkXdgDecorationHandleConfigure(void* data, struct zxdg_toplevel_decoration_v1* xdgDecoration, uint32_t mode) {
	/// NOTE: nothing to do here.
}

static const struct zxdg_toplevel_decoration_v1_listener __xkXdgDecorationListener = {
  __xkXdgDecorationHandleConfigure,
};

static void __xkWlRegistryGlobal(void* data, struct wl_registry* wlRegistry, uint32_t name, const char* interface, uint32_t version) {
  if(xkCompareString((XkString)interface, "wl_compositor")) {
		// Wayland compositor.
		_xkPlatform.handle.wlCompositor = wl_registry_bind(wlRegistry, name, &wl_compositor_interface, version);
	} else if(xkCompareString((XkString)interface, "wl_subcompositor")) {
		// Wayland subcompositor.
		_xkPlatform.handle.wlSubcompositor = wl_registry_bind(wlRegistry, name, &wl_subcompositor_interface, 1);
	} else if(xkCompareString((XkString)interface, "wl_shm")) { 
		// Wayland shared memory.
		_xkPlatform.handle.wlShm = wl_registry_bind(wlRegistry, name, &wl_shm_interface, 1);
  } else if(xkCompareString((XkString)interface, "wl_seat")) {
		// Wayland seat.
    _xkPlatform.handle.wlSeat = wl_registry_bind(wlRegistry, name, &wl_seat_interface, 4);
	} else if(xkCompareString((XkString)interface, "wl_output")) {
		// Wayland output.
			_xkPlatform.handle.wlOutput = wl_registry_bind(wlRegistry, name, &wl_output_interface, version);
  } else if(xkCompareString((XkString)interface, "xdg_wm_base")) {
		// Xdg Base.
    _xkPlatform.handle.xdgBase = wl_registry_bind(wlRegistry, name, &xdg_wm_base_interface, 1);
		xdg_wm_base_add_listener(_xkPlatform.handle.xdgBase, &_xkXdgWmBaseListener, NULL);
  } else if(xkCompareString((XkString)interface, "zxdg_decoration_manager_v1")) {
		// Xdg decoration manager.
    _xkPlatform.handle.xdgDecorationManager = wl_registry_bind(wlRegistry, name, &zxdg_decoration_manager_v1_interface, 1);
  } else if(xkCompareString((XkString)interface, "wp_viewporter")) {
		// Wp viewporter.
    _xkPlatform.handle.wpViewporter = wl_registry_bind(wlRegistry, name, &wp_viewporter_interface, 1);
  } else if(xkCompareString((XkString)interface, "zwp_relative_pointer_manager_v1")) {
  	// ZWp relative pointer manager.
     _xkPlatform.handle.zwpRelativePointerManager = wl_registry_bind(wlRegistry, name, &zwp_relative_pointer_manager_v1_interface, 1);
  } else if (xkCompareString((XkString)interface, "zwp_pointer_constraints_v1")) {
  	// ZWp pointer constraints.
    _xkPlatform.handle.zwpPointerConstraints = wl_registry_bind(wlRegistry, name, &zwp_pointer_constraints_v1_interface, 1);
  } else if (xkCompareString((XkString)interface, "zwp_idle_inhibit_manager_v1")) {
  	// ZWp idle inhibit manager.
    _xkPlatform.handle.zwpIdleInhibitManager = wl_registry_bind(wlRegistry, name, &zwp_idle_inhibit_manager_v1_interface, 1);
  } else if(xkCompareString((XkString)interface, "wl_data_device_manager") == 0) {
  	// Wayland data device manager.
		if(!_xkPlatform.handle.wlDataDeviceManager) {
			_xkPlatform.handle.wlDataDeviceManager = wl_registry_bind(wlRegistry, name, &wl_data_device_manager_interface, 1);
    }
	}
}

static void __xkWlRegistryGlobalRemove(void* data, struct wl_registry* wlRegistry, uint32_t name) {
	/// TODO: implementation
}

static const struct wl_registry_listener _xkWlRegistryListener = {
	__xkWlRegistryGlobal,
  __xkWlRegistryGlobalRemove,
};

static void __xkWlSurfaceHandleEnter(void* data, struct wl_surface* pSurface, struct wl_output* pOutput) {
	/// TODO: implementation
}

static void __xkWlSurfaceHandleLeave(void* data, struct wl_surface* pSurface, struct wl_output* pOutput) {
	/// TODO: implementation
}

static const struct wl_surface_listener _xkWlSurfaceListener = {
  __xkWlSurfaceHandleEnter,
  __xkWlSurfaceHandleLeave
};

XkResult xkWindowInitialize(void) {
	XkResult result = XK_SUCCESS;

	// Connect Wayland server.
	_xkPlatform.handle.wlDisplay = wl_display_connect(NULL);
	if(!_xkPlatform.handle.wlDisplay) {
		__xkErrorHandle("Wayland: Failed to connect display");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Get Wayland display registry.
	_xkPlatform.handle.wlRegistry = wl_display_get_registry(_xkPlatform.handle.wlDisplay);
	if(!_xkPlatform.handle.wlRegistry) {
		__xkErrorHandle("Wayland: Failed to get display registry");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Add Wayland display registry listener.
  wl_registry_add_listener(_xkPlatform.handle.wlRegistry, &_xkWlRegistryListener, NULL);

	__xkWlCreateKeycodes();

	// Create XKB context.
	_xkPlatform.handle.xkbContext = xkb_context_new(0);
 	if(!_xkPlatform.handle.xkbContext) {
		__xkErrorHandle("XKB: Failed to create context");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
 	}

	// Sync so we got all registry objects.
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);

	// Sync so we got all initial output events.
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);

// Check Wayland compositor register object.
	if(!_xkPlatform.handle.wlCompositor) {
		__xkErrorHandle("Wayland: Failed to create compositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check Wayland subcompositor register object.
	if(!_xkPlatform.handle.wlSubcompositor) {
		__xkErrorHandle("Wayland: Failed to create subcompositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check Xdg base register object.
	if(!_xkPlatform.handle.xdgBase) {
		__xkErrorHandle("Wayland: Failed to create XDG base");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Create Wayland compositor surface.
  _xkPlatform.handle.wlSurface = wl_compositor_create_surface(_xkPlatform.handle.wlCompositor);
	if(!_xkPlatform.handle.wlSurface) {
		__xkErrorHandle("Wayland: Failed to create compositor surface");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check XDG Wm base.
  if(!_xkPlatform.handle.xdgBase) {
		__xkErrorHandle("Wayland: Failed to find xdg-shell in your compositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

  // Create Wayland cursor.
  if(_xkPlatform.handle.wlPointer && _xkPlatform.handle.wlShm) {
  	const XkString cursorTheme = getenv("XCURSOR_THEME");
  	const XkString cursorSizeStr = getenv("XCURSOR_SIZE");
  	int cursorSize = 32;
  	if(cursorSizeStr) {
			char* cursorSizeEnd;
			long cursorSizeLong = strtol(cursorSizeStr, &cursorSizeEnd, 10);
			if(!(*cursorSizeEnd) && cursorSizeLong > 0 && cursorSizeLong <= INT_MAX) {
        cursorSize = (int)cursorSizeLong;
			}
  	}

  	// Load Wayland cursor theme.
		_xkPlatform.handle.wlCursorTheme = wl_cursor_theme_load(cursorTheme, cursorSize, _xkPlatform.handle.wlShm);
	  if(!_xkPlatform.handle.wlCursorTheme) {
			__xkErrorHandle("Wayland: Failed to load default cursor theme");
			result = XK_ERROR_UNKNOWN;
			goto _catch;
  	}

		_xkPlatform.handle.wlCursorThemeHiDPI = wl_cursor_theme_load(cursorTheme, 2 * cursorSize, _xkPlatform.handle.wlShm);
	  if(!_xkPlatform.handle.wlCursorThemeHiDPI) {
			__xkErrorHandle("Wayland: Failed to load hidpi cursor theme");
			result = XK_ERROR_UNKNOWN;
			goto _catch;
  	}
  }

_catch:
	return(result);
}

void xkWindowTerminate(void) {
 	if(_xkPlatform.handle.xkbComposeState) {
    xkb_compose_state_unref(_xkPlatform.handle.xkbComposeState);
  }
	if(_xkPlatform.handle.xkbKeymap) {
 		xkb_keymap_unref(_xkPlatform.handle.xkbKeymap);
  }
  if(_xkPlatform.handle.xkbState) {
 		xkb_state_unref(_xkPlatform.handle.xkbState);
  }
  if(_xkPlatform.handle.xkbContext) {
  	xkb_context_unref(_xkPlatform.handle.xkbContext);
  }

	if(_xkPlatform.handle.wlCursorTheme) {
		wl_cursor_theme_destroy(_xkPlatform.handle.wlCursorTheme);
	}
	if(_xkPlatform.handle.wlCursorThemeHiDPI) {
		wl_cursor_theme_destroy(_xkPlatform.handle.wlCursorThemeHiDPI);
	}

	if(_xkPlatform.handle.wlCursorSurface){
		wl_surface_destroy(_xkPlatform.handle.wlCursorSurface);
	}

 	if (_xkPlatform.handle.wlSubcompositor){
		wl_subcompositor_destroy(_xkPlatform.handle.wlSubcompositor);
 	}
  if (_xkPlatform.handle.wlCompositor){
		wl_compositor_destroy(_xkPlatform.handle.wlCompositor);
  }

 	if (_xkPlatform.handle.wlShm){
		wl_shm_destroy(_xkPlatform.handle.wlShm);
 	}

 	if (_xkPlatform.handle.wpViewporter){
		wp_viewporter_destroy(_xkPlatform.handle.wpViewporter);
 	}

 	if(_xkPlatform.handle.xdgBase) {
		xdg_wm_base_destroy(_xkPlatform.handle.xdgBase);
	}
 	if (_xkPlatform.handle.xdgDecorationManager){
		zxdg_decoration_manager_v1_destroy(_xkPlatform.handle.xdgDecorationManager);
 	}

 	if (_xkPlatform.handle.wlSelectionOffer){
		wl_data_offer_destroy(_xkPlatform.handle.wlSelectionOffer);
 	}
 	if (_xkPlatform.handle.wlDragOffer){
		wl_data_offer_destroy(_xkPlatform.handle.wlDragOffer);
 	}
 	if (_xkPlatform.handle.wlSelectionSource){
		wl_data_source_destroy(_xkPlatform.handle.wlSelectionSource);
 	}
 	if (_xkPlatform.handle.wlDataDevice){
		wl_data_device_destroy(_xkPlatform.handle.wlDataDevice);
 	}
 	if (_xkPlatform.handle.wlDataDeviceManager){
		wl_data_device_manager_destroy(_xkPlatform.handle.wlDataDeviceManager);
 	}
 	if (_xkPlatform.handle.wlPointer){
		wl_pointer_destroy(_xkPlatform.handle.wlPointer);
 	}
 	if (_xkPlatform.handle.wlKeyboard){
		wl_keyboard_destroy(_xkPlatform.handle.wlKeyboard);
 	}
 	if (_xkPlatform.handle.wlSeat){
		wl_seat_destroy(_xkPlatform.handle.wlSeat);
 	}

 	if (_xkPlatform.handle.zwpRelativePointerManager){
		zwp_relative_pointer_manager_v1_destroy(_xkPlatform.handle.zwpRelativePointerManager);
 	}
 	if (_xkPlatform.handle.zwpPointerConstraints){
		zwp_pointer_constraints_v1_destroy(_xkPlatform.handle.zwpPointerConstraints);
 	}
 	if (_xkPlatform.handle.zwpIdleInhibitManager) {
		zwp_idle_inhibit_manager_v1_destroy(_xkPlatform.handle.zwpIdleInhibitManager);
 	}

	if(_xkPlatform.handle.wlRegistry) {
  	wl_registry_destroy(_xkPlatform.handle.wlRegistry);
	}
	if(_xkPlatform.handle.wlDisplay) {
  	wl_display_flush(_xkPlatform.handle.wlDisplay);
		wl_display_disconnect(_xkPlatform.handle.wlDisplay);
	}
}

XkResult xkCreateWindow(XkWindow* pWindow, const XkString title, const XkSize width, const XkSize height, const XkWindowHint hint) {
	XkResult result = XK_SUCCESS;

	*pWindow = xkAllocateMemory(sizeof(struct XkWindow));
	if(!(*pWindow)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}

	XkWindow window = *pWindow;

	window->handle.title = xkDuplicateString(title);
	window->width = width;
	window->height = height;
	window->xPos = 0;
	window->yPos = 0;

	window->decorated = XK_FALSE;
	window->resizable = XK_FALSE;
	window->floating = XK_FALSE;
	window->fullscreen = XK_FALSE;
	window->maximized = XK_FALSE;
	window->minimized = XK_FALSE;

	if(hint & XK_WINDOW_DECORATED_BIT) window->decorated = XK_TRUE;
	if(hint & XK_WINDOW_RESIZABLE_BIT) window->resizable = XK_TRUE;
	if(hint & XK_WINDOW_FLOATING_BIT) window->floating = XK_TRUE;
	if(hint & XK_WINDOW_FULLSCREEN_BIT) window->fullscreen = XK_TRUE;

	// Create Wayland window surface.
	window->handle.wlSurface = wl_compositor_create_surface(_xkPlatform.handle.wlCompositor);
  if(!window->handle.wlSurface) {
		__xkErrorHandle("Wayland: Failed to create surface");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Add Wayland surface listener.
  wl_surface_add_listener(window->handle.wlSurface, &_xkWlSurfaceListener, window);

	// Set Wayland surface user data.
	wl_surface_set_user_data(window->handle.wlSurface, window);

	// Create Wayland EGL window.
	window->handle.eglWindow = wl_egl_window_create(window->handle.wlSurface, (int)width, (int)height);
  if(!window->handle.wlSurface) {
		__xkErrorHandle("Wayland: Failed to create EGL window");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Commit pending Wayland surface state.
  wl_surface_commit(window->handle.wlSurface);
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);

_catch:
	return(result);
}

void xkDestroyWindow(XkWindow window) {
	/// TODO: implementation
	if(window->handle.zwpIdleInhibitor) {
		zwp_idle_inhibitor_v1_destroy(window->handle.zwpIdleInhibitor);
	}

	if(window->handle.xdgDecoration) {
		zxdg_toplevel_decoration_v1_destroy(window->handle.xdgDecoration);
	}

	if(window->handle.xdgToplevel) {
		xdg_toplevel_destroy(window->handle.xdgToplevel);
	}

	if(window->handle.xdgSurface) {
		xdg_surface_destroy(window->handle.xdgSurface);
	}

	if(window->handle.wlSurface) {
		wl_surface_destroy(window->handle.wlSurface);
	}

	if(window->handle.eglWindow) {
		wl_egl_window_destroy(window->handle.eglWindow);
	}


	xkFreeMemory(window->handle.title);
	xkFreeMemory(window);
}

void xkShowWindow(XkWindow window, const XkWindowShow show) {
	/// TODO: implementation

	if(!window->handle.xdgToplevel) {
		__xkXdgCreateSurface(window);
	}

	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT:
			if(window->fullscreen) {
				xdg_toplevel_unset_fullscreen(window->handle.xdgToplevel);
				window->fullscreen = XK_FALSE;
			}
			if(window->maximized) {
				xdg_toplevel_unset_maximized(window->handle.xdgToplevel);
				window->maximized = XK_FALSE;
			}
			__xkZwpSetIdleInhibitor(window, XK_FALSE);
			__xkXdgSetDecorations(window);
			break;

		case XK_WINDOW_SHOW_MAXIMIZED:
			xdg_toplevel_set_maximized(window->handle.xdgToplevel);
			__xkZwpSetIdleInhibitor(window, XK_FALSE);
			__xkXdgSetDecorations(window);
			window->maximized = XK_TRUE;
			break;

		case XK_WINDOW_SHOW_MINIMIZED:
			xdg_toplevel_set_minimized(window->handle.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_FULLSCREEN:
			xdg_toplevel_set_fullscreen(window->handle.xdgToplevel, _xkPlatform.handle.wlOutput);
    	__xkZwpSetIdleInhibitor(window, XK_TRUE);
    	window->fullscreen = XK_TRUE;
			break;

		case XK_WINDOW_HIDE:
      wl_surface_attach(window->handle.wlSurface, NULL, 0, 0);
      wl_surface_commit(window->handle.wlSurface);
			break;
	}

	// Commit pending Wayland surface state.
 	wl_surface_commit(window->handle.wlSurface);
 	wl_display_roundtrip(_xkPlatform.handle.wlDisplay);
}

void xkFocusWindow(XkWindow window) {
	// A Wayland client can not focus.
	__xkErrorHandle("Wayland: platform doesn't support setting the input focus");
}

void xkSetWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	/// TODO: implementation
	window->width = width;
	window->width = height;
}

void xkGetWindowSize(XkWindow window, XkSize* const pWidth, XkSize* const pHeight) {
	if(pWidth)
		*pWidth = window->width;
  if(pHeight)
    *pHeight = window->height;
}

void xkSetWindowSizeLimits(XkWindow window, const XkSize minWidth, const XkSize minHeight, const XkSize maxWidth, const XkSize maxHeight) {
	if(window->handle.xdgToplevel) {
  	xdg_toplevel_set_min_size(window->handle.xdgToplevel, (int32_t)minWidth, (int32_t)minHeight);
		xdg_toplevel_set_max_size(window->handle.xdgToplevel, (int32_t)maxWidth, (int32_t)maxHeight);
		wl_surface_commit(window->handle.wlSurface);
	}
}

void xkSetWindowPosition(XkWindow window, const XkInt32 xPos, const XkInt32 yPos) {
	// A Wayland client can not set its position.
	__xkErrorHandle("Wayland: platform doesn't support setting the input position");
}

void xkGetWindowPosition(XkWindow window, XkInt32* const pXPos, XkInt32* const pYPos) {
  // A Wayland client is not aware of its position.
	__xkErrorHandle("Wayland: platform doesn't provide the window position");
}

void xkSetWindowTitle(XkWindow window, const XkString title) {
  if(window->handle.xdgToplevel) {
  	if(window->handle.title) {
			xkFreeMemory(window->handle.title);
		}
  	window->handle.title = xkDuplicateString(title);

		xdg_toplevel_set_title(window->handle.xdgToplevel, title);
  }
}

void xkSetWindowIcon(XkWindow window, const XkSize count, const XkWindowIcon* pIcon) {
	// A Wayland client can not set its icon
	__xkErrorHandle("Wayland: platform doesn't support setting the window icon");
}

void xkSetCursorPosition(XkWindow window, const XkFloat64 xPos, const XkFloat64 yPos) {
	zwp_locked_pointer_v1_set_cursor_position_hint(window->handle.zwpLockedPointer, wl_fixed_from_double(xPos), wl_fixed_from_double(yPos));
	wl_surface_commit(window->handle.wlSurface);
}

void xkGetCursorPosition(XkWindow window, XkFloat64* const pXPos, XkFloat64* const pYPos) {
	if(pXPos) {
		*pXPos = window->xCursorPos;
	}
	if(pYPos) {
		*pYPos = window->yCursorPos;
	}
}

XkResult xkCreateWindowCursor(XkWindowCursor* pCursor, XkWindowIcon* pIcon, const XkSize xhot, const XkSize yhot) {
	XkResult result = XK_SUCCESS;

	/// TODO: implementation.

_catch:
	return(result);
}

void xkSetWindowCursor(XkWindow window, XkWindowCursor cursor) {
	/// TODO: implementation.
}

void xkDestroyWindowCursor(XkWindowCursor cursor) {
	/// TODO: implementation.
}

void xkPollWindowEvents(void) {
	while(wl_display_dispatch(_xkPlatform.handle.wlDisplay)) {
		/// TODO: implementation.
	}
}

void xkWaitWindowEvents(void) {
	while(wl_display_dispatch(_xkPlatform.handle.wlDisplay)) {
		/// TODO: implementation
	}
}

static XkBool __xkXdgCreateSurface(XkWindow window) {
	XkBool result = XK_TRUE;

	// Get Xdg surface from Wayland surface.
	window->handle.xdgSurface = xdg_wm_base_get_xdg_surface(_xkPlatform.handle.xdgBase, window->handle.wlSurface);
	if(!window->handle.xdgSurface) {
		result = XK_FALSE;
		__xkErrorHandle("Wayland: Failed to create Xdg surface");
		goto _catch;
  }

	// Add Xdg surface listener.
  xdg_surface_add_listener(window->handle.xdgSurface, &_xkXdgSurfaceListener, window);

	// Get Xdg toplevel.
	window->handle.xdgToplevel = xdg_surface_get_toplevel(window->handle.xdgSurface);
  if(!window->handle.xdgToplevel) {
		result = XK_FALSE;
		__xkErrorHandle("Wayland: Failed to create Xdg toplevel");
		goto _catch;
  }

	// Add Xdg toplevel listener.
  xdg_toplevel_add_listener(window->handle.xdgToplevel, &_xkXdgToplevelListener, window);

	// Set Xdg window title.
  xdg_toplevel_set_title(window->handle.xdgToplevel, window->handle.title);
			
	// Commit pending Wayland surface state.
  wl_surface_commit(window->handle.wlSurface);
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);

_catch:
	return(result);
}

static void __xkXdgSetDecorations(XkWindow window) {
	if(_xkPlatform.handle.xdgDecorationManager) {
		window->handle.xdgDecoration = zxdg_decoration_manager_v1_get_toplevel_decoration(_xkPlatform.handle.xdgDecorationManager, window->handle.xdgToplevel);
  	zxdg_toplevel_decoration_v1_add_listener(window->handle.xdgDecoration, &__xkXdgDecorationListener, window);
  	zxdg_toplevel_decoration_v1_set_mode(window->handle.xdgDecoration, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
  } else {
		__xkErrorHandle("Wayland: Failed to create XDG decorations");
		goto _catch;
  }

_catch:
	return;
}

static void __xkZwpSetIdleInhibitor(XkWindow window, XkBool enabled) {
	if(enabled && !window->handle.zwpIdleInhibitor && _xkPlatform.handle.zwpIdleInhibitManager) {
		window->handle.zwpIdleInhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(_xkPlatform.handle.zwpIdleInhibitManager, window->handle.wlSurface);

		if(!window->handle.zwpIdleInhibitor) {
			__xkErrorHandle("Wayland: Failed to create idle inhibitor");
			goto _catch;
		}
  } else if(!enabled && window->handle.zwpIdleInhibitor) {
      zwp_idle_inhibitor_v1_destroy(window->handle.zwpIdleInhibitor);
      window->handle.zwpIdleInhibitor = XK_NULL_HANDLE;
  }

_catch:
	return;
}

static void __xkWlCreateKeycodes(void) {
	xkZeroMemory(_xkPlatform.keycodes, sizeof(_xkPlatform.keycodes));

	_xkPlatform.keycodes[KEY_GRAVE]      = XK_KEY_GRAVE_ACCENT;
	_xkPlatform.keycodes[KEY_1]          = XK_KEY_1;
	_xkPlatform.keycodes[KEY_2]          = XK_KEY_2;
	_xkPlatform.keycodes[KEY_3]          = XK_KEY_3;
	_xkPlatform.keycodes[KEY_4]          = XK_KEY_4;
	_xkPlatform.keycodes[KEY_5]          = XK_KEY_5;
	_xkPlatform.keycodes[KEY_6]          = XK_KEY_6;
	_xkPlatform.keycodes[KEY_7]          = XK_KEY_7;
	_xkPlatform.keycodes[KEY_8]          = XK_KEY_8;
	_xkPlatform.keycodes[KEY_9]          = XK_KEY_9;
	_xkPlatform.keycodes[KEY_0]          = XK_KEY_0;
	_xkPlatform.keycodes[KEY_SPACE]      = XK_KEY_SPACE;
	_xkPlatform.keycodes[KEY_MINUS]      = XK_KEY_MINUS;
	_xkPlatform.keycodes[KEY_EQUAL]      = XK_KEY_EQUAL;
	_xkPlatform.keycodes[KEY_Q]          = XK_KEY_Q;
	_xkPlatform.keycodes[KEY_W]          = XK_KEY_W;
	_xkPlatform.keycodes[KEY_E]          = XK_KEY_E;
	_xkPlatform.keycodes[KEY_R]          = XK_KEY_R;
	_xkPlatform.keycodes[KEY_T]          = XK_KEY_T;
	_xkPlatform.keycodes[KEY_Y]          = XK_KEY_Y;
	_xkPlatform.keycodes[KEY_U]          = XK_KEY_U;
	_xkPlatform.keycodes[KEY_I]          = XK_KEY_I;
	_xkPlatform.keycodes[KEY_O]          = XK_KEY_O;
	_xkPlatform.keycodes[KEY_P]          = XK_KEY_P;
	_xkPlatform.keycodes[KEY_LEFTBRACE]  = XK_KEY_LEFT_BRACKET;
	_xkPlatform.keycodes[KEY_RIGHTBRACE] = XK_KEY_RIGHT_BRACKET;
	_xkPlatform.keycodes[KEY_A]          = XK_KEY_A;
	_xkPlatform.keycodes[KEY_S]          = XK_KEY_S;
	_xkPlatform.keycodes[KEY_D]          = XK_KEY_D;
	_xkPlatform.keycodes[KEY_F]          = XK_KEY_F;
	_xkPlatform.keycodes[KEY_G]          = XK_KEY_G;
	_xkPlatform.keycodes[KEY_H]          = XK_KEY_H;
	_xkPlatform.keycodes[KEY_J]          = XK_KEY_J;
	_xkPlatform.keycodes[KEY_K]          = XK_KEY_K;
	_xkPlatform.keycodes[KEY_L]          = XK_KEY_L;
	_xkPlatform.keycodes[KEY_SEMICOLON]  = XK_KEY_SEMICOLON;
	_xkPlatform.keycodes[KEY_APOSTROPHE] = XK_KEY_APOSTROPHE;
	_xkPlatform.keycodes[KEY_Z]          = XK_KEY_Z;
	_xkPlatform.keycodes[KEY_X]          = XK_KEY_X;
	_xkPlatform.keycodes[KEY_C]          = XK_KEY_C;
	_xkPlatform.keycodes[KEY_V]          = XK_KEY_V;
	_xkPlatform.keycodes[KEY_B]          = XK_KEY_B;
	_xkPlatform.keycodes[KEY_N]          = XK_KEY_N;
	_xkPlatform.keycodes[KEY_M]          = XK_KEY_M;
	_xkPlatform.keycodes[KEY_COMMA]      = XK_KEY_COMMA;
	_xkPlatform.keycodes[KEY_DOT]        = XK_KEY_PERIOD;
	_xkPlatform.keycodes[KEY_SLASH]      = XK_KEY_SLASH;
	_xkPlatform.keycodes[KEY_BACKSLASH]  = XK_KEY_BACKSLASH;
	_xkPlatform.keycodes[KEY_ESC]        = XK_KEY_ESCAPE;
	_xkPlatform.keycodes[KEY_TAB]        = XK_KEY_TAB;
	_xkPlatform.keycodes[KEY_LEFTSHIFT]  = XK_KEY_LEFT_SHIFT;
	_xkPlatform.keycodes[KEY_RIGHTSHIFT] = XK_KEY_RIGHT_SHIFT;
	_xkPlatform.keycodes[KEY_LEFTCTRL]   = XK_KEY_LEFT_CONTROL;
	_xkPlatform.keycodes[KEY_RIGHTCTRL]  = XK_KEY_RIGHT_CONTROL;
	_xkPlatform.keycodes[KEY_LEFTALT]    = XK_KEY_LEFT_ALT;
	_xkPlatform.keycodes[KEY_RIGHTALT]   = XK_KEY_RIGHT_ALT;
	_xkPlatform.keycodes[KEY_LEFTMETA]   = XK_KEY_LEFT_SUPER;
	_xkPlatform.keycodes[KEY_RIGHTMETA]  = XK_KEY_RIGHT_SUPER;
	_xkPlatform.keycodes[KEY_COMPOSE]    = XK_KEY_MENU;
	_xkPlatform.keycodes[KEY_NUMLOCK]    = XK_KEY_NUM_LOCK;
	_xkPlatform.keycodes[KEY_CAPSLOCK]   = XK_KEY_CAPS_LOCK;
	_xkPlatform.keycodes[KEY_PRINT]      = XK_KEY_PRINT_SCREEN;
	_xkPlatform.keycodes[KEY_SCROLLLOCK] = XK_KEY_SCROLL_LOCK;
	_xkPlatform.keycodes[KEY_PAUSE]      = XK_KEY_PAUSE;
	_xkPlatform.keycodes[KEY_DELETE]     = XK_KEY_DELETE;
	_xkPlatform.keycodes[KEY_BACKSPACE]  = XK_KEY_BACKSPACE;
	_xkPlatform.keycodes[KEY_ENTER]      = XK_KEY_ENTER;
	_xkPlatform.keycodes[KEY_HOME]       = XK_KEY_HOME;
	_xkPlatform.keycodes[KEY_END]        = XK_KEY_END;
	_xkPlatform.keycodes[KEY_PAGEUP]     = XK_KEY_PAGE_UP;
	_xkPlatform.keycodes[KEY_PAGEDOWN]   = XK_KEY_PAGE_DOWN;
	_xkPlatform.keycodes[KEY_INSERT]     = XK_KEY_INSERT;
	_xkPlatform.keycodes[KEY_LEFT]       = XK_KEY_LEFT;
	_xkPlatform.keycodes[KEY_RIGHT]      = XK_KEY_RIGHT;
	_xkPlatform.keycodes[KEY_DOWN]       = XK_KEY_DOWN;
	_xkPlatform.keycodes[KEY_UP]         = XK_KEY_UP;
	_xkPlatform.keycodes[KEY_F1]         = XK_KEY_F1;
	_xkPlatform.keycodes[KEY_F2]         = XK_KEY_F2;
	_xkPlatform.keycodes[KEY_F3]         = XK_KEY_F3;
	_xkPlatform.keycodes[KEY_F4]         = XK_KEY_F4;
	_xkPlatform.keycodes[KEY_F5]         = XK_KEY_F5;
	_xkPlatform.keycodes[KEY_F6]         = XK_KEY_F6;
	_xkPlatform.keycodes[KEY_F7]         = XK_KEY_F7;
	_xkPlatform.keycodes[KEY_F8]         = XK_KEY_F8;
	_xkPlatform.keycodes[KEY_F9]         = XK_KEY_F9;
	_xkPlatform.keycodes[KEY_F10]        = XK_KEY_F10;
	_xkPlatform.keycodes[KEY_F11]        = XK_KEY_F11;
	_xkPlatform.keycodes[KEY_F12]        = XK_KEY_F12;
	_xkPlatform.keycodes[KEY_F13]        = XK_KEY_F13;
	_xkPlatform.keycodes[KEY_F14]        = XK_KEY_F14;
	_xkPlatform.keycodes[KEY_F15]        = XK_KEY_F15;
	_xkPlatform.keycodes[KEY_F16]        = XK_KEY_F16;
	_xkPlatform.keycodes[KEY_F17]        = XK_KEY_F17;
	_xkPlatform.keycodes[KEY_F18]        = XK_KEY_F18;
	_xkPlatform.keycodes[KEY_F19]        = XK_KEY_F19;
	_xkPlatform.keycodes[KEY_F20]        = XK_KEY_F20;
	_xkPlatform.keycodes[KEY_F21]        = XK_KEY_F21;
	_xkPlatform.keycodes[KEY_F22]        = XK_KEY_F22;
	_xkPlatform.keycodes[KEY_F23]        = XK_KEY_F23;
	_xkPlatform.keycodes[KEY_F24]        = XK_KEY_F24;
	_xkPlatform.keycodes[KEY_KPSLASH]    = XK_KEY_KP_DIVIDE;
	_xkPlatform.keycodes[KEY_KPASTERISK] = XK_KEY_KP_MULTIPLY;
	_xkPlatform.keycodes[KEY_KPMINUS]    = XK_KEY_KP_SUBTRACT;
	_xkPlatform.keycodes[KEY_KPPLUS]     = XK_KEY_KP_ADD;
	_xkPlatform.keycodes[KEY_KP0]        = XK_KEY_KP_0;
	_xkPlatform.keycodes[KEY_KP1]        = XK_KEY_KP_1;
	_xkPlatform.keycodes[KEY_KP2]        = XK_KEY_KP_2;
	_xkPlatform.keycodes[KEY_KP3]        = XK_KEY_KP_3;
	_xkPlatform.keycodes[KEY_KP4]        = XK_KEY_KP_4;
	_xkPlatform.keycodes[KEY_KP5]        = XK_KEY_KP_5;
	_xkPlatform.keycodes[KEY_KP6]        = XK_KEY_KP_6;
	_xkPlatform.keycodes[KEY_KP7]        = XK_KEY_KP_7;
	_xkPlatform.keycodes[KEY_KP8]        = XK_KEY_KP_8;
	_xkPlatform.keycodes[KEY_KP9]        = XK_KEY_KP_9;
	_xkPlatform.keycodes[KEY_KPDOT]      = XK_KEY_KP_DECIMAL;
	_xkPlatform.keycodes[KEY_KPEQUAL]    = XK_KEY_KP_EQUAL;
	_xkPlatform.keycodes[KEY_KPENTER]    = XK_KEY_KP_ENTER;
	_xkPlatform.keycodes[KEY_102ND]      = XK_KEY_WORLD_2;
}

#endif // XK_LINUX

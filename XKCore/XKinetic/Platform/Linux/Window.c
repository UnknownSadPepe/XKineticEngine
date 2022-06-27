#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_LINUX)

#define _GNU_SOURCE
#define __USE_GNU
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <linux/input.h>

#include "wayland-client-protocol.h"
#include "xdg-shell-client-protocol.h"
#include "xdg-decoration-client-protocol.h"
#include "wayland-relative-pointer-unstable-v1-client-protocol.h"
#include "wayland-pointer-constraints-unstable-v1-client-protocol.h"
#include "wayland-idle-inhibit-unstable-v1-client-protocol.h"

#include "wayland-client-protocol-code.h"
#include "xdg-shell-client-protocol-code.h"
#include "xdg-decoration-client-protocol-code.h"
#include "wayland-relative-pointer-unstable-v1-client-protocol-code.h"
#include "wayland-pointer-constraints-unstable-v1-client-protocol-code.h"
#include "wayland-idle-inhibit-unstable-v1-client-protocol-code.h"

#include "XKinetic/Core/String.h"

static XkBool __xkXDGCreateSurface(XkWindow);
static void __xkXDGDestorySurface(XkWindow);
static XkBool __xkXDGCreateDecorations(XkWindow);
static void __xkXDGDestroyDecorations(XkWindow);

struct wl_buffer* __xkWaylandCreateShmBuffer(const int, const int, const int, const int);
static void __xkWaylandSetContentAreaOpaque(XkWindow);
static void __xkWaylandResizeWindow(XkWindow);

static void __xkWaylandCreateKeyTable(void);

static void __xkXDGWmBasePing(void* data, struct xdg_wm_base* xdgBase, uint32_t serial) {
	xdg_wm_base_pong(xdgBase, serial);
}

static const struct xdg_wm_base_listener _xkXDGWmBaseListener = {
  __xkXDGWmBasePing,
};

static void __xkXDGSurfaceHandleConfigure(void* data, struct xdg_surface* xdgSurface, uint32_t serial) {
	XkWindow window = (XkWindow)data;
	if(!window) {
		goto _catch;
	}

  xdg_surface_ack_configure(xdgSurface, serial);

  int width = window->wayland.width;
  int height = window->wayland.height;

 	struct wl_buffer* wlBuffer = __xkWaylandCreateShmBuffer(width, height, width * 4, (width * 4) * height);
 	if(!wlBuffer) {
 		return;
 	}

	__xkWaylandResizeWindow(window);

	wl_surface_attach(window->wayland.wlSurface, wlBuffer, 0, 0);
	wl_surface_commit(window->wayland.wlSurface);

_catch:
	return;
}

static const struct xdg_surface_listener _xkXDGSurfaceListener = {
  __xkXDGSurfaceHandleConfigure
};

static void __xkXDGToplevelHandleConfigure(void* data, struct xdg_toplevel* xdgToplevel, int32_t width, int32_t height, struct wl_array* wlStates) {
	XkWindow window = (XkWindow)data;
	if(!window) {
		return;
	}

  XkBool maximized = XK_FALSE;
  XkBool fullscreen = XK_FALSE;
  XkBool activated = XK_FALSE;

  // Select window state.
	uint32_t* state;
	wl_array_for_each(state, wlStates) {
		switch(*state) {
			case XDG_TOPLEVEL_STATE_MAXIMIZED: maximized = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_FULLSCREEN: fullscreen = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_RESIZING: break;
      case XDG_TOPLEVEL_STATE_ACTIVATED: activated = XK_TRUE; break;
    }
  }

  // Input window size.
	if(width != 0 && height != 0) {
		window->wayland.width = (XkSize)width;
		window->wayland.height = (XkSize)height;

		__xkInputWindowSize(window, (XkSize)width, (XkSize)height);
	}

	// Input window maximized.
	if(maximized && activated) {
  	__xkInputWindowShow(window, XK_WINDOW_SHOW_MAXIMIZED);
	} 

	// Input window fullscreen.
	if(fullscreen) {
  	__xkInputWindowShow(window, XK_WINDOW_SHOW_FULLSCREEN);
		window->fullscreen = fullscreen;
  }

  // Input window minimized. 
  if(!activated) {
  	__xkInputWindowShow(window, XK_WINDOW_SHOW_MINIMIZED);
  }
}

static void __xkXDGToplevelHandleClose(void* data, struct xdg_toplevel* xdgToplevel) {
	XkWindow window = (XkWindow)data;
	if(!window) {
		return;
	}

	// Input window close.
	__xkInputWindowClose(window);
}

static const struct xdg_toplevel_listener _xkXDGToplevelListener = {
  __xkXDGToplevelHandleConfigure,
  __xkXDGToplevelHandleClose
};

static void __xkWaylandKeyboardHandleKeymap(void* data, struct wl_keyboard* wlKeyboard, uint32_t format, int fd, uint32_t size) {
	// Check keyboard keymap format.
	if(format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
		close(fd);
		return;
	}

	// Allocate keymap string.
	char* string = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	if(string == MAP_FAILED) {
		close(fd);
		return;
	}

	// Create XKB keymap
  _xkPlatform.wayland.xkbKeymap = xkb_keymap_new_from_string(_xkPlatform.wayland.xkbContext, string, XKB_KEYMAP_FORMAT_TEXT_V1, 0);

  // Free keymap string.
	munmap(string, size);

	// Close keymap file.
	close(fd);

	if(!_xkPlatform.wayland.xkbKeymap) {
		__xkErrorHandle("XKB: Failed to compile keymap");
		return;
	}
 
 	// Create XKB state.
	_xkPlatform.wayland.xkbState = xkb_state_new(_xkPlatform.wayland.xkbKeymap);
	if(!_xkPlatform.wayland.xkbState) {
		__xkErrorHandle("XKB: Failed to create state");
		xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);
		return;
	}

	// Look up the preferred locale.
	const char* locale = getenv("LC_ALL");
	if(!locale) {
		locale = getenv("LC_CTYPE");
	}
  if(!locale) {
		locale = getenv("LANG");
	}
	if(!locale) {
		locale = "C";
	}

	struct xkb_compose_table* xkbComposeTable = xkb_compose_table_new_from_locale(_xkPlatform.wayland.xkbContext, locale, XKB_COMPOSE_COMPILE_NO_FLAGS);
	if(!xkbComposeTable) {
		__xkErrorHandle("XKB: Failed to create compose table");
		xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);
		return;
	}

	_xkPlatform.wayland.xkbComposeState = xkb_compose_state_new(xkbComposeTable, XKB_COMPOSE_STATE_NO_FLAGS);
	if(!_xkPlatform.wayland.xkbComposeState) {
		__xkErrorHandle("XKB: Failed to create compose state");
		xkb_compose_table_unref(xkbComposeTable);
		xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);
		return;
	}

	// Destroy XKB compose table.
	xkb_compose_table_unref(xkbComposeTable);

	// Destroy old XKB keymap.
	if(_xkPlatform.wayland.xkbKeymap) {
		//xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);

		//_xkPlatform.wayland.xkbKeymap = NULL;
	}

	// Destroy old XKB state.
	if(_xkPlatform.wayland.xkbState) {
		//xkb_state_unref(_xkPlatform.wayland.xkbState);

		//_xkPlatform.wayland.xkbState = NULL;
	}

	__xkErrorHandler("keymap");

  // Initialize XKB mod indices.
	_xkPlatform.wayland.xkbControlIndex  = xkb_keymap_mod_get_index(_xkPlatform.wayland.xkbKeymap, "Control");
	_xkPlatform.wayland.xkbAltIndex      = xkb_keymap_mod_get_index(_xkPlatform.wayland.xkbKeymap, "Mod1");
	_xkPlatform.wayland.xkbShiftIndex    = xkb_keymap_mod_get_index(_xkPlatform.wayland.xkbKeymap, "Shift");
	_xkPlatform.wayland.xkbSuperIndex    = xkb_keymap_mod_get_index(_xkPlatform.wayland.xkbKeymap, "Mod4");
	_xkPlatform.wayland.xkbCapsLockIndex = xkb_keymap_mod_get_index(_xkPlatform.wayland.xkbKeymap, "Lock");
	_xkPlatform.wayland.xkbNumLockIndex  = xkb_keymap_mod_get_index(_xkPlatform.wayland.xkbKeymap, "Mod2");
}

static void __xkWaylandKeyboardHandleEnter(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, struct wl_surface* wlSurface, struct wl_array* wlKeys) {
	// Happens in the case we destroyed the surface.
	if(!wlSurface) {
		return;
	}

	XkWindow window = wl_surface_get_user_data(wlSurface);
	if(!window) {
		return;
  }

	_xkPlatform.wayland.keyboardWindowFocus = window;


	// Input window focus.
	__xkInputWindowFocus(window, XK_TRUE);
}

static void __xkWaylandKeyboardHandleLeave(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, struct wl_surface* wlSurface) {
	XkWindow window = _xkPlatform.wayland.keyboardWindowFocus;
	if(!window) {
		return;
	}

	_xkPlatform.wayland.keyboardWindowFocus = NULL;

	// Input window focus.
	__xkInputWindowFocus(window, XK_FALSE);
}

static void __xkWaylandKeyboardHandleKey(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, uint32_t time, uint32_t scancode, uint32_t state) {
	XkWindow window = _xkPlatform.wayland.keyboardWindowFocus;
	if(!window) {
		return;
	}

	const int key = _xkPlatform.keycodes[scancode];
	const int action = state == WL_KEYBOARD_KEY_STATE_PRESSED ? XK_PRESS : XK_RELEASE;

	__xkInputWindowKey(window, key, action, _xkPlatform.wayland.modifiers);
}

static void __xkWaylandKeyboardHandleModifiers(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, uint32_t modsDepressed, uint32_t modsLatched, uint32_t modsLocked, uint32_t group) {
	if(!_xkPlatform.wayland.xkbKeymap) {
		return;
	}

	// Update XKB state mask.
	xkb_state_update_mask(_xkPlatform.wayland.xkbState, modsDepressed, modsLatched, modsLocked, 0, 0, group);

	_xkPlatform.wayland.modifiers = 0;

	struct {
		xkb_mod_index_t xkbIndex;
		unsigned int bit;
	} modifiers[] = {
		{_xkPlatform.wayland.xkbControlIndex,  XK_MOD_CONTROL_BIT},
		{_xkPlatform.wayland.xkbAltIndex,      XK_MOD_ALT_BIT},
		{_xkPlatform.wayland.xkbShiftIndex,    XK_MOD_SHIFT_BIT},
		{_xkPlatform.wayland.xkbSuperIndex,    XK_MOD_SUPER_BIT},
		{_xkPlatform.wayland.xkbCapsLockIndex, XK_MOD_CAPS_LOCK_BIT},
		{_xkPlatform.wayland.xkbNumLockIndex,  XK_MOD_NUM_LOCK_BIT}
	};

	for(size_t i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++) {
		if(xkb_state_mod_index_is_active(_xkPlatform.wayland.xkbState, modifiers[i].xkbIndex, XKB_STATE_MODS_EFFECTIVE) == 1) {
			_xkPlatform.wayland.modifiers |= modifiers[i].bit;
		}
	}
}

#ifdef WL_KEYBOARD_REPEAT_INFO_SINCE_VERSION

static void __xkWaylandKeyboardHandleRepeatInfo(void* data, struct wl_keyboard* wlKeyboard, int32_t rate, int32_t delay) {
	if(wlKeyboard != _xkPlatform.wayland.wlKeyboard) {
		return;
	}

	/// NOTE: Nothing to do here.
}

#endif

static const struct wl_keyboard_listener _xkWaylandKeyboardListener = {
  __xkWaylandKeyboardHandleKeymap,
  __xkWaylandKeyboardHandleEnter,
  __xkWaylandKeyboardHandleLeave,
  __xkWaylandKeyboardHandleKey,
  __xkWaylandKeyboardHandleModifiers,
#ifdef WL_KEYBOARD_REPEAT_INFO_SINCE_VERSION
  __xkWaylandKeyboardHandleRepeatInfo,
#endif
};

static void __xkWaylandSeatHandleCapabilities(void* data, struct wl_seat* wlSeat, enum wl_seat_capability wlCapability) {
	if((wlCapability & WL_SEAT_CAPABILITY_POINTER) && !_xkPlatform.wayland.wlPointer) {
		_xkPlatform.wayland.wlPointer = wl_seat_get_pointer(wlSeat);
		//wl_pointer_add_listener(_xkPlatform.wayland.wlPointer, &_xkWaylandPointerListener, NULL);
	} else if(!(wlCapability & WL_SEAT_CAPABILITY_POINTER) && _xkPlatform.wayland.wlPointer) {
		wl_pointer_destroy(_xkPlatform.wayland.wlPointer);

		_xkPlatform.wayland.wlPointer = NULL;
	}

	if((wlCapability & WL_SEAT_CAPABILITY_KEYBOARD) && !_xkPlatform.wayland.wlKeyboard) {
		_xkPlatform.wayland.wlKeyboard = wl_seat_get_keyboard(wlSeat);
		wl_keyboard_add_listener(_xkPlatform.wayland.wlKeyboard, &_xkWaylandKeyboardListener, NULL);
	} else if(!(wlCapability & WL_SEAT_CAPABILITY_KEYBOARD) && _xkPlatform.wayland.wlKeyboard) {
		wl_keyboard_destroy(_xkPlatform.wayland.wlKeyboard);

		_xkPlatform.wayland.wlKeyboard = NULL;
	}
}

static void __xkWaylandSeatHandleName(void* data, struct wl_seat* wlSeat, const char* name) {
	/// NOTE: Nothing to do here.
}

static const struct wl_seat_listener _xkWaylandSeatListener = {
	__xkWaylandSeatHandleCapabilities,
	__xkWaylandSeatHandleName
};

static void __xkWaylandRegistryGlobal(void* data, struct wl_registry* wlRegistry, uint32_t name, const char* interface, uint32_t version) {
  if(xkCompareString((XkString)interface, (XkString)wl_compositor_interface.name) == 1) {
		// Wayland compositor.
		_xkPlatform.wayland.wlCompositor = wl_registry_bind(wlRegistry, name, &wl_compositor_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)wl_shm_interface.name) == 1) {
		// Wayland shared memory.
		_xkPlatform.wayland.wlShm = wl_registry_bind(wlRegistry, name, &wl_shm_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)wl_output_interface.name) == 1) {
		// Wayland output.
		_xkPlatform.wayland.wlOutput = wl_registry_bind(wlRegistry, name, &wl_output_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)wl_seat_interface.name) == 1) {
		// Wayland seat.
		_xkPlatform.wayland.wlSeat = wl_registry_bind(wlRegistry, name, &wl_seat_interface, version);
		 wl_seat_add_listener(_xkPlatform.wayland.wlSeat, &_xkWaylandSeatListener, NULL);
  } else if(xkCompareString((XkString)interface, (XkString)xdg_wm_base_interface.name) == 1) {
		// XDG Base.
    _xkPlatform.wayland.xdgBase = wl_registry_bind(wlRegistry, name, &xdg_wm_base_interface, version);
		xdg_wm_base_add_listener(_xkPlatform.wayland.xdgBase, &_xkXDGWmBaseListener, NULL);
  } else if(xkCompareString((XkString)interface, (XkString)zxdg_decoration_manager_v1_interface.name) == 1) {
		// XDG decoration manager.
    _xkPlatform.wayland.xdgDecorationManager = wl_registry_bind(wlRegistry, name, &zxdg_decoration_manager_v1_interface, version);
	}
}

static void __xkWaylandRegistryGlobalRemove(void* data, struct wl_registry* wlRegistry, uint32_t name) {
	/// NOTE: Nothing to do here.
}

static const struct wl_registry_listener _xkWaylandRegistryListener = {
	__xkWaylandRegistryGlobal,
  __xkWaylandRegistryGlobalRemove,
};

static void __xkWaylandBufferHandleRelease(void* data, struct wl_buffer* wlBuffer) {
  wl_buffer_destroy(wlBuffer);
}

static const struct wl_buffer_listener _xkWaylandBufferListener = {
  __xkWaylandBufferHandleRelease,
};

XkResult xkInitializeWindow(void) {
	XkResult result = XK_SUCCESS;

	// Connect Wayland server.
	_xkPlatform.wayland.wlDisplay = wl_display_connect(NULL);
	if(!_xkPlatform.wayland.wlDisplay) {
		__xkErrorHandle("Wayland: Failed to connect display");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Get Wayland display registry.
	_xkPlatform.wayland.wlRegistry = wl_display_get_registry(_xkPlatform.wayland.wlDisplay);
	if(!_xkPlatform.wayland.wlRegistry) {
		__xkErrorHandle("Wayland: Failed to get display registry");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Add Wayland display registry listener.
  wl_registry_add_listener(_xkPlatform.wayland.wlRegistry, &_xkWaylandRegistryListener, NULL);

  // Create key table.
  __xkWaylandCreateKeyTable();

  // Create XKB context.
	_xkPlatform.wayland.xkbContext = xkb_context_new(0);
	if(!_xkPlatform.wayland.xkbContext) {
		__xkErrorHandle("XKB: Failed to initialize context");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Sync so we got all registry objects.
  wl_display_roundtrip(_xkPlatform.wayland.wlDisplay);

	// Sync so we got all initial output events.
  wl_display_roundtrip(_xkPlatform.wayland.wlDisplay);

	// Check Wayland compositor register object.
	if(!_xkPlatform.wayland.wlCompositor) {
		__xkErrorHandle("Wayland: Failed to register compositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check Wayland shared memory register object.
	if(!_xkPlatform.wayland.wlShm) {
		__xkErrorHandle("Wayland: Failed to register shm");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check Wayland output register object.
	if(!_xkPlatform.wayland.wlOutput) {
		__xkErrorHandle("Wayland: Failed to register output");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check XDG base register object.
	if(!_xkPlatform.wayland.xdgBase) {
		__xkErrorHandle("Wayland: Failed to register XDG base");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check XDG decoration manager register object.
  if(!_xkPlatform.wayland.xdgDecorationManager) {
		__xkErrorHandle("Wayland: Failed to register XDG decoration manager");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

_catch:
	return(result);
}

void xkTerminateWindow(void) {
	// Destroy XKB compose state.
	if(_xkPlatform.wayland.xkbComposeState) {
		xkb_compose_state_unref(_xkPlatform.wayland.xkbComposeState);

		_xkPlatform.wayland.xkbComposeState = NULL;
	}

	// Destroy XKB keymap.
	if(_xkPlatform.wayland.xkbKeymap) {
		xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);

		_xkPlatform.wayland.xkbKeymap = NULL;
	}

	// Destroy XKB state.
	if(_xkPlatform.wayland.xkbState) {
		xkb_state_unref(_xkPlatform.wayland.xkbState);

		_xkPlatform.wayland.xkbState = NULL;
	}

	// Destroy XKB context.
  if(_xkPlatform.wayland.xkbContext) {
		xkb_context_unref(_xkPlatform.wayland.xkbContext);

		_xkPlatform.wayland.xkbContext = NULL;
  }

	// Destroy Wayland pointer.
  if(_xkPlatform.wayland.wlPointer) {
		wl_pointer_destroy(_xkPlatform.wayland.wlPointer);

		_xkPlatform.wayland.wlPointer = NULL;
  }

  // Destroy Wayland keyboard.
  if(_xkPlatform.wayland.wlKeyboard) {
		wl_keyboard_destroy(_xkPlatform.wayland.wlKeyboard);

		_xkPlatform.wayland.wlKeyboard = NULL;
  }

	// Destroy Wayland seat.
	if(_xkPlatform.wayland.wlSeat) {
		wl_seat_destroy(_xkPlatform.wayland.wlSeat);

		_xkPlatform.wayland.wlSeat = NULL;
	}

	// Destroy Wayland output.
	if(_xkPlatform.wayland.wlOutput) {
		wl_output_destroy(_xkPlatform.wayland.wlOutput);

		_xkPlatform.wayland.wlOutput = NULL;
	}

	// Destroy Wayland shared memory.
	if(_xkPlatform.wayland.wlShm) {
		wl_shm_destroy(_xkPlatform.wayland.wlShm);

		_xkPlatform.wayland.wlShm = NULL;
	}

	// Destroy Wayland compositor.
  if(_xkPlatform.wayland.wlCompositor){
		wl_compositor_destroy(_xkPlatform.wayland.wlCompositor);

		_xkPlatform.wayland.wlCompositor = NULL;
  }
	
	// Destroy XDG base.
 	if(_xkPlatform.wayland.xdgBase) {
		xdg_wm_base_destroy(_xkPlatform.wayland.xdgBase);

		_xkPlatform.wayland.xdgBase = NULL;
	}

	// Destroy XDG decoration manager.
 	if(_xkPlatform.wayland.xdgDecorationManager){
		zxdg_decoration_manager_v1_destroy(_xkPlatform.wayland.xdgDecorationManager);

		_xkPlatform.wayland.xdgDecorationManager = NULL;
 	}

	// Destroy Wayland register.
	if(_xkPlatform.wayland.wlRegistry) {
  	wl_registry_destroy(_xkPlatform.wayland.wlRegistry);

 		_xkPlatform.wayland.wlRegistry = NULL;
	}

	// Destroy Wayland display.
	if(_xkPlatform.wayland.wlDisplay) {
  	wl_display_flush(_xkPlatform.wayland.wlDisplay);
		wl_display_disconnect(_xkPlatform.wayland.wlDisplay);

 		_xkPlatform.wayland.wlDisplay = NULL;
	}
}

struct wl_display* __xkWaylandGetDisplay(void) {
	return(_xkPlatform.wayland.wlDisplay);
}

struct wl_surface* __xkWaylandGetSurface(const XkWindow window) {
	return(window->wayland.wlSurface);
}

XkResult xkCreateWindow(XkWindow* pWindow, const XkString title, const XkSize width, const XkSize height, const XkWindowHint hint) {
	XkResult result = XK_SUCCESS;
	
	// Allocate window.
	*pWindow = xkAllocateMemory(sizeof(struct XkWindow));
	if(!(*pWindow)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}
	
	// Template window.
	XkWindow window = *pWindow;

  // Check window hints support.
  if(
    (hint & XK_WINDOW_DECORATED_BIT && hint & XK_WINDOW_FLOATING_BIT) || 
    (hint & XK_WINDOW_RESIZABLE_BIT && hint & XK_WINDOW_FLOATING_BIT)) {
    __xkErrorHandle("Win32: Unsupported window hints");
  }

  // Initialize window hints.
	if(hint & XK_WINDOW_DECORATED_BIT) 	window->decorated = XK_TRUE;
	if(hint & XK_WINDOW_RESIZABLE_BIT) 	window->resizable = XK_TRUE;
	if(hint & XK_WINDOW_FLOATING_BIT) 	window->floating = XK_TRUE;

  // Initialize window.
  window->cursorMode 	= XK_CURSOR_NORMAL;
	if(title) {
		/// NOTE: needs to be free.
  	window->title 		= xkDuplicateString(title);
	}

	// Initialize Wayland window.
	window->wayland.width = width;
	window->wayland.height = height;

	// Create Wayland window surface.
	window->wayland.wlSurface = wl_compositor_create_surface(_xkPlatform.wayland.wlCompositor);
  if(!window->wayland.wlSurface) {
		__xkErrorHandle("Wayland: Failed to create surface");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Needs in keyboard listener.
 	wl_surface_set_user_data(window->wayland.wlSurface, window);

	if(__xkXDGCreateSurface(window)) {
		result = XK_ERROR_UNKNOWN;
		goto _catch;		
	}

	if(window->decorated) {
		if(__xkXDGCreateDecorations(window)) {
			result = XK_ERROR_UNKNOWN;
			goto _catch;		
		}
	}

	// Set XDG window title.
	if(title) {
  	xdg_toplevel_set_title(window->wayland.xdgToplevel, window->title);
	}

	// Set window not resizable.
	if(!window->resizable) {
		xkSetWindowSizeLimits(window, width, height, width, height);
	}

	/// NOTE: I don't want commit Wayland surface here, because i commit it in show function.

_catch:
	return(result);
}

void xkDestroyWindow(XkWindow window) {
	// Destroy XDG components.
	__xkXDGDestorySurface(window);

	// Destroy Wayland surface.
	if(window->wayland.wlSurface) {
		wl_surface_destroy(window->wayland.wlSurface);
	}

  // Free window title.
  if(window->title) {
		xkFreeMemory(window->title);
	}
	
  // Free window.
	xkFreeMemory(window);
}

void xkShowWindow(XkWindow window, const XkWindowShow show) {
	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			if(!window->wayland.xdgDecoration) {
				__xkXDGCreateDecorations(window);
			}

			xdg_toplevel_unset_maximized(window->wayland.xdgToplevel);
			xdg_toplevel_unset_fullscreen(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_MAXIMIZED:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			if(!window->wayland.xdgDecoration) {
				__xkXDGCreateDecorations(window);
			}

			// Minimize Wayland window.
			xdg_toplevel_set_maximized(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_MINIMIZED:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			if(!window->wayland.xdgDecoration) {
				__xkXDGCreateDecorations(window);
			}

			// Maximize Wayland window.
			xdg_toplevel_set_minimized(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_FULLSCREEN:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			if(window->wayland.xdgDecoration) {
				__xkXDGDestroyDecorations(window);
			}

			// Fullscreen Wayland window.
			xdg_toplevel_set_fullscreen(window->wayland.xdgToplevel, _xkPlatform.wayland.wlOutput);
			break;

		case XK_WINDOW_HIDE:
			// Destroy XDG components.
			if(window->wayland.xdgToplevel) {
				__xkXDGDestorySurface(window);
			}

			if(window->wayland.xdgDecoration) {
				__xkXDGDestroyDecorations(window);
			}

			// Set null Wayland surface contents.
      wl_surface_attach(window->wayland.wlSurface, NULL, 0, 0);
			break;
	}

	// Commit Wayland surface.
  wl_surface_commit(window->wayland.wlSurface);
}

void xkFocusWindow(XkWindow window) {
	// A Wayland client can not focus.
	__xkErrorHandle("Wayland: platform doesn't support setting the input focus");
}

void xkSetWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	window->wayland.width = width;
	window->wayland.width = height;

	__xkWaylandResizeWindow(window);
}

void xkGetWindowSize(XkWindow window, XkSize* const pWidth, XkSize* const pHeight) {
	if(pWidth) {
		*pWidth = window->wayland.width;
	}

  if(pHeight) {
    *pHeight = window->wayland.height;
	}
}

void xkSetWindowSizeLimits(XkWindow window, const XkSize minWidth, const XkSize minHeight, const XkSize maxWidth, const XkSize maxHeight) {
	if(minWidth != 0 && minHeight != 0) {
		// Set XDG toplevel min size.
  	xdg_toplevel_set_min_size(window->wayland.xdgToplevel, (int32_t)minWidth, (int32_t)minHeight);
	}

	if(maxWidth != 0 && maxHeight) {
		// Set XDG toplevel max size.
		xdg_toplevel_set_max_size(window->wayland.xdgToplevel, (int32_t)maxWidth, (int32_t)maxHeight);
	}

	// Commit Wayland surface.
	wl_surface_commit(window->wayland.wlSurface);
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
	// Free old window title.
  if(window->title) {
		xkFreeMemory(window->title);
	}
	// Duplication new window title.
  window->title = xkDuplicateString(title);

	// Set XDG toplevel title.
	xdg_toplevel_set_title(window->wayland.xdgToplevel, title);
}

void xkSetWindowIcon(XkWindow window, const XkSize count, const XkWindowIcon* pIcon) {
	// A Wayland client can not set its icon
	__xkErrorHandle("Wayland: platform doesn't support setting the window icon");
}

void xkSetCursorPosition(XkWindow window, const XkFloat64 xPos, const XkFloat64 yPos) {
	/// TODO: Implementation.
}

void xkGetCursorPosition(XkWindow window, XkFloat64* const pXPos, XkFloat64* const pYPos) {
	/// TODO: Implementation.
}

void xkSetWindowCursorMode(XkWindow window, const XkWindowCursorMode mode) {
	/// TODO: Implementation.
}

void xkSetWindowCursor(XkWindow window, const XkWindowIcon* pIcon) {
	/// TODO: Implementation.
}

void xkPollWindowEvents(void) {
	/// TODO: Implementation.
	wl_display_dispatch(_xkPlatform.wayland.wlDisplay);
}

void xkWaitWindowEvents(void) {
	wl_display_dispatch(_xkPlatform.wayland.wlDisplay);
}

static XkBool __xkXDGCreateSurface(XkWindow window) {
	XkBool result = XK_FALSE;

// Get XDG surface from Wayland surface.
	window->wayland.xdgSurface = xdg_wm_base_get_xdg_surface(_xkPlatform.wayland.xdgBase, window->wayland.wlSurface);
	if(!window->wayland.xdgSurface) {
		result = XK_TRUE;
		__xkErrorHandle("XDG: Failed to create surface");
		goto _catch;
  }

	// Add XDG surface listener.
  xdg_surface_add_listener(window->wayland.xdgSurface, &_xkXDGSurfaceListener, window);

	// Get XDG toplevel.
	window->wayland.xdgToplevel = xdg_surface_get_toplevel(window->wayland.xdgSurface);
  if(!window->wayland.xdgToplevel) {
		result = XK_TRUE;
		__xkErrorHandle("XDG: Failed to create toplevel");
		goto _catch;
  }

	// Add XDG toplevel listener.
  xdg_toplevel_add_listener(window->wayland.xdgToplevel, &_xkXDGToplevelListener, window);

  // Set XDG window decorations.
	if(window->decorated) {

	}

_catch:
	return(result);
}

static void __xkXDGDestorySurface(XkWindow window) {
	// Destroy XDG toplevel.
	if(window->wayland.xdgToplevel) {
		xdg_toplevel_destroy(window->wayland.xdgToplevel);

		window->wayland.xdgToplevel = NULL;
	}

	// Destroy XDG surface.
	if(window->wayland.xdgSurface) {
		xdg_surface_destroy(window->wayland.xdgSurface);

		window->wayland.xdgSurface = NULL;
	}
}

static XkBool __xkXDGCreateDecorations(XkWindow window) {
	XkBool result = XK_FALSE;

	window->wayland.xdgDecoration = zxdg_decoration_manager_v1_get_toplevel_decoration(_xkPlatform.wayland.xdgDecorationManager, window->wayland.xdgToplevel);
	if(!window->wayland.xdgDecoration) {
		result = XK_TRUE;
		__xkErrorHandle("XDG: Failed to create decorations");
		goto _catch;
	}

  zxdg_toplevel_decoration_v1_set_mode(window->wayland.xdgDecoration, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);

_catch:
	return(result);
}

static void __xkXDGDestroyDecorations(XkWindow window) {
	// Destroy XDG decoration.
	if(window->wayland.xdgDecoration) {
		zxdg_toplevel_decoration_v1_destroy(window->wayland.xdgDecoration);

		window->wayland.xdgDecoration = NULL;
	}
}

static int __xkWaylandAllocateShmFile(const int size) {
	int fd = memfd_create("XKinetic-Wayland", MFD_CLOEXEC | MFD_ALLOW_SEALING);
	if(fd >= 0) {
		fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
	} else {
		goto _catch;
	}

	int ret = posix_fallocate(fd, 0, size);
	if(ret != 0) {
		close(fd);
		fd = -1;
		goto _catch;
	}

_catch:
	return(fd);
}

struct wl_buffer* __xkWaylandCreateShmBuffer(const int width, const int height, const int stride, const int size) {
	struct wl_buffer* wlBuffer = NULL;

	// Allocate Waylnad shared file.
	int fd = __xkWaylandAllocateShmFile(size);
	if(fd == -1) {
		goto _catch;
	}

	// Allocate Wayland shared memory.
	uint32_t* data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(data == MAP_FAILED) {
		close(fd);
		goto _catch;
	}

	// Create Wayland poll from shared file.
	struct wl_shm_pool* wlPool = wl_shm_create_pool(_xkPlatform.wayland.wlShm, fd, size);

	// Create Wayland buffer.
	wlBuffer = wl_shm_pool_create_buffer(wlPool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);

	// Destroy Wayland pool.
	wl_shm_pool_destroy(wlPool);

	// Close Wayland shared file.
	close(fd);

	// Free Wayland shared memory.
	munmap(data, size);

	// Add Wayland buffer listener.
	wl_buffer_add_listener(wlBuffer, &_xkWaylandBufferListener, NULL);

_catch:
	return(wlBuffer);
}

static void __xkWaylandSetContentAreaOpaque(XkWindow window) {
	// Create Wayland region.
	struct wl_region* wlRegion = wl_compositor_create_region(_xkPlatform.wayland.wlCompositor);
	if(!wlRegion) {
		__xkErrorHandle("Wayland: Failed to create region");
		return;
	}

	// Add the specified rectangle to the Wayland region.
	wl_region_add(wlRegion, 0, 0, (int)window->wayland.width, (int)window->wayland.height);

	// Set Wayland surface opaque region.
	wl_surface_set_opaque_region(window->wayland.wlSurface, wlRegion);
	
	// Destroy Wayland region.
	wl_region_destroy(wlRegion);
}

static void __xkWaylandResizeWindow(XkWindow window) {
	__xkWaylandSetContentAreaOpaque(window);
}

static void __xkWaylandCreateKeyTable(void) {
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

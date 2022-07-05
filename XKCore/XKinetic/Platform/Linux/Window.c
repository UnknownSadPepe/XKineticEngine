/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Memory.h"
#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/String.h"

#define _GNU_SOURCE
#define __USE_GNU
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>
#include <linux/input.h>
#include <errno.h>
#include <poll.h>

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

/* ########## MACROS SECTION ########## */
#ifndef CLOCK_REALTIME
	#define CLOCK_REALTIME 0
#endif // CLOCK_REALTIME

#ifndef O_CLOEXEC
	#define O_CLOEXEC 02000000
#endif

/* ########## FUNCTION DECLARATIONS SECTION ########## */
static XkBool 			__xkXDGCreateSurface(XkWindow);
static void 				__xkXDGDestorySurface(XkWindow);

static XkBool 			__xkXDGCreateDecorations(XkWindow);
static void 				__xkXDGDestroyDecorations(XkWindow);

static XkBool 			__xkZWPCreateIdleInhibitor(XkWindow);
static void 				__xkZWPDestroyIdleInhibitor(XkWindow);

static int 					__xkWaylandAllocateShmFile(const XkSize);
struct wl_buffer* 	__xkWaylandCreateShmBuffer(const XkSize, const XkSize, const XkSize, const XkSize, const XkHandle);

static void 				__xkWaylandResizeWindow(XkWindow);

static XkBool 			__xkWaylandFlushDisplay(void);

static void 				__xkZWPLockPointer(XkWindow);
static void 				__xkZWPUnlockPointer(XkWindow);

static char* 				__xkWaylandReadDataOfferAsString(struct wl_data_offer*, const char*);

XkString* 					__xkParseURI(XkString, XkSize*);

void 								__xkWaylandSetWindowCursor(XkWindow);

static void 				__xkWaylandCreateKeyTable(void);

/* ########## FUNCTION SECTION ########## */
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

	__xkWaylandResizeWindow(window);

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

  XkBool maximized 	= XK_FALSE;
  XkBool fullscreen = XK_FALSE;
  XkBool activated 	= XK_FALSE;

	uint32_t* state;
	wl_array_for_each(state, wlStates) {
		switch(*state) {
			case XDG_TOPLEVEL_STATE_MAXIMIZED: maximized = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_FULLSCREEN: fullscreen = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_RESIZING: break;
      case XDG_TOPLEVEL_STATE_ACTIVATED: activated = XK_TRUE; break;
    }
  }

	if((width != 0 && height != 0) && ((XkSize)width != window->wayland.width || (XkSize)height != window->wayland.height)) {
		window->wayland.width = (XkSize)width;
		window->wayland.height = (XkSize)height;

		__xkInputWindowSize(window, (XkSize)width, (XkSize)height);
	}

	if(maximized && activated) {
  	__xkInputWindowShow(window, XK_WINDOW_SHOW_MAXIMIZED);
	} 

	if(fullscreen) {
  	__xkInputWindowShow(window, XK_WINDOW_SHOW_FULLSCREEN);
		window->fullscreen = fullscreen;
  }

  if(!activated) {
  	__xkInputWindowShow(window, XK_WINDOW_SHOW_MINIMIZED);
  }
}

static void __xkXDGToplevelHandleClose(void* data, struct xdg_toplevel* xdgToplevel) {
	XkWindow window = (XkWindow)data;
	if(!window) {
		return;
	}

	__xkInputWindowClose(window);
}

static void __xkXDGToplevelHandleConfigureBounds(void* data, struct xdg_toplevel* xdgToplevel, int32_t width, int32_t height) {
	/// NOTE: Nothing to do here.
}

static const struct xdg_toplevel_listener _xkXDGToplevelListener = {
  __xkXDGToplevelHandleConfigure,
  __xkXDGToplevelHandleClose,
	__xkXDGToplevelHandleConfigureBounds
};

static void __xkWaylandPointerHandleEnter(void* data, struct wl_pointer* wlPointer, uint32_t serial, struct wl_surface* wlSurface, wl_fixed_t sx, wl_fixed_t sy) {
	// Happens in the case we destroyed the surface.
	if(!wlSurface) {
		return;
	}

	XkWindow window = wl_surface_get_user_data(wlSurface);
	if(!window) {
		return;
	}

	_xkPlatform.wayland.pointerSerial = serial;
	_xkPlatform.wayland.pointerWindowFocus = window;

	__xkWaylandSetWindowCursor(window);

	__xkInputWindowCursorEnter(window, XK_TRUE);
}

static void __xkWaylandPointerHandleLeave(void* data, struct wl_pointer* wlPointer, uint32_t serial, struct wl_surface* wlSurface) {
	XkWindow window = _xkPlatform.wayland.pointerWindowFocus;
	if(!window) {
		return;
	}

	_xkPlatform.wayland.pointerSerial = serial;
	_xkPlatform.wayland.pointerWindowFocus = NULL;

	__xkWaylandSetWindowCursor(window);

	__xkInputWindowCursorEnter(window, XK_FALSE);
}

static void __xkWaylandPointerHandleMotion(void* data,	struct wl_pointer* wlPointer, uint32_t time, wl_fixed_t sx, wl_fixed_t sy) {
	XkWindow window = _xkPlatform.wayland.pointerWindowFocus;
	if(!window) {
		return;
	}

	if(window->cursorMode == XK_CURSOR_DISABLED) {
		return;
	}

	double x = wl_fixed_to_double(sx);
	double y = wl_fixed_to_double(sy);

	window->wayland.cursorPosX = (XkFloat64)x;
	window->wayland.cursorPosY = (XkFloat64)y;

	__xkInputWindowCursor(window, (XkFloat64)x, (XkFloat64)y);
}

static void __xkWaylandPointerHandleButton(void* data, struct wl_pointer* wlPointer, uint32_t serial, uint32_t time, uint32_t btn, uint32_t state) {
	XkWindow window = _xkPlatform.wayland.pointerWindowFocus;
	if(!window) {
		return;
	}

	const XkButton button = btn - BTN_LEFT;
	const XkAction action = state == WL_POINTER_BUTTON_STATE_PRESSED ? XK_PRESS : XK_RELEASE;

	__xkInputWindowButton(window, button, action, _xkPlatform.wayland.modifiers);
}

static void __xkWaylandPointerHandleAxis(void* data, struct wl_pointer* wlPointer, uint32_t time, uint32_t axis, wl_fixed_t value) {
	XkWindow window = _xkPlatform.wayland.pointerWindowFocus;
	if(!window) {
		return;
	}

	double x = 0.0;
	double y = 0.0;

  // The factor 10 is commonly used to convert to "scroll" step means 1.0.
	const double scrollFactor = 1.0 / 10.0;

	if (axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL) {
		x = -wl_fixed_to_double(value) * scrollFactor;
	} else if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL) {
		y = -wl_fixed_to_double(value) * scrollFactor;
	}

	__xkInputWindowScroll(window, (XkFloat64)x, (XkFloat64)y);
}

static void __xkWaylandPointerHandleFrame(void* data, struct wl_pointer* wlPointer) {
	/// NOTE: Nothing to do here.
}

static void __xkWaylandPointerHandleAxisSource(void* data, struct wl_pointer* wl_pointer, uint32_t axis_source) {
	/// NOTE: Nothing to do here.
}

static void __xkWaylandPointerHandleAxisStop(void* data, struct wl_pointer* wl_pointer, uint32_t time, uint32_t axis) {
	/// NOTE: Nothing to do here.
}

static void __xkWaylandPointerHandleAxisDiscrete(void* data, struct wl_pointer* wl_pointer, uint32_t axis, int32_t discrete) {
	/// NOTE: Nothing to do here.
}

static void __xkWaylandPointerHandleAxisValue(void *data, struct wl_pointer* wlPointer, uint32_t axis, int32_t value120) {
	/// NOTE: Nothing to do here.
}

static const struct wl_pointer_listener _xkWaylandPointerListener = {
	__xkWaylandPointerHandleEnter,
	__xkWaylandPointerHandleLeave,
	__xkWaylandPointerHandleMotion,
	__xkWaylandPointerHandleButton,
	__xkWaylandPointerHandleAxis,
	__xkWaylandPointerHandleFrame,
	__xkWaylandPointerHandleAxisSource,
	__xkWaylandPointerHandleAxisStop,
	__xkWaylandPointerHandleAxisDiscrete,
	__xkWaylandPointerHandleAxisValue
};

static void __xkZWPRelativePointerHandleRelativeMotion(void* data, struct zwp_relative_pointer_v1* zwpRelativePointer, uint32_t timeHi, uint32_t timeLo, wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t dxUnaccel, wl_fixed_t dyUnaccel) {
  XkWindow window = data;
	if(!window) {
		return;
	}

  if(window->cursorMode != XK_CURSOR_DISABLED) {
		return;
	}

  double xPos = window->wayland.cursorPosX;
  double yPos = window->wayland.cursorPosY;

  xPos += wl_fixed_to_double(dx);
  yPos += wl_fixed_to_double(dy);

  __xkInputWindowCursor(window, (XkFloat64)xPos, (XkFloat64)yPos);
}

static const struct zwp_relative_pointer_v1_listener _xkZWPRelativePointerListener = {
	__xkZWPRelativePointerHandleRelativeMotion
};

static void __xkZWPLockedPointerHandleLocked(void* data, struct zwp_locked_pointer_v1* zwpLockedPointer) {
	/// NOTE: Nothing to do here.
}

static void __xkZWPLockedPointerHandleUnlocked(void* data, struct zwp_locked_pointer_v1* zwpLockedPointer) {
	/// NOTE: Nothing to do here.
}

static const struct zwp_locked_pointer_v1_listener _xkZWPLockedPointerListener = {
  __xkZWPLockedPointerHandleLocked,
  __xkZWPLockedPointerHandleUnlocked
};

static void __xkWaylandKeyboardHandleKeymap(void* data, struct wl_keyboard* wlKeyboard, uint32_t format, int fd, uint32_t size) {
	if(format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
		close(fd);
		return;
	}

	char* string = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
	if(string == MAP_FAILED) {
		close(fd);
		return;
	}

  _xkPlatform.wayland.xkbKeymap = xkb_keymap_new_from_string(_xkPlatform.wayland.xkbContext, string, XKB_KEYMAP_FORMAT_TEXT_V1, 0);

	munmap(string, size);

	close(fd);

	if(!_xkPlatform.wayland.xkbKeymap) {
		__xkErrorHandle("XKB: Failed to compile keymap");
		return;
	}
 
	_xkPlatform.wayland.xkbState = xkb_state_new(_xkPlatform.wayland.xkbKeymap);
	if(!_xkPlatform.wayland.xkbState) {
		__xkErrorHandle("XKB: Failed to create state");
		xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);
		return;
	}

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

	xkb_compose_table_unref(xkbComposeTable);

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

	__xkInputWindowFocus(window, XK_TRUE);
}

static void __xkWaylandKeyboardHandleLeave(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, struct wl_surface* wlSurface) {
	XkWindow window = _xkPlatform.wayland.keyboardWindowFocus;
	if(!window) {
		return;
	}

	_xkPlatform.wayland.keyboardWindowFocus = NULL;

	__xkInputWindowFocus(window, XK_FALSE);
}

static void __xkWaylandKeyboardHandleKey(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, uint32_t time, uint32_t scancode, uint32_t state) {
	XkWindow window = _xkPlatform.wayland.keyboardWindowFocus;
	if(!window) {
		return;
	}

	const XkKey key = _xkPlatform.keycodes[scancode];
	const XkAction action = state == WL_KEYBOARD_KEY_STATE_PRESSED ? XK_PRESS : XK_RELEASE;

	__xkInputWindowKey(window, key, action, _xkPlatform.wayland.modifiers);
}

static void __xkWaylandKeyboardHandleModifiers(void* data, struct wl_keyboard* wlKeyboard, uint32_t serial, uint32_t modsDepressed, uint32_t modsLatched, uint32_t modsLocked, uint32_t group) {
	if(!_xkPlatform.wayland.xkbKeymap) {
		return;
	}

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

static void __xkWaylandDataOfferHandleOffer(void* data, struct wl_data_offer* wlDataOffer, const char* mimeType) {
	for(XkSize i = 0; i < _xkPlatform.wayland.offerCount; i++) {
		if(_xkPlatform.wayland.offers[i].wlOffer == wlDataOffer) {
			if(xkCompareString((XkString)mimeType, (XkString)"text/plain;charset=utf-8") == 1) {
				_xkPlatform.wayland.offers[i].UTF8 = XK_TRUE;
			} else if (xkCompareString((XkString)mimeType, (XkString)"text/uri-list") == 1) {
				_xkPlatform.wayland.offers[i].URI = XK_TRUE;
			}

			break;
		}
	}
}

static void __xkWaylandDataOfferHandleSourceActions(void* data, struct wl_data_offer* wlDataOffer, uint32_t source_actions) {
	/// NOTE: Nothing to do here.
}

static void __xkWaylandDataOfferHandleSourceAction(void* data, struct wl_data_offer* wlDataOffer, uint32_t dnd_action) {
	/// NOTE: Nothing to do here.
}

static const struct wl_data_offer_listener _xkWaylandDataOfferListener = {
	__xkWaylandDataOfferHandleOffer,
	__xkWaylandDataOfferHandleSourceActions,
	__xkWaylandDataOfferHandleSourceAction
};

static void __xkWaylandDataDeviceHandleDataOffer(void* data, struct wl_data_device* wlDataDevice, struct wl_data_offer* wlDataOffer) {
	__XkWaylandOffer* offers = xkReallocateMemory(_xkPlatform.wayland.offers, sizeof(__XkWaylandOffer) * _xkPlatform.wayland.offerCount + 1);
	if(!offers) {
		__xkErrorHandle("Wayland: Failed to reallocate offers");
		return;
	}

	_xkPlatform.wayland.offers = offers;
	++_xkPlatform.wayland.offerCount;

	_xkPlatform.wayland.offers[_xkPlatform.wayland.offerCount - 1] = (__XkWaylandOffer){wlDataOffer, XK_FALSE, XK_FALSE};

	wl_data_offer_add_listener(wlDataOffer, &_xkWaylandDataOfferListener, NULL);
}

static void __xkWaylandDataDeviceHandleEnter(void* data, struct wl_data_device* wlDataDevice, uint32_t serial, struct wl_surface* wlSurface, wl_fixed_t x, wl_fixed_t y, struct wl_data_offer* wlDataOffer) {
	// Happens in the case we destroyed the surface.
	if(!wlSurface) {
		return;
	}

	XkWindow window = wl_surface_get_user_data(wlSurface);
	if(!window) {
		return;
	}

	if(_xkPlatform.wayland.wlDragOffer) {
		wl_data_offer_destroy(_xkPlatform.wayland.wlDragOffer);
		_xkPlatform.wayland.wlDragOffer = NULL;
		_xkPlatform.wayland.dragWindowFocus = NULL;
	}

	for(XkSize i = 0; i < _xkPlatform.wayland.offerCount; i++) {
		if(_xkPlatform.wayland.offers[i].wlOffer == wlDataOffer) {
			if(_xkPlatform.wayland.offers[i].URI) {
				_xkPlatform.wayland.wlDragOffer = wlDataOffer;
				_xkPlatform.wayland.dragWindowFocus = window;
			}

			_xkPlatform.wayland.offers[i] = _xkPlatform.wayland.offers[_xkPlatform.wayland.offerCount - 1];
			--_xkPlatform.wayland.offerCount;
			break;
		}
	}

	if (_xkPlatform.wayland.wlDragOffer) {
		wl_data_offer_accept(wlDataOffer, serial, "text/uri-list");
	} else {
		wl_data_offer_accept(wlDataOffer, serial, NULL);
		wl_data_offer_destroy(wlDataOffer);
	}
}

static void __xkWaylandDataDeviceHandleLeave(void* data, struct wl_data_device* wlDataDevice) {
	if(_xkPlatform.wayland.wlDragOffer) {
		wl_data_offer_destroy(_xkPlatform.wayland.wlDragOffer);
		_xkPlatform.wayland.wlDragOffer = NULL;
		_xkPlatform.wayland.dragWindowFocus = NULL;
	}
}

static void __xkWaylandDataDeviceHandleMotion(void* data, struct wl_data_device* wlDataDevice, uint32_t time, wl_fixed_t x, wl_fixed_t y) {
	/// NOTE: Nothing to do here.
}

static void __xkWaylandDataDeviceHandleDrop(void* data, struct wl_data_device* wlDataDevice) {
	if(!_xkPlatform.wayland.wlDragOffer) {
		return;
	}

	XkString string = __xkWaylandReadDataOfferAsString(_xkPlatform.wayland.wlDragOffer, "text/uri-list");
	if(string) {
		XkSize count;
		XkString* paths = __xkParseURI(string, &count);
		if(paths) {
			__xkInputWindowDropFile((XkWindow)_xkPlatform.wayland.dragWindowFocus, count, (XkString*)paths);
		}

		for(XkSize i = 0; i < count; i++) {
			xkFreeMemory(paths[i]);
		}

    xkFreeMemory(paths);

		xkFreeMemory(string);
	}
}

static void __xkWaylandDataDeviceHandleSelection(void* data, struct wl_data_device* wlDataDevice, struct wl_data_offer* wlDataOffer) {
	if(_xkPlatform.wayland.wlSelectionOffer) {
		wl_data_offer_destroy(_xkPlatform.wayland.wlSelectionOffer);
		_xkPlatform.wayland.wlSelectionOffer = NULL;
	}

	for(XkSize i = 0; i < _xkPlatform.wayland.offerCount; i++) {
		if(_xkPlatform.wayland.offers[i].wlOffer == wlDataOffer) {
			if(_xkPlatform.wayland.offers[i].UTF8) {
				_xkPlatform.wayland.wlSelectionOffer = wlDataOffer;
			} else {
				wl_data_offer_destroy(wlDataOffer);
			}

			_xkPlatform.wayland.offers[i] = _xkPlatform.wayland.offers[_xkPlatform.wayland.offerCount - 1];
			--_xkPlatform.wayland.offerCount;
			break;
		}
	}
}

const struct wl_data_device_listener _xkWaylandDataDeviceListener = {
	__xkWaylandDataDeviceHandleDataOffer,
	__xkWaylandDataDeviceHandleEnter,
	__xkWaylandDataDeviceHandleLeave,
	__xkWaylandDataDeviceHandleMotion,
	__xkWaylandDataDeviceHandleDrop,
	__xkWaylandDataDeviceHandleSelection,
};

static void __xkWaylandSeatHandleCapabilities(void* data, struct wl_seat* wlSeat, enum wl_seat_capability wlCapability) {
	if((wlCapability & WL_SEAT_CAPABILITY_POINTER) && !_xkPlatform.wayland.wlPointer) {
		_xkPlatform.wayland.wlPointer = wl_seat_get_pointer(wlSeat);

		wl_pointer_add_listener(_xkPlatform.wayland.wlPointer, &_xkWaylandPointerListener, NULL);
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
		_xkPlatform.wayland.wlCompositor = wl_registry_bind(wlRegistry, name, &wl_compositor_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)wl_shm_interface.name) == 1) {
		_xkPlatform.wayland.wlShm = wl_registry_bind(wlRegistry, name, &wl_shm_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)wl_output_interface.name) == 1) {
		_xkPlatform.wayland.wlOutput = wl_registry_bind(wlRegistry, name, &wl_output_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)wl_seat_interface.name) == 1) {
		_xkPlatform.wayland.wlSeat = wl_registry_bind(wlRegistry, name, &wl_seat_interface, version);

		 wl_seat_add_listener(_xkPlatform.wayland.wlSeat, &_xkWaylandSeatListener, NULL);
	} else if(xkCompareString((XkString)interface, (XkString)wl_data_device_manager_interface.name) == 1) {
		_xkPlatform.wayland.wlDataDeviceManager = wl_registry_bind(wlRegistry, name, &wl_data_device_manager_interface, version);
  } else if(xkCompareString((XkString)interface, (XkString)xdg_wm_base_interface.name) == 1) {
    _xkPlatform.wayland.xdgBase = wl_registry_bind(wlRegistry, name, &xdg_wm_base_interface, version);

		xdg_wm_base_add_listener(_xkPlatform.wayland.xdgBase, &_xkXDGWmBaseListener, NULL);
  } else if(xkCompareString((XkString)interface, (XkString)zxdg_decoration_manager_v1_interface.name) == 1) {
    _xkPlatform.wayland.xdgDecorationManager = wl_registry_bind(wlRegistry, name, &zxdg_decoration_manager_v1_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)zwp_relative_pointer_manager_v1_interface.name) == 1) {
		_xkPlatform.wayland.zwpRelativePointerManager = wl_registry_bind(wlRegistry, name, &zwp_relative_pointer_manager_v1_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)zwp_pointer_constraints_v1_interface.name) == 1) {
		_xkPlatform.wayland.zwpPointerConstraints = wl_registry_bind(wlRegistry, name, &zwp_pointer_constraints_v1_interface, version);
	} else if(xkCompareString((XkString)interface, (XkString)zwp_idle_inhibit_manager_v1_interface.name) == 1) {
		_xkPlatform.wayland.zwpIdleInhibitManager = wl_registry_bind(wlRegistry, name, &zwp_idle_inhibit_manager_v1_interface, version);
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
	// Destroy Wayland buffer.
  wl_buffer_destroy(wlBuffer);
}

static const struct wl_buffer_listener _xkWaylandBufferListener = {
  __xkWaylandBufferHandleRelease,
};

XkResult xkInitializeWindow(void) {
	XkResult result = XK_SUCCESS;

	if(_xkPlatform.initialized) {
		goto _catch;
	}

	_xkPlatform.wayland.wlDisplay = wl_display_connect(NULL);
	if(!_xkPlatform.wayland.wlDisplay) {
		__xkErrorHandle("Wayland: Failed to connect display");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	_xkPlatform.wayland.wlRegistry = wl_display_get_registry(_xkPlatform.wayland.wlDisplay);
	if(!_xkPlatform.wayland.wlRegistry) {
		__xkErrorHandle("Wayland: Failed to get display registry");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

  wl_registry_add_listener(_xkPlatform.wayland.wlRegistry, &_xkWaylandRegistryListener, NULL);

  __xkWaylandCreateKeyTable();

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

	if(!_xkPlatform.wayland.wlCompositor) {
		__xkErrorHandle("Wayland: Failed to register compositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.wlShm) {
		__xkErrorHandle("Wayland: Failed to register shm");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.wlOutput) {
		__xkErrorHandle("Wayland: Failed to register output");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.wlSeat) {
		__xkErrorHandle("Wayland: Failed to register seat");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.wlDataDeviceManager) {
		__xkErrorHandle("Wayland: Failed to register data device manager");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.xdgBase) {
		__xkErrorHandle("Wayland: Failed to register XDG base");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

  if(!_xkPlatform.wayland.xdgDecorationManager) {
		__xkErrorHandle("Wayland: Failed to register XDG decoration manager");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

	if(!_xkPlatform.wayland.zwpRelativePointerManager) {
		__xkErrorHandle("Wayland: Failed to register relative pointer manager");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.zwpPointerConstraints) {
		__xkErrorHandle("Wayland: Failed to register pointer constraints");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	if(!_xkPlatform.wayland.zwpIdleInhibitManager) {
		__xkErrorHandle("Wayland: Failed to register idle inhibit manager");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	_xkPlatform.wayland.wlDataDevice = wl_data_device_manager_get_data_device(_xkPlatform.wayland.wlDataDeviceManager, _xkPlatform.wayland.wlSeat);
  if(!_xkPlatform.wayland.wlDataDevice) {
		__xkErrorHandle("Wayland: Failed to create data device");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

	wl_data_device_add_listener(_xkPlatform.wayland.wlDataDevice, &_xkWaylandDataDeviceListener, NULL);

  _xkPlatform.wayland.wlCursorTheme = wl_cursor_theme_load(NULL, 32, _xkPlatform.wayland.wlShm);
  if(!_xkPlatform.wayland.wlCursorTheme) {
		__xkErrorHandle("Wayland: Failed to load default cursor theme");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

  _xkPlatform.wayland.wlCursorSurface = wl_compositor_create_surface(_xkPlatform.wayland.wlCompositor);
  if(!_xkPlatform.wayland.wlCursorSurface) {
		__xkErrorHandle("Wayland: Failed to create cursor surface");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
  }

  _xkPlatform.initialized = XK_TRUE;

_catch:
	return(result);
}

void xkTerminateWindow(void) {
	if(!_xkPlatform.initialized) {
		return;
	}

	if(_xkPlatform.wayland.xkbComposeState) {
		xkb_compose_state_unref(_xkPlatform.wayland.xkbComposeState);

		_xkPlatform.wayland.xkbComposeState = NULL;
	}

	if(_xkPlatform.wayland.xkbKeymap) {
		xkb_keymap_unref(_xkPlatform.wayland.xkbKeymap);

		_xkPlatform.wayland.xkbKeymap = NULL;
	}

	if(_xkPlatform.wayland.xkbState) {
		xkb_state_unref(_xkPlatform.wayland.xkbState);

		_xkPlatform.wayland.xkbState = NULL;
	}

  if(_xkPlatform.wayland.xkbContext) {
		xkb_context_unref(_xkPlatform.wayland.xkbContext);

		_xkPlatform.wayland.xkbContext = NULL;
  }

	for(XkSize i = 0; i < _xkPlatform.wayland.offerCount; i++) {
		wl_data_offer_destroy(_xkPlatform.wayland.offers[i].wlOffer);
	}

	if(_xkPlatform.wayland.offers) {
		xkFreeMemory(_xkPlatform.wayland.offers);
	}

	if(_xkPlatform.wayland.wlCursorSurface) {
		wl_surface_destroy(_xkPlatform.wayland.wlCursorSurface);

		_xkPlatform.wayland.wlCursorSurface = NULL;
	}

	if(_xkPlatform.wayland.wlCursorTheme) {
		wl_cursor_theme_destroy(_xkPlatform.wayland.wlCursorTheme);

		_xkPlatform.wayland.wlCursorTheme = NULL;
	}

	if (_xkPlatform.wayland.wlDataDevice) {
		wl_data_device_destroy(_xkPlatform.wayland.wlDataDevice);

		_xkPlatform.wayland.wlDataDevice = NULL;
	}

  if(_xkPlatform.wayland.wlDataDeviceManager) {
  	wl_data_device_manager_destroy(_xkPlatform.wayland.wlDataDeviceManager);

  	_xkPlatform.wayland.wlDataDeviceManager = NULL;
  }

  if(_xkPlatform.wayland.wlPointer) {
		wl_pointer_destroy(_xkPlatform.wayland.wlPointer);

		_xkPlatform.wayland.wlPointer = NULL;
  }

  if(_xkPlatform.wayland.wlKeyboard) {
		wl_keyboard_destroy(_xkPlatform.wayland.wlKeyboard);

		_xkPlatform.wayland.wlKeyboard = NULL;
  }

	if(_xkPlatform.wayland.wlSeat) {
		wl_seat_destroy(_xkPlatform.wayland.wlSeat);

		_xkPlatform.wayland.wlSeat = NULL;
	}

	if(_xkPlatform.wayland.wlOutput) {
		wl_output_destroy(_xkPlatform.wayland.wlOutput);

		_xkPlatform.wayland.wlOutput = NULL;
	}

	if(_xkPlatform.wayland.wlShm) {
		wl_shm_destroy(_xkPlatform.wayland.wlShm);

		_xkPlatform.wayland.wlShm = NULL;
	}

  if(_xkPlatform.wayland.wlCompositor) {
		wl_compositor_destroy(_xkPlatform.wayland.wlCompositor);

		_xkPlatform.wayland.wlCompositor = NULL;
  }
	
 	if(_xkPlatform.wayland.xdgBase) {
		xdg_wm_base_destroy(_xkPlatform.wayland.xdgBase);

		_xkPlatform.wayland.xdgBase = NULL;
	}

 	if(_xkPlatform.wayland.xdgDecorationManager) {
		zxdg_decoration_manager_v1_destroy(_xkPlatform.wayland.xdgDecorationManager);

		_xkPlatform.wayland.xdgDecorationManager = NULL;
 	}

	if(_xkPlatform.wayland.zwpRelativePointerManager) {
		zwp_relative_pointer_manager_v1_destroy(_xkPlatform.wayland.zwpRelativePointerManager);

		_xkPlatform.wayland.zwpRelativePointerManager	= NULL;
	}

	if(_xkPlatform.wayland.zwpPointerConstraints) {
		zwp_pointer_constraints_v1_destroy(_xkPlatform.wayland.zwpPointerConstraints);

		_xkPlatform.wayland.zwpPointerConstraints	= NULL;
	}
	
  if(_xkPlatform.wayland.zwpIdleInhibitManager) {
		zwp_idle_inhibit_manager_v1_destroy(_xkPlatform.wayland.zwpIdleInhibitManager);

		_xkPlatform.wayland.zwpIdleInhibitManager = NULL;
	}

	if(_xkPlatform.wayland.wlRegistry) {
  	wl_registry_destroy(_xkPlatform.wayland.wlRegistry);

 		_xkPlatform.wayland.wlRegistry = NULL;
	}

	if(_xkPlatform.wayland.wlDisplay) {
  	wl_display_flush(_xkPlatform.wayland.wlDisplay);
		wl_display_disconnect(_xkPlatform.wayland.wlDisplay);

 		_xkPlatform.wayland.wlDisplay = NULL;
	}

  _xkPlatform.initialized = XK_FALSE;
}

struct wl_display* __xkWaylandGetDisplay(void) {
	return(_xkPlatform.wayland.wlDisplay);
}

struct wl_surface* __xkWaylandGetSurface(const XkWindow window) {
	xkAssert(window);

	return(window->wayland.wlSurface);
}

XkResult xkCreateWindow(XkWindow* pWindow, const XkString title, const XkSize width, const XkSize height, const XkWindowHint hint) {
	xkAssert(pWindow);
	xkAssert(width > 0);
  xkAssert(height > 0);

	XkResult result = XK_SUCCESS;
	
	*pWindow = xkAllocateMemory(sizeof(struct XkWindow_T));
	if(!(*pWindow)) {
		result = XK_ERROR_BAD_ALLOCATE;
		goto _catch;
	}
	
	XkWindow window = *pWindow;

  if(
    (hint & XK_WINDOW_HINT_DECORATED_BIT && hint & XK_WINDOW_HINT_FLOATING_BIT) || 
    (hint & XK_WINDOW_HINT_RESIZABLE_BIT && hint & XK_WINDOW_HINT_FLOATING_BIT)) {
    __xkErrorHandle("Win32: Unsupported window hints");
  }

	if(hint & XK_WINDOW_HINT_DECORATED_BIT) 	window->decorated = XK_TRUE;
	if(hint & XK_WINDOW_HINT_RESIZABLE_BIT) 	window->resizable = XK_TRUE;
	if(hint & XK_WINDOW_HINT_FLOATING_BIT) 		window->floating = XK_TRUE;

  window->cursorMode 	= XK_CURSOR_NORMAL;
  window->wayland.wlCursorBuffer 	= NULL;
	if(title) {
		/// NOTE: Needs to be free.
  	window->title 		= xkDuplicateString(title);
	}

	/// NOTE: Needs for create shm buffer.
	window->wayland.width 	= width;
	window->wayland.height 	= height;

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

	if(title) {
  	xdg_toplevel_set_title(window->wayland.xdgToplevel, window->title);
	}

	if(!window->resizable) {
		xkSetWindowSizeLimits(window, width, height, width, height);
	}

	/// NOTE: I don't want commit Wayland surface here, because i commit it in show function.

_catch:
	return(result);
}

void xkDestroyWindow(XkWindow window) {
	xkAssert(window);

	__xkZWPDestroyIdleInhibitor(window);

	__xkXDGDestorySurface(window);

	if(window->wayland.wlCursorBuffer) {
		wl_buffer_destroy(window->wayland.wlCursorBuffer);
	}

	if(window->wayland.wlSurface) {
		wl_surface_destroy(window->wayland.wlSurface);
	}

  if(window->title) {
		xkFreeMemory(window->title);
	}
	
	xkFreeMemory(window);
}

void xkShowWindow(XkWindow window, const XkWindowShow show) {
	xkAssert(window);

	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT:
			__xkXDGCreateSurface(window);

			__xkXDGCreateDecorations(window);

			// Restore XDG toplevel.
			xdg_toplevel_unset_maximized(window->wayland.xdgToplevel);
			xdg_toplevel_unset_fullscreen(window->wayland.xdgToplevel);

			__xkZWPDestroyIdleInhibitor(window);
			break;

		case XK_WINDOW_SHOW_MAXIMIZED:
			__xkXDGCreateSurface(window);

			__xkXDGCreateDecorations(window);

			xdg_toplevel_set_maximized(window->wayland.xdgToplevel);

			__xkZWPDestroyIdleInhibitor(window);
			break;

		case XK_WINDOW_SHOW_MINIMIZED:
			__xkXDGCreateSurface(window);

			__xkXDGCreateDecorations(window);

			xdg_toplevel_set_minimized(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_FULLSCREEN:
			__xkXDGCreateDecorations(window);

			__xkXDGDestroyDecorations(window);

			xdg_toplevel_set_fullscreen(window->wayland.xdgToplevel, _xkPlatform.wayland.wlOutput);

			__xkZWPCreateIdleInhibitor(window);
			break;

		case XK_WINDOW_HIDE:
			__xkXDGDestorySurface(window);

			__xkXDGDestroyDecorations(window);

			// Set null Wayland surface contents.
      wl_surface_attach(window->wayland.wlSurface, NULL, 0, 0);

			__xkZWPDestroyIdleInhibitor(window);
			break;
	}

  wl_surface_commit(window->wayland.wlSurface);
}

void xkFocusWindow(XkWindow window) {
	xkAssert(window);

	// A Wayland client can not focus.
	__xkErrorHandle("Wayland: platform doesn't support setting the input focus");
}

void xkSetWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	xkAssert(window);
  xkAssert(width > 0);
  xkAssert(height > 0);

	window->wayland.width = width;
	window->wayland.height = height;

	__xkWaylandResizeWindow(window);

	// Automaticaly window size event don't input.
	__xkInputWindowSize(window, width, height);
}

void xkGetWindowSize(XkWindow window, XkSize* const pWidth, XkSize* const pHeight) {
	xkAssert(window);

	if(pWidth) {
		*pWidth = window->wayland.width;
	}

  if(pHeight) {
    *pHeight = window->wayland.height;
	}
}

void xkSetWindowSizeLimits(XkWindow window, const XkSize minWidth, const XkSize minHeight, const XkSize maxWidth, const XkSize maxHeight) {
	xkAssert(window);

	if(minWidth != 0 && minHeight != 0) {
  	xdg_toplevel_set_min_size(window->wayland.xdgToplevel, (int32_t)minWidth, (int32_t)minHeight);
	}

	if(maxWidth != 0 && maxHeight) {
		xdg_toplevel_set_max_size(window->wayland.xdgToplevel, (int32_t)maxWidth, (int32_t)maxHeight);
	}

	wl_surface_commit(window->wayland.wlSurface);
}

void xkSetWindowPosition(XkWindow window, const XkInt32 xPos, const XkInt32 yPos) {
	xkAssert(window);

	// A Wayland client can not set its position.
	__xkErrorHandle("Wayland: platform doesn't support setting the input position");
}

void xkGetWindowPosition(XkWindow window, XkInt32* const pXPos, XkInt32* const pYPos) {
	xkAssert(window);

  // A Wayland client is not aware of its position.
	__xkErrorHandle("Wayland: platform doesn't provide the window position");
}

void xkSetWindowTitle(XkWindow window, const XkString title) {
	xkAssert(window);

  if(window->title) {
		xkFreeMemory(window->title);
	}

  window->title = xkDuplicateString(title);

	xdg_toplevel_set_title(window->wayland.xdgToplevel, title);
}

void xkSetWindowIcon(XkWindow window, const XkSize count, const XkWindowIcon* pIcon) {
	xkAssert(window);

	// A Wayland client can't set its icon
	__xkErrorHandle("Wayland: platform doesn't support setting the window icon");
}

void xkSetWindowCursorPosition(XkWindow window, const XkFloat64 xPos, const XkFloat64 yPos) {
	xkAssert(window);

	if(window->wayland.zwpLockedPointer != NULL) {
		zwp_locked_pointer_v1_set_cursor_position_hint(window->wayland.zwpLockedPointer, wl_fixed_from_double(xPos), wl_fixed_from_double(yPos));
	}
}

void xkGetWindowCursorPosition(XkWindow window, XkFloat64* const pXPos, XkFloat64* const pYPos) {
	xkAssert(window);

	if(pXPos) {
		*pXPos = window->wayland.cursorPosX;
	}

	if(pYPos) {
		*pYPos = window->wayland.cursorPosY;
	}
}

void xkSetWindowCursorMode(XkWindow window, const XkCursorMode mode) {
	xkAssert(window);

	window->cursorMode = mode;

	if(mode == XK_CURSOR_DISABLED) {
		__xkZWPLockPointer(window);
	} else if(mode == XK_CURSOR_HIDDEN) {
		wl_pointer_set_cursor(_xkPlatform.wayland.wlPointer, _xkPlatform.wayland.pointerSerial, NULL, 0, 0);
	} else if(mode == XK_CURSOR_NORMAL) {
		__xkZWPUnlockPointer(window);
		wl_pointer_set_cursor(_xkPlatform.wayland.wlPointer, _xkPlatform.wayland.pointerSerial, _xkPlatform.wayland.wlCursorSurface, window->wayland.cursorXHot, window->wayland.cursorYHot);
	}
}

void __xkWaylandSetWindowCursor(XkWindow window) {
	xkAssert(window);

	__xkErrorHandle("set cursor");

	if(window->wayland.wlCursorBuffer && window->cursorMode == XK_CURSOR_NORMAL) {
		wl_pointer_set_cursor(_xkPlatform.wayland.wlPointer, _xkPlatform.wayland.pointerSerial, _xkPlatform.wayland.wlCursorSurface, window->wayland.cursorXHot, window->wayland.cursorYHot);
		wl_surface_attach(_xkPlatform.wayland.wlCursorSurface, window->wayland.wlCursorBuffer, 0, 0);
		wl_surface_damage(_xkPlatform.wayland.wlCursorSurface, 0, 0, (int)window->wayland.cursorWidth, (int)window->wayland.cursorHeight);
		wl_surface_commit(_xkPlatform.wayland.wlCursorSurface);
	}
}

void xkSetWindowCursor(XkWindow window, const XkWindowIcon* pIcon) {
	xkAssert(window);

	if(pIcon) {
		const int width = pIcon->width;
		const int height = pIcon->height;

		window->wayland.wlCursorBuffer = __xkWaylandCreateShmBuffer(width, height, width * 4, (width * height) * 4, pIcon->pixels);
 		if(!window->wayland.wlCursorBuffer) {
			__xkErrorHandle("Wayland: Failed to create cursor buffer");
 			return;
 		}

		window->wayland.cursorWidth 	= width;
		window->wayland.cursorHeight 	= height;
		window->wayland.cursorXHot 		= 0;
		window->wayland.cursorYHot 		= 0;
	} else {
		struct wl_cursor* wlCursor = wl_cursor_theme_get_cursor(_xkPlatform.wayland.wlCursorTheme, "default");
		if(!wlCursor) {
			__xkErrorHandle("Wayland: Failed to find standard cursor");
			return;
		}

		struct wl_cursor_image* wlImage = wlCursor->images[0];

		window->wayland.wlCursorBuffer 	= wl_cursor_image_get_buffer(wlImage);
		window->wayland.cursorWidth 		= wlImage->width;
		window->wayland.cursorHeight 		= wlImage->height;
		window->wayland.cursorXHot 			= wlImage->hotspot_x;
		window->wayland.cursorYHot 			= wlImage->hotspot_y;
	}

	__xkWaylandSetWindowCursor(window);
}

uint64_t __xkPosixGetTimerFrequency() {
	return(1000000000);
}

uint64_t __xkPosixGetTimerValue() {
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return((uint64_t)ts.tv_sec * __xkPosixGetTimerFrequency() + (uint64_t)ts.tv_nsec);
}

static XkBool __xkPosixPoll(struct pollfd* fds, nfds_t count, double* timeout) {
	while(XK_TRUE) {
		if(timeout) {
			const uint64_t base = __xkPosixGetTimerValue();

			const time_t seconds = (time_t)*timeout;
			const long nanoseconds = (long)((*timeout - seconds) * 1e9);
			const struct timespec ts = { seconds, nanoseconds };
			const int result = ppoll(fds, count, &ts, NULL);

			const int error = errno; // clock_gettime may overwrite our error

			*timeout -= (__xkPosixGetTimerValue() - base) / (double)__xkPosixGetTimerFrequency();

			if(result > 0) {
				return(XK_TRUE);
			} else if(result == -1 && error != EINTR && error != EAGAIN) {
				return(XK_FALSE);
			} else if(*timeout <= 0.0) {
				return(XK_FALSE);
			}
		} else {
			const int result = poll(fds, count, -1);
			if(result > 0) {
				return(XK_TRUE);
			} else if(result == -1 && errno != EINTR && errno != EAGAIN) {
				return(XK_FALSE);
			}
		}
	}
}

static void __xkWaylandHandleEvents(XkFloat64* pTimeout) {
	XkBool event = XK_FALSE;
	struct pollfd fds[] = {
		{wl_display_get_fd(_xkPlatform.wayland.wlDisplay), POLLIN}
  };

	while(!event) {
		while(wl_display_prepare_read(_xkPlatform.wayland.wlDisplay) != 0) {
			wl_display_dispatch_pending(_xkPlatform.wayland.wlDisplay);			
		}

		if(!__xkWaylandFlushDisplay()) {
			wl_display_cancel_read(_xkPlatform.wayland.wlDisplay);

			return;
		}

		if(!__xkPosixPoll(fds, 1, pTimeout)) {
			wl_display_cancel_read(_xkPlatform.wayland.wlDisplay);

			return;
		}

		if(fds[0].revents & POLLIN) {
			wl_display_read_events(_xkPlatform.wayland.wlDisplay);
			if(wl_display_dispatch_pending(_xkPlatform.wayland.wlDisplay) > 0) {
				event = XK_TRUE;
			}
		} else {
			wl_display_cancel_read(_xkPlatform.wayland.wlDisplay);		
		}
	}
}

void xkPollEvents() {
	XkFloat64 timeout = 0.0;
	__xkWaylandHandleEvents(&timeout);
}

void xkWaitEvents() {
	wl_display_dispatch(_xkPlatform.wayland.wlDisplay);
}

void xkWaitEventsTimeout(XkFloat64 timeout) {
	__xkWaylandHandleEvents(&timeout);
}

static XkBool __xkXDGCreateSurface(XkWindow window) {
	xkAssert(window);

	XkBool result = XK_FALSE;

	if(window->wayland.xdgToplevel) goto _catch;

	window->wayland.xdgSurface = xdg_wm_base_get_xdg_surface(_xkPlatform.wayland.xdgBase, window->wayland.wlSurface);
	if(!window->wayland.xdgSurface) {
		result = XK_TRUE;
		__xkErrorHandle("XDG: Failed to create surface");
		goto _catch;
  }

  xdg_surface_add_listener(window->wayland.xdgSurface, &_xkXDGSurfaceListener, window);

	window->wayland.xdgToplevel = xdg_surface_get_toplevel(window->wayland.xdgSurface);
  if(!window->wayland.xdgToplevel) {
		result = XK_TRUE;
		__xkErrorHandle("XDG: Failed to create toplevel");
		goto _catch;
  }

  xdg_toplevel_add_listener(window->wayland.xdgToplevel, &_xkXDGToplevelListener, window);

_catch:
	return(result);
}

static void __xkXDGDestorySurface(XkWindow window) {
	xkAssert(window);

	if(window->wayland.xdgToplevel) {
		xdg_toplevel_destroy(window->wayland.xdgToplevel);

		window->wayland.xdgToplevel = NULL;
	}

	if(window->wayland.xdgSurface) {
		xdg_surface_destroy(window->wayland.xdgSurface);

		window->wayland.xdgSurface = NULL;
	}
}

static XkBool __xkXDGCreateDecorations(XkWindow window) {
	xkAssert(window);

	XkBool result = XK_FALSE;

	if(window->wayland.xdgDecoration) goto _catch;

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
	xkAssert(window);

	if(window->wayland.xdgDecoration) {
		zxdg_toplevel_decoration_v1_destroy(window->wayland.xdgDecoration);

		window->wayland.xdgDecoration = NULL;
	}
}

static XkBool __xkZWPCreateIdleInhibitor(XkWindow window) {
	xkAssert(window);

	XkBool result = XK_FALSE;

	if(window->wayland.zwpIdleInhibitor) goto _catch;

  window->wayland.zwpIdleInhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(_xkPlatform.wayland.zwpIdleInhibitManager, window->wayland.wlSurface);
  if(!window->wayland.zwpIdleInhibitor) {
		result = XK_TRUE;
    __xkErrorHandle("Wayland: Failed to create idle inhibitor");
		goto _catch;
	}

_catch:
	return(result);
}

static void __xkZWPDestroyIdleInhibitor(XkWindow window) {
	xkAssert(window);

	if(window->wayland.zwpIdleInhibitor) {
		zwp_idle_inhibitor_v1_destroy(window->wayland.zwpIdleInhibitor);

		window->wayland.zwpIdleInhibitor = NULL;
	}
}

static int __xkWaylandAllocateShmFile(const XkSize size) {
	xkAssert(size > 0);

	int fd = memfd_create("XKinetic-Wayland", MFD_CLOEXEC | MFD_ALLOW_SEALING);
	if(fd >= 0) {
		fcntl(fd, F_ADD_SEALS, F_SEAL_SHRINK | F_SEAL_SEAL);
	} else {
		goto _catch;
	}

	int ret = posix_fallocate(fd, 0, (int)size);
	if(ret != 0) {
		close(fd);
		fd = -1;
		goto _catch;
	}

_catch:
	return(fd);
}

struct wl_buffer* __xkWaylandCreateShmBuffer(const XkSize width, const XkSize height, const XkSize stride, const XkSize size, const XkHandle data) {
	xkAssert(width > 0);
	xkAssert(height > 0);
	xkAssert(stride > 0);
	xkAssert(size > 0);

	struct wl_buffer* wlBuffer = NULL;

	int fd = __xkWaylandAllocateShmFile(size);
	if(fd == -1) {
		goto _catch;
	}

	uint32_t* mappedData = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(mappedData == MAP_FAILED) {
		close(fd);
		goto _catch;
	}

	struct wl_shm_pool* wlPool = wl_shm_create_pool(_xkPlatform.wayland.wlShm, fd, size);

	wlBuffer = wl_shm_pool_create_buffer(wlPool, 0, (int)width, (int)height, (int)stride, WL_SHM_FORMAT_XRGB8888);

	wl_shm_pool_destroy(wlPool);

	close(fd);

	if(data) {
		XkUInt8* pSource = (XkUInt8*)data;
    XkUInt8* pTarget = (XkUInt8*)mappedData;
    for(XkSize i = 0;  i < width * height;  i++, pSource += 4) {
			XkUInt32 alpha = pSource[3];

			*pTarget++ = (XkUInt8)((pSource[2] * alpha) / 255);
			*pTarget++ = (XkUInt8)((pSource[1] * alpha) / 255);
			*pTarget++ = (XkUInt8)((pSource[0] * alpha) / 255);
			*pTarget++ = (XkUInt8)alpha;
    }
	}

	munmap(mappedData, size);

	wl_buffer_add_listener(wlBuffer, &_xkWaylandBufferListener, NULL);

_catch:
	return(wlBuffer);
}

static void __xkWaylandResizeWindow(XkWindow window) {
	xkAssert(window);

	int width = window->wayland.width;
	int height = window->wayland.height;

	struct wl_buffer* wlBuffer = __xkWaylandCreateShmBuffer(width, height, width * 4, (width * height) * 4, XK_NULL_HANDLE);
 	if(!wlBuffer) {
		__xkErrorHandle("Wayland: Failed to create shared buffer");
 		return;
 	}

	wl_surface_attach(window->wayland.wlSurface, wlBuffer, 0, 0);

	struct wl_region* wlRegion = wl_compositor_create_region(_xkPlatform.wayland.wlCompositor);
	if(!wlRegion) {
		__xkErrorHandle("Wayland: Failed to create region");
		return;
	}

	wl_region_add(wlRegion, 0, 0, (int)window->wayland.width, (int)window->wayland.height);

	wl_surface_set_opaque_region(window->wayland.wlSurface, wlRegion);

	wl_region_destroy(wlRegion);

	wl_surface_commit(window->wayland.wlSurface);
}

static XkBool __xkWaylandFlushDisplay() {
	while(wl_display_flush(_xkPlatform.wayland.wlDisplay) == -1) {
		struct pollfd fd = {wl_display_get_fd(_xkPlatform.wayland.wlDisplay), POLLOUT};

		while(poll(&fd, 1, -1) == -1) {
			if(errno != EINTR && errno != EAGAIN) {
				return(XK_FALSE);
			}
		}
	}

	return(XK_TRUE);
}

static void __xkZWPLockPointer(XkWindow window) {
	xkAssert(window);

	if(window->wayland.zwpRelativePointer) {
		return;
	}

	window->wayland.zwpRelativePointer = zwp_relative_pointer_manager_v1_get_relative_pointer(_xkPlatform.wayland.zwpRelativePointerManager, _xkPlatform.wayland.wlPointer);
	if(!window->wayland.zwpRelativePointer) {
		__xkErrorHandle("Wayland: Failed to create relative pointer");
	}

  zwp_relative_pointer_v1_add_listener(window->wayland.zwpRelativePointer, &_xkZWPRelativePointerListener, window);

	window->wayland.zwpLockedPointer = zwp_pointer_constraints_v1_lock_pointer(_xkPlatform.wayland.zwpPointerConstraints, window->wayland.wlSurface, _xkPlatform.wayland.wlPointer, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
	if(!window->wayland.zwpLockedPointer) {
		__xkErrorHandle("Wayland: Failed to create locked pointer");
	}

  zwp_locked_pointer_v1_add_listener(window->wayland.zwpLockedPointer, &_xkZWPLockedPointerListener, window);

  wl_pointer_set_cursor(_xkPlatform.wayland.wlPointer, _xkPlatform.wayland.pointerSerial, NULL, 0, 0);
}

static void __xkZWPUnlockPointer(XkWindow window) {
	xkAssert(window);

	if(window->wayland.zwpRelativePointer) {
		zwp_relative_pointer_v1_destroy(window->wayland.zwpRelativePointer);

		window->wayland.zwpRelativePointer = NULL;
	}

	if(window->wayland.zwpLockedPointer) {
		zwp_locked_pointer_v1_destroy(window->wayland.zwpLockedPointer);

		window->wayland.zwpLockedPointer = NULL;
	}
}

static char* __xkWaylandReadDataOfferAsString(struct wl_data_offer* wlDataOffer, const char* mimeType) {
	xkAssert(wlDataOffer);

	int fds[2];

	if(pipe2(fds, O_CLOEXEC) == -1) {
		__xkErrorHandle("Wayland: Failed to create pipe for data offer");
		return NULL;
	}

	wl_data_offer_receive(wlDataOffer, mimeType, fds[1]);
	__xkWaylandFlushDisplay();

	close(fds[1]);

	char* string = NULL;
	size_t size = 0;
	size_t length = 0;

	while(XK_TRUE) {
		const size_t readSize = 4096;
		const size_t requiredSize = length + readSize + 1;
		if(requiredSize > size) {
			char* longer = NULL;
			longer = xkReallocateMemory(string, requiredSize);
			if(!longer) {
				__xkErrorHandle("Wayland: Failed to reallocate data offer string");
				close(fds[0]);
				return NULL;
			}

			string = longer;
			size = requiredSize;
		}

		const ssize_t result = read(fds[0], string + length, readSize);
		if(result == 0) {
			break;
		} else if (result == -1) {
			__xkErrorHandle("Wayland: Failed to read from data offer pipe");

			close(fds[0]);
			return NULL;
		}

		length += result;
	}

	close(fds[0]);

	string[length] = '\0';

	return(string);
}

XkString* __xkParseURI(XkString text, XkSize* pCount) {
	xkAssert(pCount);

	const XkString prefix = "file://";
	XkString* paths = NULL;
	XkString next = NULL;
	XkString line = xkTokenString(text, &next, "\r\n");

	XkSize count = 0;

	while(line) {
		if(line[0] == '#') {
			continue;
		}

		if(xkNCompareString(line, prefix, xkStringLength(prefix)) == 1) {
			line += xkStringLength(prefix);

			while(*line != '/') {
				++line;
			}
    }

    ++count;

		XkString path = xkAllocateMemory(xkStringLength(line) + 1);
		paths = xkReallocateMemory(paths, count * sizeof(char*));
		paths[count - 1] = path;

		while(*line) {
			*path = *line;

			++path;
			++line;
		}

		line = xkTokenString(next, &next, "\r\n");
	}

	*pCount = count; 

	for(XkSize i = 0; i < count; i++) {
		xkFreeMemory(paths[i]);
	}
	xkFreeMemory(paths);

	return(paths);
}

static void __xkWaylandCreateKeyTable() {
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

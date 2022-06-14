#pragma once

#include <linux/input.h>
#include <linux/limits.h>
#include <regex.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-compose.h>
#include <linux/input.h>
#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/Unix/Internal.h"

typedef struct {
	struct wl_egl_window* 								eglWindow;
	struct wl_surface* 										wlSurface;
  struct xdg_surface* 									xdgSurface;
	struct xdg_toplevel* 									xdgToplevel;
	struct zxdg_toplevel_decoration_v1* 	xdgDecoration;
	struct zwp_idle_inhibitor_v1* 				zwpIdleInhibitor;

	struct zwp_relative_pointer_v1*    		zwpRelativePointer;
	struct zwp_locked_pointer_v1*      		zwpLockedPointer;

	char*	title;
} __XkLinuxWindow;

#define XK_PLATFORM_WINDOW __XkLinuxWindow handle

typedef struct {
	int                     handle;
	char                    path[PATH_MAX];
	int                     keyMap[KEY_CNT - BTN_MISC];
	int                     absMap[ABS_CNT];
	struct input_absinfo    absInfo[ABS_CNT];
	int                     hats[4][2];
} __XkLinuxJoystick;

#define XK_PLATFORM_JOYSTICK __XkLinuxJoystick handle

typedef struct {
  XkSize 										image_count;
  struct wl_cursor_image** 	wlImages;
  char* 										name;
} __XkLinuxWindowCursor;

#define XK_PLATFORM_WINDOW_CURSOR __XkLinuxWindowCursor handle

typedef struct {
	struct wl_display* wlDisplay;
  struct wl_registry* wlRegistry;
  struct wl_compositor* wlCompositor;
	struct wl_surface* wlSurface;
  struct wl_subcompositor* wlSubcompositor;
	struct wl_output* wlOutput;
  struct wl_shm*  wlShm;
  struct wl_seat* wlSeat;
  struct wl_pointer* wlPointer;
  struct wl_keyboard* wlKeyboard;

	struct wl_data_device_manager*	wlDataDeviceManager;
	struct wl_data_device*      		wlDataDevice;

  struct wl_data_offer*       wlSelectionOffer;
  struct wl_data_source*      wlSelectionSource;

  struct wl_data_offer*       wlDragOffer;

	struct wl_cursor_theme*     wlCursorTheme;
	struct wl_cursor_theme*     wlCursorThemeHiDPI;
  struct wl_surface*          wlCursorSurface;

	struct xdg_wm_base* xdgBase;
	struct zxdg_decoration_manager_v1* xdgDecorationManager;

	struct wp_viewporter*  wpViewporter;

  struct zwp_relative_pointer_manager_v1* zwpRelativePointerManager;
  struct zwp_pointer_constraints_v1*      zwpPointerConstraints;
  struct zwp_idle_inhibit_manager_v1*     zwpIdleInhibitManager;

	struct xkb_context*     	xkbContext;
	struct xkb_keymap*      	xkbKeymap;
	struct xkb_state*       	xkbState;
	struct xkb_compose_state* xkbComposeState;

	xkb_mod_index_t         xkbControlIndex;
  xkb_mod_index_t         xkbAltIndex;
  xkb_mod_index_t         xkbShiftIndex;
  xkb_mod_index_t         xkbSuperIndex;
  xkb_mod_index_t         xkbCapsLockIndex;
  xkb_mod_index_t         xkbNumLockIndex;
  unsigned int            xkbModifiers;
} __XkLinuxPlatform;

#define XK_PLATFORM __XkLinuxPlatform handle

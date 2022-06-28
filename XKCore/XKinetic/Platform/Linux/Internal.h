#pragma once

#include <wayland-client.h>
#include <wayland-cursor.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-compose.h>
#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/Unix/Internal.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct {
	struct wl_surface* 										wlSurface;

  struct xdg_surface* 									xdgSurface;
	struct xdg_toplevel* 									xdgToplevel;

	struct zxdg_toplevel_decoration_v1* 	xdgDecoration;

  struct zwp_relative_pointer_v1*				zwpRelativePointer;
  struct zwp_locked_pointer_v1*					zwpLockedPointer;
	struct zwp_idle_inhibitor_v1*					zwpIdleInhibitor;

	XkSize width;
	XkSize height;

	XkFloat64 cursorPosX;
	XkFloat64 cursorPosY;
} __XkWaylandWindow;

#define XK_PLATFORM_WINDOW __XkWaylandWindow wayland

typedef struct {
	int                     handle;
} __XkLinuxJoystick;

#define XK_PLATFORM_JOYSTICK __XkLinuxJoystick handle

typedef struct {
  XkSize 										imageCount;
  struct wl_cursor_image** 	wlImages;
  char* 										name;
} __XkWaylandWindowCursor;

typedef struct {
	struct wl_data_offer*       wlOffer;
	XkBool                    	UTF8;
	XkBool                    	URI;
} __XkWaylandOffer;

#define XK_PLATFORM_WINDOW_CURSOR __XkWaylandWindowCursor wayland

typedef struct {
	struct wl_display*												wlDisplay;
  struct wl_registry*												wlRegistry;

  struct wl_compositor*											wlCompositor;

  struct wl_shm*														wlShm;

	struct wl_output*													wlOutput;

	struct wl_seat*														wlSeat;
	struct wl_keyboard*												wlKeyboard;
	struct wl_pointer*												wlPointer;

	struct wl_cursor_theme*										wlCursorTheme;
  struct wl_cursor_theme*										wlCursorThemeHiDPI;
  struct wl_surface*												wlCursorSurface;

  struct zwp_relative_pointer_manager_v1*		zwpRelativePointerManager;
  struct zwp_pointer_constraints_v1*				zwpPointerConstraints;
	struct zwp_idle_inhibit_manager_v1*				zwpIdleInhibitManager;

	struct wl_data_device_manager*						wlDataDeviceManager;
	struct wl_data_device*										wlDataDevice;

	struct wl_data_offer*											wlDragOffer;
	struct wl_data_offer*											wlSelectionOffer;

	struct xdg_wm_base*												xdgBase;
	struct zxdg_decoration_manager_v1*				xdgDecorationManager;

	struct xkb_context*												xkbContext;
	struct xkb_keymap*												xkbKeymap;
	struct xkb_state*													xkbState;
	struct xkb_compose_state*									xkbComposeState;

	uint32_t																	pointerSerial;

	xkb_mod_index_t														xkbControlIndex;
	xkb_mod_index_t														xkbAltIndex;
	xkb_mod_index_t														xkbShiftIndex;
	xkb_mod_index_t														xkbSuperIndex;
	xkb_mod_index_t														xkbCapsLockIndex;
	xkb_mod_index_t														xkbNumLockIndex;
	unsigned int															modifiers;

	void*																			keyboardWindowFocus;
	void*																			pointerWindowFocus;
	void*																			dragWindowFocus;

	__XkWaylandOffer*													offers;
	XkSize																		offerCount;


} __XkWaylandPlatform;

#define XK_PLATFORM __XkWaylandPlatform wayland

#ifdef __cplusplus
}
#endif // __cplusplus

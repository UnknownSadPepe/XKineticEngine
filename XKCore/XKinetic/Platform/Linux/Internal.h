#pragma once

#include <wayland-client.h>

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

	struct xdg_wm_base* xdgBase;

	struct zxdg_decoration_manager_v1* xdgDecorationManager;
	struct wp_viewporter*       wlViewporter;
} __XkLinuxPlatform;

typedef struct {
	struct wl_surface* wlSurface;
	struct wl_subsurface* wlSubsurface;
	struct wp_viewport*   wlViewport;
} __XkLinuxWindowDecoration;

#define XK_PLATFORM __XkLinuxPlatform handle


#pragma once

#include <wayland-client.h>
#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/Unix/Internal.h"

typedef struct {
	struct wl_surface* wlSurface;
	struct wl_output* wlOutput;
  struct xdg_surface* xdgSurface;
	struct xdg_toplevel* xdgToplevel;
	struct zxdg_toplevel_decoration_v1* xdgDecoration;

  struct {
		struct wl_buffer* wlBuffer;
    struct {
			struct wl_surface* wlSurface;
			struct wl_subsurface* wlSubsurface;
			struct wp_viewport*   wlViewport;
		} top, left, right, bottom;
		XkBool32 serverSide;
  } decorations;
} __XkLinuxWindow;

#define XK_PLATFORM_WINDOW __XkLinuxWindow handle

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


#pragma once

#include <pthread.h>
#include <wayland-client.h>
#include "XKinetic/XKCore.h"
#include "XKinetic/Platform/Unix/External.h"

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


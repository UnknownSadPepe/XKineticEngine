#pragma once

#include <pthread.h>
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include <xkbcommon/xkbcommon-compose.h>
#include "XKinetic/XKCore.h"

typedef struct {
	int handle;
} __XkLinuxFile;

#define XK_PLATFORM_FILE __XkLinuxFile handle

typedef struct __XkLinuxThread {
	pthread_t handle;
} __XkLinuxThread;

#define XK_PLATFORM_THREAD __XkLinuxThread handle

typedef struct __XkLinuxMutex {
	pthread_mutex_t handle;
} __XkLinuxMutex;

#define XK_PLATFORM_MUTEX __XkLinuxMutex handle

typedef struct XkLinuxWindow {
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


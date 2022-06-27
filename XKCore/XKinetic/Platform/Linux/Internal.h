#pragma once

#include <wayland-client.h>
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

	XkSize width;
	XkSize height;
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

#define XK_PLATFORM_WINDOW_CURSOR __XkWaylandWindowCursor wayland

typedef struct {
	struct wl_display*										wlDisplay;
  struct wl_registry*										wlRegistry;

  struct wl_shm*												wlShm;

  struct wl_compositor*									wlCompositor;

	struct wl_output*											wlOutput;

	struct xdg_wm_base*										xdgBase;
	struct zxdg_decoration_manager_v1*		xdgDecorationManager;
} __XkWaylandPlatform;

#define XK_PLATFORM __XkWaylandPlatform wayland

#ifdef __cplusplus
}
#endif // __cplusplus

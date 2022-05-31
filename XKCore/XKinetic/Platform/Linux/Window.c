#include "XKinetic/Platform/Internal.h"

#if defined(XK_PLATFORM_LINUX)

#include <string.h>
#include "xdg-shell-client-protocol.h"
#include "xdg-decoration-client-protocol.h"
#include "wl-viewporter-client-protocol.h"
#include "XKinetic/Platform/Linux/Internal.h"

#define XK_WL_DECORATION_WIDTH 4
#define XK_WL_DECORATION_TOP 24
#define XK_WL_DECORATION_VERTICAL (XK_WL_DECORATION_TOP + XK_WL_DECORATION_WIDTH)
#define XK_WL_DECORATION_HORIZONTAL (2 * XK_WL_DECORATION_WIDTH)

static XkBool32 __xkXdgCreateSurface(XkWindow);
//static XkBool32 __xkXdgCreateDecorations(XkWindow);

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

static void __xkXdgToplevelHandleConfigure(void* data, struct xdg_toplevel* xdgToplevel, int32_t width, int32_t height, struct wl_array* states) {
	XkWindow window = (XkWindow)data;

  XkBool32 maximized = XK_FALSE;
  XkBool32 fullscreen = XK_FALSE;
  XkBool32 activated = XK_FALSE;

	uint32_t* state;
	wl_array_for_each(state, states) {
		switch (*state) {
			case XDG_TOPLEVEL_STATE_MAXIMIZED: maximized = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_FULLSCREEN: fullscreen = XK_TRUE; break;
      case XDG_TOPLEVEL_STATE_RESIZING: break;
      case XDG_TOPLEVEL_STATE_ACTIVATED: activated = XK_TRUE; break;
    }
  }

	if(width != 0 && height != 0) {
		__xkInputWindowSize(window, (XkSize)width, (XkSize)height);
		__xkSetWindowSize(window, (XkSize)width, (XkSize)height);
	}

	if(window->fullscreen) {
		if(!activated || !fullscreen)	{
			__xkShowWindow(window, XK_WINDOW_SHOW_MINIMIZED);
			window->fullscreen = XK_FALSE;
		}
	}

  if(fullscreen && activated)
		window->fullscreen = XK_TRUE;
}

static void __xkXdgToplevelHandleClose(void* data, struct xdg_toplevel* xdgToplevel) {
	XkWindow window = (XkWindow)data;
	__xkInputWindowClose(window);
}

static const struct xdg_toplevel_listener _xkXdgToplevelListener = {
  __xkXdgToplevelHandleConfigure,
  __xkXdgToplevelHandleClose
};

/*static void __xkWlCreateDecoration(__XkLinuxWindowDecoration* decoration, struct wl_surface* wlParent, struct wl_buffer* wlBuffer, XkBool32 opaque, XkInt32 x, XkInt32 y, XkInt32 width, XkInt32 height) {
  decoration->wlSurface = wl_compositor_create_surface(_xkPlatform.handle.wlCompositor);
  decoration->wlSubsurface = wl_subcompositor_get_subsurface(_xkPlatform.handle.wlSubcompositor, decoration->wlSurface, wlParent);
  wl_subsurface_set_position(decoration->wlSubsurface, (int)x, (int)y);
  decoration->wlViewport = wp_viewporter_get_viewport(_xkPlatform.handle.wlViewporter, decoration->wlSurface);
  wp_viewport_set_destination(decoration->wlViewport, (int)width, (int)height);
  wl_surface_attach(decoration->wlSurface, wlBuffer, 0, 0);

  if(opaque) {
		struct wl_region* wlRegion = wl_compositor_create_region(_xkPlatform.handle.wlCompositor);
    wl_region_add(wlRegion, 0, 0, width, height);
    wl_surface_set_opaque_region(decoration->wlSurface, wlRegion);
    wl_surface_commit(decoration->wlSurface);
    wl_region_destroy(wlRegion);
  } else {
		wl_surface_commit(decoration->wlSurface);
	}
}

static struct wl_buffer* __xkWlCreateShmBuffer(const XkWindowIcon* image) {
	struct wl_shm_pool* wlPool;
  struct wl_buffer* wlBuffer;
  XkInt32 stride = image->width * 4;
  XkInt32 length = image->width * image->height * 4;
  XkHandle data;

  const int fd = __xkCreateAnonymousFile(length);
  if(fd < 0) {
		__xkErrorHandle("Failed to create buffer file");
    return(NULL);
  }

  data = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(data == MAP_FAILED) {
    __xkErrorHandle("Failed to map file");
    close(fd);
    return(NULL);
  }

  wlPool = wl_shm_create_pool(_xkPlatform.handle.wlShm, fd, length);

  close(fd);
  XkUInt8* source = (XkUInt8*) image->pixels;
  XkUInt8* target = data;
	for(unsigned long i = 0;  i < image->width * image->height;  i++, source += 4) {
		unsigned int alpha = source[3];

    *target++ = (XkUInt8) ((source[2] * alpha) / 255);
    *target++ = (XkUInt8) ((source[1] * alpha) / 255);
    *target++ = (XkUInt8) ((source[0] * alpha) / 255);
    *target++ = (XkUInt8) alpha;
  }

  wlBuffer = wl_shm_pool_create_buffer(wlPool, 0, image->width, image->height, stride, WL_SHM_FORMAT_ARGB8888);
  munmap(data, length);
  wl_shm_pool_destroy(wlPool);

  return buffer;
}

static void __xkWlCreateDecorations(XkWindow window) {
	XkUInt8 data[] = {224, 224, 224, 255};
  const XkWindowIcon image = {1, 1, data};
  XkBool32 opaque = (data[3] == 255);

  if(!_xkPlatform.handle.wlViewporter || !window->decorated || window->handle.decorations.serverSide)
    return;

  if(!window->handle.decorations.wlBuffer)
		window->handle.decorations.wlBuffer = __xkWlCreateShmBuffer(&image);
  if(!window->handle.decorations.wlBuffer)
    return;

  __xkWlCreateDecoration(&window->handle.decorations.top, window->handle.wlSurface, window->handle.decorations.wlBuffer, opaque, 0, -XK_WL_DECORATION_TOP, window->width, XK_WL_DECORATION_TOP);
  __xkWlCreateDecoration(&window->handle.decorations.left, window->handle.wlSurface, window->handle.decorations.wlBuffer, opaque, -XK_WL_DECORATION_WIDTH, -XK_WL_DECORATION_TOP,XK_WL_DECORATION_WIDTH, window->height + XK_WL_DECORATION_TOP);
  __xkWlCreateDecoration(&window->handle.decorations.right, window->handle.wlSurface, window->handle.decorations.wlBuffer, opaque, window->width, -XK_WL_DECORATION_TOP, XK_WL_DECORATION_WIDTH, window->height + XK_WL_DECORATION_TOP);
  __xkWlCreateDecoration(&window->handle.decorations.bottom, window->handle.wlSurface, window->handle.decorations.wlBuffer, opaque, -XK_WL_DECORATION_WIDTH, window->height, window->width + XK_WL_DECORATION_HORIZONTAL, XK_WL_DECORATION_WIDTH);
}

static void __xkXdgDecorationHandleConfigure(void* data, struct zxdg_toplevel_decoration_v1* xdgDecoration, uint32_t mode) {
  XkWindow window = (XkWindow)data;

  window->handle.decorations.serverSide = (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);

  if(!window->handle.decorations.serverSide)
		__xkXdgCreateDecorations(window);
}

static const struct zxdg_toplevel_decoration_v1_listener __xkXdgDecorationListener = {
  __xkXdgDecorationHandleConfigure,
};*/

static void __xkWlRegistryGlobal(void* data, struct wl_registry* wlRegistry, uint32_t name, const char* interface, uint32_t version) {
  if(strcmp(interface, wl_compositor_interface.name) == 0) {
		// Wayland compositor.
		_xkPlatform.handle.wlCompositor = wl_registry_bind(wlRegistry, name, &wl_compositor_interface, version);
	} else if(strcmp(interface, wl_subcompositor_interface.name) == 0) {
		// Wayland subcompositor.
		_xkPlatform.handle.wlSubcompositor = wl_registry_bind(wlRegistry, name, &wl_subcompositor_interface, version);
	} else if(strcmp(interface, "wl_shm") == 0) { 
		// Wayland shared memory.
		_xkPlatform.handle.wlShm = wl_registry_bind(wlRegistry, name, &wl_shm_interface, 1);
  } else if(strcmp(interface, "wl_seat") == 0) {
		// Wayland seat.
    _xkPlatform.handle.wlSeat = wl_registry_bind(wlRegistry, name, &wl_seat_interface, version);
	} else if(strcmp(interface, wl_output_interface.name) == 0) {
		// Wayland output.
			_xkPlatform.handle.wlOutput = wl_registry_bind(wlRegistry, name, &wl_output_interface, 2);
  } else if(strcmp(interface, xdg_wm_base_interface.name) == 0) {
		// Xdg Base.
    _xkPlatform.handle.xdgBase = wl_registry_bind(wlRegistry, name, &xdg_wm_base_interface, 1);
		xdg_wm_base_add_listener(_xkPlatform.handle.xdgBase, &_xkXdgWmBaseListener, NULL);
  } else if(strcmp(interface, "zxdg_decoration_manager_v1") == 0) {
		// Xdg decoration manager.
    _xkPlatform.handle.xdgDecorationManager = wl_registry_bind(wlRegistry, name, &zxdg_decoration_manager_v1_interface, 1);
  } else if(strcmp(interface, "wp_viewporter") == 0) {
		// Wp viewporter.
    _xkPlatform.handle.wlViewporter = wl_registry_bind(wlRegistry, name, &wp_viewporter_interface, 1);
  }
}

static void __xkWlRegistryGlobalRemove(void* data, struct wl_registry* wlRegistry, uint32_t name) {
	//TODO: implementation
}

static const struct wl_registry_listener _xkWlRegistryListener = {
	.global = __xkWlRegistryGlobal,
  .global_remove = __xkWlRegistryGlobalRemove,
};

static void __xkWlSurfaceHandleEnter(void* data, struct wl_surface* pSurface, struct wl_output* pOutput) {
	//TODO: implementation
}

static void __xkWlSurfaceHandleLeave(void* data, struct wl_surface* pSurface, struct wl_output* pOutput) {
	//TODO: implementation
}

static const struct wl_surface_listener _xkWlSurfaceListener = {
  __xkWlSurfaceHandleEnter,
  __xkWlSurfaceHandleLeave
};

XkResult __xkWindowInitialize(void) {
	XkResult result = XK_SUCCESS;

	// Connect Wayland server.
	_xkPlatform.handle.wlDisplay = wl_display_connect(NULL);
	if(!_xkPlatform.handle.wlDisplay) {
		__xkErrorHandle("Failed to connect Wayland display");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Get Wayland display registry.
	_xkPlatform.handle.wlRegistry = wl_display_get_registry(_xkPlatform.handle.wlDisplay);
	if(!_xkPlatform.handle.wlRegistry) {
		__xkErrorHandle("Failed to get Wayland display registry");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Add Wayland display registry listener.
  wl_registry_add_listener(_xkPlatform.handle.wlRegistry, &_xkWlRegistryListener, NULL);

	// Sync so we got all registry objects.
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);

	// Check Wayland compositor register object.
	if(!_xkPlatform.handle.wlCompositor) {
		__xkErrorHandle("Failed to create Wayland compositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check Wayland subcompositor register object.
	if(!_xkPlatform.handle.wlSubcompositor) {
		__xkErrorHandle("Failed to create Wayland subcompositor");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Check Xdg base register object.
	if(!_xkPlatform.handle.xdgBase) {
		__xkErrorHandle("Failed to create Wayland XDG base");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Create Wayland compositor surface.
  _xkPlatform.handle.wlSurface = wl_compositor_create_surface(_xkPlatform.handle.wlCompositor);
	if(!_xkPlatform.handle.wlSurface) {
		__xkErrorHandle("Failed to create Wayland compositor surface");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

_catch:
	return(result);
}

void __xkWindowTerminate(void) {
	xdg_wm_base_destroy(_xkPlatform.handle.xdgBase);
  wl_registry_destroy(_xkPlatform.handle.wlRegistry);
  wl_display_flush(_xkPlatform.handle.wlDisplay);
	wl_display_disconnect(_xkPlatform.handle.wlDisplay);
}

XkResult __xkCreateWindow(XkWindow window, const XkChar8* title, const XkSize width, const XkSize height, const XkWindowHint hint) {
	XkResult result = XK_SUCCESS;

	window->width = width;
	window->height = height;
	window->xPos = 0;
	window->yPos = 0;

	window->maximized = XK_FALSE;
	window->minimized = XK_FALSE;

	if(hint & XK_WINDOW_DECORATED_BIT) window->decorated = XK_TRUE;
	if(hint & XK_WINDOW_RESIZABLE_BIT) window->resizable = XK_TRUE;
	if(hint & XK_WINDOW_FLOATING_BIT) window->floating = XK_TRUE;

	// Create Wayland window surface.
	window->handle.wlSurface = wl_compositor_create_surface(_xkPlatform.handle.wlCompositor);
  if(!window->handle.wlSurface) {
		__xkErrorHandle("Failed to create Wayland surface");
		result = XK_ERROR_UNKNOWN;
		goto _catch;
	}

	// Add Wayland surface listener.
  wl_surface_add_listener(window->handle.wlSurface, &_xkWlSurfaceListener, window);

	// Set Wayland surface user data.
	wl_surface_set_user_data(window->handle.wlSurface, window);

_catch:
	return(result);
}

void __xkDestroyWindow(XkWindow window) {
	//TODO: implementation
}

void __xkShowWindow(XkWindow window, const XkWindowShow show) {
	//TODO: implementation
	if(!window->handle.xdgToplevel) {
		__xkXdgCreateSurface(window);
	}

	switch(show) {
		case XK_WINDOW_SHOW_DEFAULT:
			//TODO: implementation
			break;

		case XK_WINDOW_SHOW_MAXIMIZED:
			xdg_toplevel_set_maximized(window->handle.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_MINIMIZED:
			xdg_toplevel_set_minimized(window->handle.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_FULLSCREEN:
      xdg_toplevel_set_fullscreen(window->handle.xdgToplevel, window->handle.wlOutput);
			break;

		case XK_WINDOW_HIDE:
      wl_surface_attach(window->handle.wlSurface, NULL, 0, 0);
      wl_surface_commit(window->handle.wlSurface);
			break;
	}

	wl_surface_commit(window->handle.wlSurface);
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);
}

void __xkFocusWindow(XkWindow window) {
	// A Wayland client can not focus.
	__xkErrorHandle("Wayland platform doesn't support setting the input focus");
}

void __xkSetWindowSize(XkWindow window, const XkSize width, const XkSize height) {
	//TODO: implementation
}

void __xkGetWindowSize(XkWindow window, XkSize* const pWidth, XkSize* const pHeight) {
	if(pWidth)
		*pWidth = window->width;
  if(pHeight)
    *pHeight = window->height;
}

void __xkSetWindowSizeLimits(XkWindow window, const XkSize minWidth, const XkSize minHeight, const XkSize maxWidth, const XkSize maxHeight) {
  xdg_toplevel_set_min_size(window->handle.xdgToplevel, (int32_t)minWidth, (int32_t)minHeight);
	xdg_toplevel_set_max_size(window->handle.xdgToplevel, (int32_t)maxWidth, (int32_t)maxHeight);
	wl_surface_commit(window->handle.wlSurface);
}

void __xkSetWindowPosition(XkWindow window, const XkInt32 xPos, const XkInt32 yPos) {
	// A Wayland client can not set its position.
	__xkErrorHandle("Wayland platform doesn't support setting the input position");
}

void __xkGetWindowPosition(XkWindow window, XkInt32* const pXPos, XkInt32* const pYPos) {
  // A Wayland client is not aware of its position.
	__xkErrorHandle("Wayland platform doesn't provide the window position");
}

void __xkSetWindowTitle(XkWindow window, const XkChar8* title) {
	xdg_toplevel_set_title(window->handle.xdgToplevel, title);
}

void __xkSetWindowIcon(XkWindow window, const XkSize count, const XkWindowIcon* pIcon) {
	// A Wayland client can not set its icon
	__xkErrorHandle("Wayland platform doesn't support setting the window icon");
}

void __xkPollWindowEvents(void) {
	//while(wl_display_dispatch(_xkPlatform.handle.wlDisplay)) {
		/// TODO: implementation.
		//__xkErrorHandler("Wayland display dispatch");
	//}
}

void __xkWaitWindowEvents(void) {
	//while(wl_display_dispatch(_xkPlatform.handle.wlDisplay)) {
		//TODO: implementation
		__xkErrorHandler("Wayland display dispatch");
	//}
}

static XkBool32 __xkXdgCreateSurface(XkWindow window) {
	// Get Xdg surface from Wayland surface.
	window->handle.xdgSurface = xdg_wm_base_get_xdg_surface(_xkPlatform.handle.xdgBase, window->handle.wlSurface);
	if(!window->handle.xdgSurface) {
		__xkErrorHandle("Failed to create Xdg surface");
		goto _catch;
  }

	// Add Xdg surface listener.
  xdg_surface_add_listener(window->handle.xdgSurface, &_xkXdgSurfaceListener, window);

	// Get Xdg toplevel.
	window->handle.xdgToplevel = xdg_surface_get_toplevel(window->handle.xdgSurface);
  if(!window->handle.xdgToplevel) {
		__xkErrorHandle("Failed to create Xdg toplevel");
		goto _catch;
  }

	// Add Xdg toplevel listener.
  xdg_toplevel_add_listener(window->handle.xdgToplevel, &_xkXdgToplevelListener, window);

	// Set Xdg window title.
  xdg_toplevel_set_title(window->handle.xdgToplevel, "Test");

	// Commit pending Wayland surface state.
  wl_surface_commit(window->handle.wlSurface);
  wl_display_roundtrip(_xkPlatform.handle.wlDisplay);

	return(XK_FALSE);

_catch:
	return(XK_TRUE);
}

/*static XkBool32 __xkXdgCreateDecorations(XkWindow window) { 
	window->handle.xdgDecoration = zxdg_decoration_manager_v1_get_toplevel_decoration(_xkPlatform.handle.xdgDecorationManager, window->handle.xdgToplevel);
  zxdg_toplevel_decoration_v1_add_listener(window->handle.xdgDecoration, &__xkXdgDecorationListener, window);
  zxdg_toplevel_decoration_v1_set_mode(window->handle.xdgDecoration, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);

	return(XK_FALSE);

_catch:
	return(XK_TRUE);
}*/

#endif // XK_PLATFORM_LINUX

#include "XKinetic/Platform/Internal.h"
#include "XKinetic/Platform/Window.h"
#include "XKinetic/Platform/Memory.h"

#if defined(XK_LINUX)

#define _GNU_SOURCE
#define __USE_GNU
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

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

struct wl_buffer* __xkWaylandCreateShmBuffer(const int, const int, const int, const int);
static void __xkWaylandSetContentAreaOpaque(XkWindow);
static void __xkWaylandResizeWindow(XkWindow);

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

static void __xkWaylandRegistryGlobal(void* data, struct wl_registry* wlRegistry, uint32_t name, const char* interface, uint32_t version) {
  if(xkCompareString((XkString)interface, "wl_compositor") == 1) {
		// Wayland compositor.
		_xkPlatform.wayland.wlCompositor = wl_registry_bind(wlRegistry, name, &wl_compositor_interface, version);
	} else if(xkCompareString((XkString)interface, "wl_shm") == 1) {
		// Wayland shared memory.
		_xkPlatform.wayland.wlShm = wl_registry_bind(wlRegistry, name, &wl_shm_interface, version);
	} else if(xkCompareString((XkString)interface, "wl_output") == 1) {
		// Wayland output.
			_xkPlatform.wayland.wlOutput = wl_registry_bind(wlRegistry, name, &wl_output_interface, version);
  } else if(xkCompareString((XkString)interface, "xdg_wm_base") == 1) {
		// XDG Base.
    _xkPlatform.wayland.xdgBase = wl_registry_bind(wlRegistry, name, &xdg_wm_base_interface, version);
		xdg_wm_base_add_listener(_xkPlatform.wayland.xdgBase, &_xkXDGWmBaseListener, NULL);
  } else if(xkCompareString((XkString)interface, "zxdg_decoration_manager_v1") == 1) {
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
	// Destroy Wayland output.
	if(_xkPlatform.wayland.wlOutput) {
		wl_output_destroy(_xkPlatform.wayland.wlOutput);
	}

	// Destroy Wayland shared memory.
	if(_xkPlatform.wayland.wlShm) {
		wl_shm_destroy(_xkPlatform.wayland.wlShm);
	}

	// Destroy Wayland compositor.
  if(_xkPlatform.wayland.wlCompositor){
		wl_compositor_destroy(_xkPlatform.wayland.wlCompositor);
  }
	
	// Destroy XDG base.
 	if(_xkPlatform.wayland.xdgBase) {
		xdg_wm_base_destroy(_xkPlatform.wayland.xdgBase);
	}

	// Destroy XDG decoration manager.
 	if(_xkPlatform.wayland.xdgDecorationManager){
		zxdg_decoration_manager_v1_destroy(_xkPlatform.wayland.xdgDecorationManager);
 	}

	// Destroy Wayland register.
	if(_xkPlatform.wayland.wlRegistry) {
  	wl_registry_destroy(_xkPlatform.wayland.wlRegistry);
	}

	// Destroy Wayland display.
	if(_xkPlatform.wayland.wlDisplay) {
  	wl_display_flush(_xkPlatform.wayland.wlDisplay);
		wl_display_disconnect(_xkPlatform.wayland.wlDisplay);
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

	if(__xkXDGCreateSurface(window)) {
		result = XK_ERROR_UNKNOWN;
		goto _catch;		
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

			xdg_toplevel_unset_maximized(window->wayland.xdgToplevel);
			xdg_toplevel_unset_fullscreen(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_MAXIMIZED:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			// Minimize Wayland window.
			xdg_toplevel_set_maximized(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_MINIMIZED:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			// Maximize Wayland window.
			xdg_toplevel_set_minimized(window->wayland.xdgToplevel);
			break;

		case XK_WINDOW_SHOW_FULLSCREEN:
			if(!window->wayland.xdgToplevel) {
				__xkXDGCreateSurface(window);
			}

			// Fullscreen Wayland window.
			xdg_toplevel_set_fullscreen(window->wayland.xdgToplevel, _xkPlatform.wayland.wlOutput);
			break;

		case XK_WINDOW_HIDE:
			// Destroy XDG components.
			if(window->wayland.xdgToplevel) {
				__xkXDGDestorySurface(window);
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
		window->wayland.xdgDecoration = zxdg_decoration_manager_v1_get_toplevel_decoration(_xkPlatform.wayland.xdgDecorationManager, window->wayland.xdgToplevel);
  	zxdg_toplevel_decoration_v1_set_mode(window->wayland.xdgDecoration, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
	}

_catch:
	return(result);
}

static void __xkXDGDestorySurface(XkWindow window) {
	// Destroy XDG decoration.
	if(window->wayland.xdgDecoration) {
		zxdg_toplevel_decoration_v1_destroy(window->wayland.xdgDecoration);

		window->wayland.xdgDecoration = NULL;
	}

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
	//__xkWaylandSetContentAreaOpaque(window);
}

#endif // XK_LINUX

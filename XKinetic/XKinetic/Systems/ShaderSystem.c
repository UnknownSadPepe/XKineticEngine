/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/ShaderSystem.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_SHADER_SYSTEM_ARRAY_SIZE 4

/* ########## TYPES SECTION ########## */
struct XkShaderSystem_T {
  XkPoolAllocator shaders;

  XkShaderId shaderId;
};

struct XkShader_T {
  XkShaderId id;
  /// TODO: Implementation.
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateShaderSystem(XkShaderSystem* pSystem) {
	xkAssert(pSystem)

  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkShaderSystem_T));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkShaderSystem system = *pSystem;

  system->shaderId = 1;

  result = xkCreatePoolAllocator(&system->shaders, XK_SHADER_SYSTEM_ARRAY_SIZE, struct XkShader_T);
  if(result != XK_SUCCESS) {
		goto _free;
	}

  /// TODO: Implementation.

_catch:
  return(result);

_free:
	if(system) {
		xkFreeMemory(system);
	}

	goto _catch;
}

void xkDestroyShaderSystem(XkShaderSystem system) {
	xkAssert(system);
  /// TODO: Implementation.
  xkDestroyPoolAllocator(system->shaders);
	xkFreeMemory(system);
}

XkShaderId xkCreateShader(XkShaderSystem system, const XkShaderConfig* const pConfig) {
	xkAssert(system);
	xkAssert(pConfig);

  /// TODO: Implementation.
  XkShaderId id = 0;

  id = ++system->shaderId;

_catch:
  return(id);
}

void xkDestroyShader(XkShaderSystem system, XkShaderId id) {
	xkAssert(system);
  /// TODO: Implementation.
}

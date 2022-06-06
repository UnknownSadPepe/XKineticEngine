#include "XKinetic/Systems/ShaderSystem.h"

#define XK_SHADER_SYSTEM_ARRAY_SIZE 4

struct XkShaderSystem {
  XkDynamicArray shaders;
};

XkResult xkCreateShaderSystem(XkShaderSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkShaderSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkShaderSystem system = *pSystem;

  result = xkCreateDynamicArrayCapacity(&system->shaders, XK_SHADER_SYSTEM_ARRAY_SIZE, XkShader);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: implementation.

_catch:
  return(result);
}

void xkDestroyShaderSystem(XkShaderSystem system) {
  /// TODO: implementation.
  xkDestroyDynamicArray(system->shaders);
}

XkShaderID xkCreateShader(XkShaderSystem system, XkShaderConfig* const pConfig) {
  /// TODO: implementation.
  return(-1);
}

void xkDestroyShader(XkShaderSystem system, XkShaderID id) {
  /// TODO: implementation.
}

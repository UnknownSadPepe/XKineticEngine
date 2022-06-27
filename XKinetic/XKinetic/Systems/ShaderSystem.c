#include "XKinetic/Core/PoolAllocator.h"
#include "XKinetic/Systems/ShaderSystem.h"

#define XK_SHADER_SYSTEM_ARRAY_SIZE 4

struct XkShaderSystem {
  XkPoolAllocator shaders;

  XkShaderID shaderID;
};

struct XkShader {
  XkShaderID ID;
  /// TODO: Implementation.
};

XkResult xkCreateShaderSystem(XkShaderSystem* pSystem) {
  XkResult result = XK_SUCCESS;

  *pSystem = xkAllocateMemory(sizeof(struct XkShaderSystem));
  if(!(*pSystem)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

  XkShaderSystem system = *pSystem;

  system->shaderID = 1;

  result = xkCreatePoolAllocator(&system->shaders, XK_SHADER_SYSTEM_ARRAY_SIZE, struct XkShader);
  if(result != XK_SUCCESS) goto _catch;

  /// TODO: Implementation.

_catch:
  return(result);
}

void xkDestroyShaderSystem(XkShaderSystem system) {
  /// TODO: Implementation.
  xkDestroyPoolAllocator(system->shaders);
}

XkShaderID xkCreateShader(XkShaderSystem system, XkShaderConfig* const pConfig) {
  /// TODO: Implementation.
  XkShaderID id = 0;

  id = ++system->shaderID;

_catch:
  return(id);
}

void xkDestroyShader(XkShaderSystem system, XkShaderID id) {
  /// TODO: Implementation.
}

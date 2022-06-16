#include "XKinetic/Scene/Scene.h"

#define XK_SCENE_NAME_MAX_SIZE 128

struct XkScene {
    XkChar name[XK_SCENE_NAME_MAX_SIZE];
};

XkResult xkCreateScene(XkScene* pScene) {
  XkResult result = XK_SUCCESS;

  *pScene = xkAllocateMemory(sizeof(struct XkScene));
  if(!(*pScene)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

_catch:
  return(result);
}

void xkDestroyScene(XkScene scene) {
  xkFreeMemory(scene);
}

void xkBeginScene(XkScene scene) {
  /*TODO: implement*/
}

void xkEndScene(XkScene scene) {
  /*TODO: implement*/
}

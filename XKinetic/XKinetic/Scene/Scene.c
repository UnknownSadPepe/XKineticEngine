#include "XKinetic/Scene/Scene.h"

struct XkScene {

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

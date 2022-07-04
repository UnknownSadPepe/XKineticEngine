/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Scene/Scene.h"
#include "XKinetic/Core/Assert.h"

/* ########## MACROS SECTION ########## */
#define XK_SCENE_NAME_MAX_SIZE 128

/* ########## TYPES SECTION ########## */
struct XkScene_T {
  XkChar name[XK_SCENE_NAME_MAX_SIZE];
};

/* ########## FUNCTIONS SECTION ########## */
XkResult xkCreateScene(XkScene* pScene) {
	xkAssert(pScene);

  XkResult result = XK_SUCCESS;

  *pScene = xkAllocateMemory(sizeof(struct XkScene_T));
  if(!(*pScene)) {
    result = XK_ERROR_BAD_ALLOCATE;
    goto _catch;
  }

_catch:
  return(result);
}

void xkDestroyScene(XkScene scene) {
	xkAssert(scene);

  xkFreeMemory(scene);
}

void xkBeginScene(XkScene scene) {
	xkAssert(scene);
  /*TODO: implement*/
}

void xkEndScene(XkScene scene) {
	xkAssert(scene);
  /*TODO: implement*/
}

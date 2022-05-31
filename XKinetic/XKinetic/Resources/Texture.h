#pragma once

#include "XKinetic/XKinetic.h"
#include "XKinetic/Core/Minimal.h"

typedef struct {
  XkSize width;
  XkSize height;
  XkHandle pixels;
} XkTextureConfig;

typedef struct XkTexture* XkTexture;

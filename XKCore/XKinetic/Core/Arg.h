#pragma once

#include "XKinetic/XKCore.h"

typedef __builtin_va_list XkArgs;
#define xkStartArgs(args, param) __builtin_va_start(args, param)
#define xkEndArgs(args) __builtin_va_end(args)
#define xkNextArgs(args, type) __builtin_va_arg(args, type)

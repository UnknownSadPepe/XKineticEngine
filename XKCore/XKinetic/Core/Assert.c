#include "XKinetic/Core/Assert.h"
#include "XKinetic/Core/Log.h"

void __xkAssertion(const XkChar8* expr, const XkChar8* file, const XkInt32 line) {
	xkLogFatal("Assertion failure: %s file: %s line: %d", expr, file, line);
}

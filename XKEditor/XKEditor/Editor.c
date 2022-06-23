#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"

#include "XKinetic/Math/Math.h"
#include "XKinetic/Math/Vec2.h"
#include "XKinetic/Math/Vec3.h"
#include "XKinetic/Math/Vec4.h"
#include "XKinetic/Math/Mat2.h"
#include "XKinetic/Math/Mat3.h"
#include "XKinetic/Math/Mat4.h"

struct XkApplication {
	XkApplicationConfig config;
};

XkApplication _xkApplication;

XkResult xkCreateApplication(const XkSize argc, const XkString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKEditor";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;

	result = xkInitializeLog();
	if(result != XK_SUCCESS) goto _catch;

	{
		XkVec2 vec2_1 = {0};
		vec2_1.x = 666.0f;
		vec2_1.y = 555.0f;

		XkVec2 vec2_2 = {0};
		vec2_2.x = 333.0f;
		vec2_2.y = 222.0f;

		vec2_2 = xkVec2Add(vec2_1, vec2_2);

		xkLogInfo("vec2(%ld) x: %f; y: %f", sizeof(XkVec2) * 8, vec2_2.x, vec2_2.y);
	}

	{
		XkDVec2 vec2_1 = {0};
		vec2_1.x = 666.0;
		vec2_1.y = 555.0;

		XkDVec2 vec2_2 = {0};
		vec2_2.x = 333.0;
		vec2_2.y = 222.0;

		vec2_2 = xkDVec2Add(vec2_1, vec2_2);

		xkLogInfo("dvec2(%ld) x: %f; y: %f", sizeof(XkDVec2) * 8, vec2_2.x, vec2_2.y);
	}

	{
		XkDVec3 vec3_1 = {0};
		vec3_1.x = 666.0;
		vec3_1.y = 555.0;
		vec3_1.z = 444.0;

		XkDVec3 vec3_2 = {0};
		vec3_2.x = 333.0;
		vec3_2.y = 222.0;
		vec3_2.z = 111.0;

		vec3_2 = xkDVec3Add(vec3_1, vec3_2);

		xkLogInfo("dvec2(%ld) x: %f; y: %f; z: %f", sizeof(XkDVec3) * 8, vec3_2.x, vec3_2.y, vec3_2.z);
	}

_catch:
	return(result);
}

void xkDestroyApplication(void) {
	xkTerminateLog();
}

void xkUpdateApplication(void) {

}

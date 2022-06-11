#include "XKinetic/Core/Minimal.h"
#include "XKinetic/Platform/File.h"
#include "XKinetic/Platform/Console.h"
#include "XKinetic/Application.h"

#include "XKinetic/Resources/Loaders/ModelLoader.h"
#include "XKinetic/Resources/Loaders/ShaderLoader.h"
#include "XKinetic/Resources/Loaders/ImageLoader.h"

#include "XKinetic/Systems/ModelSystem.h"
#include "XKinetic/Systems/ShaderSystem.h"
#include "XKinetic/Systems/TextureSystem.h"


struct XkApplication {
	XkApplicationConfig config;

	XkModelLoader modelLoader;
	XkShaderLoader shaderLoader;
	XkImageLoader imageLoader;

	XkModelSystem modelSystem;
	XkShaderSystem shaderSystem;
	XkTextureSystem textureSystem;
};

XkApplication _xkApplication;

XkResult xkCreateApplication(const XkSize argc, const XkWString* argv) {
	XkResult result = XK_SUCCESS;

	_xkApplication.config.name = "XKEditor";
	_xkApplication.config.version.major = 0;
	_xkApplication.config.version.minor = 0;
	_xkApplication.config.version.patch = 1;

	result = xkLogInitialize();
	if(result != XK_SUCCESS) goto _catch;
/*
	// Create shader loader.
	result = xkCreateShaderLoader(&_xkApplication.shaderLoader, "resources/shaders/");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create shader loader");
		goto _catch;
	}

	// Create shader system.
	result = xkCreateShaderSystem(&_xkApplication.shaderSystem);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to initialize shader system");
		goto _catch;			
	}

	// Load shader.
	XkShaderConfig shaderConfig;
	result = xkLoadShader(_xkApplication.shaderLoader, &shaderConfig, "shader.spv");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load shader");
		goto _catch;	
	}

	// Create shader.
	XkShaderID shaderID = xkCreateShader(_xkApplication.shaderSystem, &shaderConfig);
	if(shaderID == 0) {
		result = XK_ERROR_RESOURCE_NOT_CREATE;
		xkLogError("Failed to create shader");
		goto _catch;			
	}

	// Destroy shader.
	xkDestroyShader(_xkApplication.shaderSystem, shaderID);

	// Unload shader.
	xkUnloadShader(_xkApplication.shaderLoader, &shaderConfig);	

	// Create Model loader.
	result = xkCreateModelLoader(&_xkApplication.modelLoader, "resources/models/");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create model loader");
		goto _catch;
	}

	// Create model system.
	result = xkCreateModelSystem(&_xkApplication.modelSystem);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to initialize model system");
		goto _catch;			
	}

	// Load model.
	XkModelConfig modelConfig;
	result = xkLoadModel(_xkApplication.modelLoader, &modelConfig, "model.gltf");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load model");
		goto _catch;	
	}

	// Create model.
	XkModelID modelID = xkCreateModel(_xkApplication.modelSystem, &modelConfig);
	if(modelID == 0) {
		result = XK_ERROR_RESOURCE_NOT_CREATE;
		xkLogError("Failed to create model");
		goto _catch;			
	}

	// Destroy model.
	xkDestroyModel(_xkApplication.modelSystem, modelID);

	// Unload model.
	xkUnloadModel(_xkApplication.modelLoader, &modelConfig);

	// Create image loader.
	result = xkCreateImageLoader(&_xkApplication.imageLoader, "resources/textures/");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create image loader");
		goto _catch;
	}

	// Create texture system.
	result = xkCreateTextureSystem(&_xkApplication.textureSystem);
	if(result != XK_SUCCESS) {
		xkLogError("Failed to create texture system");
		goto _catch;			
	}

	// Load texture.
	XkImageConfig textureConfig;
	result = xkLoadTexture(_xkApplication.imageLoader, &textureConfig, "texture.png");
	if(result != XK_SUCCESS) {
		xkLogError("Failed to load texture");
		goto _catch;	
	}

	// Create texture.
	XkTextureID textureID = xkCreateTexture(_xkApplication.textureSystem, &textureConfig);
	if(textureID == 0) {
		result = XK_ERROR_RESOURCE_NOT_CREATE;
		xkLogError("Failed to create texture");
		goto _catch;			
	}

	// Destroy texture.
	xkDestroyTexture(_xkApplication.textureSystem, textureID);

	// Unload texture.
	xkUnloadTexture(_xkApplication.imageLoader, &textureConfig);
*/

	XkFreeList freelist;
	result = xkCreateFreeList(&freelist, sizeof(XkUInt32) * 16);
	if(result != XK_SUCCESS) {
		xkLogError("failed to create freelist");
		goto _catch;
	}

	xkDestroyFreeList(freelist);

_catch:
	return(result);
}

void xkDestroyApplication() {
/*
	xkDestroyTextureSystem(_xkApplication.textureSystem);
	xkDestroyShaderSystem(_xkApplication.shaderSystem);
	xkDestroyModelSystem(_xkApplication.modelSystem);

	xkDestroyImageLoader(_xkApplication.imageLoader);
	xkDestroyShaderLoader(_xkApplication.shaderLoader);
	xkDestroyModelLoader(_xkApplication.modelLoader);
*/
	xkLogTerminate();
}

void xkUpdateApplication() {
	/// TODO: implementation.
}

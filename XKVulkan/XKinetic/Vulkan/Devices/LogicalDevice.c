#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateLogicalDevice(void) {
  XkResult result = XK_SUCCESS;

  float vkQueuePriorities[1] = {1.0f};

  uint32_t vkQueueCreateInfoCount = 0;

  VkDeviceQueueCreateInfo vkQueueCreateInfos[4] = {0};

  // Template Vulkan queue families.
  uint32_t vkGraphicsQueueFamily = _xkVkContext.queueFamilyIndices.graphics;
  uint32_t vkPresentQueueFamily = _xkVkContext.queueFamilyIndices.present;
  uint32_t vkTransferQueueFamily = _xkVkContext.queueFamilyIndices.transfer;
  uint32_t vkComputeQueueFamily = _xkVkContext.queueFamilyIndices.compute;

  if(_xkVkContext.queueFamilyIndices.supportedQueues & VK_QUEUE_GRAPHICS_BIT) {
		const VkDeviceQueueCreateInfo vkGraphicsQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = vkGraphicsQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = vkQueuePriorities
    };
		vkQueueCreateInfos[vkQueueCreateInfoCount] = vkGraphicsQueueCreateInfo;

    ++vkQueueCreateInfoCount;
	} else {
		vkGraphicsQueueFamily = 0;
	}

  if(_xkVkContext.queueFamilyIndices.supportPresentQueue && vkPresentQueueFamily != vkGraphicsQueueFamily) {
    const VkDeviceQueueCreateInfo vkPresentQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = vkPresentQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = vkQueuePriorities
    };
		vkQueueCreateInfos[vkQueueCreateInfoCount] = vkPresentQueueCreateInfo;

    ++vkQueueCreateInfoCount;    
  } else {
 		vkPresentQueueFamily = 0;   
  }

	if(_xkVkContext.queueFamilyIndices.supportedQueues & VK_QUEUE_TRANSFER_BIT && vkTransferQueueFamily != vkGraphicsQueueFamily && vkTransferQueueFamily != vkPresentQueueFamily) {
		const VkDeviceQueueCreateInfo vkTransferQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = vkComputeQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = vkQueuePriorities
    };
		vkQueueCreateInfos[vkQueueCreateInfoCount] = vkTransferQueueCreateInfo;

    ++vkQueueCreateInfoCount;
	} else {
		vkTransferQueueFamily = vkGraphicsQueueFamily;
	}

	if(_xkVkContext.queueFamilyIndices.supportedQueues & VK_QUEUE_COMPUTE_BIT && vkComputeQueueFamily != vkGraphicsQueueFamily && vkComputeQueueFamily != vkPresentQueueFamily && vkComputeQueueFamily != vkTransferQueueFamily) {
		const VkDeviceQueueCreateInfo vkComputeQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = vkComputeQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = vkQueuePriorities
    };
		vkQueueCreateInfos[vkQueueCreateInfoCount] = vkComputeQueueCreateInfo;

    ++vkQueueCreateInfoCount;
	} else {
		vkComputeQueueFamily = vkGraphicsQueueFamily;
	}

  // Synchronize queue families.
  _xkVkContext.queueFamilyIndices.graphics = vkGraphicsQueueFamily;
  _xkVkContext.queueFamilyIndices.present = vkPresentQueueFamily;
  _xkVkContext.queueFamilyIndices.transfer = vkTransferQueueFamily;
  _xkVkContext.queueFamilyIndices.compute = vkComputeQueueFamily;

  VkPhysicalDeviceFeatures vkEnabledFeatures = {0};

	// Enable sample rate shading filtering if supported.
	if(_xkVkContext.vkDeviceFeatures.sampleRateShading) {
		vkEnabledFeatures.sampleRateShading = VK_TRUE;
  }

  // Fill mode non solid is required for wireframe display.
	if(_xkVkContext.vkDeviceFeatures.fillModeNonSolid) {
		vkEnabledFeatures.fillModeNonSolid = VK_TRUE;
  }

	// Wide lines must be present for line width > 1.0f.
	if(_xkVkContext.vkDeviceFeatures.wideLines) {
	  vkEnabledFeatures.wideLines = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support wireframe pipelines");
	}

  // Enable sample anisotropy if supported.
	if(_xkVkContext.vkDeviceFeatures.samplerAnisotropy) {
		vkEnabledFeatures.samplerAnisotropy = VK_TRUE;
  } else {
		xkLogWarning("Selected Vulkan GPU does not support sampler anisotropy");
  }

  // Select texture compression.
	if (_xkVkContext.vkDeviceFeatures.textureCompressionBC) {
		vkEnabledFeatures.textureCompressionBC = VK_TRUE;
	} else if (_xkVkContext.vkDeviceFeatures.textureCompressionASTC_LDR) {
		vkEnabledFeatures.textureCompressionASTC_LDR = VK_TRUE;
	} else if (_xkVkContext.vkDeviceFeatures.textureCompressionETC2) {
		vkEnabledFeatures.textureCompressionETC2 = VK_TRUE;
  }

  // Enable vertex pipeline stores nad atomic.
	if (_xkVkContext.vkDeviceFeatures.vertexPipelineStoresAndAtomics) {
		vkEnabledFeatures.vertexPipelineStoresAndAtomics = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support vertex pipeline stores and atomics");
  }

  // Enable fragment stores nad atomic.
  if(_xkVkContext.vkDeviceFeatures.fragmentStoresAndAtomics) {
		vkEnabledFeatures.fragmentStoresAndAtomics = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support fragment stores and atomics");
  }

  // Enable shader storage extended formats.
	if(_xkVkContext.vkDeviceFeatures.shaderStorageImageExtendedFormats) {
		vkEnabledFeatures.shaderStorageImageExtendedFormats = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support shader storage extended formats");
  }

  // Enable shader storage write without format. 
	if(_xkVkContext.vkDeviceFeatures.shaderStorageImageWriteWithoutFormat) {
		vkEnabledFeatures.shaderStorageImageWriteWithoutFormat = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support shader storage write without format");
  }

  // Support geometry shaders.
	if(_xkVkContext.vkDeviceFeatures.geometryShader) {
		vkEnabledFeatures.geometryShader = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support geometry shaders");
  }

  // Support tessellation shaders.
	if(_xkVkContext.vkDeviceFeatures.tessellationShader) {
		vkEnabledFeatures.tessellationShader = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support tessellation shaders");
  }

  // Support multi viewports
	if(_xkVkContext.vkDeviceFeatures.multiViewport) {
		vkEnabledFeatures.multiViewport = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support multi viewports");
  }

  // Initialize Vulkan logical device create info.
  const VkDeviceCreateInfo vkDeviceCreateInfo = {
    .sType                      = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext                      = VK_NULL_HANDLE,
    .flags                      = 0,
    .queueCreateInfoCount       = vkQueueCreateInfoCount,
    .pQueueCreateInfos          = vkQueueCreateInfos,
    .enabledLayerCount          = _xkVkInstanceLayerCount,
    .ppEnabledLayerNames        = _xkVkInstanceLayers,
    .enabledExtensionCount      = _xkVkDeviceExtensionCount,
    .ppEnabledExtensionNames    = _xkVkDeviceExtensions,
    .pEnabledFeatures           = &vkEnabledFeatures
  };

  // Create Vulkan logical device.
  VkResult vkResult = vkCreateDevice(_xkVkContext.vkPhysicalDevice, &vkDeviceCreateInfo, VK_NULL_HANDLE, &_xkVkContext.vkLogicalDevice);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan logical device: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

  // Get Vulkan logical device queues.
  vkGetDeviceQueue(_xkVkContext.vkLogicalDevice, _xkVkContext.queueFamilyIndices.graphics, 0, &_xkVkContext.vkGraphicsQueue);
  vkGetDeviceQueue(_xkVkContext.vkLogicalDevice, _xkVkContext.queueFamilyIndices.present, 0, &_xkVkContext.vkPresentQueue);
  vkGetDeviceQueue(_xkVkContext.vkLogicalDevice, _xkVkContext.queueFamilyIndices.transfer, 0, &_xkVkContext.vkTransferQueue);
  vkGetDeviceQueue(_xkVkContext.vkLogicalDevice, _xkVkContext.queueFamilyIndices.compute, 0, &_xkVkContext.vkComputeQueue);

_catch:
  return(result);
}

void __xkVkDestroyLogicalDevice(void) {
  // Vulkan logical device wait before destroy.
  vkDeviceWaitIdle(_xkVkContext.vkLogicalDevice);

  // Destroy Vulkan logical device.
  vkDestroyDevice(_xkVkContext.vkLogicalDevice, VK_NULL_HANDLE);
}

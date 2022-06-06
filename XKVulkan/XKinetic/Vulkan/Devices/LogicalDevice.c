#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateLogicalDevice(void) {
  XkResult result = XK_SUCCESS;

  float queuePriorities[1] = {1.0f};

  uint32_t queueCreateInfoCount = 0;

  VkDeviceQueueCreateInfo vkQueueCreateInfos[4] = {0};

  // Template Vulkan queue families.
  uint32_t graphicsQueueFamily = _xkVkContext.queueFamilyIndices.graphics;
  uint32_t presentQueueFamily = _xkVkContext.queueFamilyIndices.present;
  uint32_t transferQueueFamily = _xkVkContext.queueFamilyIndices.transfer;
  uint32_t computeQueueFamily = _xkVkContext.queueFamilyIndices.compute;

  if(_xkVkContext.queueFamilyIndices.supportedQueues & VK_QUEUE_GRAPHICS_BIT) {
		const VkDeviceQueueCreateInfo vkGraphicsQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = graphicsQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = queuePriorities
    };
		vkQueueCreateInfos[queueCreateInfoCount] = vkGraphicsQueueCreateInfo;

    ++queueCreateInfoCount;
	} else {
		graphicsQueueFamily = 0;
	}

  if(_xkVkContext.queueFamilyIndices.supportPresentQueue && presentQueueFamily != graphicsQueueFamily) {
    const VkDeviceQueueCreateInfo vkPresentQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = presentQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = queuePriorities
    };
		vkQueueCreateInfos[queueCreateInfoCount] = vkPresentQueueCreateInfo;

    ++queueCreateInfoCount;    
  } else {
 		presentQueueFamily = 0;   
  }

	if(_xkVkContext.queueFamilyIndices.supportedQueues & VK_QUEUE_TRANSFER_BIT && transferQueueFamily != graphicsQueueFamily && transferQueueFamily != presentQueueFamily) {
		const VkDeviceQueueCreateInfo vkTransferQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = computeQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = queuePriorities
    };
		vkQueueCreateInfos[queueCreateInfoCount] = vkTransferQueueCreateInfo;

    ++queueCreateInfoCount;
	} else {
		transferQueueFamily = graphicsQueueFamily;
	}

	if(_xkVkContext.queueFamilyIndices.supportedQueues & VK_QUEUE_COMPUTE_BIT && computeQueueFamily != graphicsQueueFamily && computeQueueFamily != presentQueueFamily && computeQueueFamily != transferQueueFamily) {
		const VkDeviceQueueCreateInfo vkComputeQueueCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
      .pNext = VK_NULL_HANDLE,
      .flags = 0,
      .queueFamilyIndex = computeQueueFamily,
      .queueCount = 1,
      .pQueuePriorities = queuePriorities
    };
		vkQueueCreateInfos[queueCreateInfoCount] = vkComputeQueueCreateInfo;

    ++queueCreateInfoCount;
	} else {
		computeQueueFamily = graphicsQueueFamily;
	}

  // Synchronize queue families.
  _xkVkContext.queueFamilyIndices.graphics = graphicsQueueFamily;
  _xkVkContext.queueFamilyIndices.present = presentQueueFamily;
  _xkVkContext.queueFamilyIndices.transfer = transferQueueFamily;
  _xkVkContext.queueFamilyIndices.compute = computeQueueFamily;

  VkPhysicalDeviceFeatures vkEnabledDeviceFeatures = {0};

	// Enable sample rate shading filtering if supported.
	if(_xkVkContext.vkDeviceFeatures.sampleRateShading) {
		vkEnabledDeviceFeatures.sampleRateShading = VK_TRUE;
  }

  // Fill mode non solid is required for wireframe display.
	if(_xkVkContext.vkDeviceFeatures.fillModeNonSolid) {
		vkEnabledDeviceFeatures.fillModeNonSolid = VK_TRUE;
  }

	// Wide lines must be present for line width > 1.0f.
	if(_xkVkContext.vkDeviceFeatures.wideLines) {
	  vkEnabledDeviceFeatures.wideLines = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support wireframe pipelines");
	}

  // Enable sample anisotropy if supported.
	if(_xkVkContext.vkDeviceFeatures.samplerAnisotropy) {
		vkEnabledDeviceFeatures.samplerAnisotropy = VK_TRUE;
  } else {
		xkLogWarning("Selected Vulkan GPU does not support sampler anisotropy");
  }

  // Select texture compression.
	if (_xkVkContext.vkDeviceFeatures.textureCompressionBC) {
		vkEnabledDeviceFeatures.textureCompressionBC = VK_TRUE;
	} else if (_xkVkContext.vkDeviceFeatures.textureCompressionASTC_LDR) {
		vkEnabledDeviceFeatures.textureCompressionASTC_LDR = VK_TRUE;
	} else if (_xkVkContext.vkDeviceFeatures.textureCompressionETC2) {
		vkEnabledDeviceFeatures.textureCompressionETC2 = VK_TRUE;
  }

  // Enable vertex pipeline stores nad atomic.
	if (_xkVkContext.vkDeviceFeatures.vertexPipelineStoresAndAtomics) {
		vkEnabledDeviceFeatures.vertexPipelineStoresAndAtomics = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support vertex pipeline stores and atomics");
  }

  // Enable fragment stores nad atomic.
  if(_xkVkContext.vkDeviceFeatures.fragmentStoresAndAtomics) {
		vkEnabledDeviceFeatures.fragmentStoresAndAtomics = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support fragment stores and atomics");
  }

  // Enable shader storage extended formats.
	if(_xkVkContext.vkDeviceFeatures.shaderStorageImageExtendedFormats) {
		vkEnabledDeviceFeatures.shaderStorageImageExtendedFormats = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support shader storage extended formats");
  }

  // Enable shader storage write without format. 
	if(_xkVkContext.vkDeviceFeatures.shaderStorageImageWriteWithoutFormat) {
		vkEnabledDeviceFeatures.shaderStorageImageWriteWithoutFormat = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support shader storage write without format");
  }

  // Support geometry shaders.
	if(_xkVkContext.vkDeviceFeatures.geometryShader) {
		vkEnabledDeviceFeatures.geometryShader = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support geometry shaders");
  }

  // Support tessellation shaders.
	if(_xkVkContext.vkDeviceFeatures.tessellationShader) {
		vkEnabledDeviceFeatures.tessellationShader = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support tessellation shaders");
  }

  // Support multi viewports
	if(_xkVkContext.vkDeviceFeatures.multiViewport) {
		vkEnabledDeviceFeatures.multiViewport = VK_TRUE;
	} else {
		xkLogWarning("Selected Vulkan GPU does not support multi viewports");
  }

  // Initialize Vulkan logical device create info.
  const VkDeviceCreateInfo vkDeviceCreateInfo = {
    .sType                      = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext                      = VK_NULL_HANDLE,
    .flags                      = 0,
    .queueCreateInfoCount       = queueCreateInfoCount,
    .pQueueCreateInfos          = vkQueueCreateInfos,
    .enabledLayerCount          = _xkVkInstanceLayerCount,
    .ppEnabledLayerNames        = _xkVkInstanceLayers,
    .enabledExtensionCount      = _xkVkDeviceExtensionCount,
    .ppEnabledExtensionNames    = _xkVkDeviceExtensions,
    .pEnabledFeatures           = &vkEnabledDeviceFeatures
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

uint32_t __xkVkFindMemoryType(uint32_t typeFilter, const VkMemoryPropertyFlags vkRequiredProperties) {
	for(uint32_t i = 0; i < _xkVkContext.vkDeviceMemoryProperties.memoryTypeCount; i++) {
		uint32_t memoryTypeBits = 1 << i;

		if (typeFilter & memoryTypeBits && (_xkVkContext.vkDeviceMemoryProperties.memoryTypes[i].propertyFlags & vkRequiredProperties) == vkRequiredProperties) {
			return(i);
		}
	}

  return(0);
}

XkResult __xkVkBeginSingleCommands(VkCommandBuffer* pVkCommandBuffer) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan single command buffer allocate info.
  const VkCommandBufferAllocateInfo vkCommandBufferAllocateInfo = {
    .sType                = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
    .pNext                = VK_NULL_HANDLE,
    .commandPool          = _xkVkContext.vkCommandPool,
    .level                = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
    .commandBufferCount   = 1
  };

  // Allocate Vulkan single command buffer.
  VkResult vkResult = vkAllocateCommandBuffers(_xkVkContext.vkLogicalDevice, &vkCommandBufferAllocateInfo, pVkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to allocate Vulkan single command buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

  VkCommandBuffer vkCommandBuffer = *pVkCommandBuffer;

  // Initialize Vulkan command buffer begin info.
  const VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {
    .sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .pNext              = VK_NULL_HANDLE,
    .flags              = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    .pInheritanceInfo   = VK_NULL_HANDLE
  };

  // Begin Vulkan command buffer.
  vkResult = vkBeginCommandBuffer(vkCommandBuffer, &vkCommandBufferBeginInfo);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to begin Vulkan single command buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }  

_catch:
  return(result);
}

XkResult __xkVkEndSingleCommands(VkCommandBuffer vkCommandBuffer) {
  XkResult result = XK_SUCCESS;

  // End Vulkan command buffer.
  VkResult vkResult = vkEndCommandBuffer(vkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to end Vulkan single command buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }  

  // Initialize Vulkan submit info.
  const VkSubmitInfo vkSubmitInfo = {
    .sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .pNext                  = VK_NULL_HANDLE,
    .waitSemaphoreCount     = 0,
    .pWaitSemaphores        = VK_NULL_HANDLE,
    .pWaitDstStageMask      = VK_NULL_HANDLE,
    .commandBufferCount     = 1,
    .pCommandBuffers        = &vkCommandBuffer,
    .signalSemaphoreCount   = 0,
    .pSignalSemaphores      = VK_NULL_HANDLE
  };

  // Sublit Vulkan queue.
  vkResult = vkQueueSubmit(_xkVkContext.vkGraphicsQueue, 1, &vkSubmitInfo, VK_NULL_HANDLE);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to submit Vulkan queue: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }  

  // Wait idle Vulkan queue.
  vkResult = vkQueueWaitIdle(_xkVkContext.vkGraphicsQueue);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to wait idle Vulkan queue: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }  

  // Free Vulkan command buffer.
  vkFreeCommandBuffers(_xkVkContext.vkLogicalDevice, _xkVkContext.vkCommandPool, 1, &vkCommandBuffer);

_catch:
  return(result);
}


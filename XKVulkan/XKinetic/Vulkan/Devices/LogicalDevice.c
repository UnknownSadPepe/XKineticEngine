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

XkResult __xkVkCopyBuffer(VkBuffer vkDstBuffer, const VkBuffer vkSrcBuffer, const VkDeviceSize vkSize) {
  XkResult result = XK_SUCCESS;

  // Begin Vulkan single command buffer.
  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVkBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to begin Vulkan command buffer");
    goto _catch;   
  }

  // Initialize Vulkan buffer copy info.
  const VkBufferCopy vkBufferCopyInfo = {
    .srcOffset  = 0,
    .dstOffset  = 0,
    .size       = vkSize
  };

  // Copy Vulkan buffer.
  vkCmdCopyBuffer(vkSingleCommandBuffer, vkSrcBuffer, vkDstBuffer, 1, &vkBufferCopyInfo);

  // End Vulkan single command buffer.
  result = __xkVkEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to end Vulkan command buffer");
    goto _catch;   
  }

_catch:
  return(result);
}

XkResult __xkVkMapBuffer(VkDeviceMemory vkBufferMemory, const VkDeviceSize vkDeviceSize, const void* data) {
  XkResult result = XK_SUCCESS;

  void* mapped;
  // Map Vulkan buffer memory.
	VkResult vkResult = vkMapMemory(_xkVkContext.vkLogicalDevice, vkBufferMemory, 0, vkDeviceSize, 0, &mapped);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to map Vulkan buffer memory: %s", __xkVkGetErrorString(vkResult));
    goto _catch;   
  }

  // Copy data.
	xkCopyMemory((XkHandle)mapped, (XkHandle)data, (XkSize)vkDeviceSize);

  // Unmap Vulkan buffer memory.
	vkUnmapMemory(_xkVkContext.vkLogicalDevice, vkBufferMemory);

_catch:
  return(result);
}

XkResult __xkVkTransitionImageLayout(VkImage vkImage, const VkFormat vkFormat, const VkImageLayout vkOldLayout, const VkImageLayout vkNewLayout, const uint32_t mipLevels) {
  XkResult result = XK_SUCCESS;

  // Begin Vulkan single command buffer.
  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVkBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to begin Vulkan command buffer");
    goto _catch;   
  }

  VkPipelineStageFlags vkSrcStage;
  VkPipelineStageFlags vkDstStage;

  // Template Vulkan source and destination access flags.
  VkAccessFlags vkSrcAccess;
  VkAccessFlags vkDstAccess;

  // Choose Vulkan access flags and pipeline stages.
  if(vkOldLayout == VK_IMAGE_LAYOUT_UNDEFINED && vkNewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    vkSrcAccess = 0;
    vkDstAccess = VK_ACCESS_TRANSFER_WRITE_BIT;

    vkSrcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    vkDstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  } else if(vkOldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && vkNewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    vkSrcAccess = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkDstAccess = VK_ACCESS_SHADER_READ_BIT;

    vkSrcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    vkDstStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  } else {
    result = XK_ERROR_UNKNOWN;
    xkLogError("unsupported Vulkan layout transition");
    goto _catch;
  }

  // Initialize Vulkan image memory barrier.
  const VkImageMemoryBarrier vkImageMemoryBarrier = {
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .pNext = VK_NULL_HANDLE,
    .srcAccessMask = vkSrcAccess,
    .dstAccessMask = vkDstAccess,
    .oldLayout = vkOldLayout,
    .newLayout = vkNewLayout,
    .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
    .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
    .image = vkImage,
    .subresourceRange = {
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .baseMipLevel = 0,
      .levelCount = mipLevels,
      .baseArrayLayer = 0,
      .layerCount = 1
    }
  };

  // Insert a Vulkan memory dependency.
  vkCmdPipelineBarrier(vkSingleCommandBuffer, vkSrcStage, vkDstStage, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &vkImageMemoryBarrier);

  // End Vulkan single command buffer.
  result = __xkVkEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to end Vulkan command buffer");
    goto _catch;   
  }

_catch:
  return(result);
}

XkResult __xkVkCopyBufferToImage(VkBuffer vkBuffer, VkImage vkImage, const VkExtent3D vkExtent) {
  XkResult result = XK_SUCCESS;

  // Begin Vulkan single command buffer.
  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVkBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to begin Vulkan command buffer");
    goto _catch;   
  }

  // Initialize Vulkan image copy info.
  const VkBufferImageCopy vkImageCopyInfo = {
    .bufferOffset         = 0,
    .bufferRowLength      = 0,
    .bufferImageHeight    = 0,
    .imageSubresource     = {
      .aspectMask       = VK_IMAGE_ASPECT_COLOR_BIT,
      .mipLevel         = 0,
      .baseArrayLayer   = 0,
      .layerCount       = 1
    },
    .imageOffset          = {0, 0, 0},
    .imageExtent          = vkExtent
  };

  // Copy Vulkan image.
  vkCmdCopyBufferToImage(vkSingleCommandBuffer, vkBuffer, vkImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vkImageCopyInfo);

  // End Vulkan single command buffer.
  result = __xkVkEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to end Vulkan command buffer");
    goto _catch;   
  }

_catch:
  return(result);
}
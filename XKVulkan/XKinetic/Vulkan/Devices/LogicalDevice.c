/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS DECLARATIONS SECTION ########## */
XkResult __xkVulkanCreateLogicalDevice() {
  XkResult result = XK_SUCCESS;

  float queuePriorities[1] = {1.0f};

  uint32_t queueCreateInfoCount = 0;

  VkDeviceQueueCreateInfo vkQueueCreateInfos[4] = {0};

  // Template Vulkan queue families.
  uint32_t graphicsQueueFamily = _xkVulkanContext.queueFamilyIndices.graphics;
  uint32_t presentQueueFamily = _xkVulkanContext.queueFamilyIndices.present;
  uint32_t transferQueueFamily = _xkVulkanContext.queueFamilyIndices.transfer;
  uint32_t computeQueueFamily = _xkVulkanContext.queueFamilyIndices.compute;

  if(_xkVulkanContext.queueFamilyIndices.supportedQueues & VK_QUEUE_GRAPHICS_BIT) {
		VkDeviceQueueCreateInfo vkGraphicsQueueCreateInfo = {0};
    vkGraphicsQueueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vkGraphicsQueueCreateInfo.pNext                   = VK_NULL_HANDLE;
    vkGraphicsQueueCreateInfo.flags                   = 0;
    vkGraphicsQueueCreateInfo.queueFamilyIndex        = graphicsQueueFamily;
    vkGraphicsQueueCreateInfo.queueCount              = 1;
    vkGraphicsQueueCreateInfo.pQueuePriorities        = queuePriorities;

		vkQueueCreateInfos[queueCreateInfoCount] = vkGraphicsQueueCreateInfo;

    ++queueCreateInfoCount;
	} else {
		graphicsQueueFamily = 0;
	}

  if(_xkVulkanContext.queueFamilyIndices.supportPresentQueue && presentQueueFamily != graphicsQueueFamily) {
		VkDeviceQueueCreateInfo vkPresentQueueCreateInfo = {0};
    vkPresentQueueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vkPresentQueueCreateInfo.pNext                   = VK_NULL_HANDLE;
    vkPresentQueueCreateInfo.flags                   = 0;
    vkPresentQueueCreateInfo.queueFamilyIndex        = presentQueueFamily;
    vkPresentQueueCreateInfo.queueCount              = 1;
    vkPresentQueueCreateInfo.pQueuePriorities        = queuePriorities;

		vkQueueCreateInfos[queueCreateInfoCount] = vkPresentQueueCreateInfo;

    ++queueCreateInfoCount;    
  } else {
 		presentQueueFamily = 0;   
  }

	if(_xkVulkanContext.queueFamilyIndices.supportedQueues & VK_QUEUE_TRANSFER_BIT && transferQueueFamily != graphicsQueueFamily && transferQueueFamily != presentQueueFamily) {
		VkDeviceQueueCreateInfo vkTransferQueueCreateInfo = {0};
    vkTransferQueueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vkTransferQueueCreateInfo.pNext                   = VK_NULL_HANDLE;
    vkTransferQueueCreateInfo.flags                   = 0;
    vkTransferQueueCreateInfo.queueFamilyIndex        = transferQueueFamily;
    vkTransferQueueCreateInfo.queueCount              = 1;
    vkTransferQueueCreateInfo.pQueuePriorities        = queuePriorities;

		vkQueueCreateInfos[queueCreateInfoCount] = vkTransferQueueCreateInfo;

    ++queueCreateInfoCount;
	} else {
		transferQueueFamily = graphicsQueueFamily;
	}

	if(_xkVulkanContext.queueFamilyIndices.supportedQueues & VK_QUEUE_COMPUTE_BIT && computeQueueFamily != graphicsQueueFamily && computeQueueFamily != presentQueueFamily && computeQueueFamily != transferQueueFamily) {
		VkDeviceQueueCreateInfo vkComputeQueueCreateInfo = {0};
    vkComputeQueueCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vkComputeQueueCreateInfo.pNext                   = VK_NULL_HANDLE;
    vkComputeQueueCreateInfo.flags                   = 0;
    vkComputeQueueCreateInfo.queueFamilyIndex        = computeQueueFamily;
    vkComputeQueueCreateInfo.queueCount              = 1;
    vkComputeQueueCreateInfo.pQueuePriorities        = queuePriorities;

		vkQueueCreateInfos[queueCreateInfoCount] = vkComputeQueueCreateInfo;

    ++queueCreateInfoCount;
	} else {
		computeQueueFamily = graphicsQueueFamily;
	}

  _xkVulkanContext.queueFamilyIndices.graphics = graphicsQueueFamily;
  _xkVulkanContext.queueFamilyIndices.present = presentQueueFamily;
  _xkVulkanContext.queueFamilyIndices.transfer = transferQueueFamily;
  _xkVulkanContext.queueFamilyIndices.compute = computeQueueFamily;

  VkPhysicalDeviceFeatures vkEnabledDeviceFeatures = {0};

	// Enable sample rate shading filtering if supported.
	if(_xkVulkanContext.vkDeviceFeatures.sampleRateShading) {
		vkEnabledDeviceFeatures.sampleRateShading = VK_TRUE;
  }

  // Fill mode non solid is required for wireframe display.
	if(_xkVulkanContext.vkDeviceFeatures.fillModeNonSolid) {
		vkEnabledDeviceFeatures.fillModeNonSolid = VK_TRUE;
  }

	// Wide lines must be present for line width > 1.0f.
	if(_xkVulkanContext.vkDeviceFeatures.wideLines) {
	  vkEnabledDeviceFeatures.wideLines = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support wireframe pipelines");
	}

  // Enable sample anisotropy if supported.
	if(_xkVulkanContext.vkDeviceFeatures.samplerAnisotropy) {
		vkEnabledDeviceFeatures.samplerAnisotropy = VK_TRUE;
  } else {
		xkLogWarning("Vulkan: Selected GPU does not support sampler anisotropy");
  }

  // Select texture compression.
	if (_xkVulkanContext.vkDeviceFeatures.textureCompressionBC) {
		vkEnabledDeviceFeatures.textureCompressionBC = VK_TRUE;
	} else if (_xkVulkanContext.vkDeviceFeatures.textureCompressionASTC_LDR) {
		vkEnabledDeviceFeatures.textureCompressionASTC_LDR = VK_TRUE;
	} else if (_xkVulkanContext.vkDeviceFeatures.textureCompressionETC2) {
		vkEnabledDeviceFeatures.textureCompressionETC2 = VK_TRUE;
  }

  // Enable vertex pipeline stores nad atomic.
	if (_xkVulkanContext.vkDeviceFeatures.vertexPipelineStoresAndAtomics) {
		vkEnabledDeviceFeatures.vertexPipelineStoresAndAtomics = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support vertex pipeline stores and atomics");
  }

  // Enable fragment stores nad atomic.
  if(_xkVulkanContext.vkDeviceFeatures.fragmentStoresAndAtomics) {
		vkEnabledDeviceFeatures.fragmentStoresAndAtomics = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support fragment stores and atomics");
  }

  // Enable shader storage extended formats.
	if(_xkVulkanContext.vkDeviceFeatures.shaderStorageImageExtendedFormats) {
		vkEnabledDeviceFeatures.shaderStorageImageExtendedFormats = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support shader storage extended formats");
  }

  // Enable shader storage write without format. 
	if(_xkVulkanContext.vkDeviceFeatures.shaderStorageImageWriteWithoutFormat) {
		vkEnabledDeviceFeatures.shaderStorageImageWriteWithoutFormat = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support shader storage write without format");
  }

  // Support geometry shaders.
	if(_xkVulkanContext.vkDeviceFeatures.geometryShader) {
		vkEnabledDeviceFeatures.geometryShader = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support geometry shaders");
  }

  // Support tessellation shaders.
	if(_xkVulkanContext.vkDeviceFeatures.tessellationShader) {
		vkEnabledDeviceFeatures.tessellationShader = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support tessellation shaders");
  }

  // Support multi viewports
	if(_xkVulkanContext.vkDeviceFeatures.multiViewport) {
		vkEnabledDeviceFeatures.multiViewport = VK_TRUE;
	} else {
		xkLogWarning("Vulkan: Selected GPU does not support multi viewports");
  }

  VkDeviceCreateInfo vkDeviceCreateInfo         = {0};
  vkDeviceCreateInfo.sType                      = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  vkDeviceCreateInfo.pNext                      = VK_NULL_HANDLE;
  vkDeviceCreateInfo.flags                      = 0;
  vkDeviceCreateInfo.queueCreateInfoCount       = queueCreateInfoCount;
  vkDeviceCreateInfo.pQueueCreateInfos          = vkQueueCreateInfos;
  vkDeviceCreateInfo.enabledLayerCount          = _xkVulkanInstanceLayerCount;
  vkDeviceCreateInfo.ppEnabledLayerNames        = _xkVulkanInstanceLayers;
  vkDeviceCreateInfo.enabledExtensionCount      = _xkVulkanDeviceExtensionCount;
  vkDeviceCreateInfo.ppEnabledExtensionNames    = _xkVulkanDeviceExtensions;
  vkDeviceCreateInfo.pEnabledFeatures           = &vkEnabledDeviceFeatures;

  VkResult vkResult = vkCreateDevice(_xkVulkanContext.vkPhysicalDevice, &vkDeviceCreateInfo, VK_NULL_HANDLE, &_xkVulkanContext.vkLogicalDevice);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to create logical device: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

  vkGetDeviceQueue(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.queueFamilyIndices.graphics, 0, &_xkVulkanContext.vkGraphicsQueue);
  vkGetDeviceQueue(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.queueFamilyIndices.present, 0, &_xkVulkanContext.vkPresentQueue);
  vkGetDeviceQueue(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.queueFamilyIndices.transfer, 0, &_xkVulkanContext.vkTransferQueue);
  vkGetDeviceQueue(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.queueFamilyIndices.compute, 0, &_xkVulkanContext.vkComputeQueue);

_catch:
  return(result);
}

void __xkVulkanDestroyLogicalDevice(void) {
  vkDeviceWaitIdle(_xkVulkanContext.vkLogicalDevice);

  if(_xkVulkanContext.vkLogicalDevice) {
    vkDestroyDevice(_xkVulkanContext.vkLogicalDevice, VK_NULL_HANDLE);

    _xkVulkanContext.vkLogicalDevice = VK_NULL_HANDLE;
  }
}

uint32_t __xkVulkanFindMemoryType(uint32_t typeFilter, const VkMemoryPropertyFlags vkRequiredProperties) {
	for(uint32_t i = 0; i < _xkVulkanContext.vkDeviceMemoryProperties.memoryTypeCount; i++) {
		uint32_t memoryTypeBits = 1 << i;

		if (typeFilter & memoryTypeBits && (_xkVulkanContext.vkDeviceMemoryProperties.memoryTypes[i].propertyFlags & vkRequiredProperties) == vkRequiredProperties) {
			return(i);
		}
	}

  return(0);
}

XkResult __xkVulkanBeginSingleCommands(VkCommandBuffer* pVkCommandBuffer) {
  xkAssert(pVkCommandBuffer);

  XkResult result = XK_SUCCESS;

  VkCommandBufferAllocateInfo vkCommandBufferAllocateInfo = {0};
  vkCommandBufferAllocateInfo.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  vkCommandBufferAllocateInfo.pNext                       = VK_NULL_HANDLE;
  vkCommandBufferAllocateInfo.commandPool                 = _xkVulkanContext.vkCommandPool;
  vkCommandBufferAllocateInfo.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  vkCommandBufferAllocateInfo.commandBufferCount          = 1;

  VkResult vkResult = vkAllocateCommandBuffers(_xkVulkanContext.vkLogicalDevice, &vkCommandBufferAllocateInfo, pVkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to allocate single command buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

  VkCommandBuffer vkCommandBuffer = *pVkCommandBuffer;

  VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {0};
  vkCommandBufferBeginInfo.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  vkCommandBufferBeginInfo.pNext                    = VK_NULL_HANDLE;
  vkCommandBufferBeginInfo.flags                    = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  vkCommandBufferBeginInfo.pInheritanceInfo         = VK_NULL_HANDLE;

  vkResult = vkBeginCommandBuffer(vkCommandBuffer, &vkCommandBufferBeginInfo);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to begin single command buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }  

_catch:
  return(result);
}

XkResult __xkVulkanEndSingleCommands(VkCommandBuffer vkCommandBuffer) {
  xkAssert(vkCommandBuffer);

  XkResult result = XK_SUCCESS;

  // End Vulkan command buffer.
  VkResult vkResult = vkEndCommandBuffer(vkCommandBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to end single command buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }  

  VkSubmitInfo vkSubmitInfo           = {0};
  vkSubmitInfo.sType                  = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  vkSubmitInfo.pNext                  = VK_NULL_HANDLE;
  vkSubmitInfo.waitSemaphoreCount     = 0;
  vkSubmitInfo.pWaitSemaphores        = VK_NULL_HANDLE;
  vkSubmitInfo.pWaitDstStageMask      = VK_NULL_HANDLE;
  vkSubmitInfo.commandBufferCount     = 1;
  vkSubmitInfo.pCommandBuffers        = &vkCommandBuffer;
  vkSubmitInfo.signalSemaphoreCount   = 0;
  vkSubmitInfo.pSignalSemaphores      = VK_NULL_HANDLE;

  vkResult = vkQueueSubmit(_xkVulkanContext.vkGraphicsQueue, 1, &vkSubmitInfo, VK_NULL_HANDLE);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to submit queue: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }  

  vkResult = vkQueueWaitIdle(_xkVulkanContext.vkGraphicsQueue);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to wait idle queue: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }  

  vkFreeCommandBuffers(_xkVulkanContext.vkLogicalDevice, _xkVulkanContext.vkCommandPool, 1, &vkCommandBuffer);

_catch:
  return(result);
}

XkResult __xkVulkanCopyBuffer(VkBuffer vkDstBuffer, const VkBuffer vkSrcBuffer, const VkDeviceSize vkSize) {
  xkAssert(vkDstBuffer);
  xkAssert(vkSrcBuffer);
  xkAssert(vkSize > 0);

  XkResult result = XK_SUCCESS;

  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVulkanBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

  VkBufferCopy vkBufferCopyInfo = {0};
  vkBufferCopyInfo.srcOffset    = 0;
  vkBufferCopyInfo.dstOffset    = 0;
  vkBufferCopyInfo.size         = vkSize;

  vkCmdCopyBuffer(vkSingleCommandBuffer, vkSrcBuffer, vkDstBuffer, 1, &vkBufferCopyInfo);

  result = __xkVulkanEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

_catch:
  return(result);
}

XkResult __xkVulkanMapBuffer(VkDeviceMemory vkBufferMemory, const VkDeviceSize vkDeviceSize, const void* data) {
  xkAssert(vkBufferMemory);
  xkAssert(vkSize > 0);
  xkAssert(data);

  XkResult result = XK_SUCCESS;

  void* mapped;
	VkResult vkResult = vkMapMemory(_xkVulkanContext.vkLogicalDevice, vkBufferMemory, 0, vkDeviceSize, 0, &mapped);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Failed to map buffer memory: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;   
  }

	xkCopyMemory((XkHandle)mapped, (XkHandle)data, (XkSize)vkDeviceSize);

	vkUnmapMemory(_xkVulkanContext.vkLogicalDevice, vkBufferMemory);

_catch:
  return(result);
}

XkResult __xkVulkanTransitionImageLayout(VkImage vkImage, const VkFormat vkFormat, const VkImageLayout vkOldLayout, const VkImageLayout vkNewLayout, const uint32_t mipLevels) {
  xkAssert(vkImage);

  XkResult result = XK_SUCCESS;

  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVulkanBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

  VkPipelineStageFlags vkSrcStage;
  VkPipelineStageFlags vkDstStage;

  VkImageMemoryBarrier vkImageMemoryBarrier                 = {0};
  vkImageMemoryBarrier.sType =                              VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  vkImageMemoryBarrier.pNext =                              VK_NULL_HANDLE;
  if(vkOldLayout == VK_IMAGE_LAYOUT_UNDEFINED && vkNewLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
    vkImageMemoryBarrier.srcAccessMask = 0;
    vkImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    vkSrcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    vkDstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  } else if(vkOldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && vkNewLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
    vkImageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkImageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    vkSrcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    vkDstStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  } else {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Vulkan: Unsupported layout transition");
    goto _catch;
  }
  vkImageMemoryBarrier.oldLayout =                          vkOldLayout,
  vkImageMemoryBarrier.newLayout =                          vkNewLayout;
  vkImageMemoryBarrier.srcQueueFamilyIndex =                VK_QUEUE_FAMILY_IGNORED;
  vkImageMemoryBarrier.dstQueueFamilyIndex =                VK_QUEUE_FAMILY_IGNORED;
  vkImageMemoryBarrier.image =                              vkImage;
  vkImageMemoryBarrier.subresourceRange.aspectMask =        VK_IMAGE_ASPECT_COLOR_BIT;
  vkImageMemoryBarrier.subresourceRange.baseMipLevel =      0;
  vkImageMemoryBarrier.subresourceRange.levelCount =        mipLevels;
  vkImageMemoryBarrier.subresourceRange.baseArrayLayer =    0;
  vkImageMemoryBarrier.subresourceRange.layerCount =        1;

  vkCmdPipelineBarrier(vkSingleCommandBuffer, vkSrcStage, vkDstStage, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &vkImageMemoryBarrier);

  result = __xkVulkanEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

_catch:
  return(result);
}

XkResult __xkVulkanCopyBufferToImage(VkBuffer vkBuffer, VkImage vkImage, const VkExtent3D vkExtent) {
  xkAssert(vkBuffer);
  xkAssert(vkImage);

  XkResult result = XK_SUCCESS;

  VkCommandBuffer vkSingleCommandBuffer;
  result = __xkVulkanBeginSingleCommands(&vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

  VkBufferImageCopy vkImageCopyInfo                 = {0};
  vkImageCopyInfo.bufferOffset                      = 0;
  vkImageCopyInfo.bufferRowLength                   = 0;
  vkImageCopyInfo.bufferImageHeight                 = 0;
  vkImageCopyInfo.imageSubresource.aspectMask       = VK_IMAGE_ASPECT_COLOR_BIT;
  vkImageCopyInfo.imageSubresource.mipLevel         = 0;
  vkImageCopyInfo.imageSubresource.baseArrayLayer   = 0;
  vkImageCopyInfo.imageSubresource.layerCount       = 1;
  vkImageCopyInfo.imageOffset.x                     = 0;
  vkImageCopyInfo.imageOffset.y                     = 0;
  vkImageCopyInfo.imageOffset.z                     = 0;
  vkImageCopyInfo.imageExtent                       = vkExtent;

  vkCmdCopyBufferToImage(vkSingleCommandBuffer, vkBuffer, vkImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vkImageCopyInfo);

  result = __xkVulkanEndSingleCommands(vkSingleCommandBuffer);
  if(result != XK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    goto _catch;   
  }

_catch:
  return(result);
}
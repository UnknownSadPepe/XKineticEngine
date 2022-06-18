#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateFrameBuffer(VkFramebuffer* pVkFrameBuffer, VkRenderPass vkRenderPass, const VkExtent2D vkExtent, VkImageView* vkAttachments, const uint32_t attachmentCount) {
  XkResult result = XK_SUCCESS;

  // Initialize Vulkan frame buffer create info.
  VkFramebufferCreateInfo vkFrameBufferCreateInfo = {0};
  vkFrameBufferCreateInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  vkFrameBufferCreateInfo.pNext                   = VK_NULL_HANDLE;
  vkFrameBufferCreateInfo.flags                   = 0;
  vkFrameBufferCreateInfo.renderPass              = vkRenderPass;
  vkFrameBufferCreateInfo.attachmentCount         = attachmentCount;
  vkFrameBufferCreateInfo.pAttachments            = vkAttachments;
  vkFrameBufferCreateInfo.width                   = vkExtent.width;
  vkFrameBufferCreateInfo.height                  = vkExtent.height;
  vkFrameBufferCreateInfo.layers                  = 1;

  // Create Vulkan frame buffer.
  VkResult vkResult = vkCreateFramebuffer(_xkVkContext.vkLogicalDevice, &vkFrameBufferCreateInfo, VK_NULL_HANDLE, pVkFrameBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan frame buffer: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroyFrameBuffer(VkFramebuffer vkFrameBuffer) {
  // Destroy Vulkan frame buffer.
  vkDestroyFramebuffer(_xkVkContext.vkLogicalDevice, vkFrameBuffer, VK_NULL_HANDLE);
}

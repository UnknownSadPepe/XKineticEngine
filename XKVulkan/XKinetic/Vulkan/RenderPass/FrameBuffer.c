/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateFrameBuffer(VkFramebuffer* pVkFrameBuffer, VkRenderPass vkRenderPass, const VkExtent2D vkExtent, VkImageView* vkAttachments, const uint32_t attachmentCount) {
  xkAssert(pVkFrameBuffer);
  xkAssert(vkRenderPass);
  xkAssert(vkAttachments);
  xkAssert(attachmentCount > 0);

  XkResult result = XK_SUCCESS;

  VkFramebufferCreateInfo vkFrameBufferCreateInfo = {};
  vkFrameBufferCreateInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  vkFrameBufferCreateInfo.pNext                   = VK_NULL_HANDLE;
  vkFrameBufferCreateInfo.flags                   = 0;
  vkFrameBufferCreateInfo.renderPass              = vkRenderPass;
  vkFrameBufferCreateInfo.attachmentCount         = attachmentCount;
  vkFrameBufferCreateInfo.pAttachments            = vkAttachments;
  vkFrameBufferCreateInfo.width                   = vkExtent.width;
  vkFrameBufferCreateInfo.height                  = vkExtent.height;
  vkFrameBufferCreateInfo.layers                  = 1;


  VkResult vkResult = vkCreateFramebuffer(_xkVulkanContext.vkLogicalDevice, &vkFrameBufferCreateInfo, VK_NULL_HANDLE, pVkFrameBuffer);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan frame buffer: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroyFrameBuffer(VkFramebuffer vkFrameBuffer) {
  xkAssert(vkFrameBuffer);

  vkDestroyFramebuffer(_xkVulkanContext.vkLogicalDevice, vkFrameBuffer, VK_NULL_HANDLE);
}

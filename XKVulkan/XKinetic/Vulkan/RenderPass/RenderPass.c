#include "XKinetic/Vulkan/Internal.h"

XkResult __xkVkCreateRenderPass(VkRenderPass* pVkRenderPass, VkAttachmentDescription* vkAttachments, const uint32_t attachmentCount, VkSubpassDescription* vkSubpasses, const uint32_t subpassCount, VkSubpassDependency* vkDependencies, const uint32_t dependencyCount) {
  XkResult result = XK_SUCCESS;

  // Initiaize Vulkan render pass create info.
  VkRenderPassCreateInfo vkRenderPassCreateInfo = {0};
  vkRenderPassCreateInfo.sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  vkRenderPassCreateInfo.pNext                  = VK_NULL_HANDLE;
  vkRenderPassCreateInfo.flags                  = 0;
	vkRenderPassCreateInfo.attachmentCount        = attachmentCount;
	vkRenderPassCreateInfo.pAttachments           = vkAttachments;
	vkRenderPassCreateInfo.subpassCount           = subpassCount;
	vkRenderPassCreateInfo.pSubpasses             = vkSubpasses;
	vkRenderPassCreateInfo.dependencyCount        = dependencyCount;
	vkRenderPassCreateInfo.pDependencies          = vkDependencies;
	
  // Create Vulkan render pass.
	VkResult vkResult = vkCreateRenderPass(_xkVkContext.vkLogicalDevice, &vkRenderPassCreateInfo, VK_NULL_HANDLE, pVkRenderPass);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan render pass: %s", __xkVkGetErrorString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVkDestroyeRenderPass(VkRenderPass vkRenderPass) {
  // Destroy Vulkan render pass.
  vkDestroyRenderPass(_xkVkContext.vkLogicalDevice, vkRenderPass, VK_NULL_HANDLE);
}

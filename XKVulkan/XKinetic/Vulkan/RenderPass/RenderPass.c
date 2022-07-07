/* ########## INCLUDE SECTION ########## */
#include "XKinetic/Vulkan/Internal.h"
#include "XKinetic/Core/Assert.h"

/* ########## FUNCTIONS SECTION ########## */
XkResult __xkVulkanCreateRenderPass(VkRenderPass* pVkRenderPass, VkAttachmentDescription* vkAttachments, const uint32_t attachmentCount, VkSubpassDescription* vkSubpasses, const uint32_t subpassCount, VkSubpassDependency* vkDependencies, const uint32_t dependencyCount) {
  xkAssert(pVkRenderPass);
  xkAssert(vkAttachments);
  xkAssert(attachmentCount > 0);
  xkAssert(vkSubpasses);
  xkAssert(subpassCount > 0);
  xkAssert(vkDependencies);
  xkAssert(dependencyCount > 0);

  XkResult result = XK_SUCCESS;

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
	
	VkResult vkResult = vkCreateRenderPass(_xkVulkanContext.vkLogicalDevice, &vkRenderPassCreateInfo, VK_NULL_HANDLE, pVkRenderPass);
  if(vkResult != VK_SUCCESS) {
    result = XK_ERROR_UNKNOWN;
    xkLogError("Failed to create Vulkan render pass: %s", __xkVulkanGetResultString(vkResult));
    goto _catch;
  }

_catch:
  return(result);
}

void __xkVulkanDestroyeRenderPass(VkRenderPass vkRenderPass) {
  xkAssert(vkRenderPass);
  
  vkDestroyRenderPass(_xkVulkanContext.vkLogicalDevice, vkRenderPass, VK_NULL_HANDLE);
}

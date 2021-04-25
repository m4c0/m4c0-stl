#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/safe_calls.hpp"
#include "m4c0/vulkan/surface_format.hpp"

#include <array>

using namespace m4c0::vulkan;

static constexpr auto create_color_attachment(VkFormat format) {
  VkAttachmentDescription res {};
  res.format = format;
  res.samples = VK_SAMPLE_COUNT_1_BIT;
  res.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  res.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  res.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  res.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  res.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  res.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
  return res;
}
static constexpr auto create_depth_attachment() {
  VkAttachmentDescription res {};
  res.format = VK_FORMAT_D32_SFLOAT;
  res.samples = VK_SAMPLE_COUNT_1_BIT;
  res.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  res.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  res.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  res.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  res.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  res.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  return res;
}

static constexpr auto create_color_attachment_ref() {
  VkAttachmentReference ref {};
  ref.attachment = 0;
  ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
  return ref;
}
static constexpr auto create_depth_attachment_ref() {
  VkAttachmentReference ref {};
  ref.attachment = 1;
  ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
  return ref;
}
static constexpr auto create_subpass(const VkAttachmentReference * color, const VkAttachmentReference * depth) {
  VkSubpassDescription subpass {};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = color;
  subpass.pDepthStencilAttachment = depth;
  return subpass;
}

static constexpr auto create_color_dependency() {
  VkSubpassDependency dep {};

  dep.srcSubpass = VK_SUBPASS_EXTERNAL;
  dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.srcAccessMask = 0;

  dep.dstSubpass = 0;
  dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  return dep;
}

static constexpr auto create_depth_dependency() {
  VkSubpassDependency dep {};

  dep.srcSubpass = VK_SUBPASS_EXTERNAL;
  dep.srcStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
  dep.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

  dep.dstSubpass = 0;
  dep.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
  dep.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

  return dep;
}

render_pass render_pass::create_with_opiniated_defaults_and_format(const surface_format * sfmt) {
  const auto attachments = std::array { create_color_attachment(sfmt->pointer()->format), create_depth_attachment() };

  const auto color_attachment_ref = create_color_attachment_ref();
  const auto depth_attachment_ref = create_depth_attachment_ref();
  const auto subpass = create_subpass(&color_attachment_ref, &depth_attachment_ref);

  const auto dependencies = std::array { create_color_dependency() };

  VkRenderPassCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  info.attachmentCount = attachments.size();
  info.pAttachments = attachments.data();
  info.subpassCount = 1;
  info.pSubpasses = &subpass;
  info.dependencyCount = dependencies.size();
  info.pDependencies = dependencies.data();
  return render_pass { details::safe_create_d<VkRenderPass>(vkCreateRenderPass, &info) };
}
render_pass render_pass::create_opiniated(const physical_device * pd, const surface * s) {
  auto sf = surface_format::best_from_device_and_surface(pd, s);
  return create_with_opiniated_defaults_and_format(&sf);
}

template<>
void details::base_handle<VkRenderPass_T>::reset() {
  safe_destroy_d(vkDestroyRenderPass, this);
}

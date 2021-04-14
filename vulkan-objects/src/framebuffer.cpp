#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/image_view.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "m4c0/vulkan/render_pass.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

using namespace m4c0::vulkan;

framebuffer framebuffer::builder::build() const {
  VkFramebufferCreateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  info.width = m_width;
  info.height = m_height;
  info.renderPass = m_render_pass->pointer();
  info.attachmentCount = m_attachments.size();
  info.pAttachments = m_attachments.data();
  info.layers = 1;
  return framebuffer { details::safe_create_d<VkFramebuffer>(vkCreateFramebuffer, &info) };
}

template<>
void details::handle<VkFramebuffer>::reset() {
  vkDestroyFramebuffer(loader::get_device(), pointer(), nullptr);
}

framebuffer::builder & framebuffer::builder::add_attachment(const image_view * iv) {
  m_attachments.push_back(iv->pointer());
  return *this;
}

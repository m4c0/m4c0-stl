#include "check.hpp"
#include "m4c0/vulkan/begin_render_pass.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/render_pass.hpp"

#include <array>

using namespace m4c0::vulkan::cmd;

void begin_render_pass::now() const {
  std::array<VkClearValue, 2> values {};
  values[0].color = { m_clear_color_r, m_clear_color_g, m_clear_color_b, m_clear_color_a };
  values[1].depthStencil = { m_clear_depth, m_clear_stencil };

  VkRenderPassBeginInfo info {};
  info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  info.renderPass = m_render_pass->pointer();
  info.framebuffer = m_framebuffer->pointer();
  info.renderArea.extent.width = m_width;
  info.renderArea.extent.height = m_height;
  info.clearValueCount = values.size();
  info.pClearValues = values.data();
  vkCmdBeginRenderPass(pointer(), &info, VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
}

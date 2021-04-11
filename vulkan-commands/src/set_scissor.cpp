#include "check.hpp"
#include "m4c0/vulkan/set_scissor.hpp"

void m4c0::vulkan::cmd::set_scissor::now() const {
  VkRect2D rect {};
  rect.extent = { m_width, m_height };
  vkCmdSetScissor(pointer(), 0, 1, &rect);
}

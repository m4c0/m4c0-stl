#include "check.hpp"
#include "m4c0/vulkan/set_viewport.hpp"

void m4c0::vulkan::cmd::set_viewport::now() const {
  VkViewport viewport {};
  viewport.width = m_width;
  viewport.height = m_height;
  viewport.maxDepth = 1;
  vkCmdSetViewport(pointer(), 0, 1, &viewport);
}

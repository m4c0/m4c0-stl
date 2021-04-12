#include "check.hpp"
#include "m4c0/vulkan/draw.hpp"

void m4c0::vulkan::cmd::draw::now() const {
  vkCmdDraw(pointer(), m_vtx_count, m_inst_count, m_vtx_first, m_inst_first);
}

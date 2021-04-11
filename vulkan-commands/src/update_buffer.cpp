#include "check.hpp"
#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/update_buffer.hpp"

void m4c0::vulkan::cmd::update_buffer::now() const {
  vkCmdUpdateBuffer(pointer(), m_buffer->pointer(), m_offset, m_data.size_bytes(), m_data.data());
}

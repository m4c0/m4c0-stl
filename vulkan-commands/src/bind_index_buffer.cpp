#include "check.hpp"
#include "m4c0/vulkan/bind_index_buffer.hpp"
#include "m4c0/vulkan/buffer.hpp"

void m4c0::vulkan::cmd::bind_index_buffer::now() const {
  vkCmdBindIndexBuffer(pointer(), m_buffer->pointer(), m_index, VK_INDEX_TYPE_UINT16);
}

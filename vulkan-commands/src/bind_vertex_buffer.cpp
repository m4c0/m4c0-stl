#include "check.hpp"
#include "m4c0/vulkan/bind_vertex_buffer.hpp"
#include "m4c0/vulkan/buffer.hpp"

void m4c0::vulkan::cmd::bind_vertex_buffer::now() const {
  VkBuffer buf = m_buffer->pointer();
  VkDeviceSize offs = m_offset;
  vkCmdBindVertexBuffers(pointer(), m_first_index, 1, &buf, &offs);
}

#include "m4c0/vulkan/bind_buffer_memory.hpp"
#include "m4c0/vulkan/buffer.hpp"
#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

void m4c0::vulkan::actions::bind_buffer_memory::now() const {
  details::safe_call_d(vkBindBufferMemory, m_buffer->pointer(), m_memory->pointer(), m_offset);
}

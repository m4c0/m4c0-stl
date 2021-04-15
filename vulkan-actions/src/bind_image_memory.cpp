#include "m4c0/vulkan/bind_image_memory.hpp"
#include "m4c0/vulkan/device_memory.hpp"
#include "m4c0/vulkan/image.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

void m4c0::vulkan::actions::bind_image_memory::now() const {
  details::safe_call_d(vkBindImageMemory, m_image->pointer(), m_memory->pointer(), m_offset);
}

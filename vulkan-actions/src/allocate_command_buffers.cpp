#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/command_pool.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

using namespace m4c0::vulkan::actions;

void allocate_command_buffers::as_primary_into(span_t s) const {
  VkCommandBufferAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.commandBufferCount = s.size();
  info.commandPool = m_pool->pointer();
  info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  details::safe_call_d(vkAllocateCommandBuffers, &info, s.data());
}
void allocate_command_buffers::as_secondary_into(span_t s) const {
  VkCommandBufferAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.commandBufferCount = s.size();
  info.commandPool = m_pool->pointer();
  info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;

  details::safe_call_d(vkAllocateCommandBuffers, &info, s.data());
}

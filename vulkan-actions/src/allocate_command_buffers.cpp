#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/command_pool.hpp"
#include "m4c0/vulkan/safe_calls.hpp"

using namespace m4c0::vulkan::actions;

std::vector<VkCommandBuffer> allocate_command_buffers::as_primary() const {
  std::vector<VkCommandBuffer> result;
  result.resize(m_size);

  VkCommandBufferAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.commandBufferCount = m_size;
  info.commandPool = m_pool->pointer();
  info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  details::safe_call_d(vkAllocateCommandBuffers, &info, result.data());
  return result;
}
std::vector<VkCommandBuffer> allocate_command_buffers::as_secondary() const {
  std::vector<VkCommandBuffer> result;
  result.resize(m_size);

  VkCommandBufferAllocateInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  info.commandBufferCount = m_size;
  info.commandPool = m_pool->pointer();
  info.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;

  details::safe_call_d(vkAllocateCommandBuffers, &info, result.data());
  return result;
}

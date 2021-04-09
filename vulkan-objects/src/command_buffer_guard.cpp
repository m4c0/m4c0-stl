#include "m4c0/vulkan/command_buffer.hpp"
#include "m4c0/vulkan/command_buffer_guard.hpp"
#include "m4c0/vulkan/loader.hpp"
#include "safe_calls.hpp"

using namespace m4c0::vulkan;

command_buffer_guard command_buffer_guard::begin_one_time_submit(const command_buffer * cb) {
  VkCommandBufferBeginInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  details::safe_call(vkBeginCommandBuffer, cb->pointer(), &info);
  return command_buffer_guard { cb };
}
command_buffer_guard::~command_buffer_guard() {
  details::safe_call(vkEndCommandBuffer, m_cmd_buf->pointer());
}

#include "check.hpp"
#include "m4c0/vulkan/begin_one_time_submit.hpp"

using namespace m4c0::vulkan::cmd;

void begin_one_time_submit::now() const {
  VkCommandBufferBeginInfo info {};
  info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  check(vkBeginCommandBuffer(pointer(), &info));
}

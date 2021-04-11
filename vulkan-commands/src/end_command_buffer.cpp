#include "check.hpp"
#include "m4c0/vulkan/end_command_buffer.hpp"

using namespace m4c0::vulkan::cmd;

void command_buffer::end() const {
  vkEndCommandBuffer(pointer());
}

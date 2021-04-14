#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/device_wait_idle.hpp"
#include "m4c0/vulkan/queue_present.hpp"

int main() {
  m4c0::vulkan::actions::device_wait_idle();

  m4c0::vulkan::command_pool * cp {};
  auto cbs = m4c0::vulkan::actions::allocate_command_buffers().with_command_pool(cp).with_size(3).as_primary();

  m4c0::vulkan::actions::queue_present().now();
}

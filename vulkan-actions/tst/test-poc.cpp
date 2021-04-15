#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/allocate_descriptor_sets.hpp"
#include "m4c0/vulkan/bind_buffer_memory.hpp"
#include "m4c0/vulkan/bind_image_memory.hpp"
#include "m4c0/vulkan/device_wait_idle.hpp"
#include "m4c0/vulkan/queue_present.hpp"
#include "m4c0/vulkan/update_descriptor_sets.hpp"

int main() {
  m4c0::vulkan::actions::device_wait_idle();

  m4c0::vulkan::command_pool * cp {};
  auto cbs = m4c0::vulkan::actions::allocate_command_buffers().with_command_pool(cp).with_size(3).as_primary();

  auto * ds = m4c0::vulkan::actions::allocate_descriptor_sets().now();

  m4c0::vulkan::actions::bind_image_memory().now();
  m4c0::vulkan::actions::bind_buffer_memory().now();

  m4c0::vulkan::actions::write_image_to_descriptor_set()
      .with_destination_set(ds)
      .with_binding(0)
      .with_image_view(nullptr)
      .with_sampler(nullptr)
      .now();

  m4c0::vulkan::actions::queue_present().now();
}

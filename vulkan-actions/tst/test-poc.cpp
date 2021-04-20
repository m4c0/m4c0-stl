#include "m4c0/vulkan/allocate_command_buffers.hpp"
#include "m4c0/vulkan/allocate_descriptor_sets.hpp"
#include "m4c0/vulkan/bind_buffer_memory.hpp"
#include "m4c0/vulkan/bind_image_memory.hpp"
#include "m4c0/vulkan/device_wait_idle.hpp"
#include "m4c0/vulkan/queue_present.hpp"
#include "m4c0/vulkan/queue_submit.hpp"
#include "m4c0/vulkan/update_descriptor_sets.hpp"

// TODO: improve these with a more realistic example
int main() {
  m4c0::vulkan::actions::device_wait_idle();

  m4c0::vulkan::command_pool * cp {};
  std::array<VkCommandBuffer, 3> cbs {};
  m4c0::vulkan::actions::allocate_command_buffers().with_command_pool(cp).as_primary_into(cbs);

  auto * ds = m4c0::vulkan::actions::allocate_descriptor_sets().now();

  m4c0::vulkan::actions::bind_image_memory().now();
  m4c0::vulkan::actions::bind_buffer_memory().now();

  m4c0::vulkan::actions::write_image_to_descriptor_set()
      .with_destination_set(ds)
      .with_binding(0)
      .with_image_view(nullptr)
      .with_sampler(nullptr)
      .now();

  m4c0::vulkan::actions::queue_submit().now();
  m4c0::vulkan::actions::queue_present().now();
}

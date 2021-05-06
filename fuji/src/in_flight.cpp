#include "m4c0/fuji/in_flight.hpp"
#include "m4c0/vulkan/queue_submit.hpp"

using namespace m4c0::fuji;

void in_flight::queue_submit(const vulkan::queue * queue, VkCommandBuffer cmd_buf) const {
  m4c0::vulkan::actions::queue_submit()
      .with_queue(queue)
      .with_command_buffer(cmd_buf)
      .with_fence(fence())
      .with_wait_semaphore(image_available_semaphore())
      .with_signal_semaphore(render_finished_semaphore())
      .now();
}

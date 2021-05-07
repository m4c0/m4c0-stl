#include "m4c0/fuji/depth_buffer.hpp"
#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/fuji/semaphores.hpp"
#include "m4c0/fuji/swapchain_context.hpp"
#include "m4c0/vulkan/queue_present.hpp"

using namespace m4c0::fuji;

swapchain_context::swapchain_context(const device_context * ld)
  : m_render_extent(ld->best_surface_capabilities().current_extent())
  , m_swapchain(ld->best_swapchain_with_size(m_render_extent))
  , m_depth_buffer(ld, m_render_extent)
  , m_present_q { ld->unified_queue() } {
}

unsigned swapchain_context::acquire_next_frame(const image_available_semaphore * s) const {
  return m_swapchain.acquire_next_image(s);
}

void swapchain_context::present(unsigned idx, const render_finished_semaphore * rfs) const {
  m4c0::vulkan::actions::queue_present()
      .with_present_queue(m_present_q)
      .with_image_index(idx)
      .with_swapchain(&m_swapchain)
      .with_wait_semaphore(rfs)
      .now();
}

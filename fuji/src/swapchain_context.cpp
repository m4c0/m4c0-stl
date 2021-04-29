#include "m4c0/fuji/depth_buffer.hpp"
#include "m4c0/fuji/device_context.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/fuji/semaphores.hpp"
#include "m4c0/fuji/swapchain_context.hpp"
#include "m4c0/vulkan/queue_present.hpp"

using namespace m4c0::fuji;

swapchain_context::swapchain_context(const device_context * ld, vulkan::extent_2d window_extent)
  : m_render_extent(ld->best_surface_capabilities().normalize_extent(window_extent))
  , m_swapchain(ld->best_swapchain_with_size(m_render_extent))
  , m_depth_buffer(ld, m_render_extent)
  , m_present_q { ld->unified_queue() } {
  int i = 0;
  for (auto * img : m_swapchain.get_images()) {
    m_frames.emplace_back(ld, m_render_extent, img, m_depth_buffer.image_view(), i++);
  }
}

const frame_context * swapchain_context::acquire_next_frame(const image_available_semaphore * s) const {
  auto img = m_swapchain.acquire_next_image(s);
  return &m_frames[img];
}

void swapchain_context::present(unsigned idx, const render_finished_semaphore * rfs) const {
  m4c0::vulkan::actions::queue_present()
      .with_present_queue(m_present_q)
      .with_image_index(idx)
      .with_swapchain(&m_swapchain)
      .with_wait_semaphore(rfs)
      .now();
}

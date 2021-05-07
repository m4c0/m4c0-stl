#pragma once

#include "m4c0/fuji/depth_buffer.hpp"
#include "m4c0/fuji/frame_context.hpp"
#include "m4c0/vulkan/extent_2d.hpp"
#include "m4c0/vulkan/swapchain.hpp"

namespace m4c0::vulkan {
  class queue;
}

namespace m4c0::fuji {
  class device_context;
  class image_available_semaphore;
  class render_finished_semaphore;

  class swapchain_context {
    vulkan::extent_2d m_render_extent;
    vulkan::swapchain m_swapchain;
    depth_buffer m_depth_buffer;
    const vulkan::queue * m_present_q {};

    std::vector<frame_context> m_frames;

  public:
    explicit swapchain_context(const device_context * ld);

    [[nodiscard]] const frame_context * acquire_next_frame(const image_available_semaphore * ias) const;

    void present(unsigned idx, const render_finished_semaphore * rfs) const;

    [[nodiscard]] auto images() const noexcept {
      return m_swapchain.get_images();
    }

    [[nodiscard]] constexpr const auto * depth_buffer() const noexcept {
      return &m_depth_buffer;
    }
    [[nodiscard]] constexpr auto render_extent() const noexcept {
      return m_render_extent;
    }
  };
}

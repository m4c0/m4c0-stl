#pragma once

#include "m4c0/vulkan/command_buffer_list.hpp"
#include "m4c0/vulkan/extent_2d.hpp"
#include "m4c0/vulkan/framebuffer.hpp"
#include "m4c0/vulkan/image_view.hpp"

namespace m4c0::fuji {
  class device_context;

  class frame_context {
    vulkan::image_view m_image_view {};
    vulkan::tools::primary_command_buffer_list<1> m_command_pool;
    vulkan::framebuffer m_framebuffer;
    unsigned m_index;

  public:
    using image_t = vulkan::details::pointer_t<VkImage_T>;
    frame_context(
        const device_context * ld,
        vulkan::extent_2d re,
        image_t image,
        const vulkan::image_view * depth_buffer,
        unsigned index);

    [[nodiscard]] constexpr auto index() const noexcept {
      return m_index;
    }

    [[nodiscard]] auto begin_primary_command_buffer() const noexcept {
      return m_command_pool.begin(0);
    }
    [[nodiscard]] auto * framebuffer() const noexcept {
      return &m_framebuffer;
    }
  };
}

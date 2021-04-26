#pragma once

#include "m4c0/vulkan/begin_render_pass.hpp"
#include "m4c0/vulkan/end_render_pass.hpp"
#include "m4c0/vulkan/extent_2d.hpp"

namespace m4c0::vulkan::tools {
  class render_pass_guard {
    m4c0::vulkan::cmd::end_render_pass m_end;

  public:
    render_pass_guard(
        VkCommandBuffer cb,
        const m4c0::vulkan::framebuffer * fb,
        const m4c0::vulkan::render_pass * rp,
        const m4c0::vulkan::extent_2d extent)
      : m_end(cb) {
      // The intent of a magenta clear color is to be a visible marker in case you forget to render a pixel.
      m4c0::vulkan::cmd::begin_render_pass(cb)
          .with_extent(extent)
          .with_framebuffer(fb)
          .with_render_pass(rp)
          .with_clear_color(1, 0, 1, 1)
          .now();
    }

    ~render_pass_guard() {
      m_end.now();
    }

    render_pass_guard(const render_pass_guard & o) = delete;
    render_pass_guard(render_pass_guard && o) = delete;
    render_pass_guard & operator=(const render_pass_guard & o) = delete;
    render_pass_guard & operator=(render_pass_guard && o) = delete;
  };
}
